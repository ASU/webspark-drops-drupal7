<?php /** @noinspection PhpUnused */

/**
 * Callback service function sent for success posting to SF
 * @param $hash
 * @param $nid
 */
function asu_rfi_success_post($hash, $nid) {
  header('Content-Type: text/json');
  $mw_auth_key = variable_get('asu_rfi_form_auth_key');
  $real_hash = sha1($mw_auth_key . '+' . $nid);
  if ($real_hash == $hash) {
    $node = node_load($nid);
    $node_wrapper = entity_metadata_wrapper('node', $node);
    if (isset($node_wrapper->field_rfi_submission_status)) {
      $node_wrapper->field_rfi_submission_status->set('SF_Completed');
    }
    if (isset($node_wrapper->field_rfi_error_message)) {
      $node_wrapper->field_rfi_error_message->set('');
    }
    $node_wrapper->save();
    $cid = 'field:node:' . $nid;
    cache_clear_all($cid, 'cache_field');
    print('Success');
  } else {
    http_response_code(403);
    watchdog('asu_rfi', __FUNCTION__ . ' - Not a valid Hash / Nid combination', array(), WATCHDOG_ERROR);
  }
}

/**
 * Post failed submissions update
 * @param $hash
 * @param $nid
 * @throws \Exception
 */
function asu_rfi_fail_post($hash, $nid) {
  header('Content-Type: text/json');
  $mw_auth_key = variable_get('asu_rfi_form_auth_key');
  $real_hash = sha1($mw_auth_key . '+' . $nid);
  if ($real_hash == $hash) {
    $request_body = @file_get_contents('php://input');
    $error_message = $request_body;

    $node = node_load($nid);
    $node_wrapper = entity_metadata_wrapper('node', $node);

    if (isset($node_wrapper->field_rfi_submission_status)) {
      if ($node_wrapper->field_rfi_submission_status->value() == "Form_Completed") {
        $node_wrapper->field_rfi_submission_status->set("SF_Failed");
      }
    }

    $to_email = variable_get('asu_rfi_error_email', NULL); // get error reporting email address from rfi admin settings page
    if (!empty($to_email)) {
      _asu_rfi_create_failed_post_email($to_email, $nid);
    }
    if (isset($node_wrapper->field_rfi_error_message)) {
      $node_wrapper->field_rfi_error_message->set($error_message);
    }
    $node_wrapper->save();
    $cid = 'field:node:' . $nid;
    cache_clear_all($cid, 'cache_field');
    print('Posted error message');
  } else {
    http_response_code(403);
    watchdog('asu_rfi', __FUNCTION__ . ' - Not a valid Hash / Nid combination', array(), WATCHDOG_ERROR);
  }
}


/** Test submissions post data update
 * @param $hash
 * @param $nid
 */
function asu_rfi_test_post($hash, $nid) {
  header('Content-Type: text/json');
  $mw_auth_key = variable_get('asu_rfi_form_auth_key');
  $real_hash = sha1($mw_auth_key . '+' . $nid);
  if ($real_hash == $hash) {
    $request_body = @file_get_contents('php://input');
    $error_message = $request_body;

    $node = node_load($nid);
    $node_wrapper = entity_metadata_wrapper('node', $node);
    if (isset($node_wrapper->field_rfi_submission_status)) {
      $node_wrapper->field_rfi_submission_status->set('SF_Completed');
    }
    if (isset($node_wrapper->field_rfi_error_message)) {
      $node_wrapper->field_rfi_error_message->set($error_message);
    }
    $node_wrapper->save();

    $cid = 'field:node:' . $nid;
    cache_clear_all($cid, 'cache_field');
    print('Posted success message for test submission');
  } else {
    print('Not a valid Hash / Nid combination');
  }
}

/**
 * Saves middleware key in the admin settings page App key field
 * @param $key
 */
function asu_rfi_middle_key($key) {
  //Check if middleware key is already set. If set, don't update the key, else set the variable with key value
  global $conf;

  if (!isset($conf['asu_rfi_form_auth_key'])) {
    variable_set('asu_rfi_form_auth_key', FALSE);
  }
  if (empty($conf['asu_rfi_form_auth_key'])) {
    $middle_key = base64_decode($key);
    variable_set('asu_rfi_form_auth_key', $middle_key);
  } else {
    http_response_code(400);
  }
}

/**
 * Adds http_response_code if not already compiled into PHP or added in Drupal
 */
if (!function_exists('http_response_code')) {
  function http_response_code($newcode = NULL)
  {
    static $code = 200;
    if ($newcode !== NULL) {
      header('X-PHP-Response-Code: ' . $newcode, true, $newcode);
      if (!headers_sent())
        $code = $newcode;
    }
    return $code;
  }
}
