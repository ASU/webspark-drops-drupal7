<?php

/**
 * Determine type of site environment (dev, test, or live)
 * NOTE: This will work for all Pantheon sites, but everywhere else it won't
 * catch everything. The "test mode" setting will have to catch the rest.
 * @return array $env - Type of environment (dev, qa, or prod), and endpoint_access (T/F).
 */
function asu_libs_detect_environment() {
  $env = &drupal_static(__FUNCTION__);
  if (!isset($env)) {
    $env = array(
      'type' => '',
      'endpoint_access' => true,
    );
    global $base_url;
    // Pantheon ENVs
    if (defined('PANTHEON_ENVIRONMENT')) {
      if ($_ENV["PANTHEON_ENVIRONMENT"] === 'live') {
        $env['type'] = 'prod_pantheon';
      }
      elseif ($_ENV["PANTHEON_ENVIRONMENT"] === 'test') {
        $env['type'] = 'qa';
      } else { // All remaining multidevs + Dev ENV
        $env['type'] = 'dev';
      }
      $env['endpoint_access'] = false; // No access to Enterprise dev/QA web service endpoints
    }
    else {
      // Local development - most local development URLs
      if (strpos($base_url, '://localhost') !== FALSE
        || strpos($base_url, '://192.168.') !== FALSE
        || strpos($base_url, '://127.') !== FALSE
        || strpos($base_url, '://10.') !== FALSE) {
        $env['type'] = 'dev';
      }
      // Non-Pantheon ENVs checks for Enterprise Drupal.
      elseif ((preg_match('#^http(s?)://dev-#', $base_url) === 1) && (strpos($base_url, '-dev.'))) {
        $env['type'] = 'dev';
      }
      elseif ((preg_match('#^http(s?)://(test|qa)-#', $base_url) === 1)
        || (strpos($base_url, '-qa.') !== FALSE || strpos($base_url, '-test.') !== FALSE)) {
        $env['type'] = 'qa';
      } else {
        $env['type'] = 'prod_not-pantheon';
      }
    }
  }
  return $env;
}

/**
 * Detect the user's OS
 * @return int|string
 */
function asu_libs_detect_os() {
  $current_os = "unknown";
  $os_list = array(
    'Windows 7' => '(Windows NT 6\.1)',
    'Windows Vista' => '(Windows NT 6\.0)',
    'Windows XP' => '(Windows NT 5\.1)|(Windows XP)',
    'Mac OS' => '(Mac_PowerPC)|(Macintosh)',
    'Linux' => '(Linux)|(X11)',
    'Search Bot' => '(nuhk)|(Googlebot)|(Yammybot)|(Openbot)|(Slurp)|(MSNBot)|(Ask Jeeves\/Teoma)|(ia_archiver)',
    'Windows 3.11' => 'Win16',
    'Windows 95' => '(Windows 95)|(Win95)|(Windows_95)',
    'Windows 98' => '(Windows 98)|(Win98)',
    'Windows 2000' => '(Windows NT 5\.0)|(Windows 2000)',
    'Windows Server 2003' => '(Windows NT 5\.2)',
    'Windows NT 4.0' => '(Windows NT 4\.0)|(WinNT4\.0)|(WinNT)|(Windows NT)',
    'Windows ME' => '(Windows 98)|(Win 9x 4\.90)|(Windows ME)',
    'Open BSD' => 'OpenBSD',
    'Sun OS' => 'SunOS',
    'QNX' => 'QNX',
    'BeOS' => 'BeOS',
    'OS/2' => 'OS\/2'
  );

  if (isset($_SERVER['HTTP_USER_AGENT'])) {
    foreach ($os_list as $current_os => $match) {
      if (preg_match('#' . $match . '#i', $_SERVER['HTTP_USER_AGENT'])) {
        break;
      }
    }
  }
  return $current_os;
}

/**
 * Detect the user's browser.
 * @return string
 */
function asu_libs_detect_browser() {
  $browser = 'unknown';
  if (isset($_SERVER['HTTP_USER_AGENT'])) {
    $u_agent = $_SERVER['HTTP_USER_AGENT'];
    if (stripos($u_agent, 'MSIE') !== FALSE) {
      $browser = "IE";
    }
    elseif (stripos($u_agent, 'Chrome') !== FALSE) {
      $browser = "Chrome";
    }
    elseif (stripos($u_agent, 'Firefox') !== FALSE) {
      $browser = "Firefox";
    }
    elseif (stripos($u_agent, 'Safari') !== FALSE) {
      $browser = "Safari";
    }
    elseif (stripos($u_agent, 'Flock') !== FALSE) {
      $browser = "Flock";
    }
    elseif (stripos($u_agent, 'Opera') !== FALSE) {
      $browser = "Opera";
    }
  }
  return $browser;
}
