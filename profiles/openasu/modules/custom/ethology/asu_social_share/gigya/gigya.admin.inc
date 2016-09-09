<?php

/**
 * @file
 * Provides the administration settings for the Gigya module.
 */


/**
 * Form builder for the Gigya keys form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The Gigya administration form.
 */
function gigya_admin_keys_form($form, &$form_state) {
  $def_val_string = "!!!!!!!!!!!!!!!!!!!!!!!!!!";

  //In form submit the message is show 2 times, we are disable it here.
  $msg = drupal_get_messages('error', false);
  if (isset($msg['error'])) {
    if (array_search(t("Note that changing encrypt machine name will require to insert secret site/application key."), $msg['error']) === false) {
      drupal_set_message(t("Note that changing encrypt machine name will require to insert secret site/application key."), 'error');
    }
  }
  else {
    drupal_set_message(t("Note that changing encrypt machine name will require to insert secret site/application key."), 'error');
  }


  include_once DRUPAL_ROOT . '/' . 'modules/user/user.pages.inc';
  module_load_include('inc', 'gigya');
  $form = array();
  $form['#attached']['js'] = array(drupal_get_path('module', 'gigya') . '/js/gigya.admin.behaviors.js');
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'gigya') . '/css/gigya_admin.css',
  );
  $form['keys'] = array(
    '#type' => 'fieldset',
    '#title' => t('Gigya Socialize keys'),
    '#description' => t('The Gigya keys required for using Gigya service, may be obtained from the !Dashboard page of Gigya\'s Admin Console site.', array(
        '!Dashboard' => l(t('Dashboard'), 'https://console.gigya.com/Site/partners/Dashboard.aspx', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        )
      )
    ),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => -400,
  );


  if (user_access('gigya_major_admin')) {
    $active = array('api' => t('Gigya secret key'), 'app' => t('Gigya Application key'));
    $form['keys']['gigya_access_mode'] = array(
      '#type' => 'radios',
      '#title' => t('Access mode'),
      '#default_value' => variable_get('gigya_access_mode', 'api'),
      '#options' => $active,
      '#weight' => -400,
    );
  }

  $form['keys']['gigya_APIKey'] = array(
    '#type' => 'textfield',
    '#title' => t('Gigya API Key'),
    '#description' => t('Specify the Gigya API key for this domain'),
    '#default_value' => variable_get('gigya_APIKey', ''),
    '#required' => TRUE,
    '#weight' => -300,
  );

  if (!user_access('gigya_major_admin')) {
    $form['keys']['gigya_APIKey']['#description'] = t('<p>Specify the Gigya API key for this domain </p><p>The secret key can only be accessed by authorized users</p>');
  }

  // show the secret key only to users with sufficient permissions
  if (user_access('gigya_major_admin')) {

    $access_key = gigya_get_secret_key();
    $description = t('Specify the Gigya Secret (Base64 encoded) key for this domain');
    if (strlen($access_key) > 0) {
      
      $description .= ", current key first and last letters are " . substr($access_key, 0, 2) . "****" . substr($access_key, strlen($access_key) - 2, 2);
      $def_val = $def_val_string;
    }
    else {
      $def_val = "";
    }

    $form['keys']['gigya_SecretKey'] = array(
      '#type' => 'password',
      '#title' => t('Gigya Secret Key'),
      '#description' => $description,
      //Default value do not work with password field, so we use attributes
      '#attributes' => array('value' => $def_val),
      '#states' => array(
        'visible' => array(
          ':input[name="gigya_access_mode"]' => array('value' => 'api'),
        ),
        'required' => array(
          ':input[name="gigya_access_mode"]' => array('value' => 'api'),
        ),
      ),
      '#weight' => -200


    );

  }

  $form['keys']['gigya_application_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Gigya Application Key'),
    '#description' => t('Specify the Gigya Application key for this domain'),
    '#default_value' => variable_get('gigya_application_key', ''),
    '#states' => array(
      'visible' => array(
        ':input[name="gigya_access_mode"]' => array('value' => 'app'),
      ),
      'required' => array(
        ':input[name="gigya_access_mode"]' => array('value' => 'app'),
      ),

    ),
    '#weight' => -199
  );

  if (user_access('gigya_major_admin')) {
    $app_access_key = gigya_get_app_secret_key();
    $description = t('Specify the Gigya Application Secret (Base64 encoded) key for this domain');
    if (strlen($app_access_key) > 0) {
      $description .= ", current key first and last letters are " . substr($app_access_key, 0, 2) . "****" . substr($app_access_key, strlen($app_access_key) - 2, 2);
      $def_val = $def_val_string;
    }
    else {
      $def_val = "";
    }

    $form['keys']['gigya_application_secret_key'] = array(
      '#type' => 'password',
      '#title' => t('Gigya Application Secret Key'),
      '#description' => $description,
      '#attributes' => array('value' => $def_val),
      '#states' => array(
        'visible' => array(
          ':input[name="gigya_access_mode"]' => array('value' => 'app'),
        ),
        'required' => array(
          ':input[name="gigya_access_mode"]' => array('value' => 'app'),
        ),

      ),

      '#weight' => -198
    );
  }

  if (function_exists('decrypt')) {
    if (user_access('gigya_major_admin')) {
      $options = array();
      $options['0'] = t("None");
      $configs = encrypt_get_configs();
      foreach ($configs as $k => $v) {
        $options[$k] = $v['label'];
      }
      $text = t("Encrypt Gigya secret (site | secret) key using encrypt module");
      $form['keys']['gigya_encrypt_config_title'] = array('#markup' => "<b>$text</b>",
        '#weight' => -197);
      $form['keys']['gigya_encrypt_config'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#title' => t('Encrypt machine name'),
        '#description' => t('To add/remove Encrypt configuration click !link', array('!link' => l(t('Here'), 'admin/config/system/encrypt/list'))),
        '#default_value' => variable_get('gigya_encrypt_config', '0'),
        '#weight' => -196
      );
    }
  }
  else {
    drupal_set_message(t('Encrypt module is required please install the module in this !link', array('!link' => l(t('Here'), 'https://www.drupal.org/project/encrypt', array('external' => TRUE)))));
  }
  $data_centers = array('us1.gigya.com' => 'US', 'eu1.gigya.com' => 'EU', 'au1.gigya.com' => 'AU', 'other' => "Other");
  $form['gigya_data_center'] = array(
    '#type' => 'select',
    '#title' => t('Data Center'),
    '#description' => t('Please select the Gigya data center in which your site is defined. To verify your site location contact your Gigya implementation manager.'),
    '#options' => $data_centers,
    '#default_value' => array_key_exists($ds = variable_get('gigya_data_center', 'us1.gigya.com'), $data_centers) ? $ds : 'other'
  );
  $form['gigya_other_data_center'] = array(
    "#type" => "hidden",
    "#default_value" => variable_get('gigya_other_data_center', ''),
    "#attributes" => array("id" => "gigya-other-data-center")
  );

  return system_settings_form($form);
}

/**
 * Implements hook_form_validate().
 *
 * Check if form API or Secret or Data-center were changed
 * If changed set new value, else retrieve default/DB value
 *
 */
