<?php

/**
 * @file
 * @todo file description.
 *
 * Development of this module is sponsered by Gigya, Inc.
 */

/**
 * Makes Gigya token replacements.
 *
 * Callback for array_walk.
 *
 * @param string $value
 *   A reference to the string to manipulate.
 * @param string $key
 *   The key of the value from the array.
 * @param array $params
 *   - replacements : An associative array containing the Gigya tokens.
 *   - token_types : An keyed array with the token types , the token types could
 *     by 'node' or 'user' or 'comment'.
 *   - object : stdClass could by node or comment or user.
 *   - type : string the object type could by 'node' or 'comment' or 'user'
 *
 * @see gigya_shareui_general_action()
 */

/**
 * Callback for array_walk().
 *
 * Receives form items and assesses whether or not they're input fields.
 * If so, then it tries to set the default value based on the profile mappings.
 *
 * see gigya_form_alter()
 */
function gigya_apply_profile_mapping(&$field, $key) {
  if (is_array($field)) {
    // Check for some key elements. We do this explicitly to make sure the
    // indexes are defined and avoid PHP notices.
    $type = isset($field['#type']) ? $field['#type'] : '';
    $field_name = isset($field['#field_name']) ? $field['#field_name'] : '';
    $theme = isset($field['#theme']) ? $field['#theme'] : '';

    // Is it a standard type to replace?
    if (in_array($type, array(
        'checkbox',
        'checkboxes',
        'date',
        'radio',
        'radios',
        'select',
        'textarea',
        'textfield',
      )
    )
    ) {
      if (isset($field['#default_value'])) {
        $orig = $field['#default_value'];
        $token = token_replace(variable_get('gigya_map_' . $key, ''));
        $field['#default_value'] = $token ? $token : $orig;
      }
    }
    // If it isn't and we have a #field_name, just go for it.
    elseif ($field_name && $type) {
      if (isset($field['#default_value'])) {
        $orig = $field['#default_value'];
        $token = token_replace(variable_get('gigya_map_' . $field['#field_name'], ''), 'gigya');
        $field['#default_value']['value'] = $token ? $token : $orig;
      }
    }
    // If it is a fieldset or multi-value field, drill in.
    elseif ($type == 'fieldset' || $theme == 'content_multiple_values') {
      array_walk($field, 'gigya_apply_profile_mapping');
    }
  }
}

/**
 * Get an avatar picutre url from Gigya by $uid.
 *
 * @param string $uid
 *   The user id to get the avatar for.
 *
 * @return bool
 *   The user thumbnail url if he has one or the photoURL if not.
 */
function gigya_avatar_check($uid) {
  $bio = gigya_get_user_info($uid);
  if ($bio['thumbnailURL']) {
    return $bio['thumbnailURL'];
  }
  elseif ($bio['photoURL']) {
    return $bio['photoURL'];
  }
  else {
    return FALSE;
  }
}

/**
 * Save an user picture from facebook and resize it.
 *
 * @param string $uid
 *   the user id to get the picture for.
 *
 * @return bool|object
 *   A file object if the user has avatar picture and we successfuly save the
 */
function gigya_save_userpic($uid) {
  // Get Facebook user picture's url.
  if ($avatar = gigya_avatar_check($uid)) {
    $result = drupal_http_request($avatar);

    if ($result->code != 200) {
      watchdog('gigya', 'Failed importing user avatar for @uid, code : @code', array(
          '@uid' => $uid,
          '@code' => $result->code,
        )
      );
      return FALSE;
    }

    $filename = 'picture-gigya_' . $uid . '.jpg';
    $dest = file_directory_path();
    if (variable_get('user_picture_path', '')) {
      $dest .= '/' . variable_get('user_picture_path', '');
    }
    $dest .= '/' . $filename;

    $file = file_save_data($result->data, $dest, FILE_EXISTS_REPLACE);
    // Resizing.
    list($width, $height) = sscanf(variable_get('user_picture_dimensions', '85x85'), '%dx%d');
    image_scale_and_crop($file, $dest, $width, $height);
    drupal_set_message(t('User picture saved successfully!'));

    return $file;
  }
  else {
    drupal_set_message(t('Your social network does not have a profile picture'));
    return FALSE;
  }
}

/**
 * Prepare a keyed array of languages.
 *
 * @return array
 *   Keyed array of languages.
 */
