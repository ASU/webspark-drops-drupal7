<?php

/**
 * @file
 * Provides API documentation for the Gigya module.
 *
 * All Gigya API calls go through drupal_alter functions so that other modules
 * could modify or add parameters. Below is a list of all relevant functions and
 * a short explanation regarding each of them.
 */

/*
 * Implements hook_gigya_global_conf_alter().
 *
 * This hook is called before adding the Gigya global configuration parameters
 * to the Javascript settings. The default parameters are the list of providers
 * and the language. A list of available parameters can be found at the @link
 * http://developers.gigya.com/020_Client_API/010_Objects/Conf_object
 * Gigya developers site. @endlink Note that these parameters are not handled
 * as standard Drupal Javascript settings, but instead are included as an object
 * in the HTML head section of the page.
 */
function hook_gigya_global_conf_alter($gigya_js_settings) {
  global $language;
  if ($language->language == 'fr') {
    //If the site language is French change Gigya language to French
    $gigya_js_settings['lang'] = 'fr';
  }
}

/*
 * Implements hook_gigya_notify_login_user_info_alter().
 *
 * This hook is called before calling gigya_notify_login function. The parameter
 * that is passed to the alter function is the user info that gets sent to gigya
 * Valid fields are nickname, photoURL, thumbnailURL, firstName, lastName,
 * gender, age, email. The relevant Gigya developers site page is @link
 * http://developers.gigya.com/020_Client_API/020_Methods/socialize.notifyLogin
 * @endlink
 */
function hook_notify_login_user_info_alter($gigya_user_info) {
  $gigya_user_info['email'] = 'email@this_site.com';
}

/*
 * Implements hook_gigya_gigya_create_user_alter().
 *
 * This hook is called before a new user is created via gigya login. The parameter
 * that is passed to the alter function is the form_state that gets sent to drupal registration form
 * and the bio, the gigya user info as it is returned from gigya
 */
function hook_gigya_create_user_alter(&$form_state, $bio) {
  $form_state['custom_field'] = 'some value';
}

/*
 * Implements hook_gigya_loginui_alter().
 *
 * This hook is called before adding the gigya.socialize.showLoginUI
 * configuration parameters to the Javascript settings. A list of available
 * parameters can be found in the Gigya developers site: @link
 * http://developers.gigya.com/020_Client_API/020_Methods/Socialize.showLoginUI
 * @endlink
 */
function hook_gigya_loginui_alter($gigya_login_params) {
  $gigya_login_params['showWhatsThis'] = TRUE;
  $gigya_login_params['whatsThisText'] = t('Some explanation text about the login widget');
}

/*
 * Implements hook_gigya_connectui_alter().
 *
 * This hook is called before adding the gigya.socialize.showAddConnectionsUI
 * configuration parameters to the Javascript settings. A list of available
 * parameters can be found in the Gigya developers site: @link
 * http://developers.gigya.com/020_Client_API/020_Methods/socialize.showAddConnectionsUI
 * @endlink
 */
function hook_gigya_connectui_alter($gigya_connect_params) {
  $gigya_connect_params['showWhatsThis'] = TRUE;
  $gigya_connect_params['whatsThisText'] = t('Some explanation text about the login widget');
}

/*
 * Implements hook_gigya_sharebar_alter().
 *
 * This hook is called before adding the socialize.showShareBarUI configuration
 * parameters to the Javascript settings. A developer guide to the Share Bar
 * plugin is available here: @link
 * http://developers.gigya.com/010_Developer_Guide/18_Plugins/015_Share_Bar
 * @endlink A list of available parameters can be found at the Gigya developers
 * site: @link
 * http://developers.gigya.com/020_Client_API/020_Methods/socialize.showAddConnectionsUI
 * @endlink
 */
function hook_gigya_sharebar_alter($share_settings, $context) {
  $share_settings['grayedOutScreenOpacity'] = 30;
  $share_settings['gigyaSharebar']['shareButtons'] = array(
    array(
      'provider' => 'MyAOL',
      'iconImgUp' => '/images/share_bar/AOL.png'
    ),
    array(
      'provider' => 'digg',
      'iconImgUp' => '/images/share_bar/Digg.png'
    ),
    array(
      'provider' => 'Facebook',
      'iconImgUp' => '/images/share_bar/Facebook.png'
    ),
    array(
      'provider' => 'Googleplus',
      'iconImgUp' => '/images/share_bar/Google_Plus.png'
    ),
    array(
      'provider' => 'Hyves',
      'iconImgUp' => '/images/share_bar/Hyves.png'
    ),
    array(
      'provider' => 'LinkedIn',
      'iconImgUp' => '/images/share_bar/LinkedIn.png'
    ),
    array(
      'provider' => 'Messenger',
      'iconImgUp' => '/images/share_bar/Messenger.png'
    ),
    array(
      'provider' => 'Twitter',
      'iconImgUp' => '/images/share_bar/Twitter.png'
    )
  );
}

/*
 * Implements hook_gigya_reactions_alter().
 *
 * This hook is called before adding the socialize.showReactionsBarUI
 * configuration parameters to the Javascript settings. A developer guide to the
 * Reactions plugin is available here: @link
 * http://developers.gigya.com/010_Developer_Guide/18_Plugins/030_The_Reactions_Plugin
 * @endlink A list of available parameters can be found at the Gigya developers
 * site: @link
 * http://developers.gigya.com/020_Client_API/020_Methods/socialize.showReactionsBarUI
 * @endlink
 */
function hook_gigya_reactions_alter($reactions_settings, $context) {
  $reactions_settings['promptShare'] = FALSE;
}

