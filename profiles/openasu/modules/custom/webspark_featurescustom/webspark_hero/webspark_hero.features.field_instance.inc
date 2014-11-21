<?php
/**
 * @file
 * webspark_hero.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function webspark_hero_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'fieldable_panels_pane-hero-field_webspark_hero_bgimg'
  $field_instances['fieldable_panels_pane-hero-field_webspark_hero_bgimg'] = array(
    'bundle' => 'hero',
    'deleted' => 0,
    'description' => '<h4>Tips & Instructions</h4>
<p>Heroes should be added <strong>only to the top region</strong> of your page.</p>
<p>Images should be 1170 x 380 px. Smaller images will be scaled up; larger ones will be cropped.</p>
<p>When adding a new image, <strong>refresh the page</strong> after saving to view the image (it displays as a CSS background image).</p>',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'backgroundfield',
        'settings' => array(),
        'type' => 'backgroundfield_formatter',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_webspark_hero_bgimg',
    'label' => 'Hero image',
    'required' => 0,
    'settings' => array(
      'alt_field' => '',
      'css_attachment' => 'scroll',
      'css_h_position' => 'center',
      'css_important' => 0,
      'css_repeat' => 'no-repeat',
      'css_selector' => '.pane-bundle-hero',
      'css_v_position' => 'center',
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'image_style' => 'no_style',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'backgroundfield',
      'settings' => array(
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => '',
      ),
      'type' => 'backgroundfield_widget',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-hero-field_webspark_hero_blurb'
  $field_instances['fieldable_panels_pane-hero-field_webspark_hero_blurb'] = array(
    'bundle' => 'hero',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_webspark_hero_blurb',
    'label' => 'Blurb',
    'required' => 0,
    'settings' => array(
      'linkit' => array(
        'enable' => 0,
        'insert_plugin' => '',
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'maxlength_js' => 170,
        'maxlength_js_enforce' => 0,
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'maxlength_js_truncate_html' => 0,
        'rows' => 2,
      ),
      'type' => 'text_textarea',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-hero-field_webspark_hero_gradbtn'
  $field_instances['fieldable_panels_pane-hero-field_webspark_hero_gradbtn'] = array(
    'bundle' => 'hero',
    'default_value' => array(
      0 => array(
        'title' => 'Graduate Programs',
        'url' => 'https://webapp4.asu.edu/programs/t5/graduate/false',
      ),
    ),
    'deleted' => 0,
    'description' => 'It is recommended to add a button to explore graduate programs.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_webspark_hero_gradbtn',
    'label' => 'Explore graduate programs button  (recommended)',
    'required' => 0,
    'settings' => array(
      'attributes' => array(
        'class' => 'btn btn-blue btn-block',
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'linkit' => array(
        'enable' => 0,
        'insert_plugin' => '',
      ),
      'rel_remove' => 'default',
      'title' => 'required',
      'title_maxlength' => 25,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'link_field',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-hero-field_webspark_hero_primarybtn'
  $field_instances['fieldable_panels_pane-hero-field_webspark_hero_primarybtn'] = array(
    'bundle' => 'hero',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If you do not add the explore degree buttons, you can optionally add a single call to action button to support the single most important item of the hero message and to drive the user.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_webspark_hero_primarybtn',
    'label' => 'Other call to action button (alternative)',
    'required' => 0,
    'settings' => array(
      'attributes' => array(
        'class' => 'btn btn-primary btn-col-4',
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 0,
      'linkit' => array(
        'enable' => 0,
        'insert_plugin' => '',
      ),
      'rel_remove' => 'default',
      'title' => 'required',
      'title_maxlength' => 25,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'link_field',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'fieldable_panels_pane-hero-field_webspark_hero_ugradbtn'
  $field_instances['fieldable_panels_pane-hero-field_webspark_hero_ugradbtn'] = array(
    'bundle' => 'hero',
    'default_value' => array(
      0 => array(
        'title' => 'Undergraduate Programs',
        'url' => 'https://webapp4.asu.edu/programs/t5/undergrad',
      ),
    ),
    'deleted' => 0,
    'description' => 'It is recommended to add a button to explore undergraduate programs.',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'field_name' => 'field_webspark_hero_ugradbtn',
    'label' => 'Explore undergraduate programs button (recommended)',
    'required' => 0,
    'settings' => array(
      'attributes' => array(
        'class' => 'btn btn-blue btn-block',
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'linkit' => array(
        'enable' => 0,
        'insert_plugin' => '',
      ),
      'rel_remove' => 'default',
      'title' => 'required',
      'title_maxlength' => 25,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'link_field',
      'weight' => 4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<h4>Tips & Instructions</h4>
<p>Heroes should be added <strong>only to the top region</strong> of your page.</p>
<p>Images should be 1170 x 380 px. Smaller images will be scaled up; larger ones will be cropped.</p>
<p>When adding a new image, <strong>refresh the page</strong> after saving to view the image (it displays as a CSS background image).</p>');
  t('Blurb');
  t('Explore graduate programs button  (recommended)');
  t('Explore undergraduate programs button (recommended)');
  t('Hero image');
  t('If you do not add the explore degree buttons, you can optionally add a single call to action button to support the single most important item of the hero message and to drive the user.');
  t('It is recommended to add a button to explore graduate programs.');
  t('It is recommended to add a button to explore undergraduate programs.');
  t('Other call to action button (alternative)');

  return $field_instances;
}