function gigya_get_languages() {
  return array("en" => "English (default)","ar" => "Arabic","br" => "Bulgarian","ca" => "Catalan","hr" => "Croatian",
    "cs" => "Czech","da" => "Danish","nl" => "Dutch","fi" => "Finnish","fr" => "French","de" => "German",
    "el" => "Greek","he" => "Hebrew","hu" => "Hungarian","id" => "Indonesian (Bahasa)","it" => "Italian",
    "ja" => "Japanese","ko" => "Korean","ms" => "Malay","no" => "Norwegian","fa" => "Persian (Farsi)",
    "pl" => "Polish","pt" => "Portuguese","ro" => "Romanian","ru" => "Russian","sr" => "Serbian (Cyrillic)",
    "sk" => "Slovak","sl" => "Slovenian","es" => "Spanish","sv" => "Swedish","tl" => "Tagalog","th" => "Thai",
    "tr" => "Turkish","uk" => "Ukrainian","vi" => "Vietnamese","zh-cn" => "Chinese (Mandarin)","Chinese (Hong Kong)" => "zh-cn",
    "zh-hk" => "Chinese (Hong Kong)","Chinese (Taiwan)" => "zh-hk","zh-tw" => "Chinese (Taiwan)","Croatian" => "zh-tw","nl-inf" => "Dutch Informal",
    "Finnish" => "nl-inf","fr-inf" => "French Informal","German" => "fr-inf","de-inf" => "German Informal","Greek" => "de-inf",
    "pt-br" => "Portuguese (Brazil)","Romanian" => "pt-br","es-inf" => "Spanish Informal","Spanish (Lat-Am)" => "es-inf",
    "es-mx" => "Spanish (Lat-Am)","Swedish" => "es-mx");
}

/**
 * Gets the list of the Gigya profile fields.
 *
 * @return array
 *   An associative array (machine-name => human-readable display name).
 */
function _gigya_get_profile_fields() {
  return array(
    'nickname' => t('Nickname'),
    'photoURL' => t('Gigya Profile photo URL'),
    'thumbnailURL' => t('Thumbnail profile photo URL'),
    'profileURL' => t('Profile URL'),
    'firstName' => t('First name'),
    'lastName' => t('Last name'),
    'gender' => t('Gender'),
    'age' => t('Age'),
    'birthDay' => t('Birth day'),
    'birthMonth' => t('Birth month'),
    'birthYear' => t('Birth year'),
    'email' => t('Email'),
    'country' => t('Country'),
    'state' => t('State'),
    'city' => t('City'),
    'zip' => t('Zip'),
    'likes' => t('likes'),
    'proxiedEmail' => t('proxiedEmail'),
    'languages' => t('languages'),
    'address' => t('address'),
    'honors' => t('honors'),
    'professionalHeadline' => t('professionalHeadline'),
    'bio' => t('bio'),
    'industry' => t('industry'),
    'specialties' => t('specialties'),
    'religion' => t('religion'),
    'politicalView' => t('politicalView'),
    'interestedIn' => t('interestedIn'),
    'relationshipStatus' => t('relationshipStatus'),
    'hometown' => t('hometown'),
    'username' => t('Facebook Username'),
    'locale' => t('locale'),
    'ltimezone' => t('ltimezone'),
  );
}

/**
 * Callback for array_walk, helper function for trimming.
 *
 * @value string
 *   The string to trim.
 */
function _gigya_trim_value(&$value) {
  $value = trim($value);
}

/**
 * Logs user in to Gigya's service and optionally registers them.
 *
 * @param string $uid
 *   The drupal User ID.
 * @param bool $is_new_user
 *   Tell Gigya if we add a new user.
 * @param mixed $user_info_json
 *   Extra info for the user.
 *   see gigya_user_login()
 *
 * @return bool|NULL|string
 *   True if the notify login request succeeded or the error message from Gigya.
 */
function gigya_notify_login($uid, $is_new_user = FALSE, $user_info_json = NULL) {
  $request = gigya_prepare_request('socialize.notifyLogin');
  $request->setParam("siteUID", $uid);
  if (!empty($is_new_user)) {
    $request->setParam('newUser', TRUE);
  }
  if (!empty($user_info_json)) {
    $request->setParam('userInfo', $user_info_json);
  }
  $response = $request->send();
  if ($response->getErrorCode() !== 0) {
    // Error.
    watchdog('gigya', 'error in notify login, the message was @msg', array('@msg' => $response->getErrorMessage()));
    return $response->getErrorMessage();
  }
  try {
    setcookie($response->getString("cookieName"), $response->getString("cookieValue"), 0, $response->getString("cookiePath"), $response->getString("cookieDomain"));
  }
  catch (Exception $e) {
    watchdog('gigya', 'error setting gigya cookie, the error message was @error', array('@error' => $e->getMessage()));
  }

  return TRUE;
}

