<?php
/**
 * @file
 * webspark_newsevents.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function webspark_newsevents_filter_default_formats() {
  $formats = array();

  // Exported format: ASU Feeds Input Format.
  $formats['asu_feeds_input_format'] = array(
    'format' => 'asu_feeds_input_format',
    'name' => 'ASU Feeds Input Format',
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
