<?php

/**
 * Fetches feeds using IXR XML-RPC library
 * @todo Provide mechanism to pass arguments through to service.
 */
class ASUeAdvisorFeedFetcherResult extends FeedsFetcherResult {

  // Parameters
  protected $domain;
  protected $path;
  protected $service;
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

  // GET methods to use $program and $cert in asu_programs_feed_parser.inc
  public function getProgram() {
    return $this->program;
  }
  public function getCert() {
    return $this->cert;
  }

  public function getRaw() {
    if ($this->protocol == 'http') {
      $client = asu_ixr_create_client($this->url, $this->path);
    }
    if ($this->protocol == 'https') {
      $client = asu_ixr_create_clientssl($this->url, $this->path);
    }

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

class ASUeAdvisorFeedFetcher extends FeedsFetcher {
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);

    $protocol_config = 'https';
    $server_config = 'webapp4.asu.edu';
    $path_config = '/programs/XmlRpcServer';
    $cert_choice = 0;

    if ($source_config['program'] == 'undergrad_mc') {
      $cert_choice = 1;
      $source_config['program'] = 'undergrad';
    } elseif ($source_config['program'] == 'undergrad') {
      $cert_choice = 0;
    } elseif ($source_config['program'] == 'graduate') {
      $cert_choice = 0;
    }

    if ($source_config['unit_filter'] != '') {
      $unit_filter_var = $source_config['unit_filter'];
      variable_set('unit_filter', $unit_filter_var);
    } else {
      variable_set('unit_filter', '');
    }

    return new ASUeAdvisorFeedFetcherResult($protocol_config, $server_config, $path_config, $source_config['service'], $source_config['unit_identifier'], $source_config['program'], $cert_choice);
  }

  public function sourceForm($source_config) {

    // Available college codes for importing
    $unit_options2 = array(
      'CHO' => t('Barrett, The Honors College'),
      'CHL' => t('College of Health Solutions'),
      'CLS' => t('College of Integrative Sciences & Arts'),
      'CLA' => t('College of Liberal Arts & Sciences'),
      'CNU' => t('College of Nursing & Health Innovation'),
      'CPP' => t('College of Public Services & Community Solutions'),
      'CTS' => t('College of Technology & Innovation'),
      'CHI' => t('Herberger Institute for Design & the Arts'),
      'CES' => t('Ira A. Fulton Schools of Engineering'),
      'CTE' => t('Mary Lou Fulton Teachers College'),
      'CAS' => t('New College of Interdisciplinary Arts & Sciences'),
      'CLW' => t('Sandra Day O\'Connor College of Law'),
      'CFI' => t('School for the Future of Innovation in Society'),
      'CSS' => t('School of Sustainability'),
      'CTB' => t('Thunderbird School of Global Management'),
      'CBA' => t('W. P. Carey School of Business'),
      'CCS' => t('Walter Cronkite School of Journalism & Mass Communication'),
    );

    // Available campus codes for importing
    $campus_options = array(
      'ONLNE' => t('ASU Online'),
      'COCHS' => t('ASU@Cochise'),
      'LOSAN' => t('ASU@Los Angeles'),
      'NEAZ' => t('ASU@Northeastern Arizona'),
      'PIMA' => t('ASU@Pima'),
      'CAC' => t('ASU@Pinal'),
      'EAC' => t('ASU@TheGilaValley'),
      'TUCSN' => t('ASU@Tucson'),
      'YAVAP' => t('ASU@Yavapai'),
      'AWC' => t('ASU@Yuma'),
      'CALHC' => t('Colleges at Lake Havasu City'),
      'DTPHX' => t('Downtown Phoenix campus'),
      'POLY' => t('Polytechnic campus'),
      'TEMPE' => t('Tempe campus'),
      'TBIRD' => t('Thunderbird campus'),
      'WEST' => t('West campus'),
    );

    $unit_options = array_merge($unit_options2, $campus_options);

    // Program importer form
    $form = array();
    $form['service'] = array(
      '#type' => 'select',
      '#title' => t('Service'),
      '#options' => array(
        'eAdvisorDSFind.findDegreeByCollegeAndProgram' => t('Import by academic unit'),
        'eAdvisorDSFind.findDegreeByCampusMapArray' => t('Import by entire campus'),
      ),
      '#default_value' => isset($source_config['service']) ? $source_config['service'] : '',
      '#description' => t('Name of service to call. Import by academic unit or campus.'),
    );
    $form['unit_identifier'] = array(
      '#type' => 'select',
      '#title' => t('Identifier'),
      '#options' => $unit_options,
      '#default_value' => isset($source_config['unit_identifier']) ? $source_config['unit_identifier'] : '',
      '#description' => t('Identifer for importing; academic unit or campus. If you do not see the academic unit or campus you are looking for, please contact webconsulting@asu.edu.'),
    );
    $form['unit_filter'] = array(
  		'#type' => 'textfield',
  		'#title' => t('Subunit name'),
  		'#default_value' => isset($source_config['unit_filter']) ? $source_config['unit_filter'] : '',
  		'#size' => 30,
  		'#maxlength' => 256,
  		'#description' => t('The department name will be used as a filter when importing ASU Academic Programs nodes. Thus, only nodes with this department name will be imported.'),
  		'#required' => FALSE,
  	);
    $form['program'] = array(
      '#type' => 'select',
      '#title' => t('Program'),
      '#options' => array(
        'undergrad' => t('Undergraduate Programs'),
        'undergrad_mc' => t('Undergraduate - Minors & Certificates'),
        'graduate' => t('Graduate Programs & Certificates'),
      ),
      '#default_value' => isset($source_config['program']) ? $source_config['program'] : '',
    );
    return $form;
  }


}