/**************************************************
 *  Internal Gigya signature verification functions
 **************************************************/

/**
 * Helper function that validates the SDK response.
 *
 * @param mixed $response
 *   The SDK response.
 *
 * @return bool
 *   True if response signature is valid FALSE if not.
 */
function _gigya_validate_sig($uid, $sig_timestamp, $uid_sig, $domain = "socialize") {
  $valid = TRUE;
  $mode = variable_get('gigya_access_mode', 'api');
  if ($mode == "app") {
    $secret_key = gigya_get_app_secret_key();
    $app_key = variable_get('gigya_application_key', '');
    $response = _gigya_api("$domain.exchangeUIDSignature", array('UID' => $uid, 'UIDSignature' => $uid_sig, 'signatureTimestamp' => $sig_timestamp, 'userKey' => $app_key), TRUE);
    if ($response['errorCode'] == 0) {
      $uid = $response['UID'];
      $sig_timestamp = $response['signatureTimestamp'];
      $uid_sig = $response['UIDSignature'];
    }
    else {
      $valid = FALSE;
    }
  }
  else {
    $secret_key = gigya_get_secret_key();
  }
  if ($valid) {
    $valid = SigUtils::validateUserSignature($uid, $sig_timestamp, $secret_key, $uid_sig);
  }
  if ($valid) {
    return TRUE;
  }
  else {
    watchdog('gigya', 'Response signature is not valid.', NULL, WATCHDOG_WARNING);
    return FALSE;
  }
}

function _gigya_validate_sig_response($response) {
  return _gigya_validate_sig($response->getString("UID", ""), $response->getString("signatureTimestamp", ""), $response->getString("UIDSignature", ""), $response->getString("signature", ""));
}



/**
 * A helper function that calculate the Gigya signature.
 *
 * @param int $timestamp
 *   The request timestamp.
 * @param mixed $user_id
 *   The Gigya user id.
 *
 * @return string
 *   The calculated signature.
 */
function _gigya_calculate_signature($timestamp, $user_id) {
  $base_str = $timestamp . '_' . $user_id;
  $key = gigya_get_secret_key();
  if ($key == "") {
    $key = FALSE;
  }
  $sig = SigUtils::calcSignature($base_str, $key);
  return $sig;
}

/**
 * Validates the Gigya session keys.
 *
 * We use the site 'admin' username to find out the status. If it shows the
 * user logged out, that's good, if it returns an error then our keys are
 * most likely bad.
 */
function gigya_validate($mode, $api_key, $secret_key, $app_key, $app_secret, $data_center, $update = FALSE) {
  $orig_validate_state = variable_get('gigya_validate', FALSE);
  if ($mode == "app") {
    $request = new GSRequest($api_key, $app_secret, 'shortenURL', NULL, TRUE, $app_key);
    $caf_path = drupal_get_path('module', 'gigya') . "/cacert.pem";
    $request->setCAFile(realpath($caf_path));

  }
  else {
    $request = new GSRequest($api_key, $secret_key, 'shortenURL', NULL, TRUE);
    $caf_path = drupal_get_path('module', 'gigya') . "/cacert.pem";
    $request->setCAFile(realpath($caf_path));
  }
  $request->setAPIDomain($data_center);
  $request->setParam('url', 'http://gigya.com');
  ini_set('arg_separator.output', '&');
  $response = $request->send();
  ini_restore('arg_separator.output');
  $error = $response->getErrorCode();
  if (!$update) {
    if ($error == 0) {
      global $user;
      $account = clone $user;
      $datestr = format_date(time(), 'custom', 'Y-m-d H:i:s');
      watchdog('gigya', 'secret key has changed by @name date @date', array('@name' => $account->name, "@date" => $datestr), WATCHDOG_DEBUG);
      drupal_set_message(t('Gigya validated properly. This site is authorized to use Gigya services'));
      variable_set('need_validation_msg', TRUE);
      variable_set('gigya_validate', TRUE);
      return TRUE;
    }
    else {
      variable_set('gigya_validate', FALSE);
      return $response;
    }
  }
  if (!$orig_validate_state || variable_get('need_validation_msg', FALSE)) {
    drupal_set_message(t('Gigya validated properly. This site is authorized to use Gigya services'));
    variable_set('need_validation_msg', TRUE);
  }

  variable_set('gigya_validate', TRUE);
  return TRUE;
}

