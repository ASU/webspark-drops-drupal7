<?php

/**
 * ASU Brand administration functions.
 */
function asu_brand_get_block_configure_form($delta) {
  
  $form['asu_brand'] = array(
      '#type' => 'fieldset',
      '#title' => t('ASU Brand settings'),
      '#description' => t('This block is cached for %lifetime. To update now, <a href="@link">clear the cache</a>.', array('%lifetime' => format_interval(ASU_BRAND_CACHE_LIFETIME), '@link' => url('admin/config/development/performance'))),
  );
  
  switch ($delta) {
    
    case ASU_BRAND_HEADER_DELTA:
      
      $form['asu_brand']['asu_brand_header_basepath'] = array(
          '#type' => 'textfield',
          '#title' => t('ASU theme basepath'),
          '#default_value' => variable_get('asu_brand_header_basepath', ASU_BRAND_HEADER_BASEPATH_DEFAULT),
          '#description' => t('This setting is shared between all ASU Brand blocks. The default is %default. To use a local path, use %local_path', array('%default' => ASU_BRAND_HEADER_BASEPATH_DEFAULT, '%local_path' => '/afs/asu.edu/www/asuthemes')),
          '#required' => TRUE,
          '#ajax' => array(
              'event' => 'change',
              'callback' => 'asu_brand_basepath_ajax_callback',
              'wrapper' => 'dropdown_header_version_replace',
          ),
      );
      $form['asu_brand']['asu_brand_header_version'] = array(
          '#type' => 'select',
          '#title' => t('ASU header version'),
          '#description' => t('Select the version of the ASU header. <strong>This setting is shared between all ASU Brand blocks.</strong>'),
          '#options' => asu_brand_get_version_options(FALSE, (!empty($form_state['values']['asu_brand_header_basepath'])) ? $form_state['values']['asu_brand_header_basepath'] : variable_get('asu_brand_header_basepath', ASU_BRAND_HEADER_BASEPATH_DEFAULT)),
          '#default_value' => variable_get('asu_brand_header_version', ASU_BRAND_HEADER_VERSION_DEFAULT),
          '#required' => TRUE,
          '#prefix' => '<div id="dropdown_header_version_replace">',
          '#suffix' => '</div>',
      );
      $form['asu_brand']['asu_brand_preview_pages'] = array(
          '#type' => 'textarea',
          '#title' => t('Preview pages'),
          '#default_value' => variable_get('asu_brand_preview_pages', ASU_BRAND_PREVIEW_PAGES_DEFAULT),
          '#description' => t('This setting is shared between all ASU Brand blocks.<br />Specify "preview pages" by using their paths. Enter one path per line. The \'*\' character is a wildcard. Example paths are blog for the blog page and blog/* for every personal blog. <front> is the front page.<br />The default is %default.', array('%default' => ASU_BRAND_PREVIEW_PAGES_DEFAULT)),
          '#required' => TRUE,
      );
      
      $form['asu_brand']['asu_brand_header_template'] = array(
        '#type' => 'textfield',
        '#title' => t('ASU header template key'),
        '#default_value' => variable_get('asu_brand_header_template', ASU_BRAND_HEADER_TEMPLATE_DEFAULT),
        '#description' => t('The default is %default. For a list of template keys, visit <a href="@template_path">@template_path</a>.', array('%default' => ASU_BRAND_HEADER_TEMPLATE_DEFAULT, '@template_path' => url('https://asu.edu/asuthemes/' . variable_get('asu_brand_header_version', ASU_BRAND_HEADER_VERSION_DEFAULT) . '/heads/'))),
        '#required' => TRUE,
      );
      
      $form['asu_brand']['site_menu'] = array(
          '#type' => 'fieldset',
          '#title' => t('Site menu injection'),
          '#collapsed' => FALSE,
      );
      
      $form['asu_brand']['site_menu']['asu_brand_sitemenu_injection_flag'] = array(
        '#type' => 'checkbox',
        '#title' => t('Append local site menu into ASU header menu and display in responsive state.'),
        '#default_value' => variable_get('asu_brand_sitemenu_injection_flag', 1),
      );
      
      $form['asu_brand']['site_menu']['asu_brand_sitemenu_name'] = array(
          '#type' => 'select',
          '#title' => t('Menu to inject'),
          '#description' => t('Select the site menu to inject.'),
          '#options' => asu_brand_get_site_menu_options(),
          '#default_value' => variable_get('asu_brand_sitemenu_name', ASU_BRAND_SITE_MENU_NAME_DEFAULT),
          '#states' => array(
              'visible' => array(
                  ':input[name="asu_brand_sitemenu_injection_flag"]' => array('checked' => TRUE),
              ),
          ),
      );
      
      $form['asu_brand']['gtm'] = array(
          '#type' => 'fieldset',
          '#title' => t('Override Google Tag Manager (GTM) settings'),
          '#description' => t('ASU Universal GTM settings are automatically set. Overriding is not common.'),
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
      );
      
      $form['asu_brand']['gtm']['asu_brand_gtm_override'] = array(
          '#type' => 'textarea',
          '#title' => t('Custom GTM Script'),
          '#default_value' => variable_get('asu_brand_gtm_override', ''),
          '#description' => t('This script should be provided by the ASU google Analytics Administrator.'),
      );

      break;
      
      case 'asu_brand_footer':
        // Footer standardized with no color options
        $form['asu_brand']['#title'] = t('ASU Brand Footer settings');
        break;
      
      case 'asu_brand_students_footer':
        
        break;
  }
  
  return $form;
}

