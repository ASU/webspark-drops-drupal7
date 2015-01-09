<?php

/**
* @file
* A specification for the custom spotlight entity that is part of Panopoly Widgets
*/

/**
* Implements hook_field_info().
*/
function asu_spotlight_field_info() {
  return array(
    'asu_spotlight' => array(
      'label' => t('ASU Spotlight'),
      'description' => t('A wonderfully (ASU modified) widgetsal spotlight field'),
      'default_widget' => 'asu_spotlight_form',
      'default_formatter' => 'asu_spotlight',
      'settings' => array(
        'uri_scheme' => variable_get('file_default_scheme', 'public'),
        'default_image' => 1,
      ),
      'instance_settings' => array(
        'file_extensions' => 'jpg jpeg gif png',
        'file_directory' => 'general',
        'max_filesize' => '',
        'alt_field' => 0,
        'title_field' => 0,
        'max_resolution' => '',
        'min_resolution' => '',
      ),
    ),
  );
}




function asu_spotlight_field_is_empty($item, $field) {
  if (empty($item['title']) && empty($item['link']) && empty($item['description']) && empty($item['fid'])) {
    return TRUE;
  }
  return FALSE;
}

/**
* Implements hook_field_widget_info().
*/
function asu_spotlight_field_widget_info() {
  return array(
    'asu_spotlight_form' => array(
    'label' => t('ASU Spotlight'),
    'field types' => array('asu_spotlight'),
    'behaviors' => array(
    'multiple values' => FIELD_BEHAVIOR_DEFAULT,
    'default value' => FIELD_BEHAVIOR_DEFAULT,
    ),
    ),
    );
  }

  /**
  * Implements hook_field_settings_form()
  */
  function asu_spotlight_field_settings_form($field, $instance, $has_data) {
    $form = array();
    $defaults = field_info_field_settings($field['type']);
    $settings = array_merge($defaults, $field['settings']);

    $scheme_options = array();
    foreach (file_get_stream_wrappers(STREAM_WRAPPERS_WRITE_VISIBLE) as $scheme => $stream_wrapper) {
      $scheme_options[$scheme] = $stream_wrapper['name'];
    }
    $form['uri_scheme'] = array(
    '#type' => 'radios',
    '#title' => t('Upload destination'),
    '#options' => $scheme_options,
    '#default_value' => $settings['uri_scheme'],
    '#description' => t('Select where the final files should be stored. Private file storage has significantly more overhead than public files, but allows restricted access to files within this field.'),
    );

    // When the user sets the scheme on the UI, even for the first time, it's
    // updating a field because fields are created on the "Manage fields"
    // page. So image_field_update_field() can handle this change.
    $form['default_image'] = array(
    '#title' => t('Default image'),
    '#type' => 'managed_file',
    '#description' => t('If no image is uploaded, this image will be shown on display.'),
    '#default_value' => $field['settings']['default_image'],
    '#upload_location' => $settings['uri_scheme'] . '://default_images/',
    );

    return $form;
  }

  /**
  * Implements hook_field_instance_settings_form()
  */
  function asu_spotlight_field_instance_settings_form($field, $instance) {
    $form = image_field_instance_settings_form($field, $instance);
    return $form;
  }

  /**
  * Implementation of hook_field_formatter_info().
  * We're going to be using our own formatter based on our own theme.
  */
  function asu_spotlight_field_formatter_info() {
    return array(
    'asu_spotlight' => array(
        'label' => t('ASU Spotlight'),
        'field types' => array('asu_spotlight'),
        'settings' => array(
            'image_style' => 'panopoly_image_spotlight',
            'caption' => FALSE,
            'optionset' => 'default',
            ),
        ),
    );
  }

  /**
  * Implements hook_field_formatter_settings_form().
  *
  */
  function asu_spotlight_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
    $display = $instance['display'][$view_mode];
    $settings = $display['settings'];
    $element = array();

    if ($display['type'] == 'asu_spotlight') {
      $element['image_style'] = array(
      '#title' => t('Image style'),
      '#type' => 'select',
      '#options' => image_style_options(),
      '#default_value' => $settings['image_style'],
      '#required' => TRUE,
      );

    }
    return $element;
  }

  /**
  * Implements hook_field_formatter_settings_summary().
  *
  */
  function asu_spotlight_field_formatter_settings_summary($field, $instance, $view_mode) {

    $display = $instance['display'][$view_mode];
    $settings = $display['settings'];

    $summary = array();

    $summary[] = t('Image Style: @style', array('@style' => $settings['image_style']));

    $summary[] = !empty($settings['caption']) ? t('Display captions') : t('Do not display captions');

    return $summary;
  }

  /**
  * Implements hook_field_formatter_view().
  */
  function asu_spotlight_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
    $element = array();

    if (!empty($items)) {
      foreach ($items as $key => $item) {
        $tmp = $item;
        $item = array();
        $item['item'] = $tmp;

        // Setup the variables for calling theme_image_style
        $item['slide']['path'] = $item['item']['uri'];
        $item['slide']['style_name'] = $display['settings']['image_style'];
        $item['slide']['width'] = $item['item']['metadata']['width'];
        $item['slide']['height'] = $item['item']['metadata']['height'];
        $item['slide']['alt'] = $item['item']['alt'];
        $item['slide']['title'] = $item['item']['title'];

        // Render the slide item
        // If not style set, we have to call theme_image since theme_image_style
        // doesn't auto-fallback to full size image
        if (!empty($item['slide']['style_name'])) {
          // Generate the HTML for the slide
          $item['slide'] = theme('image_style', $item['slide']);
        }
        else {
          // Generate the HTML for the slide
          $item['slide'] = theme('image', $item['slide']);
        }

        // Check caption settings
        if ($display['settings']['caption']) {
          $item['caption'] = filter_xss($item['item']['title']);
        }

        $items[$key] = $item;
      }
      if(!empty($entity->field_optionset)) {
          $display['settings']['optionset'] = $entity->field_optionset['und'][0]['value'];
      } else {

      }
      $element = array(
      '#theme' => 'asu_spotlight',
      '#items' => $items,
      '#settings' => $display['settings'],
      );
    }

    return $element;
  }

  /**
  *Implements hook_form_alter().
  * This allows us to populate the proper options and default for selecting optionsets on the form
  */
  function asu_spotlight_form_alter(&$form, &$form_state, $form_id) {

    if($form_id=='fieldable_panels_panes_fieldable_panels_pane_content_type_edit_form') {

        $optionsets = array();
        ctools_include('export');
        foreach (flexslider_optionset_load_all() as $name => $optionset) {
          $optionsets[$name] = check_plain($optionset->title);
        }
        $form['field_optionset']['und']['#options'] = $optionsets;

        if(isset($form['#entity']->field_optionset) && !empty($form['#entity']->field_optionset)) {
           $form['field_optionset']['und']['#default_value'] =
           $form['#entity']->field_optionset['und'][0]['value'];
        }
    }
  }

  /**
  * Implements hook_field_widget_form().
  */
  function asu_spotlight_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {

    if ($instance['widget']['type'] == 'asu_spotlight_form') {

      // Make it a multipart form
      $form['#attributes']['enctype'] = 'multipart/form-data';

      // Define the element
      $element['title'] = array(
      '#title' => t('Title'),
      '#type' => 'textfield',
      '#default_value' => isset($items[$delta]['title']) ? $items[$delta]['title'] : NULL,
      );

      $element['link'] = array(
      '#title' => t('Link for Title'),
      '#type' => 'textfield',
      '#default_value' => isset($items[$delta]['link']) ? $items[$delta]['link'] : NULL,
      );

      $element['fid'] = array(
      '#title' => t('Image'),
      '#type' => 'managed_file',
      '#upload_location' => file_field_widget_uri($field, $instance),
      '#default_value' => isset($items[$delta]['fid']) ? $items[$delta]['fid'] : NULL,
      );

      $element['alt'] = array(
      '#title' => t('Image alt text'),
      '#type' => 'textfield',
      '#default_value' => isset($items[$delta]['alt']) ? $items[$delta]['alt'] : NULL,
      );

      $element['description'] = array(
      '#title' => t('Text'),
      '#type' => 'textarea',
      '#rows' => '2',
      '#resizable' => FALSE,
      '#default_value' => isset($items[$delta]['description']) ? $items[$delta]['description'] : NULL,
      );

      $element['actionlink'] = array(
      '#title' => t('Button Link'),
      '#type' => 'textfield',
      '#default_value' => isset($items[$delta]['actionlink']) ? $items[$delta]['actionlink'] : NULL,
      );


      $element['actiontitle'] = array(
      '#title' => t('Button Title'),
      '#type' => 'textfield',
      '#default_value' => isset($items[$delta]['actiontitle']) ? $items[$delta]['actiontitle'] : NULL,
      );

      $element['actionlink2'] = array(
      '#title' => t('Button Link 2'),
      '#type' => 'textfield',
      '#default_value' => isset($items[$delta]['actionlink2']) ? $items[$delta]['actionlink2'] : NULL,
      );

      $element['actiontitle2'] = array(
      '#title' => t('Button Title 2'),
      '#type' => 'textfield',
      '#default_value' => isset($items[$delta]['actiontitle2']) ? $items[$delta]['actiontitle2'] : NULL,
      );

      $element['color'] = array(
      '#title' => t('Button color'),
      '#type' => 'select',
      '#options' => array('blue' => 'blue', 'red' => 'red'),
      '#default_value' => isset($items[$delta]['color']) ? $items[$delta]['color'] : 'blue',
      );

      $element['position'] = array(
      '#title' => t('Text position on image'),
      '#type' => 'select',
      '#options' => array('top-left' => 'top-left', 'top-center' => 'top-center', 'top-right' => 'top-right',
      'mid-left' => 'mid-left', 'mid-center' => 'mid-center', 'mid-right' => 'mid-right', 'bottom-left' => 'bottom-left',
      'bottom-center' => 'bottom-center', 'bottom-right' => 'bottom-right'),
      '#default_value' => isset($items[$delta]['position']) ? $items[$delta]['position'] : 'top-left',
      );


    }
    return $element;

  }

  /**
  * Implements hook_field_validate().
  */
  function asu_spotlight_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
    foreach ($items as $delta => $item) {
      if (!panopoly_widgets_field_is_empty($item, $field) && empty($item['fid'])) {
        $errors[$field['field_name']][$langcode][$delta][] = array(
        'error' => 'panopoly_widgets_spotlight_image_required',
        'message' => t('!name field is required.', array('!name' => t('Image'))),
        );
      }
    }
  }

  /**
  * Implements hook_field_presave()
  */
  function asu_spotlight_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
    // We need to set presave values if fids are not set. This shouldn't effect save operations
    // form API validation will prevent this from ever happening unless previewing.
    if (!empty($items)) {
      foreach ($items as &$item) {
        if (empty($item['fid'])) {
          $fid = variable_get('panopoly_widgets_default_' . $entity->bundle . '_fid', NULL);

          if (!empty($fid)) {
            $item['fid'] = $fid;
          }
        }
      }
      image_field_presave($entity_type, $entity, $field, $instance, $langcode, $items);
    }
  }

  /**
  * Implements hook_field_load().
  */
  function asu_spotlight_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
    $entity_items_copy = $items;
    image_field_load($entity_type, $entities, $field, $instances, $langcode, $items, $age);
    // image_field_load() will overwrite 'title' with the image title. Here we
    // return it to the item title.
    foreach ($entity_items_copy as $entity_id => $items_copy) {
      foreach ($items_copy as $delta => $item) {
        $items[$entity_id][$delta]['title'] = $item['title'];
      }
    }
  }

  /**
  * Implements hook_field_insert().
  */
  function asu_spotlight_field_insert($entity_type, $entity, $field, $instance, $langcode, &$items) {
    image_field_insert($entity_type, $entity, $field, $instance, $langcode, $items);
  }

  /**
  * Implements hook_field_update().
  */
  function asu_spotlight_field_update($entity_type, $entity, $field, $instance, $langcode, &$items) {

    // Load the original entity, if $entity->original is not already set.
    // This is done as per http://drupal.org/node/985642 and can be removed when that patch is committed.
    if (empty($entity->original)) {
      $entity->original = entity_load_unchanged($entity_type, $field['id']);
    }

    image_field_update($entity_type, $entity, $field, $instance, $langcode, $items);
  }

  /**
  * Implements hook_field_delete().
  */
  function asu_spotlight_field_delete($entity_type, $entity, $field, $instance, $langcode, &$items) {
    image_field_delete($entity_type, $entity, $field, $instance, $langcode, $items);
  }

  /**
  * Implements hook_field_delete_revision().
  */
  function asu_spotlight_field_delete_revision($entity_type, $entity, $field, $instance, $langcode, &$items) {
    image_field_delete_revision($entity_type, $entity, $field, $instance, $langcode, $items);
  }

  /**
  * Implements hook_field_prepare_view().
  */
  function asu_spotlight_field_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items) {
    // If there are no files specified at all, use the default.
    // TODO - make sure this works
    foreach ($entities as $id => $entity) {
      if (empty($items[$id]) && $field['settings']['default_image']) {
        if ($file = file_load($field['settings']['default_image'])) {
          $items[$id][0] = (array) $file + array(
          'is_default' => TRUE,
          'alt' => '',
          'title' => '',
          );
        }
      }
    }
  }