/****************************
 * Gigya API functions
 ****************************/

/**
 * Delete user from Gigya's database.
 *
 * @param int $uid
 *   The drupal user id to delete.
 *
 * internal param int $timestamp The request timestamp.*
 * The request timestamp.
 *
 * @return array
 *   The response from Gigya.
 */
function gigya_delete_account($uid) {
  if (empty($uid)) {
    return FALSE;
  }

  $params = array(
    'uid' => $uid,
  );

  return _gigya_api('deleteAccount', $params);
}

/**
 * Notifies Gigya that we've completed registering this user.
 *
 * @param mixed $gigya_uid
 *   The Gigya uid.
 * @param int $drupal_uid
 *   internal param int $uid The drupal user id.*
 *   The drupal user id.
 *
 * @return array
 *   The response from Gigya.
 */
function gigya_notify_registration($gigya_uid, $drupal_uid) {
  if (empty($gigya_uid) || empty($drupal_uid)) {
    return FALSE;
  }

  $params = array(
    'uid' => $gigya_uid,
    'siteUID' => $drupal_uid,
  );

  return _gigya_api('notifyRegistration', $params);
}


/**
 * Sets the Gigya UID to match the Drupal UID.
 *
 * @param mixed $gigya_uid
 *   The Gigya uid.
 * @param int $drupal_uid
 *   internal param int $uid The drupal user id.*
 *   The drupal user id.
 *
 * @return array
 *   The response from Gigya.
 */
function gigya_set_uid($gigya_uid, $drupal_uid) {
  if (empty($gigya_uid) || empty($drupal_uid)) {
    return FALSE;
  }

  $params = array(
    'uid' => $gigya_uid,
    'siteUID' => $drupal_uid,
  );

  return _gigya_api('setUID', $params);
}

/**
 * Fetches information about user following a given Gigya account.
 *
 * @param mixed $gigya_uid
 *   The Gigya uid.
 *
 * @return array
 *   The response from Gigya.
 */
function gigya_get_user_info($gigya_uid) {
  if (empty($gigya_uid)) {
    return FALSE;
  }

  $params = array(
    'uid' => $gigya_uid,
  );

  return _gigya_api('getUserInfo', $params);
}

/**
 * Fetches information about the user friends following a given Gigya account.
 *
 * @param mixed $gigya_uid
 *   The Gigya uid.
 * @param array $params
 *   An associative array of params to pass to Gigya.
 *   see http://developers.gigya.com/020_Client_API/020_Methods/socialize.getFriends
 *
 * @return array
 *   The response from Gigya.
 * deprecated
 */
function gigya_get_friends_info($gigya_uid, $params = array()) {
  if (empty($gigya_uid)) {
    return FALSE;
  }

  $params += array(
    'uid' => $gigya_uid,
  );

  return _gigya_api('getFriendsInfo', $params);
}

/**
 * Sets the user's status in social networks that support this feature.
 *
 * @param mixed $gigya_uid
 *   The Gigya uid.
 * @param string $status
 *   The status string to set.
 *
 * @return array
 *   The response from Gigya.
 */
function gigya_set_status($gigya_uid, $status) {
  if (empty($gigya_uid)) {
    return FALSE;
  }

  $params = array(
    'uid' => $gigya_uid,
    'status' => $status,
  );

  return _gigya_api('setStatus', $params);
}

/**
 * Publishes a user action to the newsfeed on all the connected providers.
 *
 * @param mixed $gigya_uid
 *   The Gigya uid.
 * @param array $content
 *   template :  the template.
 *   action : the action.
 *   title : the action title.
 *   path : the path.
 *
 * @return array
 *   The response from Gigya or FALSE if there is no uid.
 */
function gigya_publish_user_action($gigya_uid, $content) {
  if (empty($gigya_uid)) {
    return FALSE;
  }

  $params = array(
    'uid' => $gigya_uid,
    'userAction' => _gigya_get_useraction_xml($content),
  );

  return _gigya_api('publishUserAction', $params);
}