function gigya_admin_keys_form_validate($form, &$form_state) {
  //Default values string used to check if the secrets keys changed.
  //Since we output garbage to the text field we use this string to check if the user change the key
  $has_error = FALSE;
  $encrypt_mode_update = FALSE;
  if ($form_state['values']['gigya_encrypt_config'] != $form['keys']['gigya_encrypt_config']['#default_value']) {
    $encrypt_mode = $form_state['values']['gigya_encrypt_config'];
    $encrypt_mode_update = TRUE;
  }
  else {
    $encrypt_mode = $form['keys']['gigya_encrypt_config']['#default_value'];
  }


  $def_val_string = "!!!!!!!!!!!!!!!!!!!!!!!!!!";
  $_validate = FALSE;
  // MODE was changed ?
  if ($form_state['values']['gigya_access_mode'] != $form['keys']['gigya_access_mode']['#default_value']) {
    $_mode = $form_state['values']['gigya_access_mode'];
    $_validate = TRUE;
  }
  else {
    $_mode = $form['keys']['gigya_access_mode']['#default_value'];
  }
  // API key was changed ?
  if ($form_state['values']['gigya_APIKey'] != $form['keys']['gigya_APIKey']['#default_value']) {
    $_apiKey = $form_state['values']['gigya_APIKey'];
    $_validate = TRUE;
  }
  else {
    $_apiKey = $form['keys']['gigya_APIKey']['#default_value'];
  }
  // secret key was changed ?
  if (isset($form_state['values']['gigya_SecretKey']) && $form_state['values']['gigya_SecretKey'] != $def_val_string) {
    $_secret = $form_state['values']['gigya_SecretKey'];
    $_validate = TRUE;
  }
  else {
    if ($encrypt_mode_update && $_mode == "api") {
      form_set_error('gigya_SecretKey', t("In order to change encrypt mode the Gigya Secret Key field is required."));
      $has_error = TRUE;
    }
    else {
      $_secret = gigya_get_secret_key();
      //Set the old value back.
      $form_state['values']['gigya_SecretKey'] = gigya_get_secret_key(NULL);
    }
  }

  // APP key was changed ?
  if ($form_state['values']['gigya_application_key'] != $form['keys']['gigya_application_key']['#default_value']) {
    $_appKey = $form_state['values']['gigya_application_key'];
    $_validate = TRUE;
  }
  else {
    $_appKey = $form['keys']['gigya_application_key']['#default_value'];
  }
  // APP secret key was changed ?
  if (isset($form_state['values']['gigya_application_secret_key']) && $form_state['values']['gigya_application_secret_key'] != $def_val_string) {
    $_appSecret = $form_state['values']['gigya_application_secret_key'];
    $_validate = TRUE;
  }
  else {
    //Set the old value back.
    if ($encrypt_mode_update && $_mode == "app") {
      form_set_error('gigya_application_secret_key', t("In order to change encrypt mode the Gigya Application Secret Key field is required."));
      $has_error = TRUE;
    }
    else {
      $form_state['values']['gigya_application_secret_key'] = gigya_get_app_secret_key(NULL);
      $_appSecret = gigya_get_app_secret_key();
    }
  }
  // Data Center was changed ?
  if ($form_state['values']['gigya_data_center'] != $form['gigya_data_center']['#default_value'] || $form_state['values']['gigya_other_data_center'] != $form['gigya_other_data_center']['#default_value']) {
    if ($form_state['values']['gigya_data_center'] == "other") {
      $_dataCenter = $form_state['input']['data-center-other'] . ".gigya.com";
      $form_state['values']['gigya_data_center'] = $_dataCenter;
      $form_state['values']['gigya_other_data_center'] = $_dataCenter;
    }
    else {
      $form_state['values']['gigya_other_data_center'] = "";
      $_dataCenter = $form_state['values']['gigya_data_center'];
    }
    $_validate = TRUE;
  }
  else {
    $_dataCenter = $form['gigya_data_center']['#default_value'];
  }
  if ($_validate && !$has_error) {

    if (!$_apiKey) {
      form_set_error('gigya_APIKey', t("Gigya API field is required."));
      $has_error = TRUE;
    }
    if ($_mode == "app") {
      if (!$_appSecret) {
        form_set_error('gigya_application_secret_key', t("Gigya Application Secret Key field is required."));
        $has_error = TRUE;
      }
      if (!$_appKey) {
        form_set_error('gigya_application_key', t("Gigya Application Key field is required."));
        $has_error = TRUE;
      }

    }
    else {
      if (!$_secret) {
        form_set_error('gigya_SecretKey', t("Gigya Secret Key field is required."));
        $has_error = TRUE;
      }
    }
    if ($has_error) {
      return;
    }

    $valid = gigya_validate($_mode, $_apiKey, $_secret, $_appKey, $_appSecret, $_dataCenter);
    if ($valid !== TRUE) {
      if (is_object($valid)) {
        $code = $valid->getErrorCode();
        $msg = $valid->getErrorMessage();
        form_set_error('gigya_APIKey', t("Gigya API error: {$code} - {$msg}."));
        form_set_error('keys', "For more information please refer to <a href=http://developers.gigya.com/037_API_reference/zz_Response_Codes_and_Errors target=_blank>Response_Codes_and_Errors page</a>");
        watchdog('gigya', 'Error setting API key, error code: @code - @msg', array('@code' => $code, '@msg' => $msg));
      }
      else {
        form_set_error('keys', t('Your API key or Secret key could not be validated. Please try again'));
        watchdog('gigya', 'Error setting API key, no error object returned', NULL, WATCHDOG_DEBUG);
      }
    }
    else {
      if ($encrypt_mode != "0") {
        $form_state['values']['gigya_SecretKey'] = gigya_encrypt_value($_secret, $encrypt_mode);
        $form_state['values']['gigya_application_secret_key'] = gigya_encrypt_value($_appSecret, $encrypt_mode);
      }
    }
  }

  if ($encrypt_mode_update && !$has_error) {
    global $user;
    $account = clone $user;
    $datestr = format_date(time(), 'custom', 'Y-m-d H:i:s');
    if ($encrypt_mode == "0") {
      watchdog('gigya', 'Encrypt module config has been disabled by @name date @date', array('@name' => $account->name, "@date" => $datestr), WATCHDOG_DEBUG);
    }
    else {
      watchdog('gigya', 'Encrypt module config has been enabled by @name date @date', array('@name' => $account->name, "@date" => $datestr), WATCHDOG_DEBUG);
    }
  }
}

/**
 * Form builder for the Gigya administration form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   The Gigya administration form.
 */
function gigya_admin_form($form, &$form_state) {
  $def_val_string = "!!!!!!!!!!!!!!!!!!!!!!!!!!";

  include_once DRUPAL_ROOT . '/' . 'modules/user/user.pages.inc';
  module_load_include('inc', 'gigya');
  $form = array();
  $form['#attached']['js'] = array(drupal_get_path('module', 'gigya') . '/js/gigya.admin.behaviors.js');
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'gigya') . '/css/gigya_admin.css',
  );

  $from['gigya_networks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Giya network providers'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['gigya_networks']['gigya_network_list'] = array(
    '#type' => 'textfield',
    '#title' => t('Providers'),
    '#size' => 60,
    '#maxlength' => 400,
    '#description' => t('Comma separated list of networks that would be included. For example: "Facebook, Twitter, Yahoo". <br />* means all networks. See list of available !providers',
      array(
        '!providers' => l(t('providers.'), 'http://developers.gigya.com/020_Client_API/020_Methods/Socialize.showLoginUI', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        ),
      )
    ),
    '#default_value' => variable_get('gigya_network_list', '*'),
  );
  $gigya_lang['auto'] = t("Drupal page language");

  $gigya_lang += gigya_get_languages();
  $form['gigya_language'] = array(
    '#type' => 'select',
    '#title' => t('Gigya Interface Language'),
    '#description' => t('Select the language to be used in Gigya screen-sets, or select “Drupal page language” to have each screen-set use the language set in Drupal for the containing page.'),
    '#options' => $gigya_lang,
    '#default_value' => variable_get('gigya_language', 'auto'),
  );

  $form['gigya_language_fallback'] = array(
    "#type" => "select",
    "#default_value" => variable_get('gigya_language_fallback', 'en'),
    '#title' => t('Drupal page language fallback'),
    '#options' => gigya_get_languages(),
    '#description' => t('Screen-sets will use this language if the Drupal page language is not offered by Gigya.'),
    '#states' => array(
      'visible' => array(
        ':input[name="gigya_language"]' => array('value' => 'auto'),
      ),
    ),
  );

  $form['gigya_social_analytics'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Google Social Analytics'),
    '#default_value' => variable_get('gigya_social_analytics', FALSE),
  );

  $form['gigya_login_plugins_login'] = array(
    '#type' => 'select',
    '#title' => t('Login behavior'),
    '#description' => t('This parameter controls the behavior of connecting to social networks using one of Gigya\'s
    plugins while the current user is not logged in. !add_connections', array(
      '!add_connections' => l(t('Learn more in Add Connections without Logging in.'), 'http://developers.gigya.com/010_Developer_Guide/10_UM360/070_Connect#Add_Connections_without_Logging_in',
        array(
          'external' => TRUE,
          'attributes' => array('target' => '_blank')
        ))
    )),
    '#options' => array(
      'loginExistingUser' => t('Login existing user'),
      'alwaysLogin' => t('Always login'),
    ),
    '#default_value' => variable_get('gigya_login_plugins_login', 'loginExistingUser'),
  );


  $form['gigyaSessionControl'] = array('#type' => 'radios', '#title' => t('Session management - (Applies only to RaaS)'),
    '#description' => t('Which platform controls login sessions. If you select Drupal, you will not be able to use Gigya’s Single Sign-On (SSO).'),
    '#options' => array('gigya' => t('Gigya (best practice)'), 'drupal' => t('Drupal')), '#default_value' => variable_get('gigyaSessionControl', 'drupal'));


  $form['gigya_advanced_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Gigya advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );



  $extra_parms = variable_get('gigya_global_extra', array());
  $form['gigya_advanced_settings']['gigya_global_extra'] = array(
    '#type' => 'textarea',
    '#title' => t('Custom Global Conf'),
    '#rows' => 5,
    '#element_validate' => array('gigya_key_val_filed_validate'),
    '#description' => t('Enter valid !JSON object format. See list of available !parameters', array(
      '!parameters' => l(t('parameters'), 'http://developers.gigya.com/030_API_reference/010_Client_API/010_Objects/Conf_object', array(
          'external' => TRUE,
          'attributes' => array('target' => '_blank'),
        )
      ),
      '!JSON' => l(t('JSON'), 'http://json.org', array(
          'external' => TRUE,
          'attributes' => array('target' => '_blank'),
        )
      )
    )),
    '#default_value' => !empty($extra_parms) ? gigya_values_array_to_string($extra_parms) : '',
    '#attributes' => array('placeholder' => 'facebookExtraPermissions|rsvp_event,sms'),
  );
  $form['gigya_advanced_settings']['gigya_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Gigya debugging'),
    '#description' => t('Write Gigya API calls to <a href="@watchdog">Drupal Watchdog</a> log', array('@watchdog' => url('admin/reports/dblog'))),
    '#default_value' => variable_get('gigya_debug', FALSE),
  );
  return system_settings_form($form);
}


/**
 * LoginUI admin form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return mixed
 *   Returns login admin from.
 */
