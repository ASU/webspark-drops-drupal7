<?php

/**
 * ASU Brand administration functions.
 */

function asu_brand_get_block_configure_form($delta) {
  $form['asu_brand'] = array(
    '#type' => 'fieldset',
    '#title' => t('ASU Brand settings'),
    '#description' => t('This block is cached for %lifetime. To update now, <a href="@link">clear the cache</a>.', array('%lifetime' => format_interval(ASU_BRAND_CACHE_LIFETIME), '@link' => url('admin/config/development/performance'))),
  );
  $form['asu_brand']['asu_brand_header_basepath'] = array(
    '#type' => 'textfield',
    '#title' => t('ASU theme basepath'),
    '#description' => t('Enter the path to the asuthemes folder.'),
    '#default_value' => variable_get('asu_brand_header_basepath', ASU_BRAND_HEADER_BASEPATH_DEFAULT),
    '#description' => t(' This setting is shared between all ASU Brand blocks. The default is %default. To use a local path, use %local_path', array('%default' => ASU_BRAND_HEADER_BASEPATH_DEFAULT, '%local_path' => '/afs/asu.edu/www/asuthemes')),
    '#required' => TRUE,
  );
  
  switch ($delta) {
    case 'asu_brand_header':
      $form['asu_brand']['asu_brand_header_template'] = array(
        '#type' => 'textfield',
        '#title' => t('ASU header template key'),
        '#description' => t('Enter the key for your custom header.'),
        '#default_value' => variable_get('asu_brand_header_template', ASU_BRAND_HEADER_TEMPLATE_DEFAULT),
        '#description' => t('The default is %default. For a list of template keys, visit <a href="@template_path">@template_path</a>.', array('%default' => ASU_BRAND_HEADER_TEMPLATE_DEFAULT, '@template_path' => url('https://asu.edu/asuthemes/' . ASU_BRAND_HEADER_VERSION . '/heads/'))),
        '#required' => TRUE,
      );
      break;
      
      case 'asu_brand_footer':
        $form['asu_brand']['asu_brand_footer_color'] = array(
          '#type' => 'select',
          '#title' => t('ASU footer color'),
          '#description' => t('Select the color of the footer.'),
          '#options' => array('' => 'Black', '_light_grey' => 'Light Grey', '_dark_grey' => 'Dark Grey'),
          '#default_value' => variable_get('asu_brand_footer_color', ASU_BRAND_FOOTER_COLOR_DEFAULT),
        );
        break;
      
      case 'asu_brand_students_footer':
        
        break;
  }
  
  return $form;
}
