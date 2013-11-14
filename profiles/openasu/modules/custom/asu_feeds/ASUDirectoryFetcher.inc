<?php
/**
 * @file
 * Generates form and fetches values from the form for ASU Directory Feed.
 *
 * Generates form (/?q=import/asu_directory_feed).
 * Fetches values (url, department code, eid and taxonomy term) from the form.
 */
 
/**
 * Adds a field for user to enter Department code.
 */
class ASUDirectoryFetcherResult extends FeedsHTTPFetcherResult {
  protected $dc;
  protected $eid;
  protected $eids;
  protected $t_term;

  // We need get methods. So, we can use $eids and $t_term in ASUDirectoryFeedParser.inc.
  public function getEids() {
    return $this->eids;
  }

  public function getT_term() {
    return $this->t_term;
  }

  public function __construct($url, $dc, $eid, $t_term) {
    // Depending on the URL, it will fetch by employee ID or by department code

    // Fetch by emmployee ID
    if ($url == "https://webapp4.asu.edu/directory-ws/services/public/person/v1.0") {

      // If there are more than one employee IDs entered
      if (substr_count($eid, ",") > 0) {
        $eids = $eid;
        $eid_array = explode( ",", $eid);
        $eid = trim($eid_array[0]);
      }
      // If there is only one Employee ID entered
      else {
        $eids = "";
      }

      $url = $url . '?eid=' . $eid;
    }

    // Fetch by department code
    elseif ($url == "https://webapp4.asu.edu/directory-ws/services/public/search/department/v1.0" ) {
      $url = $url . '?dc=' . $dc;
			
			$eids = "";
			$eid = "";
    }

    // Wrong URL
    else {
      drupal_set_message($message = "Please enter correct URL.", $type = 'error', $repeat = TRUE);
    }

    $this->dc = $dc;
    $this->url = $url;
    $this->eid = $eid;
    $this->eids = $eids;
    $this->t_term = $t_term;
    //parent::__construct($url, 0);
    parent::__construct($url);

  } // End of function __construct

} // End of class ASUDirectoryBatch


class ASUDirectoryFetcher extends FeedsHTTPFetcher {
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    //return new ASUDirectoryBatch($source_config['url'],$source_config['dc'], $source_config['eid'], $source_config['t_term']); // Changed to $source_config['source'] on 9/16/2011 - Chizuko
    if (isset($source_config['url'])) { // Made it backward-compatible. So, it works with $form['url'] also. - Chizuko 9/30/2011
      $source_config['source'] = $source_config['url'];
    }
    return new ASUDirectoryFetcherResult($source_config['source'], $source_config['dc'], $source_config['eid'], $source_config['t_term']);
  }

  public function sourceForm($source_config) {
    $form = array();

// 9/16/2011 - Chizuko Swanson
// Needed to change $form['url'] to $form['source'] to make it work with new version of Feeds module (feeds 6.x-1.0-beta11).
// feeds 6.x-1.0-beta11 -> feeds/plugins/FeedsHTTPFetcher.inc line 151
//  public function sourceFormValidate(&$values) {
//		error_log("let's see: " . $values['source']); //chizuko
//		
//    if (!feeds_valid_url($values['source'], TRUE)) {
//      $form_key = 'feeds][' . get_class($this) . '][source';
//      form_set_error($form_key, t('The URL %source is invalid.', array('%source' => $values['source'])));
//    }
//    elseif ($this->config['auto_detect_feeds']) {
//      feeds_include_library('http_request.inc', 'http_request');
//      if ($url = http_request_get_common_syndication($values['source'])) {
//        $values['source'] = $url;
//      }
//    }
//  }
// They added this if statement. I noticed $values['source'] was not set. So, it was throwing "The URL is invalid." error.
// Therefore, I changed $form['url'] to $form['source'].


//		$form['url'] = array(
//      '#type' => 'textfield',
//      '#title' => t('URL'),
//      '#description' => t('Enter a feed URL. <br />To use department code: https://webapp4.asu.edu/directory-ws/services/public/search/department/v1.0<br />To use Employee ID:  https://webapp4.asu.edu/directory-ws/services/public/person/v1.0'),
//      '#default_value' => $source_config['url'] ? $source_config['url'] : 'https://webapp4.asu.edu/directory-ws/services/public/search/department/v1.0',
//      '#maxlength' => NULL,
//      '#required' => TRUE,
//    );
    $form['source'] = array(
      '#type' => 'textfield',
      '#title' => t('URL'),
      '#description' => t('Enter a feed URL. <br />To use department code: https://webapp4.asu.edu/directory-ws/services/public/search/department/v1.0<br />To use Employee ID:  https://webapp4.asu.edu/directory-ws/services/public/person/v1.0'),
      '#default_value' => isset($source_config['source']) ? $source_config['source'] : 'https://webapp4.asu.edu/directory-ws/services/public/search/department/v1.0',
      '#maxlength' => NULL,
      '#required' => TRUE,
    );

    $form['dc'] = array(
      '#type' => 'textfield',
      '#title' => t('Department code'),
      '#description' => t('Department code, i.e. U0101'),
      '#default_value' => isset($source_config['dc']) ? $source_config['dc'] : '',
    );
    $form['eid'] = array(
      '#type' => 'textfield',
      '#title' => t('ASU Directory Feed EID'),
      '#description' => t('For example, for person (https://webapp4.asu.edu/directory/person/1633409), please enter 1633409.<br />Or you can enter comma-separated list of Emplpyee IDs.<br />i.e. 66195, 965469, 1292998'),
      '#default_value' => isset($source_config['eid']) ? $source_config['eid'] : '',
    );
    $form['t_term'] = array(
      '#type' => 'textfield',
      '#title' => t('Taxonomy term'),
      '#description' => t('This taxonomy term will be attached to the people being pulled.'),
      '#default_value' => isset($source_config['t_term']) ? $source_config['t_term'] : '',
    );
    return $form;
  }

}