/*
 * Implements hook_gigya_shareui_alter().
 *
 * This hook is called before adding the socialize.showShareUI configuration
 * parameters to the Javascript settings. A list of available parameters can be
 * found at the Gigya developers site: @link
 * http://developers.gigya.com/020_Client_API/020_Methods/socialize.showShareUI
 * @endlink Note this is used for “action sharing”, defined by Drupal’s rules
 * mechanism.
 */
function hook_gigya_shareui_alter($shareui_params) {
  $shareui_params['showSuccessMessage'] = FALSE;
}

/*
 * Implements hook_gigya_comments_alter().
 *
 * This hook is called before adding the socialize.showCommentsUI configuration
 * parameters to the Javascript settings. A developer guide to the Comments
 * plugin is available here: @link
 * http://developers.gigya.com/010_Developer_Guide/18_Plugins/020_The_Comments_Plugin
 * @endlink A list of available parameters can be found at the Gigya developers
 * site: @link
 * http://developers.gigya.com/020_Client_API/020_Methods/socialize.showCommentsUI
 * @endlink
 */
function hook_gigya_comments_alter($comments_params) {
  $comments_paremes['useSiteLogin'] = TRUE;
  $comments_paremes['onSiteLoginClicked'] = 'onSiteLoginHandler'; // Registering to the onSiteLoginClicked event
}

/*
 * Implements hook_gigya_tokens_alter().
 * This hook is run before the Gigya tokens are returned. Other modules can implement this hook
 * to changes values provide by Gigya or to add values.
 * the parameters are the $replacements that get returned, the $tokens and the $gigya_user_info for reference
 */

function hook_gigya_tokens_alter(&$replacements, $tokens, $gigya_user_info) {
  //take the first name from a different provider
  $replacements['gigya:gigya-firstName'] = $gigya_user_info['identities'][2]['firstName'];
  //When using RaaS you would have the custom data fields under data
  $replacements['[gigya:subscribe]'] = $gigya_user_info['data']['subscribe'];
}

/**
 * this hook lets other modules modify the user array before it is sent to the user save function
 * when a drupal is created via the Gigya RaaS.
 * the first parameter is the array that would be sent to the user_save function
 * the second on is the parameter is the info passed from gigya.
 * http://developers.gigya.com/020_Client_API/020_Accounts/accounts.socialLogin#response
 * @param $new_user_array
 * @param $gigya_info
 */
function hook_gigya_raas_create_user_alter(&$new_user_array, $gigya_info) {
  // Use the user first name as a drupal user name
  $new_user_array['name'] = $gigya_info['firstName'];
}

/**
 * @param array $edit the user edit array
 * @param object $user the Drupal user object
 * @param array $gigya_info the gigya account as returned from getAccountInfo
 */
function hook_gigya_raas_update_user_alter(&$edit, $user, $gigya_info) {
  // Use the user first name as a drupal user name
  $new_user_array['name'] = $gigya_info['firstName'];
}

/**
 * The following example just sets the width of the achievements plugin to 200 in a block named example_block.
 * the js_array will have arrays of the  selected plugins the key name will be plugin_nameParams (see example).
 * The relevant keys for the plugin can be found here
 * http://developers.gigya.com/020_Client_API/040_GM/gm.showAchievementsUI (Achievements plugin)
 * http://developers.gigya.com/020_Client_API/040_GM/gm.showChallengeStatusUI (Challenge plugin)
 * http://developers.gigya.com/020_Client_API/040_GM/gm.showLeaderboardUI (Leaderboard plugin)
 * http://developers.gigya.com/020_Client_API/040_GM/gm.showUserStatusUI (UserStatus plugin)
 * @param $js_array the array that would be passed to the plugins
 * @param $js_block_name the name of the block as it was created in the admin section
 */
function hook_gigya_gm_block_alter(&$js_array, $js_block_name) {
  if ($js_block_name == 'example_block') {
    $js_array['achievementsParams']['width'] = 200;
    $js_array['challengeStatusParams']['width'] = 700;
    $js_array['leaderboardParams']['width'] = 500;
    $js_array['userStatusParams']['width'] = 800;
  }
}

/**
 * The following example would prevent the notification popup from closing automatically.
 * The relevant keys can be found here http://developers.gigya.com/020_Client_API/040_GM/gm.showNotifications
 * @param $notification_settings the array that would passed to the notification plugin.
 */
function hook_gigya_gm_notifications_alter(&$notification_settings) {
  $notification_settings['closeTimeout'] = 0;
}

/**
 * The following example adds the hometown to the user info request so it could be used later in the field mappings.
 * @param $req_params
 */
function hook_gigya_get_account_info_alter(&$req_params) {
  $req_params['extraProfileFields'] = "username,hometown";
}

/**
 * Lets other alter the upon user creation.
 * The following example adds a field named some_field to the profile of the type main.
 * @param object $profile the profile2 object
 * @param array $gigya_account the gigya account array as retread from gigya getAccountInfo.
 */
function hook_gigya_raas_create_profile2_alter(&$profile, $gigya_account) {
  if ($profile->type == "main") {
    $profile->some_field[LANGUAGE_NONE][0]['value'] = $gigya_account['profile']['zip'];
  }
}

/**
 * Lets other alter the upon user update/login.
 * The following example changes the value of the field named some_field of the profile of the type main.
 * @param object $profile the profile2 object
 * @param array $gigya_account the gigya account array as retread from gigya getAccountInfo.
 */
function hook_gigya_raas_update_profile2_alter(&$profile, $gigya_account) {
  if ($profile->type == "main") {
    $profile->some_field[LANGUAGE_NONE][0]['value'] = $gigya_account['profile']['zip'];
  }
}