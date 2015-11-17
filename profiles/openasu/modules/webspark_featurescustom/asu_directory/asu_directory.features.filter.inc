<?php
/**
 * @file
 * asu_directory.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function asu_directory_filter_default_formats() {
  $formats = array();

  // Exported format: ASU Feeds.
  $formats['asu_feeds'] = array(
    'format' => 'asu_feeds',
    'name' => 'ASU Feeds',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_html' => array(
        'weight' => -10,
        'status' => 1,
        'settings' => array(
          'allowed_html' => '<a> <em> <strong> <b> <i> <cite> <code> <pre> <ul> <ol> <li> <dl> <dt> <dd> <p> <h1> <h2> <h3> <h4> <h5> <h6> <img> <table> <thead> <tbody> <tr> <th> <td> <div> <span> <blockquote> <br> <hr> <small> <ins> <big> <sub> <sup>',
          'filter_html_help' => 0,
          'filter_html_nofollow' => 0,
        ),
      ),
      'filter_url' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_htmlcorrector' => array(
        'weight' => 10,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
