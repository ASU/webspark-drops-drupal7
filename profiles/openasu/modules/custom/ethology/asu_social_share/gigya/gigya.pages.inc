<?php

/**
 * @file
 * Page display functions for for Gigya module.
 */

/**
 * Page callback for the user/%user/edit/gigya page.
 *
 * see gigya_menu()
 *
 * @return null|string
 *   Gigya connect page HTML.
 */
function gigya_connect() {
  drupal_set_title(t('Edit your Social Network connections'));
  global $user;
  if ($user->uid === arg(1)) {
    return theme('gigya_connect_display');
  }
  return t('Only users can edit their own connections.');
}

/**
 * Socialize-login page callback.
 *
 * see gigya_menu()
 *
 * return array
 *   An array of ajax commands.
 */
function gigya_login_ajax() {
  require_once drupal_get_path('module', 'gigya') . '/GSSDK.php';
  ctools_include('ajax');
  ctools_include('modal');
  $parms = $_POST; // check for XSS line 54.
  /* If the admin set a post login redirect send
  the user to it if no just reload the page. */
  $dest = variable_get('gigya_login_uiconfig_urlredirect', '');
  if (!empty($dest)) {
    $success_command[] = ctools_ajax_command_redirect($dest);
  }
  else {
    $success_command[] = ctools_ajax_command_reload();
  }
  // Check if the user is not logged in.
  if (!user_is_logged_in()) {
    $commands = array();
    $_SESSION['gigya_suppress_notifylogin_js'] = TRUE;
    module_load_include('inc', 'gigya');
    if (_gigya_validate_sig($parms['UID'], $parms['signatureTimestamp'], $parms['UIDSignature'], "socialize")) {
      // Check for XSS inside object;
      gigya_filter_xss_array($parms);
      $gigya_user = $parms['user'];

      /* Check to see if the Gigya user is a Drupal user.
      if the uid isn't a Drupal uid then the user_load will return false. */
      if (is_numeric($gigya_user['UID']) && $parms['isSiteUID'] === 'true' && $usr = user_load($gigya_user['UID'])) {
        if (!variable_get('user_email_verification', TRUE)) {
          /* We can suppress the notify login JS because the user is clearly
          already logged into gigya.
          $_SESSION['gigya_suppress_notifylogin_js'] = TRUE;
          Log the user in. */
          $form_state =array('uid' => $usr->uid);
          $form = array();
          // A small hack because on variables can be passed by reference
          user_login_submit($form, $form_state);
        }
        else {
          $commands[] = ajax_command_alert(t('You must validate your email address for this account before logging in.'));
        }
        return array('#type' => 'ajax', '#commands' => $success_command);
      }
      // If the user isn't a Drupal user, try to register them if allowed.
      elseif (variable_get('user_register', 1)) {
        $form_state['values'] = array();
        $uname = $parms['user']['email'];
        $user_existes = gigya_dose_user_exist($uname);
        if ($user_existes) {
          $form_state = array(
            'title' => t('Please login to link the accounts'),
            'ajax' => TRUE,
            'email' => $parms['user']['email'],
          );
          $commands = ctools_modal_form_wrapper('gigya_link_accounts_form', $form_state);
          return array('#type' => 'ajax', '#commands' => $commands);
        }
        else {
          $form_state['values']['name'] = $uname;
        }
        $form_state['values']['mail'] = $uname;
        $form_state['values']['pass'] = user_password();
        $_SESSION['gigya_uid'] = $parms['user']['UID'];

        // Allow other modules to change this info before we create the user.
        drupal_alter('gigya_create_user', $form_state, $parms);
        drupal_form_submit('user_register_form', $form_state);

        if (form_get_errors()) {
          if (variable_get('gigya_debug', 0)) {
            $messages = drupal_get_messages('error');
            $output = print_r($messages, TRUE);
            // We were unable to register a valid new user.
            // Send the error messages to watchdog.
            watchdog('gigya', 'Unable to auto-create user account:' . $output);
          }
          /* If there is an error in the registration process,
          return the registration form in a modal. */
          $form_state = array(
            'title' => t('Please fill-in missing details'),
            'ajax' => TRUE,
            'gigya' => TRUE,
          );
          $commands = ctools_modal_form_wrapper('user_register_form', $form_state);
          return array('#type' => 'ajax', '#commands' => $commands);
        }
        // The register process is done.
        $commands[] = $success_command;
        return array('#type' => 'ajax', '#commands' => $commands);
      }
      else {
        $commands[] = ajax_command_alert(t('Only site administrators can create new user accounts.'));
        return array('#type' => 'ajax', '#commands' => $commands);
      }
    }
    $commands[] = ajax_command_alert(t('Gigya signature not valid.'));
    return array('#type' => 'ajax', '#commands' => $commands);
  }
  $commands[] = $success_command;
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * RaaS login callback.
 *
 * @return array
 *   An array or ajax commands
 */
function gigya_raas_login_ajax() {
  if (!empty($_POST)) {
    ctools_include('ajax');
    ctools_include('modal');
    $redirect_url = variable_get('raas_redirect_url', NULL);
    if (!empty($redirect_url)) {
      $sucess_command = ctools_ajax_command_redirect($redirect_url);
    }
    else {
      $sucess_command = ctools_ajax_command_reload();
    }
    require_once drupal_get_path('module', 'gigya') . '/GSSDK.php';
    $parms = $_POST; // Post is not displayed on screen no need to filter_xss
    // noting is used except the UID to validate that the call is from Gigya or not
    if (!user_is_logged_in()) {
      $commands = array();
      $_SESSION['gigya_suppress_notifylogin_js'] = TRUE;
      module_load_include('inc', 'gigya');
      // Make sure the request came from Gigya.
      if (_gigya_validate_sig($parms['UID'], $parms['signatureTimestamp'], $parms['UIDSignature'], "accounts")) {
        // Get the account from Gigya.
        $req_params = array(
          'UID' => $parms['UID'],
          'include' => 'loginIDs,profile,data',
          'extraProfileFields' => 'username,languages,address,phones,education,honors,publications,patents,
          certifications,professionalHeadline,bio,industry,specialties,work,skills,religion,politicalView,
          interestedIn,relationshipStatus,hometown,favorites,followersCount,followingCount,locale,verified,timezone,likes'
        );
        drupal_alter('gigya_get_account_info', $req_params);
        $gigya_account = _get_gigya_account($req_params);
        // If we get an error abort the process with a message.
        if (is_numeric($gigya_account)) {
          $msg = t("Oops! Something went wrong during your login/registration process. Please try to login/register again.");
          _gigya_set_logout_cookie();
          $commands[] = ajax_command_alert($msg);
          $commands[] = ctools_ajax_command_reload();
          return array('#type' => 'ajax', '#commands' => $commands);
        }
        // Check for XSS inside object;
        gigya_filter_xss_array($gigya_account);
        $email = $gigya_account['profile']['email'];
        if (empty($email)) {
          _gigya_set_logout_cookie();
          $commands[] = ajax_command_alert(t('Email address is required by Drupal and is missing, please contact the site administrator.'));
          $commands[] = ctools_ajax_command_reload();
          return array('#type' => 'ajax', '#commands' => $commands);


        }
        // Check if users exists on the system.
        $user_exist = gigya_dose_user_exist($email);
        if ($user_exist) {
          if (gigya_is_raas_primary_user($gigya_account, $email)) {
            $user = user_load_by_mail($email);
            /* Set global variable so we would know the user as logged in
            RaaS in other functions down the line.*/
            global $_gigya_raas_login;
            $_gigya_raas_login = TRUE;
            $_SESSION['gigya_raas_uid'] = $parms['UID'];
            // A small hack because on variables can be passed by reference
            $form_state = array('uid' => $user->uid);
            $form = array();
            user_login_submit($form, $form_state);



            $additional_user_fields = variable_get('gigya_raas_extra_mappings', array());
            if (!empty($additional_user_fields)) {
              if (module_exists("profile2")) {
                $p2_fields = gigya_remove_p2_fields($additional_user_fields, TRUE);
              }
              else {
                gigya_remove_p2_fields($additional_user_fields, FALSE);
              }
              foreach ($additional_user_fields as $raas_field => $drupal_field) {
                $raas_field_parts = explode(".", $raas_field);
                $drupal_field_parts = explode("::", $drupal_field);
                $val = gigya_get_nested_value($gigya_account, $raas_field_parts);
                $val = drupal_strlen($val) > $drupal_field_parts[1] ? drupal_substr($val, 0, $drupal_field_parts[1]) : $val;
                $edit[$drupal_field_parts[0]][LANGUAGE_NONE][0]['value'] = $val;
              }
            }
            try {
              drupal_alter('gigya_raas_update_user', $edit, $user, $gigya_account);
              user_save($user, $edit);
              if (!empty($p2_fields)) {
                foreach ($p2_fields as $raas_field => $p2field) {
                  $parts = explode('::', $p2field);
                  $raas_field_parts = explode(".", $raas_field);
                  $val = gigya_get_nested_value($gigya_account, $raas_field_parts);
                  $val = drupal_strlen($val) > $parts[3] ? drupal_substr($val, 0, $parts[3]) : $val;
                  $bundles[$parts[1]][$parts[2]] = $val;
                }
                $profs = profile2_load_by_user($user);
                foreach ($bundles as $profile => $field) {
                  if (isset($profs[$profile])) {
                    $prof = $profs[$profile];
                  }
                  else {
                    $prof = profile2_create(array('type' => $profile, 'uid' => $user->uid));
                  }
                  foreach ($field as $p2_field => $val) {
                    $prof->{$p2_field}[LANGUAGE_NONE][0]['value'] = $val;
                  }
                  drupal_alter('gigya_raas_update_profile2', $prof, $gigya_account);
                  profile2_save($prof);
                }
              }
            } catch (Exception $e) {
              session_destroy();
              $msg = t("Oops! Something went wrong during your login process. Please try to login again.");
              _gigya_set_logout_cookie();
              $commands[] = ajax_command_alert($msg);
              $commands[] = ctools_ajax_command_reload();
              return array('#type' => 'ajax', '#commands' => $commands);
            }
          }
          else {
            /* If this user is not the primary user account in gigya we
            disable the account
            (we don't want two different users with the same email) */
            _disable_gigya_account($parms['UID']);
            watchdog('gigya', 'User tried to create a new account with an existing email. Please enable social link account in your RaaS policies. For more info, please refer to: http://developers.gigya.com/015_Partners/030_CMS_and_Ecommerce_Platforms/020_Drupal/010_RaaS#Gigya_Configuration', NULL, WATCHDOG_NOTICE);
            $msg = t('We found your email in our system.<br />Please use your existing account to login to the site, or create a new account using a different email address.');
            $commands[] = ctools_modal_command_display('Email already exist in system', '<div class="gigya-error">' . $msg . '</div>');
            return array('#type' => 'ajax', '#commands' => $commands);
          }
        }
        // If the user does not exist register him/her.
        else {
          if (variable_get('raas_username_map', 'email') == 'username') {
            $uname = !empty($gigya_account['profile']['username']) ? $gigya_account['profile']['username'] : $gigya_account['profile']['firstName'];
            if (gigya_check_username_available($uname)) {
              $username = $uname;
            }
            else {
              // If user name is taken use first name if it is not empty.
              if (!empty($gigya_account['profile']['firstName']) && gigya_check_username_available($gigya_account['profile']['firstName'])) {
                $username = $gigya_account['profile']['firstName'];
              }
              else {
                // When all fails add unique id  to the username so we could register the user.
                $username = $uname . '_' . uniqid();
              }
            }
          }
          else {
            $username = $email;
          }
          $new_user = array(
            'name' => $username,
            'pass' => user_password(),
            'mail' => $email,
            'status' => 1,
            'init' => $email,
          );
          $additional_user_fields = variable_get('gigya_raas_extra_mappings', array());
          // Check for profile2 module.
          if (module_exists("profile2")) {
            $p2_fields = gigya_remove_p2_fields($additional_user_fields, TRUE);
          }
          else {
            gigya_remove_p2_fields($additional_user_fields, FALSE);
          }
          if (!empty($additional_user_fields)) {
            foreach ($additional_user_fields as $raas_field => $drupal_field) {
              $raas_field_parts = explode(".", $raas_field);
              $drupal_field_parts = explode("::", $drupal_field);
              $val = gigya_get_nested_value($gigya_account, $raas_field_parts);
              $val = drupal_strlen($val) > $drupal_field_parts[1] ? drupal_substr($val, 0, $drupal_field_parts[1]) : $val;
              $new_user[$drupal_field_parts[0]][LANGUAGE_NONE][0]['value'] = $val;
            }
          }
          /* Allow other modules to modify the data before user
          is created in drupal database. */
          drupal_alter('gigya_raas_create_user', $new_user, $gigya_account);
          global $user;
          global $_gigya_raas_login;
          $_gigya_raas_login = TRUE;
          try {
            $user = user_save(NULL, $new_user);
            if (!empty($p2_fields)) {
              foreach ($p2_fields as $raas_field => $p2field) {
                $parts = explode("::", $p2field);
                $raas_field_parts = explode(".", $raas_field);
                $val = gigya_get_nested_value($gigya_account, $raas_field_parts);
                $val = drupal_strlen($val) > $parts[3] ? drupal_substr($val, 0, $parts[3]) : $val;
                $bundles[$parts[1]][$p2field] = $val;
              }
              foreach ($bundles as $profile => $field) {
                $prof = profile2_create(array('type' => $profile, 'uid' => $user->uid));
                foreach ($field as $p2_field => $val) {
                  $prof->{$p2_field}[LANGUAGE_NONE][0]['value'] = $val;
                }
                drupal_alter('gigya_raas_create_profile2', $prof, $gigya_account);
                profile2_save($prof);
              }
            }
          } catch (Exception $e) {
            session_destroy();
            $msg = t("Oops! Something went wrong during your registration process. You are registered to the site but
            not logged-in. Please try to login again.");
            _gigya_set_logout_cookie();
            $commands[] = ajax_command_alert($msg);
            $commands[] = ctools_ajax_command_reload();
            return array('#type' => 'ajax', '#commands' => $commands);

          }
          $_SESSION['gigya_raas_uid'] = $parms['UID'];
          user_login_finalize();
        }
        if ($user !== FALSE) {
          $commands[] = $sucess_command;
          return array('#type' => 'ajax', '#commands' => $commands);
        }
        else {
          watchdog('gigya-RaaS', "User UID=@uid logged to Gigya", array('@uid' => $parms['UID']), WATCHDOG_DEBUG);
          $msg = t("Oops! Something went wrong during your login/registration process. Please try to login/register again.");
          _gigya_set_logout_cookie();
          $commands[] = ajax_command_alert($msg);
          $commands[] = ctools_ajax_command_reload();
          watchdog('gigya-RaaS', 'There was a problem registering a user');
          return array('#type' => 'ajax', '#commands' => $commands);
        }
      }
      else {
        watchdog('gigya-RaaS', 'Invalid signature check apiKey and secret');
        _gigya_set_logout_cookie();
        $commands[] = ajax_command_alert(t('Gigya signature not valid.'));
        $commands[] = ctools_ajax_command_reload();
        return array('#type' => 'ajax', '#commands' => $commands);
      }
    }
  }
}

function gigya_check_username_available($username) {
  return !db_query("SELECT COUNT(*) FROM {users} WHERE name = :name;", array(':name' => $username))->fetchField();
}

/**
 * @param $fields Array user fields passed by reference
 * @param $return Boolean should we return the profile2 fields
 *
 * @return array profile2 fields
 */
function gigya_remove_p2_fields(&$fields, $return) {
  $p2_fields = array();
  foreach ($fields as $raas_field => $drupal_field) {
    if (strpos($drupal_field, 'p2::') === 0) {
      if ($return) {
        $p2_fields[$raas_field] = $drupal_field;
      }
      unset($fields[$raas_field]);
    }
  }
  if ($return) {
    return $p2_fields;
  }
}

/**
 * Wrapper for the Gigya Javascript userInfo function.
 *
 * @param object $account
 *   The user object.
 *
 * @return string
 *   The user info from Gigya.
 */
function gigya_get_user($account) {
  $title = isset($account->title) ? $account->title : $account->name;
  drupal_set_title(check_plain($title));

  // Add the onload functions.
  $behavior_js = 'Drupal.behaviors.gigyaGetUserInfo = { attach: function(context, settings) { gigya.services.socialize.getUserInfo(Drupal.settings.gigya.conf, {callback:Drupal.gigya.getUserInfoCallback}); }}';
  drupal_add_js($behavior_js, array('type' => 'inline', 'scope' => JS_DEFAULT));

  $userinfo = '<div id="userinfo"></div>';
  return $userinfo;
}

/**
 * A helper method to xss filter arrays.
 *
 * @param array $array
 *   The array to filter.
 */
function gigya_filter_xss_array(&$array) {
  array_walk_recursive($array, '_gigya_filter_xss');
}

/**
 * Helper to filter items passed from array_walk_recursive().
 *
 * @param string $item
 *   The array value.
 * @param string|int $key
 *   The array key.
 */
function _gigya_filter_xss(&$item, $key) {
  $item = filter_xss($item);
}


/**
 * AJAX registering callback.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   From state.
 *
 * @return array
 *   An array of ajax commands.
 */
function gigya_register_ajax($form, $form_state) {
  ctools_include('ajax');
  ctools_include('modal');
  ctools_add_js('ajax-responder');
  drupal_process_form('user_register_form', $form, $form_state);
  $commands[] = ctools_modal_command_dismiss();
  $dest = variable_get('gigya_login_uiconfig_urlredirect', '');
  if (!empty($dest)) {
    $commands[] = ctools_ajax_command_redirect($dest);
  }
  else {
    $commands[] = ctools_ajax_command_reload();
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

function gigya_raas_profile_edit_ajax() {
  global $user;
  $gigya_profile = $_POST;
  $additional_user_fields = variable_get('gigya_raas_extra_mappings', array());
  if (!empty($additional_user_fields)) {
    if (module_exists("profile2")) {
      $p2_fields = gigya_remove_p2_fields($additional_user_fields, TRUE);
    }
    else {
      gigya_remove_p2_fields($additional_user_fields, FALSE);
    }
    foreach ($additional_user_fields as $raas_field => $drupal_field) {
      $raas_field_parts = explode(".", $raas_field);
      if (isset($raas_field_parts[0]) && $raas_field_parts[0] == 'profile') {
        array_shift($raas_field_parts);
      }
      else {
        continue;
      }
      $drupal_field_parts = explode("::", $drupal_field);
      $val = gigya_get_nested_value($gigya_profile, $raas_field_parts);
      $val = drupal_strlen($val) > $drupal_field_parts[1] ? drupal_substr($val, 0, $drupal_field_parts[1]) : $val;
      $edit[$drupal_field_parts[0]][LANGUAGE_NONE][0]['value'] = $val;
    }
    user_save($user, $edit);
    if (!empty($p2_fields)) {
      foreach ($p2_fields as $raas_field => $p2field) {
        $parts = explode('::', $p2field);
        $raas_field_parts = explode(".", $raas_field);
        if (isset($raas_field_parts[0]) && $raas_field_parts[0] == 'profile') {
          array_shift($raas_field_parts);
        }
        else {
          continue;
        }
        $val = gigya_get_nested_value($gigya_profile, $raas_field_parts);
        $val = drupal_strlen($val) > $parts[3] ? drupal_substr($val, 0, $parts[3]) : $val;
        $bundles[$parts[1]][$parts[2]] = $val;
      }
      $profs = profile2_load_by_user($user);
      foreach ($bundles as $profile => $field) {
        if (isset($profs[$profile])) {
          $prof = $profs[$profile];
        }
        else {
          $prof = profile2_create(array('type' => $profile, 'uid' => $user->uid));
        }
        foreach ($field as $p2_field => $val) {
          $prof->{$p2_field}[LANGUAGE_NONE][0]['value'] = $val;
        }
        profile2_save($prof);
      }
    }
  }
}