/**
 * Implements hook_form_alter().
 * Rebuild the version options and deselect item.
 */
function asu_brand_form_block_admin_configure_alter(&$form, $form_state) {
  if ($form['module']['#value'] == 'asu_brand' && $form['delta']['#value'] == 'asu_brand_header') {
    // if form state is set (ajax call) then set the header version options to match the base path.
    if (isset($form_state['values'])) {
      $options = asu_brand_get_version_options(FALSE, $form_state['values']['asu_brand_header_basepath']);
      $form['settings']['asu_brand']['asu_brand_header_version']['#options'] = $options;
    }
  }
}

/**
 * Selects just the asu_brand_header_version to be returned for re-rendering
 * @param array $form
 * @param array $form_state
 * @return renderable array (asu_brand_header_version)
 */
function asu_brand_basepath_ajax_callback($form, $form_state) {
  // force user to select header version again as basepath has changed.
  // available header versions can differ between DEV, QA and PROD.
  $form['settings']['asu_brand']['asu_brand_header_version']['#value'] = '';
  return $form['settings']['asu_brand']['asu_brand_header_version'];
}


/**
 * Get the header version options as an associative array in the form of
 * array(
 *   'version' => description text,
 * );
 */
function asu_brand_get_version_options($reset = FALSE, $basepath = '') {
  // disabling the caching of version options to enable sensitivity to basepath changes.
  //$options = &drupal_static(__FUNCTION__);
  if ($reset || !isset($options)) {
    $options = array('' => t('Select a version'));
    
    // Use internal xml errors to provide user readable errors.
    libxml_use_internal_errors(TRUE);
    try {
      $items = new SimpleXMLElement((($basepath != '') ? $basepath : variable_get('asu_brand_header_basepath', ASU_BRAND_HEADER_BASEPATH_DEFAULT)).'/gtmheaders.xml', 0, TRUE);

      if ($items) {
        $brand_module_info = system_get_info('module', $name = 'asu_brand');
        $brand_module_version = (isset($brand_module_info['version'])) ? $brand_module_info['version'] : null;
        foreach ($items->header as $header) {
          $dep_min = (isset($header->compatibility->brand_module->min)) ? $header->compatibility->brand_module->min : null;
          $dep_max = (isset($header->compatibility->brand_module->max)) ? $header->compatibility->brand_module->max : null;

          if (asu_brand_dependencies_met($brand_module_version, $dep_min, $dep_max)) {
            $options[(string) $header->version] = t((string) $header->name);
          }
        }
        
        // Save options to variable table in case xml is not available at a later time.
        variable_set('asu_brand_version_options', $options);
      }
      else {
        // There was an error with loading the xml. Get versions from the
        // variable table.
        $options = variable_get('asu_brand_version_options', $options);
        
        $log_message = "Failed loading ASU header version XML file\n";
        foreach(libxml_get_errors() as $error) {
          $log_message .= "\t" . $error->message;
        }
        drupal_set_message($log_message, 'error');
      }
    }
    catch (Exception $e) {
      // There was an error with loading the xml. Get versions from the
      // variable table.
      $options = variable_get('asu_brand_version_options', $options);
        
      drupal_set_message('Failed loading ASU header version XML file. Please try again later. The full error description has been logged.', 'error');
      watchdog('asu_brand', $e, array(), WATCHDOG_ERROR);
    }
  }
  return $options;
}


function asu_brand_get_site_menu_options() {
  return menu_get_menus();
}

/**
 * Checks if passed brand module version meets the minimum
 *   and maximum versino dependancies
 * @param string $current_version
 * @param string $min_version
 * @param string $mac_version
 * @return boolean
 */
function asu_brand_dependencies_met($current_version, $min_version, $max_version) {

  if(count($curr_varr = explode('-', $current_version)) < 2) return FALSE;
  if(count($min_varr = explode('-', $min_version)) < 2) return FALSE;
  // min check
  if(floatval($curr_varr[0]) != floatval($min_varr[0])) return FALSE;

  $min_varr = explode('.', $min_varr[1]);
  $curr_varr = explode('.', $curr_varr[1]);

  if (count($min_varr) < 2 || count($curr_varr) < 2) return FALSE;

  if(floatval($curr_varr[1]) < floatval($min_varr[1])) return FALSE;
  // max check (optional)

  //Removed Max check
  /*if ($max_version) {
    if(count($max_varr = explode('-', $max_version)) < 2) return FALSE;
    if(floatval($curr_varr[0]) != floatval($max_varr[0])) return FALSE;

    if(floatval($curr_varr[1]) < floatval($max_varr[1])) return FALSE;
  }*/
  // all checks successful
  return TRUE;
}