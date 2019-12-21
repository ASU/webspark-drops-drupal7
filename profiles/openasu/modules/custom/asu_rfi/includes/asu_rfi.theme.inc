<?php /** @noinspection PhpUnused */
/** @noinspection PhpDocSignatureInspection */

/*********************************************************************
 * THEMING
 *********************************************************************/

/**
 * Implements hook_js_alter().
 */
function asu_rfi_js_alter(&$javascript) {
  // Form API #states works only with Jquery 1.5, so altering JS version only
  // form ASU RFI block settings page to jQuery 1.5 or core.
  if ((arg(4) == 'multiblock') && variable_get('jquery_update_jquery_version', FALSE) == '1.7') {
    $javascript['profiles/openasu/modules/contrib/jquery_update/replace/misc/1.7/states.js'] = array(
      'data' => drupal_get_path('core', '') . 'misc/states.js',
      'group' => '-100',
      'weight' => '1.019',
      'version' => '7.32',
      'type' => "file",
      'cache' => TRUE,
      'every_page' => FALSE,
      'preprocess' => TRUE,
      'defer' => FALSE,
      'scope' => 'header'
    );
  }
}

/**
 * Implements hook_preprocess_page().
 */
// Send data transaction variable dataLayer to GTM JS object.
// Get degree mappings to grab content type specific values.
function asu_rfi_preprocess_page(&$variables) {
  $degreeMappings = _asu_rfi_get_degree_field_mappings();

  // If /degree-programs/request-info-thank-you is loaded, then grab the node
  // id from the URL, load the node and get the variables, and add Google
  // analytics code to the header.
  if (isset($variables['theme_hook_suggestions'][1])) {

    if ($variables['theme_hook_suggestions'][1] == "page__degree_programs__request_info_thank_you") {

      $nodeid = base64_decode(arg(2));
      // Get node data
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', 'node')
        ->entityCondition('bundle', 'asu_rfi')
        ->propertyCondition('nid', $nodeid)
        ->addMetaData('account', user_load(1)); // Run the query as user 1.

      $result = $query->execute();
      if (isset($result['node'])) {
        $items_nids = array_keys($result['node']);
        $items = entity_load('node', $items_nids);
      } else {
        $items = array();
        watchdog('asu_rfi', __FUNCTION__ . ' - No asu_rfi nodes selected.', array(), WATCHDOG_NOTICE);
      }

      $price = $locale = 'unset';

      foreach ($items as $nid => $submissions) {
        $sub_wrapper = entity_metadata_wrapper('node', $submissions);
        $prog_full_name = (!empty($sub_wrapper->field_rfi_program_name)) ? $sub_wrapper->field_rfi_program_name->value() : '';
        $plan_code = (!empty($sub_wrapper->field_rfi_program)) ? $sub_wrapper->field_rfi_program->value() : '';
        $program_code = (!empty($sub_wrapper->field_rfi_college_code)) ? $sub_wrapper->field_rfi_college_code->value() : '';
        $program_name = (!empty($sub_wrapper->field_rfi_college_name)) ? $sub_wrapper->field_rfi_college_name->value() : '';
        $prospect_level = (!empty($sub_wrapper->field_rfi_prospect_level)) ? $sub_wrapper->field_rfi_prospect_level->value() : '';
        $zip = (!empty($sub_wrapper->field_rfi_zipcode)) ? $sub_wrapper->field_rfi_zipcode->value() : '';
        $country = (!empty($sub_wrapper->field_rfi_country)) ? $sub_wrapper->field_rfi_country->value() : '';
      }
      $host = explode(".", $_SERVER['HTTP_HOST']);
      $subdomain = array_shift($host);
      $sku = (isset($program_code) && isset($plan_code)) ? $program_code . $plan_code . '-RFI' : 'unset-RFI';
      $ga_id = (isset($nid)) ? $subdomain . '-' . variable_get('asu_rfi_google_analytics_key') . '-' . $nid : '';
      $category = 'RFI';
      $zip_section = (isset($zip)) ? substr($zip, 0, 2) : '00000';

      if (isset($country)) {
        if ($country == "United States") {
          if (!empty($zip_section) && (($zip_section == "85") || ($zip_section == "86"))) {
            $price = '100.00';
            $locale = 'In State';
          }
          else {
            $price = '200.00';
            $locale = 'Out of State';
          }
        }
        else {
          if (!empty($country) && $country !== "United States") {
            $price = '300.00';
            $locale = "International";
          }
          else {
            $price = '100';
            $locale = 'Online';
          }
        }
      }

      $college = (isset($prog_full_name)) ? 'RFI - ' . $locale . ' - ' . $prog_full_name : '';
      $program_code = (isset($program_code)) ? $program_code : '';

      drupal_add_js("(function ($) {
        dataLayer = [{
           'event': 'ecommerce_event',
           'transactionId': '$ga_id',
          'transactionAffiliation': '$program_code',
          'transactionTotal': '$price',
          'transactionProducts': [{
                'sku': '$sku',
                'name': '$college',
                'category': '$category',
                'price': '$price',
                'quantity': '1'
              }]
            }];
        })(jQuery)", array(
        'type' => 'inline',
        'scope' => 'header',
        'weight' => 0
      ));
    }

    // If confirmation node ID specified in module settings page is called instead:

    else {
      $undergrad_confirm_nid = variable_get('asu_rfi_undergrad_confirm_node');
      $grad_confirm_nid = variable_get('asu_rfi_grad_confirm_node');

      if (isset($variables['node']) && ($variables['node']->nid == $undergrad_confirm_nid || $variables['node']->nid == $grad_confirm_nid)) {
        if (isset($_GET['pro']) || isset($_GET['ccode']) || isset($_GET['maj']) || isset($_GET['sub'])) {
          //$college = base64_decode($_GET['pro']); // NOT USED??
          //$college_rfi = $college . " - RFI"; // NOT USED??
          $college_code = base64_decode($_GET['ccode']);
          $major = base64_decode($_GET['maj']);
          $major_rfi = $college_code . '-RFI';
          $sku = $college_code . $major . '-RFI';
          $nid = base64_decode($_GET['sub']);
          $zip = base64_decode($_GET['zcode']);
          $country = base64_decode($_GET['con']);
          $zip_section = substr($zip, 0, 2);
          $category = 'RFI';
          $tmp_host = explode(".", $_SERVER['HTTP_HOST']);
          $subdomain = array_shift($tmp_host);
          $ga_id = $subdomain . '-' . variable_get('asu_rfi_google_analytics_key') . '-' . $nid;
          $price = '300.00';
          if ($country == "United States") {
            if (!empty($zip_section)) {
              if (($zip_section == "85") || ($zip_section == "86")) {
                $price = '100.00';
              }
              else {
                $price = '200.00';
              }
            }
          }
          drupal_add_js("(function ($) {
          dataLayer = [{
             'event': 'ecommerce_event',
             'transactionId': '$ga_id',
             'transactionAffiliation': '$college_code',
             'transactionTotal': '$price',
             'transactionProducts': [{
                'sku': '$sku',
                'name': '$major_rfi',
                'category': '$category',
                'price': '$price',
                'quantity': '1'
              }]
         }];
       })(jQuery)", array(
            'type' => 'inline',
            'scope' => 'header',
            'weight' => 0
          ));
        }
      }
      else {
        $thisNode = menu_get_object();
        if (isset($thisNode->type) && $thisNode->type == $degreeMappings['content_type'] && isset($_SESSION['rfi_data'])) {

          $price = '100.00';
          $category = 'RFI';
          $nid = $thisNode->nid;
          $college_code = $_SESSION['rfi_data']['college'];
          $college = $_SESSION['rfi_data']['college_name'];
          $program_code = $_SESSION['rfi_data']['program_code'];
          $country = $_SESSION['rfi_data']['country'];
          $zip_section = $_SESSION['rfi_data']['zipcode'];
          if (isset($nid) && isset($college_code) && isset($college) && isset($program_code) && isset($country) && isset($zip_section)) {
            $ga_id = variable_get('asu_rfi_google_analytics_key') . '-' . $nid;
            $sku = $college_code . $program_code . '-RFI';
            if ($country == "United States") {
              if (!empty($zip_section)) {
                if (($zip_section == "85") || ($zip_section == "86")) {
                  $price = '100.00';
                }
                else {
                  $price = '200.00';
                }
              }
            }
            else {
              $price = '300.00';
            }
            drupal_add_js("(function ($) {
                   if($('#asu-rfi-multi-part1-thanks')){
                    dataLayer = [{
                      'event': 'ecommerce_event',
                      'transactionId': '$ga_id',
                      'transactionAffiliation': '$program_code',
                      'transactionTotal': '$price',
                      'transactionProducts': [{
                        'sku': '$sku',
                        'name': '$college',
                        'category': '$category',
                        'price': '$price',
                        'quantity': '1'
                      }]
                    }];
                   }
                })(jQuery)", array(
              'type' => 'inline',
              'scope' => 'header',
              'weight' => 0
            ));
          }
        }
      }
    }
  }
}