function gigya_login_admin_form($form, $form_state) {

  $form['gigya_login_mode'] = array(
    '#type' => 'radios',
    '#title' => t('User Management System'),
    '#options' => array(
      'drupal' => t('Drupal only'),
      'drupal_and_gigya' => t('Drupal + Social Login'),
      'gigya' => t('Social Login only'),
      'raas' => t('Registration-as-a-Service'),
    ),
    '#default_value' => variable_get('gigya_login_mode', 'drupal_and_gigya'),
    '#pre_render' => array('gigya_check_raas'),
  );

  // Social Login settings.
  $form['gigya_social_login'] = array(
    '#type' => 'fieldset',
    '#title' => t('Social Login Settings'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['gigya_social_login']['gigya_login_buttons_style'] = array(
    '#type' => 'select',
    '#title' => t('Button style'),
    '#options' => array(
      'standard' => t('Icons'),
      'fullLogo' => t('Full logos'),
      'fullLogoColored' => t('Full logos colored'),
      'signInWith' => t('Sign in with'),
    ),
    '#default_value' => variable_get('gigya_login_buttons_style', 'standard'),
  );
  $form['gigya_social_login']['gigya_login_uiconfig_urlredirect'] = array(
    '#type' => 'textfield',
    '#title' => t('URL redirect after login'),
    '#default_value' => variable_get('gigya_login_uiconfig_urlredirect', ''),
    '#description' => t('Specify a URL to which to redirect users to after login. By default the user stays on the
     original page from which the login process started, and the page is reloaded.
     Please, do not use a beginning or ending slash in the URL'),
  );
  $form['gigya_social_login']['gigya_login_hide_title'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide title'),
    '#description' => t('Hide login block title'),
    '#default_value' => variable_get('gigya_login_hide_title', FALSE),
  );
  $form['gigya_social_login']['gigya_login_uiconfig_terms'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show terms link'),
    '#description' => t('Display the Gigya terms of service link'),
    '#default_value' => variable_get('gigya_login_uiconfig_terms', FALSE),
  );
  $form['gigya_social_login']['gigya_login_plugin_size'] = array(
    '#type' => 'checkbox',
    '#title' => t('Set custom size for plugin'),
    '#default_value' => variable_get('gigya_login_plugin_size', FALSE),
  );
  $form['gigya_social_login']['gigya_login_plugin_width'] = array(
    '#prefix' => '<div class="height-with">',
    '#type' => 'textfield',
    '#title' => t('W:'),
    '#size' => 5,
    '#states' => array(
      'visible' => array(
        '#edit-gigya-login-plugin-size' => array('checked' => TRUE),
      ),
    ),
    '#default_value' => variable_get('gigya_login_plugin_width', GIGYA_DEFAULT_LOGINUI_WIDTH),
  );
  $form['gigya_social_login']['gigya_login_plugin_height'] = array(
    '#type' => 'textfield',
    '#title' => t('H:'),
    '#size' => 5,
    '#states' => array(
      'visible' => array(
        '#edit-gigya-login-plugin-size' => array('checked' => TRUE),
      ),
    ),
    '#default_value' => variable_get('gigya_login_plugin_height', GIGYA_DEFAULT_LOGINUI_HEIGHT),
    '#suffix' => '</div>',
  );
  // RaaS settings.
  $form['gigya_ras'] = array(
    '#type' => 'fieldset',
    '#title' => t('Registration-as-a-Service Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        ':input[name="gigya_login_mode"]' => array('value' => 'raas'),
      ),
    ),
  );
  $form['gigya_ras']['message'] = array(
    '#markup' => t("Please make sure to initially configure RaaS in Gigya's site. Go to the !Builder page
     after logging in to Gigya's site. The page presents the list of predefined default screen-sets, each has an ID.
     Click on the \"Visual Editor\" link next to a screen-set that you wish to use. This will open the !Editor window.
      You can modify the screens, or just hit the \"Save\" button to activate it. Please make sure that the screen-sets
       IDs that are defined below match the IDs of the screen-sets you have configured in the !Builder page.",
      array(
        '!Builder' => l(t('UI Builder'),
          'https://platform.gigya.com/site/partners/Settings.aspx#cmd%3DUserManagement360.ScreenSets',
          array('external' => TRUE, 'attributes' => array('target' => '_blank'))
        ),
        '!Editor' => l(t('Visual Editor'), 'http://developers.gigya.com/010_Developer_Guide/10_UM360/040_Raas/020_UI_Builder#Visual_Editor',
          array('external' => TRUE, 'attributes' => array('target' => '_blank'))
        ),
      )
    ),
  );
  // Login registration screen set.
  $form['gigya_ras']['login_screen_set'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login/Registration Screen Sets'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['gigya_ras']['login_screen_set']['web_screen_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Web Screen Set ID'),
    '#size' => 30,
    '#default_value' => variable_get('web_screen_id', 'Default-RegistrationLogin'),
  );
  $form['gigya_ras']['login_screen_set']['mobile_screen_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Mobile Screen Set ID'),
    '#size' => 30,
    '#default_value' => variable_get('mobile_screen_id', 'DefaultMobile-RegistrationLogin'),
  );
  $form['gigya_ras']['login_screen_set']['login_screen_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Login Screen ID'),
    '#size' => 30,
    '#default_value' => variable_get('login_screen_id', 'gigya-login-screen'),
  );
  $form['gigya_ras']['login_screen_set']['register_screen_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Register Screen ID'),
    '#size' => 30,
    '#default_value' => variable_get('register_screen_id', 'gigya-register-screen'),
  );
  // Profile settings.
  $form['gigya_ras']['profile_screen_set'] = array(
    '#type' => 'fieldset',
    '#title' => t('Profile Screen Sets'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['gigya_ras']['profile_screen_set']['profile_web_screen_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Web Screen Set ID'),
    '#size' => 30,
    '#default_value' => variable_get('profile_web_screen_id', 'Default-ProfileUpdate'),
  );
  $form['gigya_ras']['profile_screen_set']['profile_mobile_screen_id'] = array(
    '#type' => 'textfield',
    '#title' => t('mobile Screen Set ID'),
    '#size' => 30,
    '#default_value' => variable_get('profile_mobile_screen_id', 'DefaultMobile-ProfileUpdate'),
  );

  // Links and labels.
  $form['gigya_ras']['labels_links'] = array(
    '#type' => 'fieldset',
    '#title' => t("Links' Labels"),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['gigya_ras']['labels_links']['message'] = array(
    '#markup' => t('Specify the labels of the links that invoke the screen-sets.'),
  );
  $form['gigya_ras']['labels_links']['raas_login_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Login'),
    '#size' => 30,
    '#default_value' => variable_get('raas_login_label', 'Login'),
  );
  $form['gigya_ras']['labels_links']['raas_register_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Register'),
    '#size' => 30,
    '#default_value' => variable_get('raas_register_label', 'Register'),
  );
  $form['gigya_ras']['labels_links']['raas_profile_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Profile'),
    '#size' => 30,
    '#default_value' => variable_get('raas_profile_label', 'Profile'),
  );
  $form['gigya_login_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced showLoginUI settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 1,
  );
  $form['gigya_login_advanced']['gigya_login_uiconfig_containerID'] = array(
    '#type' => 'textfield',
    '#title' => t('showLoginUI container ID'),
    '#default_value' => variable_get('gigya_login_uiconfig_containerID', GIGYA_DEFAULT_LOGINUI_CONTAINERID),
    '#description' => t('Specify the DIV ID in which to present the Gigya\'s !Login_Plugin', array(
        '!Login_Plugin' =>
          l(t('Login Plugin'), 'http://developers.gigya.com/020_Client_API/010_Socialize/Socialize.showLoginUI',
            array(
              'external' => TRUE,
              'attributes' => array('target' => '_blank'),
            )
          )
      )
    ),
    '#required' => TRUE,
  );
  $login_extra_parms = variable_get('gigya_login_extra', array());
  $form['gigya_login_advanced']['gigya_login_extra'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced showLoginUI settings'),
    '#rows' => 5,
    '#element_validate' => array('gigya_key_val_filed_validate'),
    '#description' => t('Enter valid !JSON object format. See list of available !parameters',
      array(
        '!parameters' => l(t('parameters'), 'http://developers.gigya.com/030_Gigya_Socialize_API_2.0/030_API_reference/010_Client_API_%28JavaScript%29/Social_service/Socialize.showLoginUI',
          array('external' => TRUE, 'attributes' => array('target' => '_blank'))
        ),
        '!JSON' => l(t('JSON'), 'http://json.org', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        )
      )
    ),
    '#default_value' => !empty($login_extra_parms) ? gigya_values_array_to_string($login_extra_parms) : '',
  );
  // General RaaS settings
  $form['gigya_ras']['general'] = array(
    '#type' => 'fieldset',
    '#title' => t("General RaaS settings"),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['gigya_ras']['general']['raas_redirect_url'] = array(
    '#type' => 'textfield',
    '#required' => FALSE,
    '#title' => t('Post Login Redirect'),
    '#description' => t('Define a URL to which to redirect users after logging-in to the site.'),
    '#default_value' => variable_get('raas_redirect_url', ''),
  );
  $form['gigya_ras']['general']['raas_username_map'] = array(
    '#type' => 'select',
    '#required' => FALSE,
    '#title' => t('Map Drupal username field'),
    '#description' => t('Drupal requires a unique username field. By default the module sets the field with the user\'s
    email . If you select "RaaS username field" please make sure to define the username field in RaaS to be required
    and unique . Learn more !here . ', array(
        '!here' => l(t('here'), 'http://developers.gigya.com/015_Partners/030_CMS_and_Ecommerce_Platforms/020_Drupal/Using_RaaS_with_Drupal#Gigya_Configuration',
          array('external' => TRUE, 'attributes' => array('target' => '_blank'))
        )
      )
    ),
    '#default_value' => variable_get('raas_username_map', 'email'),
    '#options' => array('email' => t('RaaS email address'), 'username' => t('RaaS username field')),
  );
  $form['gigya_ras']['gigya_raas_mappings'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#title' => t('Mapping RaaS Fields to Drupal Fields'),
    '#description' => t('Define which fields from RaaS (= Sources) map to which fields in Drupal (= Targets).
The mapped target fields will be updated each time the user logs in or updates his profile.'
    ),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $gigya_fields = gigya_get_raas_fields();
  $drupal_fields = _get_drupal_user_fields();
  $form['gigya_ras']['gigya_raas_mappings']['label'] = array(
    '#type' => 'item',
    '#title' => t('Add a mapping pair'),
  );
  $form['gigya_ras']['gigya_raas_mappings']['source'] = array(
    '#prefix' => '<div class="raas-mappings-add">',
    '#type' => 'select',
    '#title' => t('Source (Raas)'),
    '#attributes' => array('class' => array('gigya-t-cell')),
    '#empty_option' => t('- Select -'),
    '#options' => $gigya_fields,
  );
  $form['gigya_ras']['gigya_raas_mappings']['target'] = array(
    '#type' => 'select',
    '#title' => t('Target (Drupal)'),
    '#attributes' => array('class' => array('gigya-t-cell')),
    '#empty_option' => t('- Select -'),
    '#options' => $drupal_fields,
  );
  $form['gigya_ras']['gigya_raas_mappings']['raas_map_add'] = array(
    '#prefix' => '<div class="raas-add-button">',
    '#suffix' => '</div></div>',
    '#type' => 'submit',
    '#value' => t('Add'),
    '#ajax' => array(
      'callback' => 'gigya_raas_add_map',
      'wrapper' => 'raas-mapping-tbl-wrap',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $form['gigya_ras']['gigya_raas_mappings']['label_tbl'] = array(
    '#prefix' => '<div class="mapping-table">',
    '#type' => 'item',
    '#title' => t('Mapped fields'),
    '#markup' => '<p>' . t('To remove mappings, select the checkboxs in rows to remove and then click "Save configuration" button') . '</p>',
  );
  $form['gigya_ras']['gigya_raas_mappings']['gigya_raas_extra_mappings'] = gigya_build_raas_map_tbl();
  // End RaaS

  // ConnectUI.
  $form['gigya_connect_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced showAddConnectionsUI settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 2,
  );
  $form['gigya_connect_advanced']['gigya_connect_uiconfig_containerID'] = array(
    '#type' => 'textfield',
    '#title' => t('showAddConnectionsUI container ID:'),
    '#default_value' => variable_get('gigya_connect_uiconfig_containerID', GIGYA_DEFAULT_CONNECTUI_CONTAINERID),
    '#description' => t('Specify the DIV ID in which to present the Gigya\'s !Add_Connection_Plugin',
      array(
        '!Add_Connection_Plugin' => l(t('Add Connection Plugin'), 'http://developers.gigya.com/020_Client_API/010_Socialize/socialize.showAddConnectionsUI',
          array('external' => TRUE, 'attributes' => array('target' => '_blank'))
        ),
      )),
  );
  $connect_extra_parms = variable_get('gigya_connect_extra', array());
  $form['gigya_connect_advanced']['gigya_connect_extra'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced showAddConnectionsUI settings'),
    '#rows' => 5,
    '#element_validate' => array('gigya_key_val_filed_validate'),
    '#description' => t('Enter valid !JSON object format. See list of available !parameters',
      array(
        '!parameters' => l(t('parameters'), 'http://developers.gigya.com/020_Client_API/020_Methods/socialize.showAddConnectionsUI',
          array('external' => TRUE, 'attributes' => array('target' => '_blank'))
        ),
        '!JSON' => l(t('JSON'), 'http://json.org', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        )
      )
    ),
    '#default_value' => !empty($connect_extra_parms) ? gigya_values_array_to_string($connect_extra_parms) : '',
  );

  $form['#attached']['js'] = array(drupal_get_path('module', 'gigya') . '/js/gigya.admin.behaviors.js');
  $form['#attached']['css'] = array(drupal_get_path('module', 'gigya') . '/css/gigya_admin.css');
  $form['#submit'] = array('gigya_mapping_remove');
  return system_settings_form($form);
}

function gigya_login_admin_form_validate($form, $form_state) {
  if ($form_state['clicked_button']['#value'] == 'Add') {
    $vals = $form_state['values'];
    if (empty($vals['gigya_raas_mappings']['source']) || empty($vals['gigya_raas_mappings']['target'])) {
      form_set_error('gigya_raas_mappings', t('Both source and target are required'));
    }
  }
}

function _get_drupal_user_fields() {
  $cache = cache_get("gigya_drupal_fields", "cache");
  if ($cache !== FALSE) {
    return $cache->data;
  }
  $drupal_user_fields = array();
  $valid_fields = array("text", "varchar", "char", "blob");
  $user_info = entity_get_property_info('user');
  if (!empty($user_info['bundles']) && is_array($user_info)) {
    $cust_fields = is_array($user_info['bundles']['user']['properties']) ? $user_info['bundles']['user']['properties'] : array();
    $base_fields = is_array($user_info['properties']) ? $user_info['properties'] : array();
    $remove = array('uid', 'name', 'mail', 'status');
    if (!empty($base_fields)) {
      foreach ($remove as $fname) {
        unset($base_fields[$fname]);
      }
    }
    foreach ($base_fields as $filed_name => $field_info) {
      if (!empty($field_info['type']) && in_array($field_info['type'], $valid_fields)) {
        $drupal_user_fields['Base Fields'][$filed_name . "::255"] = $field_info['label'];
      }
    }
    foreach ($cust_fields as $filed_name => $field_info) {
      if (!empty($field_info['type']) && in_array($field_info['type'], $valid_fields)) {
        $len = _gigya_get_field_length($filed_name);
        $drupal_user_fields['Added Fields'][$filed_name . "::" . $len] = $field_info['label'];
      }
    }
    if (module_exists("profile2")) {
      $profile2_fields = _gigya_get_profile2_fields();
      $drupal_user_fields['Profile2 fields'] = $profile2_fields;
    }
  }
  cache_set("gigya_drupal_fields", $drupal_user_fields, "cache", CACHE_TEMPORARY);
  return $drupal_user_fields;
}

function _gigya_get_field_length($field_name) {
  $info = field_read_field($field_name);
  if (!empty($info)) {
    if (isset($info['columns']['value']['length'])) {
      return $info['columns']['value']['length'];
    }
    elseif (isset($info['columns']['value']['size'])) {
      switch ($info['columns']['value']['size']) {
        case "big":
          return "4294967296";
          break;
        case "tiny":
          return "255";
          break;
        case "small":
          return "255";
          break;
        case "medium":
          return "16777216";
          break;
        case "normal":
          return "16384";
      }
    }
  }
  return FALSE;
}

function _gigya_get_profile2_fields() {
  $valid_fields = array("text", "varchar", "char", "blob");
  $fields = array();
  $profile2_info = entity_get_property_info("profile2");
  if (!empty($profile2_info['bundles']) && is_array($profile2_info)) {
    foreach ($profile2_info['bundles'] as $bundle_name => $bundle) {
      foreach ($bundle['properties'] as $fld_name => $fld_properties) {
        if (!empty($fld_properties['type']) && in_array($fld_properties['type'], $valid_fields)) {
          $len = _gigya_get_field_length($fld_name);
          $fields[$bundle_name]['p2::' . $bundle_name . '::' . $fld_name . "::" . $len] = $fld_properties['label'];
        }
      }
    }
  }
  return $fields;
}

function gigya_mapping_remove($form, &$form_state) {
  if ($form_state['clicked_button']['#value'] != 'Add') {
    $vals = $form_state['values']['gigya_raas_mappings']['gigya_raas_extra_mappings'];
    $mappings = variable_get('gigya_raas_extra_mappings', array());
    if (!empty($mappings)) {
      foreach ($vals as $src => $target) {
        if ($src === $target) {
          unset($mappings[$src]);
        }
        if (empty($src)) {
          unset($mappings[$src]);
        }
      }
    }
    variable_set('gigya_raas_extra_mappings', $mappings);
  }
}

function gigya_build_raas_map_tbl() {
  $header = array(
    1 => t('Source (RaaS)'),
    2 => t('Target (Drupal)'),
  );
  $mappings = variable_get('gigya_raas_extra_mappings', array());
  $tbl_opts = array();
  if (!empty($mappings)) {
    foreach ($mappings as $src => $target) {
      $tbl_opts[$src] = array(
        1 => $src,
        2 => $target
      );
    }
  }
  return array(
    '#prefix' => '<div id="raas-mapping-tbl-wrap">',
    '#suffix' => '</div></div>',
    '#type' => 'tableselect',
    '#header' => $header,
    '#multiple' => TRUE,
    '#js_select' => TRUE,
    '#empty' => t('No items'),
    '#options' => $tbl_opts,
    '#theme' => 'gigya_raas_mappings_tbl',
    '#attributes' => array('id' => 'raas-mapping-tbl')
  );

}

function theme_gigya_raas_mappings_tbl($variables) {
  $element = $variables['element'];
  $rows = array();
  $header = $element['#header'];
  if (!empty($element['#options'])) {
    // Generate a table row for each selectable item in #options.
    foreach (element_children($element) as $key) {
      $row = array();

      $row['data'] = array();
      if (isset($element['#options'][$key]['#attributes'])) {
        $row += $element['#options'][$key]['#attributes'];
      }
      // Render the checkbox / radio element.
      $row['data'][] = drupal_render($element[$key]);

      // As theme_table only maps header and row columns by order, create the
      // correct order by iterating over the header fields.
      foreach ($element['#header'] as $fieldname => $title) {
        $row['data'][] = $element['#options'][$key][$fieldname];
      }
      $rows[] = $row;
    }
    // Add an empty header or a "Select all" checkbox to provide room for the
    // checkboxes/radios in the first table column.
    if ($element['#js_select']) {
      // Add a "Select all" checkbox.
      drupal_add_js('misc/tableselect.js');
      array_unshift($header, t('Remove'));
    }
    else {
      // Add an empty header when radio buttons are displayed or a "Select all"
      // checkbox is not desired.
      array_unshift($header, '');
    }
  }
  return theme('table', array(
    'header' => $header,
    'rows' => $rows,
    'empty' => $element['#empty'],
    'attributes' => $element['#attributes']
  ));
}

function gigya_raas_add_map($form, &$form_state) {
  $errors = form_get_errors();
  if (empty($errors)) {
    $vals = $form_state['values'];
    $mappings = variable_get('gigya_raas_extra_mappings', array());
    $mappings[$vals['gigya_raas_mappings']['source']] = $vals['gigya_raas_mappings']['target'];
    variable_set('gigya_raas_extra_mappings', $mappings);
  }
  $form = drupal_rebuild_form('gigya_login_admin_form', $form_state, $form);
  return $form['gigya_ras']['gigya_raas_mappings']['gigya_raas_extra_mappings'];
}



/**
 * Form builder for the Gigya sharebar administration form.
 *
 * @return array
 *   The Gigya sharebar administration form.
 */
function gigya_sharebar_settings_form() {
  $form['gigya_share_message'] = array(
    '#markup' => t('To position a Gigya Share Bar plugin, place a "Gigya Share Bar" field via the "Structure"/"Content types" menu'),
    '#weight' => -50,
  );
  $form['gigya_share_global'] = array(
    '#type' => 'fieldset',
    '#title' => t('Sharing global configuration'),
    '#collapsible' => FALSE,
    '#weight' => -10,
  );
  $form['gigya_share_global']['gigya_share_container_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Container ID'),
    '#description' => t('The HTML DIV ID in which the Share Bar should be embedded.'),
    '#size' => 60,
    '#default_value' => variable_get('gigya_share_container_id', 'gigya-share'),
  );
  $form['gigya_share_global']['gigya_share_buttons'] = array(
    '#type' => 'textfield',
    '#title' => t('Share Buttons'),
    '#size' => 60,
    '#maxlength' => 400,
    '#default_value' => variable_get('gigya_share_buttons', GIGYA_DEFAULT_SHARE_BOTTONS),
    '#description' => t('Specify the list of share buttons that should be displayed on this plugin (comma separated).
    List of relevant values is available !here under the "shareButtons" parameter',
      array(
        '!here' => l(t('here'), 'http://developers.gigya.com/020_Client_API/020_Methods/socialize.showShareBarUI',
          array('external' => TRUE, 'attributes' => array('target' => '_blank'))
        ),
      )
    ),
  );
  $form['gigya_share_global']['gigya_share_layout'] = array(
    '#type' => 'select',
    '#title' => t('Share Bar layout'),
    '#options' => array(
      'horizontal' => t('Horizontal'),
      'vertical' => t('Vertical'),
    ),
    '#default_value' => variable_get('gigya_share_layout', 'horizontal'),
  );
  $form['gigya_share_global']['gigya_share_showcounts'] = array(
    '#type' => 'select',
    '#title' => t('Show counts'),
    '#description' => t('Where to display the share counts in relation to the share button'),
    '#options' => array(
      'right' => t('Right'),
      'top' => t('Top'),
      'none' => t('none'),
    ),
    '#default_value' => variable_get('gigya_share_showcounts', 'right'),
  );
  $form['gigya_share_global']['gigya_share_af_scope'] = array(
    '#type' => 'select',
    '#title' => t('Scope for publishing to Activity Feed'),
    '#description' => t('When publishing feed items, by default the feed items are published to social
     networks only and will not appear on the site\'s Activity Feed plugin. To change this behavior,
      you must change the publish scope to "Both".'
    ),
    '#options' => array(
      'external' => t('External'),
      'both' => t('Both'),
    ),
    '#default_value' => variable_get('gigya_share_af_scope', 'external'),
  );
  $form['gigya_share_global']['gigya_share_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Share title'),
    '#size' => 60,
    '#default_value' => variable_get('gigya_share_title', '[node:title]'),
  );
  $form['gigya_share_global']['gigya_share_desc'] = array(
    '#type' => 'textfield',
    '#title' => t('Default share description'),
    '#size' => 60,
    '#default_value' => variable_get('gigya_share_desc', '[node:summary]'),
  );
  $form['gigya_share_global']['gigya_share_link_back'] = array(
    '#type' => 'textfield',
    '#title' => t('Default linkback URL'),
    '#size' => 60,
    '#default_value' => variable_get('gigya_share_link_back', '[node:url:absolute]'),
  );
  $form['gigya_share_global']['gigya_share_image_behavior'] = array(
    '#type' => 'radios',
    '#title' => t('Image'),
    '#options' => array(
      'default' => t('Use image tag if exists, first image on post otherwise.'),
      'first' => t('First image on the post'),
      'url' => t('Specify an image URL'),
    ),
    '#default_value' => variable_get('gigya_share_image_behavior', 'default'),
    '#attributes' => array('class' => array('image-behv')),
  );
  $form['gigya_share_global']['gigya_share_image_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Default URL of the image to share'),
    '#size' => 20,
    '#states' => array(
      'visible' => array(
        '.image-behv' => array('value' => 'url'),
      ),
    ),
    '#default_value' => variable_get('gigya_share_image_url', ''),
  );
  $form['gigya_share_global']['gigya_share_short_url'] = array(
    '#type' => 'checkbox',
    '#title' => t('Share using short URLs'),
    '#default_value' => variable_get('gigya_share_short_url', FALSE),
  );
  $form['gigya_share_global']['gigya_share_tokens'] = array(
    '#type' => 'fieldset',
    '#title' => t('Token list'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['gigya_share_global']['gigya_advanced_sharing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Share Bar settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $adv_parmas = variable_get('gigya_share_advanced', '');
  $form['gigya_share_global']['gigya_advanced_sharing']['gigya_share_advanced'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced showShareBarUI settings'),
    '#element_validate' => array('gigya_key_val_filed_validate'),
    '#default_value' => !empty($adv_parmas) ? gigya_values_array_to_string($adv_parmas) : '',
    '#description' => t('Enter valid !JSON object format. See list of available !parameters', array(
        '!parameters' => l(t('parameters'), 'http://developers.gigya.com/020_Client_API/020_Methods/socialize.showShareBarUI', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        ),
        '!JSON' => l(t('JSON'), 'http://json.org', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        )
      )
    ),
  );
  $form['gigya_share_global']['gigya_share_tokens']['tokens_list'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('node'),
    '#global_types' => FALSE,
  );
  $form['gigya_action_sharing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Action sharing'),
  );
  $form['gigya_action_sharing']['gigya_rules_message'] = array(
    '#markup' => t('Gigya action sharing can be configured with !rules', array('!rules' => l(t('Rules'), 'admin/config/workflow/rules'))),
  );
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'gigya') . '/css/gigya_admin.css',
  );

  $form['#attached']['js'] = array(drupal_get_path('module', 'gigya') . '/js/gigya.admin.behaviors.js');
  return system_settings_form($form);
}

