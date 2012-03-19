<?php
/**
 * @file
 * Themes the Office hours formatter and widget.
 *
 */

/**
 * Theme function for 'default' text field formatter.
 */
function office_hours_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  if ($items) {
    $element[0] = array('#markup' => theme($field['type'] . '_formatter_default',
                                           array('element' => $items,
                                                 //'field' => $instance,
                                                 'display' => $display,
                                                 )),);
  }
  return $element;
}

/**
 * Theme function for field formatter.
 * Adapted for 2 types:
 * - default, 'normal', tabular format
 * - inline format, adapted for use in interfaces such as Google Places.
 * This is put in 1 function, since there is a lot of pre-processing before the actual formatting,
 * So you'll find 2 parts: part1 = Preprocessing, part2 = Formatting, depending on the choosen formatter.
 * @TODO: use e.g. strtotime() / Date_module http://php.net/manual/en/function.date.php functions for proper time formatting.
 */
function theme_office_hours_formatter_default($vars) {
  $element = $vars['element'];
  $settings = $vars['display']['settings'];
  $max_label_length = 3; // This is the minimum width for day labels. It is adjusted when adding new labels.

  // Get the label per weekday.
  switch ($settings['daysformat']) {
    case 'long':
      $weekdays = date_week_days(TRUE);
      break;
    case 'short':
      $weekdays = date_week_days_abbr(TRUE, TRUE, 3); // Abbreviate up to 3 characters
      break;
    case 'number':
      $weekdays = array(0 => 1, 1 => 2, 2 => 3, 3 => 4, 4 => 5, 5 => 6, 6 => 7 );
      break;
    case 'none':
      $weekdays = array(0 => '', 1 => '', 2 => '', 3 => '', 4 => '', 5 => '', 6 => '' );
      $settings['separator_day_hours'] = '';  // override user's setting if daysformat = 'none'. (Should we?)
      break;
  }

  $items = array();
  // Format the 'hours', e.g. 0900 -> 09:00.
  foreach (element_children($element) as $key => $arraykey) {
    $item = $element[$arraykey];
    $day = (int)($item['day'] / 2); // Keys are 0+1 for sunday, 2+3 for monday, etc. Each day may have normal hours + extra hours.
    if (isset($day)) {
      // @TODO: use e.g. strtotime() or Date_module for standard time formatting. See http://php.net/manual/en/function.date.php.
      $strhrs = _office_hours_mil_to_tf(check_plain($item['starthours']));
      $endhrs = _office_hours_mil_to_tf(check_plain($item['endhours']));
      if (!empty($settings['hoursformat'])) {
        $strhrs = _office_hours_convert_to_ampm($strhrs);
        $endhrs = _office_hours_convert_to_ampm($endhrs);
      }

      $items[$day][] = array('strhrs' => $strhrs, 'endhrs' => $endhrs) ; // We're aggregating hours for days together.
      $items[$day]['label'] = $weekdays[$day];
      $max_label_length = max( $max_label_length, strlen($items[$day]['label']));

      // Add group_id to group days with equal hours.
      if ($settings['grouped']) {
        $group_id = "$strhrs::$endhrs";
        if (!isset ($items[$day]['group_id'])) {
          $items[$day]['group_id'] = $group_id;
        }
        else { // more hours info.
          $items[$day]['group_id'] .= '-'. $group_id;
        }
      }
    }
  }

  // add the closed days again, to 1) sort by first_day_of_week and 2) toggle show on/off
  foreach ($weekdays as $day => $label) {
    if (!array_key_exists($day, $items)) {
      $items[$day][]= array('closed' => 'closed'); //silly, but we need this as an array because we can't use a string offset later
      $items[$day]['label'] = $weekdays[$day];
      $max_label_length = max($max_label_length, strlen($items[$day]['label']));

      // Add group_id for closed days
      if ($settings['grouped']) {
        $group_id = 'closed';
        $items[$day]['group_id'] = $group_id;
      }
    }
  }

  // Sort the days of the week again, because sorting is lost by adding the closed days.
  // Do not sort by first_day_of_week for certain types: 'number'/'none' are more frequently used by machines/interfaces.
  ksort($items);
  switch ($settings['daysformat']) {
    case 'long':
    case 'short':
      $items = date_week_days_ordered($items);
      $weekdays = date_week_days_ordered($weekdays);
      break;
    case 'number':
    case 'none':
      break;
  }

  // Change label for grouped days.
  if ($settings['grouped']) {
    $group_id = '';
    $settings['separator_grouped_days'] = isset($settings['separator_grouped_days']) ? $settings['separator_grouped_days'] : ' - ';

    foreach ($items as $day => $hours) {
      if ($group_id != $hours['group_id']) {
        // new group, save label of first day.
        $group_id = $hours['group_id'];
        $group_from_label = $hours['label'];
      }
      else {
        // second, third day of group: adjust the label of this group to e.g. 'mon-wed'
        $items[$day]['label'] = $group_from_label . $settings['separator_grouped_days'] . $hours['label'];
        $max_label_length = max($max_label_length, strlen($items[$day]['label']));
        // delete previous item of this group, so it will not be shown.
        unset ($items[$day-1]);
      }
    }
  }

  // Finally, generate the formatter output.
  $output = '';
  $values = array();
  foreach ($items as $day => $hours) {
    $closed = '';
    $regular = '';
    $additional = '';
    if ( isset($hours[0]['closed']) ) {
      if ( !empty($settings['showclosed']) ) {
        // Format the empty day with a text like 'Closed' or '00:00-00:00'
        $closed = check_plain( t($settings['closedformat'] ) );
      }
      else {
        // Don't output unnecessary fields.
      }
    }
    else {
      $strhrs1 = $hours[0]['strhrs'];
      $endhrs1 = $hours[0]['endhrs'];
      if ( isset($hours[1] ) ) {
        if (!$settings['compress']) {
          $strhrs2 = $hours[1]['strhrs'];
          $endhrs2 = $hours[1]['endhrs'];
          $additional = $settings['separator_more_hours'] . $strhrs2 . $settings['separator_hours_hours'] . $endhrs2;
        }
        else {
          // Override endhours of morning with endhours of evening.
          $endhrs1 = $hours[1]['endhrs'];
        }
      }
      $regular = $strhrs1 . $settings['separator_hours_hours'] . $endhrs1;
    }

    $output_hours = $closed . $regular . $additional;
    if (!empty($output_hours)) {
      $output .= '<span class="oh-display">'
               .   '<span class="oh-display-label" style="width: ' . ($max_label_length * 0.70) . 'em; ">'
               .     $hours['label']
               .     $settings['separator_day_hours']
               .   '</span>';
      if ($closed) {
        $output .= '<span class="oh-display-closed">'
                 .   $closed . $regular . $additional
                 .   $settings['separator_days']
                 . '</span>';
      }
      else {
        $output .= '<span class="oh-display-hours">'
                 .   $closed . $regular . $additional
                 .   $settings['separator_days']
                 . '</span>';

      }
      $output .= '</span>';
    }
  }

  return $output;
}