/**
 * Log a user out using the Rest API.
 *
 * @param mixed $gigya_uid
 *   The Gigya uid.
 *
 * @return array
 *   The response from Gigya or FALSE if there is no uid.
 */
function gigya_logout_uid($gigya_uid) {
  if (empty($gigya_uid)) {
    return FALSE;
  }

  $params = array(
    'uid' => $gigya_uid,
  );

  return _gigya_api('logout', $params);
}

/*
 * Handles all calls to the Gigya API.
 */
require_once drupal_get_path('module', 'gigya') . '/GSSDK.php';

/**
 * Helper function that handles Gigya API calls.
 *
 * @param mixed $method
 *   The Gigya API method.
 * @param mixed $params
 *   The method parameters.
 *
 * @param bool $return_code
 *   Should error be returned.
 *
 * @return array
 *   The Gigya response.
 */
function _gigya_api($method, $params, $return_code = FALSE) {

  //Add environment params
  if ($method == 'accounts.getAccountInfo') {
    $info = system_get_info('module', 'gigya');
    $gigya_version = $info['version'];
    $params['environment'] = "cms_version:" . "Drupal_" . VERSION . ",gigya_version:" . "Gigya_module_" . $gigya_version;
  }

  $request = gigya_prepare_request($method);

  $user_info = NULL;
  if (!empty($params)) {
    $user_info = in_array('getUserInfo', $params);
    foreach ($params as $param => $val) {
      $request->setParam($param, $val);
    }
    if (!empty($params['uid'])) {
      $gig_uid = $params['uid'];
    }
  }
  $request->setAPIDomain(variable_get('gigya_data_center', 'us1.gigya.com'));
  ini_set('arg_separator.output', '&');
  $response = $request->send();
  ini_restore('arg_separator.output');
  $mode = variable_get('gigya_access_mode', 'api');
  if (variable_get('gigya_debug', 0)) {

    // on first module load, api & secret are empty, so no values in response
    if ((variable_get('gigya_APIKey', '') != "")) {
      if ($response->getData()) {
        watchdog('gigya', 'Response from gigya <br /><pre>callId : ' . $response->getData()->getString('callId') .
                          "apicall:$method" .
                          '</pre>', NULL, WATCHDOG_DEBUG);
      }
    }
    watchdog('gigya', 'Access mode <br /><pre>' . $mode . '</pre>', NULL, WATCHDOG_DEBUG);
  }
  $code = _gigya_request_failure($response, $user_info, $return_code);
  if ($code !== TRUE && $code !== 0) {
    watchdog('gigya', 'Access mode <br /><pre>' . $mode . '</pre>', NULL, WATCHDOG_DEBUG);
    watchdog('gigya', 'errorcode :<pre>' . $code . '</pre>', NULL, WATCHDOG_DEBUG);
    if ($response->getData()) {
      watchdog('gigya', 'Response from gigya <br /><pre>callId : ' . $response->getData()->getString('callId') .
        "apicall:$method,Error:$code" .
        '</pre>', NULL, WATCHDOG_DEBUG);
    }
    //Always write error to log.
    return $code;
  }

  return _gigya_convert_json_to_array($response->getResponseText());
}

function _get_gigya_account($params) {
  $gigya_account = _gigya_api("accounts.getAccountInfo", $params, TRUE);
  // If we get an error retry
  if (is_numeric($gigya_account)) {
    $gigya_account = _gigya_api("accounts.getAccountInfo", $params, TRUE);
  }
  return $gigya_account;
}

function _disable_gigya_account($uid) {
  $params = array(
    'UID' => $uid,
    'isActive' => FALSE
  );
  return _gigya_api('accounts.setAccountInfo', $params);
}
/**
 * Internal helper function to deal cleanly with various HTTP response codes.
 *
 * @param mixed $response
 *   the gigya response.
 * @param bool $user_info
 *   tell if the request has the user info parm.
 *
 * @param bool $return_error
 *   Should error be returned.
 *
 * @return bool
 *   TRUE if we have errors FALSE if not.
 */
function _gigya_request_failure($response, $user_info = NULL, $return_error = FALSE) {
  $code = $response->getErrorCode();

  switch ($code) {
    case '403005':
      if (variable_get('gigya_validate', FALSE)) {
        return FALSE;
      }
      else {
        watchdog('gigya', $response->getErrorMessage(), NULL, WATCHDOG_WARNING);
        return (isset($return_error)) ? $code : TRUE;
      }

    default:
      return ($return_error) ? $code : TRUE;
  }
}

