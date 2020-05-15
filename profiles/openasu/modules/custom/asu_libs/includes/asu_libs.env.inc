<?php

/**
 * Determine type of site environment (dev, test, or live)
 * NOTE: This will work for all Pantheon sites, but everywhere else it won't
 * catch everything.
 * @return string (str) $env - Type of environment (dev, qa, or prod).
 */
function asu_libs_get_environment_type() {
  $env = &drupal_static(__FUNCTION__);
  if (!isset($env)) {
    global $base_url;
    // Pantheon ENVs
    if (defined('PANTHEON_ENVIRONMENT')) {
      if ($_ENV["PANTHEON_ENVIRONMENT"] === 'live') {
        $env = 'prod_pantheon';
      } elseif ($_ENV["PANTHEON_ENVIRONMENT"] === 'test') {
        $env = 'qa';
      } else { // All remaining multidevs + Dev ENV
        $env = 'dev';
      }
    }
    else {
      // Local development - most local development URLs
      if (strpos($base_url, '://localhost') !== FALSE
        || strpos($base_url, '://192.168.') !== FALSE
        || strpos($base_url, '://127.') !== FALSE
        || strpos($base_url, '://10.') !== FALSE) {
        $env = 'dev';
      }
      // Non-Pantheon ENVs checks for Enterprise Drupal.
      elseif ((preg_match('#^http(s?)://dev-#', $base_url) === 1) && (strpos($base_url, '-dev.'))) {
        $env = 'dev';
      }
      elseif ((preg_match('#^http(s?)://(test|qa)-#', $base_url) === 1)
        || (strpos($base_url, '-qa.') !== FALSE || strpos($base_url, '-test.') !== FALSE)) {
        $env = 'qa';
      } else {
        $env = 'prod_not-pantheon';
      }
    }
  }
  return $env;
}

/**
 * Detect access to endpoint/middleware/data resources (ASU Enterprise, behind ASU firewall, etc.)
 *
 * @param string $module - machine name of module setting value (ex. asu_rfi, etc.)
 * @param string $data_type - Ex. 'start_date', 'degrees'. Left blank, does general access check.
 * @param string $url - URL inside the enterprise ENV to check. If blank, does general access check to "Enterprise" space.
 * @param int $timeout - cURL timeout for request. Defaults to 5 seconds.
 */
function asu_libs_set_asset_access_value($module, $data_type = '', $url = "https://webapp4-qa.asu.edu", $timeout = 5) {
  $curl = curl_init($url);
  $timeout = (int) $timeout;
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE); // If you don't want to use any of the return information, set to false
  curl_setopt($curl, CURLOPT_SSLVERSION, 1); // This will set the security protocol to TLSv1
  curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);
  curl_setopt($curl, CURLOPT_CONNECTTIMEOUT, $timeout); // If no response in $timeout seconds, no access is assumed
  curl_exec($curl);
  $curl_info = curl_getinfo($curl); // Used by your drupal messages below

  $is_available = ($curl_info['http_code'] === 200) ? 1 : 0;
  variable_set(check_plain($module) . '_enterprise_access_' . check_plain($data_type), $is_available);
  flogger($module, "Access to " . $url . " - " . $is_available);
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
