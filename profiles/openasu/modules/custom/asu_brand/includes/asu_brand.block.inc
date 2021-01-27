<?php

/**
 * ASU Brand block generating functions.
 */

/**
 * Get ASU brand block settings.
 * @param bool $reset - Use cacbed block settings. Defaults to FALSE.
 * @return array|mixed|StdClass
 */
function asu_brand_get_block_settings($reset = FALSE) {
  $settings = &drupal_static(__FUNCTION__);

  if ($reset || !isset($settings)) {

    $settings = new StdClass;
    $settings->header_version = variable_get('asu_brand_header_version',
      ASU_BRAND_HEADER_VERSION_DEFAULT);
    // 4.x only
    $settings->head_path = ASU_BRAND_HEADER_BASEPATH_DEFAULT . '/' . $settings->header_version
      . '/heads/default.shtml';
    // 4.x ALL, 5.x cookie consent only
    $settings->header_path = ASU_BRAND_HEADER_BASEPATH_DEFAULT . '/' . $settings->header_version
      . '/headers/default.shtml';
    // 4.x only - DONE
    $settings->footer_path = ASU_BRAND_HEADER_BASEPATH_DEFAULT . '/' . $settings->header_version
      . '/includes/footer.shtml';
    // Both 4.x and 5.x
    $settings->gtm_path = ASU_BRAND_HEADER_BASEPATH_DEFAULT . '/' . $settings->header_version
      . '/includes/gtm.shtml';

    // Set javascript settings.
    $js_settings = array(
      'asu_sso_signedin' => (user_is_logged_in() ? 'true' : 'false'),
      'asu_sso_signinurl' => '',
      'asu_sso_signouturl' => '',
    );

    // Alter the signin/signout URL if cas in enabled.
    if (module_exists('cas')) {
      $js_settings['asu_sso_signinurl'] = url('cas', array(
        'https' => TRUE,
        'query' => drupal_get_destination()
      ));
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
 * Build the content of the WS1.0 header block.
 * @param int $ws_version
 * @return mixed|null
 */
function asu_brand_get_block_header($delta) {
  $settings = asu_brand_get_block_settings();
  $cache_id = ($delta === 'asu_brand_header_ws2') ? 'asu_brand:header_ws2' : 'asu_brand:header';

  // Set js settings, include js file, and inject head into <head>.
  asu_brand_head_inject();
  return asu_brand_get_asset_content($cache_id, $settings->header_path, $settings->header_version);
}

/**
 * Build the content of the footer block.
 * @param int $delta - Block delta value (machine name of the block)
 * @return mixed|null
 */
function asu_brand_get_block_footer($delta) {
  $settings = asu_brand_get_block_settings();
  $cache_id = ($delta === 'asu_brand_footer_ws2') ? 'asu_brand:footer_ws2' : 'asu_brand:footer';
  return asu_brand_get_asset_content($cache_id, $settings->footer_path, $settings->header_version);
}

/**
 * Get a block's content in this order as they are available:
 * 1. Regular Drupal cache.
 * 2. Off-site resource file.
 * 3. Long-cache stored in variable table (this is updated if #2 is performed).
 *
 * If $reset == TRUE, then skip #1.
 * @param string $cache_id
 * @param string $file_path
 * @param string $version - header version (4.x or 5.x)
 * @param bool $reset
 * @return mixed|null
 */
function asu_brand_get_asset_content($cache_id, $file_path, $version, $reset = FALSE) {
  if ($output = cache_get($cache_id)) {
    $output = $output->data;
  }
  if ($reset || $output == NULL || !isset($output)) {
    $module_path = drupal_get_path('module', 'asu_brand');
    // Render WS2.0 header w/Preact
    if ($cache_id === 'asu_brand:header_ws2') {
      global $base_url;
      $output = array(
        '#markup' => '<div id="headerContainer"></div>',
        '#attached' => array(
          'css' => array(
            drupal_get_path('module', 'asu_brand') . '/styles/styles_ws2.css'
          ),
          'js' => array(
            array(
              'type' => 'file',
              'data' => $module_path . '/scripts_ws2/vendor.production.js',
            ),
            array(
              'type' => 'file',
              'data' => $module_path . '/scripts_ws2/core.production.js',
            ),
            array(
              'type' => 'file',
              'data' => $module_path . '/scripts_ws2/render.js',
            ),
            array(
              'type' => 'setting',
              'data' => array('asu_brand' => array(
                'siteName' => variable_get('site_name'),
                'siteSubtitle' => variable_get('site_slogan'),
                'isLoggedIn' => user_is_logged_in(),
                'casLoginLink' => $base_url . '/cas',
                'casLogoutLink' => $base_url . '/caslogout',
                'navTree' => _asu_brand_create_json(),
              )),
            )
          )
        ),
      );
    }
    // Render WS2.0 footer - currently static in code
    elseif ($cache_id === 'asu_brand:footer_ws2') {
      $markup = <<<EOL
<div id="innovation-footer">
  <div id="innovation-bar">
    <div class="innovation-top">
      <div class="innovation-status">
        <nav aria-label="University Services">
                <ul class="default">
                <li class="footer-link"><a href="https://www.asu.edu/maps">Maps and Locations</a></li>
                <li class="footer-link"><a href="https://www.asu.edu/asujobs">Jobs</a></li>
                <li class="footer-link"><a href="https://isearch.asu.edu">Directory</a></li>
                <li class="footer-link"><a href="https://www.asu.edu/contactasu/">Contact ASU</a></li>
                <li class="footer-link"><a href="https://my.asu.edu/">My ASU</a></li>
                </ul>
        </nav>
      </div>
      <div class="innovation-image">
        <a href="https://www.asu.edu/rankings"><img src="//www.asu.edu/asuthemes/5.0/assets/Number-1-in-the-us-for-innovation@2x.png" alt="Number 1 in the United States for Innovation" /></a>
      </div>
    </div>
  </div>
  <div class="footer-menu">
        <nav class="nav colophon" aria-label="University Legal and Compliance">
        <ul class="default">
          <li class="footer-link"><a href="https://www.asu.edu/copyright/">Copyright and Trademark</a></li>
          <li class="footer-link"><a href="https://www.asu.edu/accessibility/">Accessibility</a></li>
          <li class="footer-link"><a href="https://www.asu.edu/privacy/">Privacy</a></li>
          <li class="footer-link"><a href="https://www.asu.edu/tou/">Terms of Use</a></li>
          <li class="footer-link"><a href="https://www.asu.edu/emergency/">Emergency</a></li>
        </ul>
    </nav>
  </div>
</div>
EOL;
      $output = array(
        '#markup' => $markup,
        '#attached' => array(
          'css' => array(
            $module_path . '/styles/footer_ws2.css',
          ),
        ),
      );
      cache_set($cache_id, $output, 'cache', time() + ASU_BRAND_CACHE_LIFETIME);
      variable_set($cache_id, $output);
    }

    // Render GTM header
    elseif ($cache_id === 'asu_brand:gtm') {
      $markup = <<<EOL
<!-- Google Tag Manager ASU Universal-->
<noscript><iframe src="//www.googletagmanager.com/ns.html?id=GTM-KDWN8Z"
                  height="0" width="0" style="display:none;visibility:hidden"></iframe></noscript>
<script>(function(w,d,s,l,i){w[l]=w[l]||[];w[l].push({'gtm.start':
        new Date().getTime(),event:'gtm.js'});var f=d.getElementsByTagName(s)[0],
    j=d.createElement(s),dl=l!='dataLayer'?'&l='+l:'';j.async=true;j.src=
    '//www.googletagmanager.com/gtm.js?id='+i+dl;f.parentNode.insertBefore(j,f);
})(window,document,'script','dataLayer','GTM-KDWN8Z');</script>
<!-- End Google Tag Manager ASU Universal -->
EOL;
      $output = array(
        '#markup' => $markup,
      );
      cache_set($cache_id, $output, 'cache', time() + ASU_BRAND_CACHE_LIFETIME);
      variable_set($cache_id, $output);
    }

    else { // Possible WS1.0 assets needed? Depends on version requested.
      if ($version === '5.0') { // Skip AFS assets for v5.0
        if ($cache_id === 'asu_brand:footer' || $cache_id === 'asu_brand:head') {
          return '<!-- No ' . $cache_id . ' from AFS for v5.x -->';
        } elseif ($cache_id === 'asu_brand:header') {
          return _asu_brand_get_cookie_consent($cache_id);
        }
      }
      else { // Render WS1.0 header + footer from AFS or cached version (legacy block)
        // Set timeout to 1.5 seconds.  if it takes too long, fall back to long term caching
        $options = array(
          'timeout' => 1.5
        );
        $output = drupal_http_request($file_path, $options);
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
    }
  }
  return $output;
}

/**
 * Inject the head file into <head>. The order of the injections matter due to
 * how the includes are updating the header.
 */
function asu_brand_head_inject() {

  $suffix = (variable_get('asu_brand_header_version', 'stable') === '5.0') ? '_ws2' : '';
  $overrides = variable_get('asu_brand_header' . $suffix . '_do_not_override', '["www.asu.edu"]');
  $settings = asu_brand_get_block_settings();
  $cache_id = 'asu_brand:head';

  $settings->js_settings['overrides'] = $overrides;
  $head_output = asu_brand_get_asset_content($cache_id, $settings->head_path, $settings->header_version);
  drupal_add_js(array('asu_brand' => $settings->js_settings), 'setting');
  drupal_add_html_head(array('#type' => 'markup', '#markup' => $head_output, '#weight' => -99), 'asu_brand_head');

  // Likely only necessary for header v4.x...
  // Inject header javascript into <head> and set the weight to a high negative value.
  $asu_sso_signedin = $settings->js_settings['asu_sso_signedin'];
  $asu_sso_signinurl = $settings->js_settings['asu_sso_signinurl'];
  $asu_sso_signouturl = $settings->js_settings['asu_sso_signouturl'];

  $inline_script = <<<EOL
   <script type="text/javascript">
    <!--//--><![CDATA[//><!--

    var overrides = $overrides;
    var hostname = window.location.hostname;
    var ASUHeader = ASUHeader || {};

    if (overrides.indexOf(hostname) == -1) {
        ASUHeader.user_signedin = $asu_sso_signedin;
        ASUHeader.signout_url = "$asu_sso_signouturl";
    }

    //--><!]]>
  </script>
EOL;

  drupal_add_html_head(array('#type' => 'markup', '#markup' => $inline_script, '#weight' => -100), 'asu_brand_head_js');

  // For 4.x only
  if ($settings->header_version !== "5.0") {
    drupal_add_html_head(array('#type' => 'markup', '#markup' => $head_output, '#weight' => -99), 'asu_brand_head');
    drupal_add_js(array('asu_brand' => $settings->js_settings), 'setting');
  }

  // This appears to repeat the inline script above(?)
  drupal_add_js(drupal_get_path('module', 'asu_brand') . '/asu_brand.js', array()); // Repeats the above inline JS
}

/**
 * Return Cookie Consent markup
 *
 * @param string $cache_id - Cache ID
 * @return string
 */
function _asu_brand_get_cookie_consent($cache_id) {
  return <<<EOL
<!-- Partial ' . $cache_id . ' asset for v5.x -->
<link rel="stylesheet" type="text/css" href="https://www.asu.edu/asuthemes/5.0/vendor/cookieconsent/cookieconsent.min.css"/>
<script src="https://www.asu.edu/asuthemes/5.0/vendor/cookieconsent/cookieconsent.min.js"></script>
<!-- End Partial ' . $cache_id . ' asset for v5.x -->
EOL;
}
