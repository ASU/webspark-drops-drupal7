<?php

/**
 * @file - mega_footer.social.inc
 * Local functions for social media icons
 */

/**
 * Add social media sections to the page
 *
 * @param $name name of social media
 * @param $class image class name
 * @param $title social media title
 * @param $mark footer to add to
 * @return string
 */
function _mega_footer_social_media($name, $class, $title, $mark) {
  $check = variable_get('mega_footer_unit_' . $name . '_link', NULL);
  $className = 'fa-' . $class;

  if (!empty($check)) {
    $mark .= "<li><a href='" . $check . "' title=$title><span class='sr-only'>$title</span>
    <i class='fa $className' aria-hidden='true'></i></a>
</li>";
  }
  return $mark;
}

/**
 * Adds social media link field to form
 *
 * @param $name name of social media
 * @param $title title of social media
 * @return array
 */
function _social_media_form_array($name, $title) {
  return array(
    '#type' => 'textfield',
    '#title' => t($title . ' Connect Link'),
    '#default_value' => variable_get('mega_footer_unit_' . $name . '_link', NULL),
  );
}

/**
 * Gets custom icon and link and displays it
 *
 * Think custom theme_socialmedia_icon output
 *
 * @param $type kind of custom field
 * @param $num count of custom field
 * @param $mark footer to add to
 * @return string
 */
function _mega_footer_custom_icon_and_link($type, $num, $mark) {

  $check = variable_get('mega_footer_unit_custom_' . $type . '_' . $num . '_link', NULL);
  $name = variable_get('mega_footer_unit_custom_' . $type . '_' . $num . '_name', NULL);
  $logo = variable_get('mega_footer_unit_custom_' . $type . '_' . $num . '_logo', '');

  if ($logo != '' && $logo != NULL) {
    $file = file_load($logo);
    $file_url = file_create_url($file->uri);

    if (!empty($file_url)) {
      if (!empty($check)) {
        $mark .= "<li><a href='" . $check . "' title='" . $name . "'><span class='sr-only'>" . $name . "</span>
    <span class='gray'><img class='fa' id ='" . $name . "' alt ='" . $name . "' src='$file_url' aria-hidden='true' style='top:7px'/></span></a></li>";
      }
    }
  }
  return $mark;
}

/**
 * Adds custom icon and link fields to the form
 *
 * Think custom hook_form_alter...
 *
 * @param $form form to add custom icon and link to
 * @param $name name to insert for item
 * @param $title text to display for the field
 * @return the original form
 */
function _mega_footer_custom_icon_and_link_fields($form, $name, $title) {
  $form['social_media']['mega_footer_unit_' . $name . '_link'] = array(
    '#type' => 'textfield',
    '#title' => t($title . ' Link'),
    '#default_value' => variable_get('mega_footer_unit_' . $name . '_link', NULL),
  );

  $form['social_media']['mega_footer_unit_' . $name . '_name'] = array(
    '#type' => 'textfield',
    '#title' => t($title . ' Name'),
    '#default_value' => variable_get('mega_footer_unit_' . $name . '_name', NULL),
  );

  $form['social_media']['mega_footer_unit_' . $name . '_logo'] = array(
    '#type' => 'managed_file',
    '#title' => t('Choose a ' . strtolower($title) . ' image'),
    '#default_value' => variable_get('mega_footer_unit_' . $name . '_logo', ''),
    '#upload_location' => 'public://',
  );

  return $form;
}