/**
 * Form builder for the Gigya comments administration form.
 *
 * @return array
 *   The Gigya comments administration form.
 */
function gigya_comments_settings_form() {
  $form['gigya_comments_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Gigya Comments'),
    '#default_value' => variable_get('gigya_comments_enabled', TRUE),
  );
  $form['gigya_comments_categoryid'] = array(
    '#type' => 'textfield',
    '#title' => t('Gigya Comments category ID'),
    '#default_value' => variable_get('gigya_comments_categoryid', ''),
    '#description' => t('The identifier of the Comments Category, as set up in the !setup page of Gigya\'s
     admin console site.', array(
      '!setup' => l(t('Comments Setup'), 'https://console.gigya.com/Site/partners/Settings.aspx#cmd%3DSettings.CommentsSetup',
        array(
          'external' => TRUE,
          'attributes' => array('target' => '_blank')
        ))
    )),
    '#attributes' => array('placeholder' => 'category1'),
  );
  $form['gigya_comments_container'] = array(
    '#type' => 'textfield',
    '#title' => t('Container ID'),
    '#size' => 30,
    '#description' => t('The container ID that the comments will be displayed in the default is "comments" (Drupal default)'),
    '#default_value' => variable_get('gigya_comments_container', 'comments'),
  );
  $form['gigya_comments_af_scope'] = array(
    '#type' => 'select',
    '#title' => t('Scope for publishing to Activity Feed'),
    '#description' => t('When publishing feed items, by default the feed items are published to social networks only and will not appear on the site\'s Activity Feed plugin. To change this behavior, you must change the publish scope to "Both".'),
    '#options' => array(
      'external' => t('External'),
      'both' => t('Both'),
    ),
    '#default_value' => variable_get('gigya_comments_af_scope', 'external'),
  );
  $form['gigya_comments_hide_drupal_comments'] = array(
    '#type' => 'checkbox',
    '#title' => t('Do not load Drupal comments'),
    '#description' => t("If checked only Gigya comments will be loaded and not Drupal comments. Note: this may harm the
    site's SEO as comments will not be indexed by search engines"),
    '#default_value' => variable_get('gigya_comments_hide_drupal_comments', TRUE),
  );

  $form['gigya_comments_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $comments_extra_parms = variable_get('gigya_comments_extra', array());
  $form['gigya_comments_advanced']['gigya_comments_extra'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced showCommentsUI settings'),
    '#rows' => 5,
    '#element_validate' => array('gigya_key_val_filed_validate'),
    '#description' => t('Enter valid !JSON object format. See list of available !parameters', array(
        '!parameters' => l(t('parameters'), 'http://developers.gigya.com/020_Client_API/030_Comments/comments.showCommentsUI', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        ),
        '!JSON' => l(t('JSON'), 'http://json.org', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        )
      )
    ),
    '#default_value' => !empty($comments_extra_parms) ? gigya_values_array_to_string($comments_extra_parms) : '',
  );

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'gigya') . '/css/gigya_admin.css',
  );
  $form['#attached']['js'] = array(drupal_get_path('module', 'gigya') . '/js/gigya.admin.behaviors.js');
  return system_settings_form($form);
}


