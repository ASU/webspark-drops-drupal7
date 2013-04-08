<?php

/**
 * ASU Brand block generating functions.
 */

/**
 * Build the content of the header block. Use a manually cached
 * version, if available.
 */
function asu_brand_get_block_header() {
  // Set the header settings for the injected javascript into <head>.
  $asu_sso_signedin = (user_is_logged_in() ? 'true' : 'false');
  
  // Alter the signin/signout URL if cas in enabled.
  if(module_exists('cas')) {
    $asu_sso_signinurl = url('cas', array('https' => TRUE, 'query' => cas_login_destination()));
    $asu_sso_signouturl = url('caslogout', array('https' => TRUE));
  }
  else {
    $asu_sso_signinurl = url('user/login', array('query' => user_login_destination()));
    $asu_sso_signouturl = url('user/logout');
  }
  
  // Inject header javascript into <head> and set the weight to a high negative value.
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
  drupal_add_html_head(array('#type' => 'markup', '#markup' => $inline_script, '#weight' => -100), 'asu_brand_head_js');
  
  // Build the head and header file paths.
  $header_version = variable_get('asu_brand_header_version', ASU_BRAND_HEADER_VERSION_DEFAULT);
  $header_basebath = variable_get('asu_brand_header_basepath', ASU_BRAND_HEADER_BASEPATH_DEFAULT);
  $header_template = variable_get('asu_brand_header_template', ASU_BRAND_HEADER_TEMPLATE_DEFAULT);
  
  $cache = array('asu_brand:head', 'asu_brand:header');
  $cache = cache_get_multiple($cache);
  
  // Get the cached version of head, if available. Inject the head file into
  // <head>. The weight of this item must occur after the injection of the
  // header javascript.
  if (isset($cache['asu_brand:head'])) {
    $head_output = $cache['asu_brand:head']->data;
  }
  else {
    $head_path = $header_basebath . '/' . $header_version . '/heads/' . $header_template . '.shtml';
    if ($head_output = file_get_contents($head_path)) {
      cache_set('asu_brand:head', $head_output, 'cache', time() + ASU_BRAND_CACHE_LIFETIME);
    }
    else {
      $head_output = '';
      watchdog('asu_brand', 'Unable to load @path to the cache.', array('@path' => $head_path), WATCHDOG_ERROR);
    }
  }
  drupal_add_html_head(array('#type' => 'markup', '#markup' => $head_output, '#weight' => -99), 'asu_brand_head');
  
  // Get the cached version of header, if available.
  if (isset($cache['asu_brand:header'])) {
    $output = $cache['asu_brand:header']->data;
  }
  else {
    $header_path = $header_basebath . '/' . $header_version . '/headers/' . $header_template . '.shtml';
    if ($output = file_get_contents($header_path)) {
      cache_set('asu_brand:header', $output, 'cache', time() + ASU_BRAND_CACHE_LIFETIME);
    }
    else {
      $output = '';
      watchdog('asu_brand', 'Unable to load @path to the cache.', array('@path' => $header_path), WATCHDOG_ERROR);
    }
  }
  
  // Return the content from the ASU header.
  return $output;
}

/**
 * Build the content of the footer block. Use a manually cached
 * version, if available.
 */
function asu_brand_get_block_footer() {
  if ($cache = cache_get('asu_brand:footer')) {
    $output = $cache->data;
  }
  else {
    $header_version = variable_get('asu_brand_header_version', ASU_BRAND_HEADER_VERSION_DEFAULT);
    $header_basebath = variable_get('asu_brand_header_basepath', ASU_BRAND_HEADER_BASEPATH_DEFAULT);
    $footer_color = variable_get('asu_brand_footer_color', ASU_BRAND_FOOTER_COLOR_DEFAULT);
    $path = $header_basebath . '/' . $header_version . '/includes/footer' . $footer_color . '.shtml';
    if ($output = file_get_contents($path)) {
      cache_set('asu_brand:footer', $output, 'cache', time() + ASU_BRAND_CACHE_LIFETIME);
    }
    else {
      $output = '';
      watchdog('asu_brand', 'Unable to load @path to the cache.', array('@path' => $path), WATCHDOG_ERROR);
    }
  }
  return $output;
}

/**
 * Build the content of the students footer block. Use a manually cached
 * version, if available.
 */
function asu_brand_get_block_students_footer() {
  if ($cache = cache_get('asu_brand:students_footer')) {
    $output = $cache->data;
  }
  else {
    $header_version = variable_get('asu_brand_header_version', ASU_BRAND_HEADER_VERSION_DEFAULT);
    $header_basebath = variable_get('asu_brand_header_basepath', ASU_BRAND_HEADER_BASEPATH_DEFAULT);
    $path = $header_basebath . '/' . $header_version . '/includes/students_footer.shtml';
    if ($output = file_get_contents($path)) {
      cache_set('asu_brand:students_footer', $output, 'cache', time() + ASU_BRAND_CACHE_LIFETIME);
    }
    else {
      $output = '';
      watchdog('asu_brand', 'Unable to load @path to the cache.', array('@path' => $path), WATCHDOG_ERROR);
    }
  }
  return $output;
}
