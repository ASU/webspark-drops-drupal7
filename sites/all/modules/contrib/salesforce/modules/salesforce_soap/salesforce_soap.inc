<?php

/**
 * @file
 * Contains SalesforceSoapPartner.
 */

/**
 * Expose the partner SOAP API by extending SforcePartnerClient and configuring
 * it with the OAUTH credentials and endpoints from the Salesforce API class.
 */
class SalesforceSoapPartner extends SforcePartnerClient {
  protected $salesforceApi;
  protected $isConnected;

  /**
   * Constructor for SalesforceSoapPartner.
   *
   * @param Salesforce $sfapi
   *   Salesforce API object
   * @param string $wsdl
   *   WSDL provided by Salesforce account.  One will be created if not
   *   explicitly provided.
   */
  public function __construct(Salesforce $sfapi, $wsdl = NULL) {
    parent::__construct();
    if (empty($wsdl)) {
      $wsdl = libraries_get_path('salesforce') . '/soapclient/partner.wsdl.xml';
    }
    $this->setConnected(FALSE);
    $this->createConnection($wsdl);
    $this->salesforceApi = $sfapi;

    // We have to run a test API call here every time a new instance is
    // created for a couple of reasons. These reasons are explained below.
    //
    //   - The Salesforce instance may very well be authorized, which means
    //     it has a consumer key, secret and refresh token. However, merely
    //     checking for authorization does not deal with expired access tokens.
    //     If we were to pass an expired access token to the SOAP client it
    //     will cheerfully throw INVALID_SESSION_ID exceptions. This situation
    //     can arise if a client goes to use the SOAP api before interacting
    //     with the REST api.
    //
    //   - We also need to account for cases where there is no access token.
    //     This can manifest itself during cron runs where cron is running as
    //     an anonymous user that has yet to establish a session. In this
    //     scenario the Salesforce instance is authorized, but doesn't have an
    //     access token yet. If you pass an empty access token to
    //     setSessionHeader the SOAP API will throw a fatal PHP error when it
    //     attempts to set it's own internal SOAP headers via
    //     __setSoapHeaders().
    if ($this->salesforceApi->isAuthorized()) {
      // Run an API call for the reasons discussed above.
      $this->salesforceApi->apiCall('');
      $this->setSessionHeader($this->salesforceApi->getAccessToken());
      $this->setEndPoint($this->salesforceApi->getApiEndPoint('partner'));
      $this->setConnected(TRUE);
    }
    else {
      // Alert the caller that the Salesforce instance has not been configured.
      watchdog('salesforce_soap', 'Attempting to use an instance of
        the SalesforceSoapPartner class with a non-authorized Salesforce API
        instance. Please ensure the Salesforce API module has been configured
        and successfully authorized with a Salesforce org.', NULL, WATCHDOG_ERROR);

      $this->setConnected(FALSE);
    }
  }

  /**
   * Setter for isConnected private variable.
   *
   * @param bool $is_connected
   *   Boolean to indicate whether the instance made a successful connection
   *   to the SOAP API.
   */
  protected function setConnected($is_connected) {
    $this->isConnected = $is_connected;
  }

  /**
   * Indicates whether or not a successfull connection was made the SOAP API.
   */
  public function isConnected() {
    return $this->isConnected;
  }
}