/**
 * Reactions form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return mixed
 *   Reactions admin form.
 */
function gigya_resctions_settings_form($form, $form_state) {
  $form = array();
  $form['gigya_reaction_message'] = array(
    '#markup' => t('To position a Gigya Reactions plugin, place a "Gigya Reactions" field via the "Structure"/"Content types" menu') . '<br /><br />',
    '#weight' => -50,
  );
  $form['gigya_reactions_global'] = array(
    '#type' => 'fieldset',
    '#title' => t('Gigya reaction global settings'),
    '#collapsible' => FALSE,
  );
  $form['gigya_reactions_global']['gigya_reactions_container_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Container ID'),
    '#description' => t('The HTML DIV ID in which the Reactions Bar should be embedded.'),
    '#size' => 20,
    '#default_value' => variable_get('gigya_reactions_container_id', 'gigya-reactions'),
  );
  $form['gigya_reactions_global']['gigya_reactions_bar_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Bar ID'),
    '#size' => 20,
    '#default_value' => variable_get('gigya_reactions_bar_id', 'reactions-bar'),
  );
  $form['gigya_reactions_global']['gigya_reactions_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Reaction title'),
    '#size' => 60,
    '#default_value' => variable_get('gigya_reactions_title', '[node:title]'),
  );
  $form['gigya_reactions_global']['gigya_reactions_link_back'] = array(
    '#type' => 'textfield',
    '#title' => t('Default linkback URL'),
    '#size' => 60,
    '#default_value' => variable_get('gigya_reactions_title', '[node:url:absolute]'),
  );
  $form['gigya_reactions_global']['gigya_reactions_show_counts'] = array(
    '#type' => 'select',
    '#title' => t('Show counts'),
    '#options' => array(
      'right' => t('Right'),
      'top' => t('Top'),
      'none' => t('None'),
    ),
    '#description' => t('Where to display the reaction counts in relation to the reaction button.'),
    '#default_value' => variable_get('gigya_reactions_show_counts', 'right'),
  );
  $form['gigya_reactions_global']['gigya_reactions_layout'] = array(
    '#type' => 'select',
    '#title' => t('Layout'),
    '#options' => array(
      'horizontal' => t('Horizontal'),
      'vertical' => t('Vertical'),
    ),
    '#default_value' => variable_get('gigya_reactions_layout', 'horizontal'),
  );
  $form['gigya_reactions_global']['gigya_reactions_multiple_reactions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use multiple Reactions'),
    '#default_value' => variable_get('gigya_reactions_multiple_reactions', TRUE),
  );
  $form['gigya_reactions_global']['gigya_reactions_count_type'] = array(
    '#type' => 'select',
    '#title' => t('Count type'),
    '#options' => array(
      'number' => t('Number'),
      'percentage' => t('Percentage'),
    ),
    '#default_value' => variable_get('gigya_reactions_count_type', 'number'),
  );
  $form['gigya_reactions_global']['gigya_reactions_af_scope'] = array(
    '#type' => 'select',
    '#title' => t('Scope for publishing to Activity Feed'),
    '#description' => t('When publishing feed items, by default the feed items are published to social networks only and will not appear on the site\'s Activity Feed plugin. To change this behavior, you must change the publish scope to "Both".'),
    '#options' => array(
      'external' => t('External'),
      'both' => t('Both'),
    ),
    '#default_value' => variable_get('gigya_reactions_af_scope', 'external'),
  );
  $form['gigya_reactions_global']['gigya_reactions_image_behavior'] = array(
    '#type' => 'radios',
    '#title' => t('Image'),
    '#options' => array(
      'default' => t('Use image tag if exists, first image on post otherwise.'),
      'first' => t('First image on the post'),
      'url' => t('Specify an image URL'),
    ),
    '#default_value' => variable_get('gigya_reactions_image_behavior', 'default'),
    '#attributes' => array('class' => array('image-behv')),
  );
  $form['gigya_reactions_global']['gigya_reactions_image_url'] = array(
    '#type' => 'textfield',
    '#title' => t('The URL of the image to share'),
    '#size' => 20,
    '#states' => array(
      'visible' => array(
        '.image-behv' => array('value' => 'url'),
      ),
    ),
    '#default_value' => variable_get('gigya_reactions_image_url', ''),
  );
  $form['gigya_reactions_global']['gigya_advanced_reactions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Reactions settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $adv_parmas = variable_get('gigya_reactions_advanced', '');
  $form['gigya_reactions_global']['gigya_advanced_reactions']['gigya_reactions_advanced'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced showReactionsBarUI settings'),
    '#element_validate' => array('gigya_key_val_filed_validate'),
    '#default_value' => !empty($adv_parmas) ? gigya_values_array_to_string($adv_parmas) : '',
    '#description' => t('Enter valid !JSON object format. See list of available !parameters', array(
        '!parameters' => l(t('parameters'), 'http://developers.gigya.com/020_Client_API/020_Methods/socialize.showReactionsBarUI', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        ),
        '!JSON' => l(t('JSON'), 'http://json.org', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        ),
      )
    )
  );
  $form['gigya_reactions_global']['gigya_reactions_tokens'] = array(
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#title' => t('Token List'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['gigya_reactions_global']['gigya_reactions_tokens']['tokens_list'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('node'),
    '#global_types' => FALSE,
  );
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'gigya') . '/css/gigya_admin.css',
  );

  $form['#attached']['js'] = array(drupal_get_path('module', 'gigya') . '/js/gigya.admin.behaviors.js');
  return system_settings_form($form);
}