/**
 * Convert JSON response to a PHP array.
 *
 * @param string $data
 *   The JSON data.
 *
 * @return array
 *   The converted array from the JSON.
 */
function _gigya_convert_json_to_array($data) {
  $array = json_decode($data, TRUE);
  return $array;
}


/**
 * Checks if user exist by querying the database.
 *
 * @param string $id
 *   email or username.
 *
 * @return bool
 *   True if user exist.
 */
function gigya_dose_user_exist($id) {
  return (bool) db_select('users')->fields('users', array('uid'))->condition('mail', db_like($id), 'LIKE')->range(0, 1)
    ->execute()->fetchField() || (bool) db_select('users')->fields('users', array('uid'))
    ->condition('name', db_like($id), 'LIKE')->range(0, 1)->execute()->fetchField();
}

/**
 * Checks if this email is the primary user email.
 *
 * @param array $user_info
 *   The user info from accounts.getUserInfo api call.
 * @param string $email
 *   The user email.
 *
 * @return bool
 *   True if this email is the primary.
 */
function gigya_is_raas_primary_user($user_info, $email) {
  return in_array($email, $user_info['loginIDs']['emails']);
}

function gigya_get_raas_fields() {
  $cache = cache_get('raas_fields', 'cache');
  if (!$cache) {
    $gigya_schema = _gigya_api('accounts.getSchema', array(), TRUE);
    if (!empty($gigya_schema) && is_array($gigya_schema)) {
      $schema['Account fields']['UID'] = 'UID';
      $profile_fields = array_keys($gigya_schema['profileSchema']['fields']);
      foreach ($profile_fields as $field) {
        $fld = current(explode('.', $field));
        $schema['Profile fields']['profile.' . $fld] = $fld;
      }
      $data_fields = array_keys($gigya_schema['dataSchema']['fields']);
      foreach ($data_fields as $field) {
        $schema['Data fields']['data.' . $field] = $field;
      }
      cache_set('raas_fields', $schema, 'cache', CACHE_TEMPORARY);
      return $schema;
    }
    else {
      return array();
    }

  }
  else {
    return $cache->data;
  }
}

function gigya_get_nested_value($array, $keys) {
  while (!empty($keys)) {
    $key = array_shift($keys);
    if (array_key_exists($key, $array)) {
      $array = $array[$key];
    }
    else {
      return FALSE;
    }
  }
  if (gettype($array) == 'array') {
    return drupal_json_encode($array);
  }
  return $array;
}

function gigya_prepare_request($method) {
  $apikey = variable_get('gigya_APIKey', '');
  $mode = variable_get('gigya_access_mode', 'api');
  $app_key = NULL;
  $secret_key = NULL;
  if ($mode == "app") {
    $secret_key = gigya_get_app_secret_key();
    $app_key = variable_get('gigya_application_key', '');
  }
  else {
    $secret_key = gigya_get_secret_key();
  }
  $request = new GSRequest($apikey, $secret_key, $method, NULL, TRUE, $app_key);
  $caf_path = drupal_get_path('module', 'gigya') . "/cacert.pem";
  $request->setCAFile(realpath($caf_path));
  return $request;
}

function gigya_get_secret_key($encrypt_mode = FALSE) {
  return gigya_decrypt_value(variable_get('gigya_SecretKey', ''), $encrypt_mode);

}
function gigya_get_app_secret_key($encrypt_mode = FALSE) {
  return gigya_decrypt_value(variable_get('gigya_application_secret_key', ''), $encrypt_mode);
}

function gigya_decrypt_value($val, $encrypt_mode = FALSE) {
  if (!function_exists('decrypt')) {
    return $val;
  }
  if ($encrypt_mode === FALSE) {
    $encrypt_mode = variable_get('gigya_encrypt_config', '0');
  }
  if ($encrypt_mode && $encrypt_mode != "0") {
    try {
      $val = decrypt($val, array(), NULL, NULL, $encrypt_mode);
    } catch (Exception $e) {
      watchdog('gigya', 'Error decrypt values');
    }
  }
  return $val;
}

function _gigya_set_logout_cookie() {
  if (variable_get('gigyaSessionControl', 'drupal') == 'drupal') {
    user_cookie_save(array('gigya' => 'gigyaLogOut'));
  }
}