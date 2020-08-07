<?php

/**
 * Fetches feeds using IXR XML-RPC library
 * @todo Provide mechanism to pass arguments through to service.
 */
//class IXRFeedsBatch extends FeedsImportBatch {
class ASUeAdvisorFeedsFetcherResult extends FeedsFetcherResult {
  protected $domain;
  protected $path;
  protected $service;
  // Chizuko added the following for eAdvisor Degree Feed:
  protected $unit_identifier;
  protected $program;
  protected $cert;

  public function __construct($protocol, $url, $path, $service, $unit_identifier, $program, $cert) {
    $this->protocol = $protocol;
    $this->url = $url;
    $this->path = $path;
    $this->service = $service;
    $this->unit_identifier = strtoupper($unit_identifier);
    $this->program = $program;
    $this->cert = (boolean) $cert;
    parent::__construct(NULL);
  }

  // We need get methods. So, we can use $program and $cert in ASUeAdvisorTransferFeedParser.inc.
  public function getProgram() {
    return $this->program;
  }
  public function getCert() {
    return $this->cert;
  }

  public function getRaw() {
    if ($this->protocol == 'http') {
      $client = ixr_create_client($this->url, $this->path);
    }
    if ($this->protocol == 'https') {
      $client = ixr_create_clientssl($this->url, $this->path);
    }

    // TODO obtain Example Careers data in here?

    if ($this->service) {

      // This 'if' has been added for eAdvisor Degree Feed in order to be able to pass parameters with eAdvisorDSFind.findDegreeByCollegeAndProgram web service method. When $this->service (web service method) is not eAdvisorDSFind.findDegreeByCollegeAndProgram, then, 'else' will be exacuted. So, when we have $this->service == "eAdvisorDSFind.findDegreeWithTransferAgreementsMapArray" for transfer.asu.edu, then, 'else' will be executed.
      if ($this->service == "eAdvisorDSFind.findDegreeByCollegeAndProgram") {
        if ($this->program == "graduate") {
          $this->cert = false;
        }
        $client->query($this->service, $this->unit_identifier, $this->program, $this->cert); //For example, $client->query($this->service, "CLA", "undergrad", false);
      } elseif ($this->service == "eAdvisorDSFind.findDegreeByCampusMapArray") {
        if ($this->program == "graduate") {
          $this->cert = false;
        }
        $client->query($this->service, $this->unit_identifier, $this->program, $this->cert);
      } else {
        $client->query($this->service);
      }
      $response = $client->getResponse();

      //watchdog('asu debug', var_export($response, 1));

      return $response ? $response : array();
    }
  }
}

class ASUeAdvisorFeedsFetcher extends FeedsFetcher {
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    return new ASUeAdvisorFeedsFetcherResult($source_config['protocol'], $source_config['server'], $source_config['path'], $source_config['service'], $source_config['unit_identifier'], $source_config['program'], $source_config['cert']);
  }

  public function sourceForm($source_config) {

    // Available college codes for importing
    $college_options = array(
      'CHO' => t('Barrett, The Honors College'),
      'CHL' => t('College of Health Solutions'),
      'CLS' => t('College of Letters & Sciences'),
      'CLA' => t('College of Liberal Arts & Sciences'),
      'CNU' => t('College of Nursing & Health Innovation'),
      'CPP' => t('College of Public Programs'),
      'CTS' => t('College of Technology & Innovation'),
      'CHI' => t('Herberger Institute for Design & the Arts'),
      'CES' => t('Ira A. Fulton Schools of Engineering'),
      'CTE' => t('Mary Lou Fulton Teachers College'),
      'CAS' => t('New College of Interdisciplinary Arts & Sciences'),
      'CSS' => t('School of Sustainability'),
      'CBA' => t('W. P. Carey School of Business'),
      'CCS' => t('Walter Cronkite School of Journalism & Mass Communication'),
    );

    // Available campus codes for importing
    $campus_options = array(
      'ONLNE' => t('ASU Online'),
      'EAC' => t('ASU@TheGilaValley'),
      'CAC' => t('ASU@Pinal'),
      'TUCSN' => t('ASU@Tucson'),
      'AWC' => t('ASU@Yuma'),
      'CALHC' => t('Colleges at Lake Havasu City'),
      'DTPHX' => t('Downtown Phoenix campus'),
      'POLY' => t('Polytechnic campus'),
      'TEMPE' => t('Tempe campus'),
      'WEST' => t('West campus'),
    );

    $unit_options = array_merge($college_options, $campus_options);

    $form = array();
    $form['protocol'] = array(
      '#type' => 'select',
      '#title' => t('Protocol'),
      '#options' => array(
        'http' => t('HTTP'),
        'https' => t('HTTPS (SSL)'),
      ),
      '#default_value' => 'https',
    );
    $form['server'] = array(
      '#type' => 'textfield',
      '#title' => t('Server name'),
      '#description' => t('Domain name of the XML-RPC server, i.e. webapp4-dev.asu.edu'),
      '#default_value' => 'webapp4.asu.edu',
    );
    $form['path'] = array(
      '#type' => 'textfield',
      '#title' => t('Path'),
      '#description' => t('Path to XML-RPC service on server.'),
      '#default_value' => '/programs/XmlRpcServer',
    );
    $form['service'] = array(
      '#type' => 'select',
      '#title' => t('Service'),
      '#options' => array(
        'eAdvisorDSFind.findDegreeByCollegeAndProgram' => t('Import by college'),
        'eAdvisorDSFind.findDegreeByCampusMapArray' => t('Import by campus'),
      ),
      '#default_value' => isset($source_config['service']) ? $source_config['service'] : '',
      '#description' => t('Name of service to call.
        For example, use \'Import by college\' to utilize findDegreeByCollegeAndProgram
        and \'Import by campus\' to utilize findDegreeByCampusMapArray. If you do not
        see the college or campus you are looking for, please contact webconsulting@asu.edu.'),
    );

    //Chizuko added the following for eAdvisor Degree Feed:
    $form['unit_identifier'] = array(
      '#type' => 'select',
      '#title' => t('Unit Identifier'),
      '#options' => $unit_options,
      '#default_value' => isset($source_config['unit_identifier']) ? $source_config['unit_identifier'] : '',
      '#description' => t('Identifer for unit (college or campus).
        Colleges are compatible solely with the \'Import by college\' option and campuses are
        compatible solely with the \'Import by campus\' option.'),
    );
    $form['program'] = array(
      '#type' => 'select',
      '#title' => t('Program'),
      '#options' => array(
        'undergrad' => t('Undergraduate'),
        'graduate' => t('Graduate'),
      ),
      '#default_value' => isset($source_config['program']) ? $source_config['program'] : '',
    );
    $form['cert'] = array(
      '#type' => 'select',
      '#title' => t('Certificate'),
      '#description' => t('When the intended program is undergraduate, selecting \'True\' will result in
        Undergraduate Minors & Certificates, while selecting \'False\' will result in Undergraduate Majors.
        When the selected program is graduate, this T/F choice is ignored, and either selection will result in
        Graduate Majors, Minors & Certificates.'),
      '#options' => array(
        0 => t('False'),
        1 => t('True'),
      ),
      '#default_value' => isset($source_config['cert']) ? $source_config['cert'] : '',
    );
    return $form;
  }


}
