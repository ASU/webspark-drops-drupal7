<?php

function ace_categories_settings($form, &$form_state) {
  $categories = ace_categories('topics');
  ace_categories_settings_init_form_state($form_state);
  
  $form = array();
  ahah_helper_register($form, $form_state);
  
  $form['categories'] = array (
    '#type' => 'item',
    '#tree'   => TRUE,
  );
  
  $form['categories']['mailing_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Interest Mailing List Campaigns'),
  );
  
  foreach ($categories as $term) {
    $form['categories']['mailing_list'][$term->tkey]['campaign_id'] = array(
      '#type' => 'textfield',
      '#title' => "'$term->name' Campaign ID",
      '#required' => FALSE,
      '#size' => 40,
      '#default_value' => $form_state['storage']['categories']['mailing_list'][$term->tkey]['campaign_id'],
    );
  }
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );
  
  return $form;
}

function ace_categories_settings_init_form_state(&$form_state) {
  $category_campaigns = get_category_campaign();
  foreach ($category_campaigns as $cat_key => $campaign_id) {
    $form_state['storage']['categories']['mailing_list'][$cat_key]['campaign_id'] = $campaign_id;
  }
}

function ace_categories_settings_submit($form, &$form_state) {
  db_query('DELETE FROM {ace_categories}');
  foreach($form_state['values']['categories']['mailing_list'] as $cat_key => $campaign) {
    $ace_category = new stdClass();
    $ace_category->category_key = $cat_key;
    $ace_category->campaign_id = $campaign['campaign_id'];
    if (!empty($ace_category->campaign_id)) {
      drupal_write_record('ace_categories', $ace_category);
    }
  }
  drupal_set_message('Category information saved!');
}
