<?php

/**
 * ASU Brand block generating functions.
 */

/**
 * Get ASU brand block settings.
 */
function asu_brand_get_block_settings($reset = FALSE) {
  $settings = &drupal_static(__FUNCTION__);
  if ($reset || !isset($settings)) {
    $settings = new StdClass;
    $settings->header_version = variable_get('asu_brand_header_version', ASU_BRAND_HEADER_VERSION_DEFAULT);
    $settings->header_basebath = variable_get('asu_brand_header_basepath', ASU_BRAND_HEADER_BASEPATH_DEFAULT);
    $settings->header_template = variable_get('asu_brand_header_template', ASU_BRAND_HEADER_TEMPLATE_DEFAULT);
    $settings->footer_color = variable_get('asu_brand_footer_color', ASU_BRAND_FOOTER_COLOR_DEFAULT);
    $settings->head_path = $settings->header_basebath . '/' . $settings->header_version . '/heads/' . $settings->header_template . '.shtml';
    $settings->header_path = $settings->header_basebath . '/' . $settings->header_version . '/headers/' . $settings->header_template . '.shtml';
    $settings->footer_path = $settings->header_basebath . '/' . $settings->header_version . '/includes/footer' . $settings->footer_color . '.shtml';
    $settings->gtm_path = $settings->header_basebath . '/' . $settings->header_version . '/includes/gtm.shtml';
    $settings->students_footer_path = $settings->header_basebath . '/' . $settings->header_version . '/includes/students_footer.shtml';
    
    // Set javascript settings.
    $js_settings = array(
      'asu_sso_signedin' => (user_is_logged_in() ? 'true' : 'false'),
      'asu_sso_signinurl' => '',
      'asu_sso_signouturl' => '',
    );
    // Alter the signin/signout URL if cas in enabled.
    if(module_exists('cas')) {
      $js_settings['asu_sso_signinurl'] = url('cas', array('https' => TRUE, 'query' => drupal_get_destination()));
      $js_settings['asu_sso_signouturl'] = url('caslogout', array('https' => TRUE));
    }
    else {
      $js_settings['asu_sso_signinurl'] = url('user/login', array('query' => user_login_destination()));
      $js_settings['asu_sso_signouturl'] = url('user/logout');
    }
    $settings->js_settings = $js_settings;
    
    // Get cached data.
    $cache_ids = asu_brand_get_cache_ids();
    $settings->cache = cache_get_multiple($cache_ids);
    $settings->long_term_cache = array();
    foreach ($cache_ids as $cache_id) {
      $settings->long_term_cache[$cache_id] = variable_get($cache_id, NULL);
    }
  }
  
  return $settings;
}

/**
 * Get a block's content in this order as they are available:
 * 1. Regular Drupal cache.
 * 2. Off-site resource file.
 * 3. Long-cache stored in variable table (this is updated if #2 is performed).
 *
 * If $reset == TRUE, then skip #1.
 */
function asu_brand_get_cached_content($cache_id, $file_path, $reset = FALSE) {

  if($output = cache_get($cache_id)) {
    $output = $output->data;
  }

  if ($reset || $output==NULL || !isset($output)) {

    // set timeout to 1.5 seconds.  if it takes too long, fall back
    // to long term caching
    $options = array(
      'timeout' => 1.5
    );

    $output = drupal_http_request($file_path, $options);

    //if ($output = drupal_http_request($file_path)) {//$output = file_get_contents($file_path)) {
    if ($output->code == 200) {
      $output = $output->data;

      cache_set($cache_id, $output, 'cache', time() + ASU_BRAND_CACHE_LIFETIME);
      variable_set($cache_id, $output);
    } else {
      // File resource is not available; use long term cache and cache it for 1 hour.
      $output = variable_get($cache_id, NULL);
      cache_set($cache_id, $output, 'cache', time() + 3600);
      watchdog('asu_brand', 'Unable to load @path to the cache; using long term cache.', array('@path' => $file_path), WATCHDOG_ERROR);
    }
  }
  
  return $output;
}

/**
 * Build the content of the header block.
 */
function asu_brand_get_block_header() {
  $settings = asu_brand_get_block_settings();
  $cache_id = 'asu_brand:header';
  
  // Set js settings, include js file, and inject head into <head>.
  asu_brand_head_inject();
  
  return asu_brand_get_cached_content($cache_id, $settings->header_path);
}

/**
 * Build the content of the footer block.
 */
function asu_brand_get_block_footer() {
  $settings = asu_brand_get_block_settings();
  $cache_id = 'asu_brand:footer';
  return asu_brand_get_cached_content($cache_id, $settings->footer_path);
}

/**
 * Build the content of the students footer block.
 */
function asu_brand_get_block_students_footer() {
  $settings = asu_brand_get_block_settings();
  $cache_id = 'asu_brand:students_footer';
  return asu_brand_get_cached_content($cache_id, $settings->students_footer_path);
}

/**
 * Inject the head file into <head>. The order of the injections matter due to
 * how the includes are updating the header.
 */
function asu_brand_head_inject() {
  $settings = asu_brand_get_block_settings();
  $cache_id = 'asu_brand:head';
  
  $head_output =  asu_brand_get_cached_content($cache_id, $settings->head_path);

  // Inject header javascript into <head> and set the weight to a high negative value.
  $asu_sso_signedin = $settings->js_settings['asu_sso_signedin'];
  $asu_sso_signinurl = $settings->js_settings['asu_sso_signinurl'];
  $asu_sso_signouturl = $settings->js_settings['asu_sso_signouturl'];
  $inline_script = <<<EOL
   <script type="text/javascript">
    <!--//--><![CDATA[//><!--
    var ASUHeader = ASUHeader || {};
    ASUHeader.user_signedin = $asu_sso_signedin;
    ASUHeader.signin_url = "$asu_sso_signinurl";
    ASUHeader.signout_url = "$asu_sso_signouturl";
    //--><!]]>
  </script>
EOL;
  
  // TODO: If asu.edu/asuthemes/x/headers/default.shtml and asu.edu/asuthemes/x/js/asu_header.js
  // get updated we can remove the first drupal_add_html_head() and $inline_script above.
  drupal_add_js(array('asu_brand' => $settings->js_settings), 'setting');
  drupal_add_js(drupal_get_path('module', 'asu_brand') . '/asu_brand.js', array());
  drupal_add_html_head(array('#type' => 'markup', '#markup' => $inline_script, '#weight' => -100), 'asu_brand_head_js');
  drupal_add_html_head(array('#type' => 'markup', '#markup' => $head_output, '#weight' => -99), 'asu_brand_head');
}