function theme_office_hours($vars) {
  return $vars['element']['#children'];
}

/**
 * Theme function for the office hours selector element.
 */
function theme_office_hours_select($vars) {
  return $vars['element']['#children'];
}

/**
 * copied from content module's theme_content_multiple_values- we're taking out the draggable feature.
 *
 * Theme the hour table form
 *
 */
function office_hours_field_multiple_value_form($variables) {
  // Use Field's theme function for non-office hours fields.
  if (empty($variables['element'][0]['#type']) || $variables['element'][0]['#type'] != 'office_hours') {
    return theme_field_multiple_value_form($variables);
  }

  // The following is a copy from standard theme_field_multiple_value_form()
  // http://api.drupal.org/api/drupal/modules%21field%21field.form.inc/function/theme_field_multiple_value_form/7
  // Modifications for the Office Hours form are commented out.
  // We've removed the columns 'order' and 'drag&drop', and do not add the drap&drop JS.

  $element = $variables['element'];
  $output = '';
  if ($element['#cardinality'] > 1 || $element['#cardinality'] == FIELD_CARDINALITY_UNLIMITED) {
    $table_id = drupal_html_id($element['#field_name'] . '_values');
    $order_class = $element['#field_name'] . '-delta-order';
    $required = !empty($element['#required']) ? theme('form_required_marker', $variables) : '';

    $header = array(
      array(
        'data' => '<label>' . t('!title: !required', array('!title' => $element['#title'], '!required' => $required)) . "</label>",
        'colspan' => 2,
        'class' => array('field-label'),
      ),
//      t('Order'),
    );
    $rows = array();

    // Sort items according to '_weight' (needed when the form comes back after
    // preview or failed validation)
    $items = array();
    foreach (element_children($element) as $key) {
      if ($key === 'add_more') {
        $add_more_button = &$element[$key];
      }
      else {
        $items[] = &$element[$key];
      }
    }
    usort($items, '_field_sort_items_value_helper');

    $items = _office_hours_arrange_day($items); //this calls the function that arranges the first day of the week.

    // Add the items as table rows.
    foreach ($items as $key => $item) {
      $item['_weight']['#attributes']['class'] = array($order_class);
      $delta_element = drupal_render($item['_weight']);
      $cells = array(
//        array('data' => '', 'class' => array('field-multiple-drag')),
        drupal_render($item),
//        array('data' => $delta_element, 'class' => array('delta-order')),
      );
      $rows[] = array(
        'data' => $cells,
//        'class' => array('draggable'),
      );
    }

    $output = '<div class="form-item">';
    $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => $table_id, 'class' => array('field-multiple-table'))));
    $output .= $element['#description'] ? '<div class="description">' . $element['#description'] . '</div>' : '';
    $output .= '<div class="clearfix">' . drupal_render($add_more_button) . '</div>';
    $output .= '</div>';

//    drupal_add_tabledrag($table_id, 'order', 'sibling', $order_class);
  }
  else {
    foreach (element_children($element) as $key) {
      $output .= drupal_render($element[$key]);
    }
  }

  return $output;
}
