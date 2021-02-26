<?php

/**
 * ASU Brand administration functions.
 */

/**
 * Implements hook_block_configure_form().
 *
 * @param $delta
 * @return mixed
 */
function asu_brand_get_block_configure_form($delta) {

  $form['asu_brand'] = array(
      '#type' => 'fieldset',
      '#title' => t('ASU Brand settings'),
      '#description' => t('This block is cached for %lifetime. To update now, <a href="@link">clear the cache</a>.', array('%lifetime' => format_interval(ASU_BRAND_CACHE_LIFETIME), '@link' => url('/admin/config/development/performance'))),
  );

  switch ($delta) {
    case 'asu_brand_header': // WS1.0 header default
    case 'asu_brand_header_ws2':
      // Customize the site title, add the parent org title (and their URLs)
      $form['asu_brand']['custom_title'] = array(
        '#type' => 'fieldset',
        '#title' => t('Site and parent org name settings'),
        '#description' => t('Settings to override the site name link URL. Also allows setting a parent organization name and URL.'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
      );
      $form['asu_brand']['custom_title']['asu_brand_site_name'] = array(
        '#markup' => "<p><b>Site Title</b></p><p>" . t('Go to the '
            . l('Site information form', '/admin/config/system/site-information'))
          . ' to change the title.' . "</p>",
      );
      $form['asu_brand']['custom_title']['asu_brand_parent_org_title'] = array(
        '#type' => 'textfield',
        '#title' => t('Parent Organization Title'),
        '#default_value' => variable_get($delta . '_parent_org_title', ''),
        '#description' => t('If added, this name will be placed before (or above) the site title in the header.'
          . ' Requires a URL to be added below.'),
      );
      $form['asu_brand']['custom_title']['asu_brand_parent_org_url'] = array(
        '#type' => 'textfield',
        '#title' => t('Parent Organization URL'),
        '#default_value' => variable_get($delta . '_parent_org_url', ''),
        '#description' => t('The destination URL of the parent organization link.'),
        '#states' => array(
          'required' => array(
            ':input[name="asu_brand_parent_org_title"]' => array('empty' => FALSE),
          ),
        ),
      );
      $form['asu_brand']['custom_title']['asu_brand_override_url'] = array(
        '#type' => 'textfield',
        '#title' => t('Override Site Name Base URL'),
        '#default_value' => variable_get($delta . '_override_url', '/'),
        '#description' => t("Overrides the URL for the site name link in the header. If not provided, the link will be set to the root '/'"),
      );

      $form['asu_brand']['asu_brand_preview_pages'] = array(
        '#type' => 'textarea',
        '#title' => t('Preview pages'),
        '#default_value' => variable_get('asu_brand_preview_pages', ASU_BRAND_PREVIEW_PAGES_DEFAULT),
        '#description' => t('This setting is shared between all ASU Brand blocks.<br />Specify "preview pages"'
          . ' by using their paths. Enter one path per line. The \'*\' character is a wildcard. Example paths are'
          . ' blog for the blog page and blog/* for every personal blog. <front> is the front page.<br />The default'
          . ' is %default.', array('%default' => ASU_BRAND_PREVIEW_PAGES_DEFAULT)),
        '#required' => TRUE,
      );

      // Site menu injection - Insert a selected Drupal menu into the mobile/responsive menu.
      $form['asu_brand']['site_menu'] = array(
        '#type' => 'fieldset',
        '#title' => t('Drupal menu injection'),
        '#collapsed' => FALSE,
      );
      $form['asu_brand']['site_menu']['asu_brand_sitemenu_injection_flag'] = array(
        '#type' => 'checkbox',
        '#title' => t('Append local Drupal (site) menu into ASU header menu and display in the mobile state.'),
        '#default_value' => variable_get($delta . '_sitemenu_injection_flag', 1),
      );
      $form['asu_brand']['site_menu']['asu_brand_sitemenu_name'] = array(
        '#type' => 'select',
        '#title' => t('Menu to inject'),
        '#description' => t('Select the Drupal (site) menu to inject.'),
        '#options' => asu_brand_get_site_menu_options(),
        '#default_value' => variable_get($delta . '_sitemenu_name', ASU_BRAND_SITE_MENU_NAME_DEFAULT),
        '#states' => array(
          'visible' => array(
            ':input[name="asu_brand_sitemenu_injection_flag"]' => array('checked' => TRUE),
          ),
        ),
      );

      // Add custom GTM code
      $form['asu_brand']['gtm'] = array(
        '#type' => 'fieldset',
        '#title' => t('Google Tag Manager (GTM) setting overrides'),
        '#description' => t('Add your own custom, ASU Universal GTM code here to override the default GTM'
          . ' settings managed by the ASU Marketing Hub. WARNING: Your site analytics data and other ASU data'
          . ' collection may be broken or stopped completely if this field is not'
          . ' used correctly. Leave this legacy field blank unless you REALLY know what you are doing.'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
      $form['asu_brand']['gtm']['asu_brand_gtm_override'] = array(
        '#type' => 'textarea',
        '#title' => t('Custom GTM Script'),
        '#default_value' => variable_get($delta . '_gtm_override', ''),
        '#description' => t('This script should be provided by an ASU Google Tag Manager administrator.'),
      );

      // Login URL alteration/override blocking
      $form['asu_brand']['do_not_override'] = array(
        '#type' => 'fieldset',
        '#title' => t('Altering the Login URL'),
        '#description' => t('Configure which domains to not override the login URL'
          . ' or whether successful logins are redirected to the referrer or home page.'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      // format our do not override list array as a comma-delimted list in the form field, for easy editing
      $overrides = drupal_json_decode(variable_get($delta . '_do_not_override', '["www.asu.edu"]'));
      $fstring = implode(', ', $overrides);

      $form['asu_brand']['do_not_override']['asu_brand_do_not_override'] = array(
        '#type' => 'textarea',
        '#title' => t('Domains to NOT Override Login URLs'),
        '#description' => t('The ASU Brand module will not override the login URL'
          . ' with the CAS module path for any of the hostnames entered below.'
          . ' SEPARATE EACH HOST NAME BY COMMA. Examples: www.asu.edu,yoursite.lab.asu.edu'),
        '#default_value' => $fstring,
      );
      $form['asu_brand']['do_not_override']['asu_brand_attach_dest_url'] = array(
        '#type' => 'checkbox',
        '#title' => t('Return to last page upon login'),
        '#description' => t('If checked, the site will return successfully logged in users to the'
          . ' page they came from, instead of the home page of the site.'),
        '#default_value' => variable_get('asu_brand_attach_dest_url', 1),
      );

      // No longer options......
      // Header template - hard-coded
      // Header basepath - hard-coded
      // Header version
      break;

      case 'asu_brand_footer':
      case 'asu_brand_footer_ws2':
        // Footer standardized with no color options
        $form['asu_brand']['#title'] = t('ASU Brand Footer settings');
        break;

  }
  return $form;
}

/**
 * Implements hook_form_ID_alter().
 * Rebuild the version options and deselect item.
 */
function asu_brand_form_block_admin_configure_alter(&$form, $form_state) {
  if ($form['module']['#value'] === 'asu_brand') {
    if (in_array($form['delta']['#value'], array('asu_brand_header', 'asu_brand_header_ws2'))) {
      // If form state is set (ajax call) then set the header version options to match the base path.
      if (isset($form_state['values'])) {
        $options = asu_brand_get_version_options(FALSE);
        $form['settings']['asu_brand']['asu_brand_header_version']['#options'] = $options;
      }
      $form['#validate'][] = '_asu_brand_block_form_validate';
      $form['settings']['title']['#access'] = FALSE;
    } elseif (in_array($form['delta']['#value'], array('asu_brand_footer', 'asu_brand_footer_ws2'))) {
      $form['settings']['title']['#access'] = FALSE;
    }
  }
}

/**
 * Get the header version options as an associative array in the form of
 * array(
 *   'version' => description text,
 * );
 * @param bool $reset
 * @return array|mixed|null
 */
function asu_brand_get_version_options($reset = FALSE) {
  $options = &drupal_static(__FUNCTION__);

  if ($reset || !isset($options)) {
    // Hard-coded here because the XML feed at asu.edu/asuthemes/gtmheaders.xml will no longer be used.
    $options = array(
      '' => t('Select a version'),
      'stable' => 'Web Standards 1.0',
      '5.0' => 'Web Standards 2.x',
    );
  }
  return $options;
}

function asu_brand_get_site_menu_options() {
  return menu_get_menus();
}

/**
 * ASU Brand admin settings form definition.
 */
function asu_brand_admin_settings($form, &$form_state) {
  if (!module_exists('webspark_featurescustom')) { // Save settings
    $form['instructions'] = array(
      '#markup' => '<div class="messages warning">'
        . '<p><strong>Only the ASU Brand header and footer blocks are swapped in or out by this setting.</strong></p>'
        . '<p>Any blocks containing Web standards compliant megafooters or main menus must'
        . ' be handled at the <a href="/admin/structure/block">block configuration</a> page.</p></div>',
    );
    $form['ws_version'] = array(
      '#type' => 'select',
      '#title' => 'Web Standards version',
      '#description' => 'Select which version of Web Standards assets to display.',
      '#options' => asu_brand_get_version_options(),
      '#required' => TRUE,
      '#default_value' => variable_get('asu_brand_header_version', ''),
    );
    $form['#submit'][] = '_asu_brand_admin_settings_submit';
    $form = system_settings_form($form);
  } else {
    $form['not_available'] = array(
    '#markup' => '<h3>Disabled</h3><p>The ASU Brand settings form is disabled for Webspark installations'
      . ' because the Web Standards block management is handled automatically when '
      . '<a href="/admin/appearance">themes are changed</a>.</p>'
      . '<p>If you must change the placement of a global Web standards block (header/footer) without'
      . ' changing themes, this can be done manually at the <a href="/admin/structure/block">block '
      . ' configuration</a> page. But note that these changes may be overwritten when the site theme is'
      . ' changed again.</p>',
    );
    $form = system_settings_form($form);
    $form['actions']['submit'] = array();
  }
  return $form;
}

/**
 * ASU Brand admin settings form submission callback. Can only be reached by non-Webspark sites.
 * @param $form
 * @param $form_state
 */
function _asu_brand_admin_settings_submit($form, &$form_state) {
  variable_set('asu_brand_header_version', $form_state['values']['ws_version']);
  module_load_include('inc', 'asu_brand', 'includes/asu_brand.theme_update');
  $ws_data = ($form_state['values']['ws_version'] === '5.0')
    ? asu_brand_get_ws_data('college')
    : asu_brand_get_ws_data('innovation');
  asu_brand_block_theme_update('__standalone__', $ws_data);
  // Flush ASU Brand caches so updated ASU header/footer (and any other related blocks) are right
  asu_brand_cache_clear();
}
