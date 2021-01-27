<?php
/**
 * @file
 * Contains the GTM snippet insertion code.
 *
 * @author Chandi Cumaranatunge
 */

/**
 * Implements callback_post_render().
 *
 * Inserts GTM snippet as immediate child of the opening body tag.
 */
function asu_brand_page_process(&$children, $elements) {
  if (asu_brand_is_header_visible($elements)) {
    // Added check for testing - Hide GTM code during testing
    if (variable_get('asu_brand_ci_testing', 0) !== 1 ) {
       module_load_include('inc', 'asu_brand', 'includes/asu_brand.block');
       $suffix = (variable_get('asu_brand_header_version', 'stable') === '5.0' ? '_ws2' : '');
       $custom_gtm = variable_get('asu_brand_header' . $suffix . '_gtm_override', '');
       $gtm = (trim($custom_gtm) != '') ? $custom_gtm : asu_brand_get_default_gtm();
       // Convert GTM from render array into raw code again
       $gtm = $gtm['#markup'];
     }
    else {
      $gtm = '<!--GTM Code removed for testing -->';
    }
    // Insert snippet after the opening body tag.
    if ($gtm) {
      $children = preg_replace('@<body[^>]*>@', '$0' . $gtm, $children, 1);
    }
  }
  return $children;
}

/**
 * Checks if ASU Brand header is visible on current page
 * @param array $elements
 *   Render array of page elements
 * @return bool
 */
function asu_brand_is_header_visible($elements) {
  $module_name = basename(__FILE__, '.gtm.inc');
  $needle = '|^' . $module_name . '_asu_brand_header|';
  foreach ($elements as $region_key => $region) {
    if (($region_key[0] != '#') && is_array($region)) {
      foreach ($region as $block_key => $block) {
        if (preg_match($needle, $block_key) !== FALSE) {
          return TRUE;
        }
      }
    }
  }
  return FALSE;
}

/**
 * Get GTM snippet from header assets
 */
function asu_brand_get_default_gtm() {
  $settings = asu_brand_get_block_settings();
  return asu_brand_get_asset_content('asu_brand:gtm', $settings->gtm_path, $settings->header_version);
}
