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
  protected $college_code;
  protected $program;
  protected $cert;

  public function __construct($protocol, $url, $path, $service, $college_code, $program, $cert) {
    $this->protocol = $protocol;
    $this->url = $url;
    $this->path = $path;
    $this->service = $service;
    $this->college_code = strtoupper($college_code);
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
        $client->query($this->service, $this->college_code, $this->program, $this->cert); //For example, $client->query($this->service, "CLA", "undergrad", false);
      }
      else {
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
    return new ASUeAdvisorFeedsFetcherResult($source_config['protocol'], $source_config['server'], $source_config['path'], $source_config['service'], $source_config['college_code'], $source_config['program'], $source_config['cert']);
  }

  public function sourceForm($source_config) {
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
      '#type' => 'textfield',
      '#title' => t('Service'),
      '#description' => t('Name of service to call. For example, eAdvisorDSFind.findDegreeByCollegeAndProgram'),
      '#default_value' => 'eAdvisorDSFind.findDegreeByCollegeAndProgram',
    );

    //Chizuko added the following for eAdvisor Degree Feed:
    $form['college_code'] = array(
      '#type' => 'textfield',
      '#title' => t('College code'),
      '#description' => t('Code for college. For example, CLA for College of Liberal Arts and Sciences.'),
      '#default_value' => isset($source_config['college_code']) ? $source_config['college_code'] : '',
    );
    $form['program'] = array(
      '#type' => 'select',
      '#title' => t('Program'),
      '#options' => array(
        'undergrad' => t('Undergrad'),
        'graduate' => t('Graduate'),
      ),
      '#default_value' => isset($source_config['program']) ? $source_config['program'] : '',
    );
    $form['cert'] = array(
      '#type' => 'select',
      '#title' => t('Certificate'),
      '#description' => t('True for Undergraduate Minors and Certificates, false for
Undergraduate Majors and Graduate Majors, Certificates and Minors. If you chose Graduate program, then, this option would be ignored and False would be used.'),
      '#options' => array(
        '1' => t('True'),
        '0' => t('False'),
      ),
      '#default_value' => isset($source_config['cert']) ? $source_config['cert'] : '',
    );
    return $form;
  }


}
