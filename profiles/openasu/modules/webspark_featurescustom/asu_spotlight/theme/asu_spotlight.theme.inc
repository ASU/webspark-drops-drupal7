<?php
/**
 * @file
 * Theming functions for the ASU Spotlight module.
 */

/**
 * Default theme implementation for flexslider_list
 */
function theme_asu_spotlight_list(&$vars) {
  // Reference configuration variables

  $optionset = &$vars['settings']['optionset'];
  $items = &$vars['items'];
  $attributes = &$vars['settings']['attributes'];
  $type = check_plain($vars['settings']['type']);
  $output = '';
  // Build the list
  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    foreach ($items as $i => $item) {

      $caption = '';
      if (!empty($item['caption'])) {
        $caption = $item['caption'];
      }

      $output .= theme('asu_spotlight_list_item', array(
        'package' => $item,
        'settings' => array(
          'optionset' => $optionset,
        ),
        'caption' => $caption,
      ));
    }
    $output .= "</$type>";
  }

  return $output;
}

/**
 * Default theme implementation for flexslider_list_item
 */
function theme_asu_spotlight_list_item(&$vars) {

  $item = $vars['package']['item'];

  // INIT values
  $overlaytextwidth = (isset($item['overlaytextwidth'])) ? check_plain($item['overlaytextwidth']) : 'full-width';
  $description = (isset($item['description'])) ? check_markup($item['description']) : '';
  $position = (isset($item['position'])) ? check_plain($item['position']) : '';
  $title_string = $item['title'];
  $clean = FALSE;
  if(!empty($item['link'])) {
    $title_string = l($title_string, $item['link']);
    $clean = TRUE; // l() sanitizes the output
  }
  $title_string = ($clean === FALSE) ? '<h1>' . check_plain($title_string) . '</h1>' : '<h1>' . $title_string . '</h1>';

  $list_item = '<li' . drupal_attributes($vars['settings']['attributes']) . '>' .
    '<div class="slidecontainer" position="relative">' . $vars['package']['slide'] .
    '<div class="blurbcontainer"> ' .
    '<div class="blurbshell ' . $position . ' ' .
    $overlaytextwidth . '">' .
    $title_string . '<div class="asu-spotlight-item-description"><p>' . $description . '</p></div>';

  // Button color
  if (isset($item['color'])) {
    if ($item['color'] == 'red') {
      $color = 'primary';
    }
    elseif ($item['color'] == 'blue') {
      $color = 'blue';
    }
    elseif ($item['color'] == 'gold') {
      $color = 'gold';
    }
    elseif ($item['color'] == 'grey') {
      $color = 'secondary';
    }
    else {
      $color = '-not-defined'; // not defined
    }
  } else {
    $color = '-not-defined'; // not defined
  }

  // Button #1
  if (isset($item['actiontitle']) && isset($item['actionlink'])) {
    if ($item['actiontitle'] != NULL && $item['actionlink'] != NULL) {
      $class = "btn-" . $color;
      $list_item .= l($item['actiontitle'], $item['actionlink'],
        array (
          'attributes' => array(
            'class' => array(
              'btn',
              $class,
              'btn-block',
            ),
          ),
        ));
    }
  }
  // Button #2
  if (isset($item['actiontitle2']) && isset($item['actionlink2'])) {
    if ($item['actiontitle2'] != NULL && $item['actionlink2'] != NULL) {
      $class = "btn-" . $color;
      $list_item .= l($item['actiontitle2'], $item['actionlink2'],
        array (
          'attributes' => array(
            'class' => array(
              'btn',
              $class,
              'btn-block',
            ),
          ),
        ));
    }
  }

  $list_item .= '</div>
              </div>
            </div>
          </li>';

  return $list_item;

}

/**
 * Template preprocess handler for 'asu_spotlight' theme.
 */
function template_process_asu_spotlight(&$vars) {
  // Reference configuration variables

  $optionset = &$vars['settings']['optionset'];
  $settings = &$vars['settings'];

  // Set the default container type
  if (empty($settings['type'])) {
    $settings['type'] = 'ul';
  }

  // Load the selected optionset
  if (!empty($optionset)) {
    $optionset = flexslider_optionset_load($optionset);
  }

  // Check if an optionset was loaded
  if (empty($optionset)) {
    // Fall back to 'default' option set
    $optionset = flexslider_optionset_load('default');
    watchdog('asu_spotlight', 'Fallback to default optionset.', array(), WATCHDOG_NOTICE);
  }

  // Configure attributes for containing elements
  $attributes = array();
  // Merge with defined attributes
  if (isset($settings['attributes']) and is_array($settings['attributes'])) {
    $attributes += $settings['attributes'];
  }

  // Set the ID for each flexslider instance if none is provided
  if (empty($attributes['id'])) {
    $flexslider_id = &drupal_static('flexslider_id', 0);
    $attributes['id'] = 'flexslider-' . ++$flexslider_id;
  }

  // Add the namespace to any classes
  // @todo figure out what this is supposed to do
  if (!empty($attributes['class']) && !empty($optionset->options['namespace'])) {
    foreach ($attributes['class'] as $key => $value) {
      $attributes['class'][$key] = $optionset->options['namespace'] . $value;
    }
  }

  // Add the flexslider class to be namespaced
  $attributes['class'][] = 'flexslider';

  // Add the attributes to the settings array.
  $settings['attributes'] = $attributes;

  // Finally, add the configuration to the page
  flexslider_add($vars['settings']['attributes']['id'], $vars['settings']['optionset']);

}

/**
 * Process function for asu_spotlight_list_item
 */
function template_process_asu_spotlight_list(&$vars) {

  // Reset the list of attributes
  $vars['settings']['attributes'] = array(
    // @todo find a way to detect the outter container class if possible
    'class' => array('slides'),
  );

}

/**
 * Process function for asu_spotlight_list_item
 */
function template_process_asu_spotlight_list_item(&$vars) {
  // Reset the list of attributes

  $vars['settings']['attributes'] = array();

  // Reference configuration variables
  $item = &$vars['item'];
  $settings = &$vars['settings'];
  $caption = &$vars['caption'];
  $attributes = &$vars['settings']['attributes'];

  // Generated thumbnail support
  if (isset($settings['optionset']->options['controlNav']) and $settings['optionset']->options['controlNav'] === "thumbnails") {
    // If the thumbnails are enabled in the option set, scan for the first img
    // tag and extract the src attribute to set as the thumbnail data
    $src = array();
    preg_match("<img.+?src=[\"'](.+?)[\"'].+?>", $item, $src);

    if (!empty($src[1])) {
      $attributes['data-thumb'] = $src[1];
    }
  }

  if (isset($settings['optionset']->options['thumbCaptions']) && $settings['optionset']->options['thumbCaptions'] && !empty($caption)) {
    $attributes['data-thumbcaption'] = $caption;
    // Prevent captions from appearing in the slider as well
    if (isset($settings['optionset']->options['thumbCaptionsBoth']) && FALSE === $settings['optionset']->options['thumbCaptionsBoth']) {
      $caption = '';
    }
  }

  if (isset($settings['optionset']->options['thumbCaptions']) && $settings['optionset']->options['thumbCaptions'] && !empty($caption)) {
    $attributes['data-thumbcaption'] = $caption;
    // Prevent captions from appearing in the slider as well
    if (isset($settings['optionset']->options['thumbCaptionsBoth']) && FALSE === $settings['optionset']->options['thumbCaptionsBoth']) {
      $caption = '';
    }
  }

  if (!empty($caption)) {
    $caption = '<div class="flex-caption">' . check_plain($caption) . '</div>';
  }
}