/**
 * Validate GM setting form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return mixed
 *   GM admin form.
 */
function gigya_gm_settings_form($form, $form_state) {
  $form['gigya_gm_message'] = array(
    '#markup' => t('To position Gigya Gamification plugins, create a Gamification block via the menu below,
     and then position it via the "Structure"/"Blocks" menu.') . '<br /><br />',
    '#weight' => -50,
  );
  $form['gigya_gm_global'] = array(
    '#type' => 'fieldset',
    '#title' => t('Gigya Gamification global settings'),
    '#collapsible' => FALSE,
  );
  $form['gigya_gm_global']['gigya_gm_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Gigya Gamification'),
    '#default_value' => variable_get('gigya_gm_enable', FALSE),
  );
  $form['gigya_gm_global']['gigya_gm_enable_notifications'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Gamification notifications'),
    '#default_value' => variable_get('gigya_gm_enable_notifications', FALSE),
    '#suffix' => '<hr>',
  );
  $form['gigya_gm_global']['gigya_gm_leaderboard_period'] = array(
    '#type' => 'select',
    '#title' => t('Leaderboard time period'),
    '#options' => array(
      '7days' => t('7 Days'),
      'all' => t('All'),
    ),
    '#default_value' => variable_get('gigya_gm_leaderboard_period', '7days'),
    '#description' => t('The period for which to display the Leaderboard plugin. \'All\' - Stands for the all-time highest ranking users.'),
    '#suffix' => '<hr>',
  );
  $form['gigya_gm_global']['gigya_gm_total_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Leaderboard user count'),
    '#size' => 2,
    '#description' => t('The number of users to display in the Leaderboard plugin. The maximum is 36.'),
    '#default_value' => variable_get('gigya_gm_total_count', '12'),
  );
  $form['gigya_gm_blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Gigya Gamification blocks'),
    '#collapsible' => FALSE,
  );
  $gm_blocks = variable_get('gigya_gm_blobks', array());
  if (!empty($gm_blocks)) {
    foreach ($gm_blocks as $block_id => $block) {
      $opts[$block_id] = $block['block_name'];
    }
    $form['gigya_gm_blocks']['gigya_gm_delete'] = array(
      '#type' => 'fieldset',
      '#title' => t('Delete blocks'),
      '#collapsible' => FALSE,
      '#weight' => -11,
      '#attributes' => array('class' => array('gm-delete')),
    );
    $form['gigya_gm_blocks']['gigya_gm_delete']['gigya_gm_delete_blocks'] = array(
      '#type' => 'checkboxes',
      '#title' => '',
      '#options' => $opts,
      '#weight' => -10,
    );
    $form['gigya_gm_blocks']['gigya_gm_delete']['gigya_gm_delete_blocks_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#ajax' => array(
        'callback' => 'gigya_gm_delete_block',
        'wrapper' => 'gigya-gm-settings-form',
        'method' => 'html',
        'effect' => 'fade',
      ),
    );
  }
  else {
    $form['gigya_gm_blocks']['gigya_gm_delete']['gigya_gm_delete_blocks'] = array(
      '#markup' => '<div id="gm-delete"></div>',
    );
  }
  $form['gigya_gm_blocks']['gigya_gm_new_block'] = array(
    '#type' => 'fieldset',
    '#title' => t('Create a new block'),
    '#collapsible' => FALSE,
  );
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_block_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Block name'),
    '#size' => 60,
  );

  // Achievements.
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_achievements'] = array(
    '#markup' => '<span class="label">' . t('Achievements') . '</span>',
    '#prefix' => '<div class="gm-element">',
  );
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_achievements_enable'] = array(
    '#type' => 'checkbox',
  );
  $achiv_def_id = gigya_gm_default_id($gm_blocks, 'achievements', 'divAchievements');
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_achievements_div-id'] = array(
    '#type' => 'textfield',
    '#title' => t('Div ID'),
    '#size' => 60,
    '#default_value' => $achiv_def_id,
  );
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_achievements_weight'] = array(
    '#type' => 'select',
    '#title' => t('Weight'),
    '#options' => drupal_map_assoc(range(-20, 20)),
    '#default_value' => 0,
    '#suffix' => '</div>',
  );

  // Challenge status.
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_challenge_status'] = array(
    '#markup' => '<span class="label">' . t('Challenge status') . '</span>',
    '#prefix' => '<div class="gm-element">',
  );
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_challenge_status_enable'] = array(
    '#type' => 'checkbox',
  );
  $ch_def_id = gigya_gm_default_id($gm_blocks, 'challenge_status', 'divChallengeStatus');
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_challenge_status_div-id'] = array(
    '#type' => 'textfield',
    '#title' => t('Div ID'),
    '#size' => 60,
    '#default_value' => $ch_def_id,
  );
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_challenge_status_weight'] = array(
    '#type' => 'select',
    '#title' => t('Weight'),
    '#options' => drupal_map_assoc(range(-20, 20)),
    '#default_value' => 0,
    '#suffix' => '</div>',
  );

  // User status.
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_user_status'] = array(
    '#markup' => '<span class="label">' . t('User status') . '</span>',
    '#prefix' => '<div class="gm-element">',
  );
  $us_def_id = gigya_gm_default_id($gm_blocks, 'user_status', 'divUserStatus');
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_user_status_enable'] = array(
    '#type' => 'checkbox',
  );
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_user_status_div-id'] = array(
    '#type' => 'textfield',
    '#title' => t('Div ID'),
    '#size' => 60,
    '#default_value' => $us_def_id,
  );
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_user_status_weight'] = array(
    '#type' => 'select',
    '#title' => t('Weight'),
    '#options' => drupal_map_assoc(range(-20, 20)),
    '#default_value' => 0,
    '#suffix' => '</div>',
  );

  // Leaderboard.
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_leaderboard'] = array(
    '#markup' => '<span class="label">' . t('Leaderboard') . '</span>',
    '#prefix' => '<div class="gm-element">',
  );
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_leaderboard_enable'] = array(
    '#type' => 'checkbox',
  );
  $lead_def_id = gigya_gm_default_id($gm_blocks, 'leaderboard', 'divLeaderboard');
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_leaderboard_div-id'] = array(
    '#type' => 'textfield',
    '#title' => t('Div ID'),
    '#size' => 60,
    '#default_value' => $lead_def_id,
  );
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_leaderboard_weight'] = array(
    '#type' => 'select',
    '#title' => t('Weight'),
    '#options' => drupal_map_assoc(range(-20, 20)),
    '#default_value' => 0,
    '#suffix' => '</div>',
  );
  $form['gigya_gm_blocks']['gigya_gm_new_block']['gigya_gm_blocks_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create a block'),
    '#ajax' => array(
      'callback' => 'gigya_gm_create_block',
      'wrapper' => 'gigya-gm-settings-form',
      'method' => 'html',
      'effect' => 'fade',
    ),
  );
  $form['gigya_gm_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['gigya_gm_advanced']['gigya_gm_achievements_advanced'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced showAchievementsUI settings'),
    '#element_validate' => array('gigya_json_element_validate'),
    //'#default_value' => !empty($adv_parmas) ? gigya_values_array_to_string($adv_parmas) : '',
    '#default_value' => variable_get('gigya_gm_achievements_advanced', ''),
    '#description' => t('Enter valid !JSON object format. See list of available !parameters', array(
        '!parameters' => l(t('parameters'), 'http://developers.gigya.com/020_Client_API/040_GM/gm.showAchievementsUI', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        ),
        '!JSON' => l(t('JSON'), 'http://json.org', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        )
      )
    ),
  );
  $form['gigya_gm_advanced']['gigya_gm_notifications_advanced'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced showNotifications settings'),
    '#element_validate' => array('gigya_json_element_validate'),
    //'#default_value' => !empty($adv_parmas) ? gigya_values_array_to_string($adv_parmas) : '',
    '#default_value' => variable_get('gigya_gm_notifications_advanced', ''),
    '#description' => t('Enter valid !JSON object format. See list of available !parameters', array(
        '!parameters' => l(t('parameters'), 'http://developers.gigya.com/020_Client_API/040_GM/gm.showNotifications', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        ),
        '!JSON' => l(t('JSON'), 'http://json.org', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        )
      )
    ),
  );
  $form['gigya_gm_advanced']['gigya_gm_challenge_status_advanced'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced showChallengeStatusUI settings'),
    '#element_validate' => array('gigya_json_element_validate'),
    //'#default_value' => !empty($adv_parmas) ? gigya_values_array_to_string($adv_parmas) : '',
    '#default_value' => variable_get('gigya_gm_challenge_status_advanced', ''),
    '#description' => t('Enter valid !JSON object format. See list of available !parameters', array(
        '!parameters' => l(t('parameters'), 'http://developers.gigya.com/020_Client_API/040_GM/gm.showChallengeStatusUI', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        ),
        '!JSON' => l(t('JSON'), 'http://json.org', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        )
      )
    ),
  );
  $form['gigya_gm_advanced']['gigya_gm_leaderboard_advanced'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced showLeaderboardUI settings'),
    '#element_validate' => array('gigya_json_element_validate'),
    //'#default_value' => !empty($adv_parmas) ? gigya_values_array_to_string($adv_parmas) : '',
    '#default_value' => variable_get('gigya_gm_leaderboard_advanced', ''),
    '#description' => t('Enter valid !JSON object format. See list of available !parameters', array(
        '!parameters' => l(t('parameters'), 'http://developers.gigya.com/020_Client_API/040_GM/gm.showLeaderboardUI', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        ),
        '!JSON' => l(t('JSON'), 'http://json.org', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        )
      )
    )
  );
  $form['gigya_gm_advanced']['gigya_gm_user_status_advanced'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced showUserStatusUI settings'),
    '#element_validate' => array('gigya_json_element_validate'),
    //'#default_value' => !empty($adv_parmas) ? gigya_values_array_to_string($adv_parmas) : '',
    '#default_value' => variable_get('gigya_gm_user_status_advanced', ''),
    '#description' => t('Enter valid !JSON object format. See list of available !parameters', array(
        '!parameters' => l(t('parameters'), 'http://developers.gigya.com/020_Client_API/040_GM/gm.showUserStatusUI', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        ),
        '!JSON' => l(t('JSON'), 'http://json.org', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        )
      )
    ),
  );

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'gigya') . '/css/gigya_admin.css',
  );
  $form['#attached']['js'] = array(drupal_get_path('module', 'gigya') . '/js/gigya.admin.behaviors.js');
  $form['#attributes'] = array('class' => 'gigya-gm-settings-form');
  return system_settings_form($form);
}

