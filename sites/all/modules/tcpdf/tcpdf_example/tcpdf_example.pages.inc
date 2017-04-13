<?php
/**
 * @file
 * Contains page callbacks and related functions of TCPDF module.
 */

/**
 * Page callback for contents page.
 */
function tcpdf_example_contents() {
  return l(t('Basic pdf'), 'tcpdf_example/download/simple');
}

/**
 * Page callback for downloading example pdf files.
 */
function tcpdf_example_download($example_name) {
  switch ($example_name) {
    case 'simple':
      $pdf = tcpdf_example_simple_pdf();
      break;
    default:
      return t('No such example.');
  }

  if (!$pdf) {
    return t('An error occured.');
  }

  // Tell the browser that this is not an HTML file to show, but a pdf file to
  // download.
  header('Content-Type: application/pdf');
  header('Content-Length: ' . strlen($pdf));
  header('Content-Disposition: attachment; filename="mydocument.pdf"');
  print $pdf;
  return NULL;
}

/**
 * Generates a pdf file using TCPDF module.
 *
 * @return string Binary string of the generated pdf.
 */
function tcpdf_example_simple_pdf() {
  // Get the content we want to convert into pdf.
  $html = theme('tcpdf_example_basic_html');

  // Never make an instance of TCPDF or TCPDFDrupal classes manually.
  // Use tcpdf_get_instance() instead.
  $tcpdf = tcpdf_get_instance();
  /* DrupalInitialize() is an extra method added to TCPDFDrupal that initializes
  *  some TCPDF variables (like font types), and makes possible to change the
  *  default header or footer without creating a new class.
  */
  $tcpdf->DrupalInitialize(array(
    'footer' => array(
      'html' => 'This is a test!! <em>Bottom of the page</em>',
    ),
    'header' => array(
      'callback' => array(
        'function' => 'tcpdf_example_default_header',
        // You can pass extra data to your callback.
        'context' => array(
          'welcome_message' => 'Hello, context array!',
        ),
      ),
    ),
  ));
  // Insert the content. Note that DrupalInitialize automaticly adds the first
  // page to the pdf document.
  $tcpdf->writeHTML($html);

  return $tcpdf->Output('', 'S');
}

/**
 * Callback for generating the header. This function acts like if it overridded
 *   the Header() function of tcpdf class except the tcpdf instance is not $this
 *   but a parameter.
 *
 * @param type $tcpdf TCPDFDrupal instance. It can be used as $this in the
 *   Header() function of a siebling of TCPDF.
 */
function tcpdf_example_default_header(&$tcpdf, $context) {
  // $args contains passed variable...
  $theme_settings = variable_get('theme_' . variable_get('theme_default', '') . '_settings', '');
  if (isset($theme_settings['logo_path']) && (file_exists($theme_settings['logo_path']))) {
    $tcpdf->Image(drupal_realpath($theme_settings['logo_path']), 10, 10, 30, 0, '', variable_get('site_url', ''), '', TRUE, 150, '', FALSE, FALSE, 0, FALSE, FALSE, FALSE);
  }
  $tcpdf->Write(0, $context['welcome_message'], '', 0, 'J', true, 0, false, true, 0);
}
