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
    parent::__construct();
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
      'CBA' => t('CBA'),
      'CHI' => t('CHI'),
      'CES' => t('CES'),
      'CHL' => t('CHL'),
      'CHO' => t('CHO'),
      'CAS' => t('CAS'),
      'CCS' => t('CCS'),
      'CLS' => t('CLS'),
      'CLA' => t('CLA'),
      'CNU' => t('CNU'),
      'CPP' => t('CPP'),
      'CSS' => t('CSS'),
      'CTE' => t('CTE'),
      'CTS' => t('CTS'),
    );

    // Available campus codes for importing
    $campus_options = array(
      'DTPHX' => t('DTPHX'),
      'EAC' => t('EAC'),
      'CALHC' => t('CALHC'),
      'ONLNE' => t('ONLNE'),
      'POLY' => t('POLY'),
      'TEMPE' => t('TEMPE'),
      'WEST' => t('WEST'),
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
      '#description' => t('Name of service to call. For example, use \'Import by college\' to utilize findDegreeByCollegeAndProgram
        and \'Import by campus\' to utilize findDegreeByCampusMapArray. A list of available college and campus codes is located
        at https://webspark.asu.edu/features/asu-degrees-feed.'),
    );

    //Chizuko added the following for eAdvisor Degree Feed:
    $form['unit_identifier'] = array(
      '#type' => 'select',
      '#title' => t('Unit Identifier'),
      '#options' => $unit_options,
      '#default_value' => isset($source_config['unit_identifier']) ? $source_config['unit_identifier'] : '',
      '#description' => t('Identifer for unit (college or campus).
        For example, use \'CALHC\' for ASU Colleges at Lake Havasu City or \'CLA\' for College of Liberal Arts and Sciences.
        College codes are compatible solely with the \'Import by college\' option and campus codes are compatible solely with
        the \'Import by campus\' option.'),
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