/**
 * Creates GM blocks.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   blocks form.
 */
function gigya_gm_create_block($form, $form_state) {
  $gigya_gm_blobks = variable_get('gigya_gm_blobks', array());
  $values = $form_state['values'];
  // Create blocks.
  if (!empty($values['gigya_gm_blocks_block_name'])) {
    foreach ($values as $key => $val) {
      if (strpos($key, 'gigya_gm_blocks_') === 0 && $key !== 'gigya_gm_blocks_block_name') {
        $key = str_replace('gigya_gm_blocks_', '', $key);
        $karray = explode('_', $key);
        $prop = end($karray);
        array_pop($karray);
        $comp_key = implode('_', $karray);
        $componentes[$comp_key][$prop] = $val;
      }
    }
    $block_id = str_replace(' ', '_', $values['gigya_gm_blocks_block_name']);
    $gigya_gm_blobks[$block_id] = array(
      'block_name' => $values['gigya_gm_blocks_block_name'],
      'componentes' => $componentes,
    );
    variable_set('gigya_gm_blobks', $gigya_gm_blobks);
  }
  else {
    form_set_error('gigya_gm_blocks_block_name', t('Block name is required'));
  }
  $form_state['input'] = array();
  $form = drupal_rebuild_form('gigya_gm_settings_form', $form_state, $form);
  return $form;
}

/**
 * Delete GM block.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   Delete block from.
 */
function gigya_gm_delete_block($form, $form_state) {
  $gigya_gm_blobks = variable_get('gigya_gm_blobks', array());
  $values = $form_state['values'];
  // Delete blocks.
  if (!empty($values['gigya_gm_delete_blocks'])) {
    foreach ($values['gigya_gm_delete_blocks'] as $block_id => $val) {
      if (!empty($val)) {
        unset($gigya_gm_blobks[$block_id]);
      }
    }
  }
  variable_set('gigya_gm_blobks', $gigya_gm_blobks);
  $form_state['input'] = array();
  $form = drupal_rebuild_form('gigya_gm_settings_form', $form_state, $form);
  return $form;
}

/**
 * Generate GM block id.
 *
 * @param array $blocks
 *   An array of the blocks
 * @param string $key
 *   The block key
 * @param string $id
 *   The block id.
 *
 * @return string
 *   A HTML id from the block.
 */
