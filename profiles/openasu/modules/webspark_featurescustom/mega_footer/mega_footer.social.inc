<?php

/**
 * @file - mega_footer.social.inc
 * Local functions for social media icons
 */

/**
 * Render/theme the social media HTML <li>s for the page
 *
 * @param string $name name of social media
 * @param string $class image class name
 * @param string $title social media title
 * @param string $mark footer to add to
 * @param string $external
 * @param string $theme - which Web standard to use
 * @param bool $svg - Is replaced by SVG because bootstrap 4.x is out of date?
 * @return string
 */

function _mega_footer_social_media($name, $class, $title, $mark, $external, $theme, $svg = FALSE) {
  $check = variable_get('mega_footer_unit_' . $name . '_link', NULL);
  $className = 'fa-' . $class;

  if (!empty($check)) {
    $mark .= '<li><a ' . $external . ' href="' . $check . '" title="' . $title . '">';
    // Instagram, Youtube custom icons
    if ($svg === TRUE) {
      if ($name === 'instagram') {
        $mark .= '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 448 512"><path d="M224,202.66A53.34,53.34,0,1,0,277.36,256,53.38,53.38,0,0,0,224,202.66Zm124.71-41a54,54,0,0,0-30.41-30.41c-21-8.29-71-6.43-94.3-6.43s-73.25-1.93-94.31,6.43a54,54,0,0,0-30.41,30.41c-8.28,21-6.43,71.05-6.43,94.33S91,329.26,99.32,350.33a54,54,0,0,0,30.41,30.41c21,8.29,71,6.43,94.31,6.43s73.24,1.93,94.3-6.43a54,54,0,0,0,30.41-30.41c8.35-21,6.43-71.05,6.43-94.33S357.1,182.74,348.75,161.67ZM224,338a82,82,0,1,1,82-82A81.9,81.9,0,0,1,224,338Zm85.38-148.3a19.14,19.14,0,1,1,19.13-19.14A19.1,19.1,0,0,1,309.42,189.74ZM400,32H48A48,48,0,0,0,0,80V432a48,48,0,0,0,48,48H400a48,48,0,0,0,48-48V80A48,48,0,0,0,400,32ZM382.88,322c-1.29,25.63-7.14,48.34-25.85,67s-41.4,24.63-67,25.85c-26.41,1.49-105.59,1.49-132,0-25.63-1.29-48.26-7.15-67-25.85s-24.63-41.42-25.85-67c-1.49-26.42-1.49-105.61,0-132,1.29-25.63,7.07-48.34,25.85-67s41.47-24.56,67-25.78c26.41-1.49,105.59-1.49,132,0,25.63,1.29,48.33,7.15,67,25.85s24.63,41.42,25.85,67.05C384.37,216.44,384.37,295.56,382.88,322Z"/></svg>';
      }
      if ($name === 'youtube') { // Youtube from FontAwesome v5.14
        $mark .= '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 448 512"><path d="M186.8 202.1l95.2 54.1-95.2 54.1V202.1zM448 80v352c0 26.5-21.5 48-48 48H48c-26.5 0-48-21.5-48-48V80c0-26.5 21.5-48 48-48h352c26.5 0 48 21.5 48 48zm-42 176.3s0-59.6-7.6-88.2c-4.2-15.8-16.5-28.2-32.2-32.4C337.9 128 224 128 224 128s-113.9 0-142.2 7.7c-15.7 4.2-28 16.6-32.2 32.4-7.6 28.5-7.6 88.2-7.6 88.2s0 59.6 7.6 88.2c4.2 15.8 16.5 27.7 32.2 31.9C110.1 384 224 384 224 384s113.9 0 142.2-7.7c15.7-4.2 28-16.1 32.2-31.9 7.6-28.5 7.6-88.1 7.6-88.1z"/></svg>';
      }
    } else {
      if ($theme !== '_ws2') {
        $mark .= '<span class="fa ' . $className . '"><span class="sr-only">' . $title . '</span></span>';
      } else {
        $fa_prefix = ($title == 'RSS') ? 'fa' : 'fa';
        $mark .= '<i class="' . $fa_prefix . ' ' . $className . '"></i>';
      }
    }
    $mark .= '</a></li>';
  }

  return $mark;
}

/**
 * Returns part of social media link properties for the Form API generated social media form elements
 *
 * @param string $name name of social media
 * @param string $title title of social media
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
 * Gets custom icon name and link, manually themes it, and returns the HTML
 *
 * Think custom theme_socialmedia_icon output
 *
 * @param string $type kind of custom field
 * @param string $num count of custom field
 * @param string $mark footer to add to
 * @param string $external
 * @return string
 */
function _mega_footer_custom_icon_and_link($type, $num, $mark, $external, $theme) {

  $check = variable_get('mega_footer_unit_custom_' . $type . '_' . $num . '_link', NULL);
  $name = variable_get('mega_footer_unit_custom_' . $type . '_' . $num . '_name', NULL);
  $logo = variable_get('mega_footer_unit_custom_' . $type . '_' . $num . '_logo', '');

  if ($logo != '' && $logo != NULL) {
    $file = file_load($logo);
    $file_url = file_create_url($file->uri);

    if (!empty($file_url)) {
      if (!empty($check)) {
        if ($theme !== '_ws2') {
          $mark .= '<li><a ' . $external . ' href="' . $check . '" title="' . $name . '"><span class="sr-only">' . $name . '</span>
            <span class="gray"><img class="fa" id ="' . $name . '" alt ="' . $name . '" src="' . $file_url . '" aria-hidden="true"
            style="top:7px"/></span></a></li>';
        }
      }
    }
  }
  return $mark;
}

/**
 * Adds custom icon and link fields to the form. Only for any custom links/icons not already available
 * in this module's default list.
 *
 * Think custom hook_form_alter...
 *
 * @param array $form
 * @param string $name - name to insert for item
 * @param string $title - text to display for the field
 * @return array $form
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
