<?php

/**
 * @file
 * Contains the GTM snippet insertion code.
 *
 * @author Chandi Cumaranatunge
 */


/*********************************************************************
 DRUPAL HOOKS
*********************************************************************/

/**
 * Implements callback_post_render().
 *
 * Inserts GTM snippet as immediate child of the opening body tag.
 */
function asu_brand_page_process(&$children, $elements) {
  
  if (asu_brand_is_header_visible($elements)) {
     $custom_gtm = variable_get('asu_brand_gtm_override', '');
     $gtm = (trim($custom_gtm) != '') ? $custom_gtm : asu_brand_get_gtm_snippet();
     if ($gtm) {
      // Insert snippet after the opening body tag.
      $children = preg_replace('@<body[^>]*>@', '$0' . $gtm, $children, 1);
    }
  }
  
  return $children;
}


/*********************************************************************
 INTERNAL
*********************************************************************/

/**
 * Checks if ASU Brand header is visible on current page
 * @param array $elements
 *   Render array of page elements
 */
function asu_brand_is_header_visible($elements) {
  $module_name = basename(__FILE__, '.gtm.inc');
  foreach ($elements as $region_key => $region) {
  if (($region_key[0] != '#') && is_array($region)) {
      foreach ($region as $block_key => $block) {
        if ($block_key == $module_name.'_'.ASU_BRAND_HEADER_DELTA) {
          return TRUE;
        }
      }
    }
  }
  return false;
}


/**
 * Get GTM snippet from header assets
 */
function asu_brand_get_gtm_snippet() {
  $settings = asu_brand_get_block_settings();
  $cache_id = 'asu_brand:gtm';

  return asu_brand_get_cached_content($cache_id, $settings->gtm_path);
}