function gigya_gm_default_id($blocks, $key, $id) {
  $ids = array();
  foreach ($blocks as $block_id => $block) {
    $ids[] = $block['componentes'][$key]['div-id'];
  }
  $last_id = array_search($id, $ids);
  if ($last_id !== FALSE) {
    $parts = explode('-', end($ids));
    if (!empty($parts[1]) && is_numeric($parts[1])) {
      list($seen_id, $i) = $parts;
      $i++;
    }
    else {
      $i = 1;
    }
    $id = $id . '-' . $i;
  }
  return $id;
}

/**
 * Checks if the current api key has RaaS enabled.
 *
 * @param array $element
 *   The form element.
 *
 * @return mixed
 *   Validated element or an error.
 */
function gigya_check_raas(&$element) {
  $res = _gigya_api('accounts.getScreenSets', array(), TRUE);
  if ($res === 403036) {
    $element['raas']['#attributes']['disabled'] = 'disabled';
    $element['raas']['#attributes']['class'] = array('disabled');
    $element['raas']['#description'] = t("Gigya's Registration-as-a-Service (RaaS) is currently not part of your site package.
     Please contact your Gigya account manager to activate the package. RaaS is Gigya's end-to-end user management system package. Learn more !here. ",
      array(
        '!here' => l(t('here'), 'http://developers.gigya.com/010_Developer_Guide/10_UM360/040_Raas',
          array('external' => TRUE, 'attributes' => array('target' => '_blank'))
        ),
      )
    );
  }
  else {
    $element['raas']['#description'] = t("Selecting this option overrides Drupal's user management system.
     This requires additional administration steps. Learn more !here",
      array(
        '!here' => l(t('here'), 'http://developers.gigya.com/050_Partners/050_CMS_Modules/020_Drupal/Using_RaaS_with_Drupal',
          array('external' => TRUE, 'attributes' => array('target' => '_blank'))
        ),
      )
    );
    $element['drupal_and_gigya']['#description'] = t('<span class="warnning hidden"> Warning: this site is configured on Gigya server to use Registration-as-a-Service. Please contact your Gigya account manager for migration instruction.</span>');
    $element['gigya']['#description'] = t('<span class="warnning hidden"> Warning: this site is configured on Gigya server to use Registration-as-a-Service. Please contact your Gigya account manager for migration instruction.</span>');
  }
  return $element;
}


/**
 * Activity feed setting form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The form state.
 *
 * @return mixed
 *   Form.
 */
function gigya_activity_feed_settings_form($form, $form_state) {
  $form['gigya_activety_feed_message'] = array(
    '#markup' => t('To position a Gigya Activity Feed plugin, enter the "Structure" -> "Blocks" menu and choose where
     to position the "Gigya Activity Feed" block.') . '<br /><br />',
    '#weight' => -50,
  );
  $form['gigya_activety_feed_global'] = array(
    '#type' => 'fieldset',
    '#title' => t('Gigya Activity Feed settings'),
    '#collapsible' => FALSE,
  );

  $form['gigya_activety_feed_global']['gigya_activety_feed_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Gigya Activity Feed'),
    '#default_value' => variable_get('gigya_activety_feed_enable', FALSE),
  );

  $form['gigya_activety_feed_global']['gigya_activety_feed_container_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Activity Feed container ID'),
    '#size' => 30,
    '#default_value' => variable_get('gigya_activety_feed_container_id', 'ActivityFeedDiv'),
    '#description' => t('The HTML DIV ID in which the Activity Feed should be embedded.')
  );
  $form['gigya_activety_feed_global']['gigya_activety_feed_tabs'] = array(
    '#type' => 'textfield',
    '#title' => t('Tabs and order'),
    '#size' => 30,
    '#description' => t("A comma delimited list of tabs names that defines which tabs to show and the tabs order.
     The optional tabs names are: \"everyone\", \"friends\", \"me\"."
    ),
    '#default_value' => variable_get('gigya_activety_feed_tabs', 'everyone,friends,me'),
  );

  $form['gigya_activety_feed_global']['gigya_activety_feed_size'] = array(
    '#type' => 'checkbox',
    '#title' => t('Specify a custom size for the plugin'),
    '#default_value' => variable_get('gigya_activety_feed_size', FALSE),
  );
  $form['gigya_activety_feed_global']['gigya_activety_feed_width'] = array(
    '#prefix' => '<div class="height-with">',
    '#type' => 'textfield',
    '#title' => t('Width'),
    '#size' => 5,
    '#default_value' => variable_get('gigya_activety_feed_width', '309'),
    '#states' => array(
      'visible' => array(
        '#edit-gigya-activety-feed-size' => array('checked' => TRUE),
      ),
    ),
  );
  $form['gigya_activety_feed_global']['gigya_activety_feed_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Height'),
    '#size' => 5,
    '#default_value' => variable_get('gigya_activety_feed_height', '270'),
    '#suffix' => '</div>',
    '#states' => array(
      'visible' => array(
        '#edit-gigya-activety-feed-size' => array('checked' => TRUE),
      ),
    ),
  );
  $form['gigya_activety_feed_global']['gigya_activety_feed_privacy'] = array(
    '#type' => 'select',
    '#title' => t('Activity Feed privacy level'),
    '#description' => t('The privacy level determines how the user action is presented in each of the Activity Feed plugin tabs.'),
    '#options' => array(
      'private' => t('Private'),
      'public' => t('Public'),
      'friends' => t('Friends'),
    ),
    '#default_value' => variable_get('gigya_activety_feed_privacy', 'private'),
  );
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'gigya') . '/css/gigya_admin.css',
  );
  $form['#attached']['js'] = array(drupal_get_path('module', 'gigya') . '/js/gigya.admin.behaviors.js');
  return system_settings_form($form);
}

function gigya_follow_bar_settings_form($form, $form_state) {
  $form['gigya_follow_bar_global'] = array(
    '#type' => 'fieldset',
    '#tree' => FALSE,
    '#title' => t('Follow Bar global settings'),
    '#description' => t('Global settings for gigya follow bar'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['gigya_follow_bar_global']['gigya_follow_bar_container_id'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Container ID'),
    '#description' => t('The HTML DIV in which the Follow Bar should be embedded.'),
    '#default_value' => variable_get('gigya_follow_bar_container_id', 'gigya-follow-bar'),
  );
  $form['gigya_follow_bar_global']['gigya_follow_bar_layout'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t('Orientation'),
    '#description' => t('Sets the arrangement of buttons in the bar.'),
    '#default_value' => variable_get('gigya_follow_bar_layout', 'horizontal'),
    '#options' => array('horizontal' => 'Horizontal', 'vertical' => 'Vertical'),
  );
  $form['gigya_follow_bar_global']['gigya_follow_bar_icon_size'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Icon Size'),
    '#description' => t('The size in pixels of the icons displayed in the bar.'),
    '#default_value' => variable_get('gigya_follow_bar_icon_size', '32'),
  );
  include_once 'includes/placeholders.inc';
  $form['gigya_follow_bar_global']['gigya_follow_bar_buttons'] = array(
    '#type' => 'textarea',
    '#title' => t('Follow Bar Buttons'),
    '#rows' => 20,
    '#default_value' => variable_get('gigya_follow_bar_buttons', ''),
    '#description' => t('Please enter a list of !FollowButton_objects. that should appear on the Follow Bar.', array(
        '!FollowButton_objects' => l(t('FollowButton objects'), 'http://developers.gigya.com/020_Client_API/010_Socialize/socialize.showFollowBarUI#FollowButton_Object', array(
            'external' => TRUE,
            'attributes' => array('target' => '_blank'),
          )
        ),
      )
    ),
    '#attributes' => array('placeholder' => $follow_bar_placeholder),
  );
  $form['gigya_follow_bar_global']['gigya_advanced_follow_bar'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Follow Bar settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $adv_parmas = variable_get('gigya_follow_bar_advanced', '');
  $form['gigya_follow_bar_global']['gigya_advanced_follow_bar']['gigya_follow_bar_advanced'] = array(
    '#type' => 'textarea',
    '#title' => t('Advanced showFollowBarUI settings'),
    '#element_validate' => array('gigya_key_val_filed_validate'),
    '#default_value' => !empty($adv_parmas) ? gigya_values_array_to_string($adv_parmas) : '',
    '#description' => t('Enter valid !JSON object format. See list of available !parameters', array(
        '!parameters' => l(t('parameters'), 'http://developers.gigya.com/020_Client_API/010_Socialize/socialize.showFollowBarUI', array(
          'external' => TRUE,
          'attributes' => array('target' => '_blank'),
        )),
        '!JSON' => l(t('JSON'), 'http://json.org', array('external' => TRUE, 'attributes' => array('target' => '_blank'))
        ),
      )
    ),
  );
  return system_settings_form($form);
}

function gigya_json_element_validate($element, &$form_state, $form) {
  $valid = gigya_validate_json($element['#value']);
  if (is_array($valid)) {
    $str = $element['#title'] . ": " . join(', ', $valid);
    form_set_error($element['#name'], check_plain($str));
  }
}

function gigya_encrypt_value($val, $encrypt_mode = FALSE) {
  if (!function_exists('encrypt')) {
    return $val;
  }
  if (!$encrypt_mode) {
    $encrypt_mode =  variable_get('gigya_encrypt_config', '0');
  }
  if ($encrypt_mode && $encrypt_mode != "0") {
    try {
      $val = encrypt($val, array(), NULL, NULL, $encrypt_mode);
    } catch (Exception $e) {
      watchdog('gigya', 'Error encrypt values');

    }

  }
  return $val;
}


