<?php

/**
 * @file
 * Display suite extras fields.
 */

/**
 * Implements hook_ds_fields_info().
 */
function ds_extras_ds_fields_info($entity_type) {
  $fields = array();

  // Switch field support.
  if (variable_get('ds_extras_switch_field', FALSE) && $entity_type == 'node') {
    $fields[$entity_type]['ds_switch_field'] = array(
      'title' => t('Switch view mode'),
      'field_type' => DS_FIELD_TYPE_FUNCTION,
      'function' => 'ds_extras_switch_view_mode_field',
      'properties' => array('settings' => array()),
    );
  }

  // DS Views.
  if ($entity_type == 'ds_views') {
    $fields[$entity_type] = array(
      'title' => array(
        'title' => t('Views title'),
        'field_type' => DS_FIELD_TYPE_FUNCTION,
        'function' => 'ds_vd_render_title_field',
        'properties' => array(
          'formatters' => array(
            'vd_title_h1' => t('H1 title'),
            'vd_title_h2' => t('H2 title'),
            'vd_title_p' => t('Paragraph title'),
          ),
        )
      ),
      'header' => array(
        'title' => t('Views header'),
        'field_type' => DS_FIELD_TYPE_PREPROCESS,
      ),
      'exposed' => array(
        'title' => t('Exposed filters'),
        'field_type' => DS_FIELD_TYPE_PREPROCESS,
      ),
      'attachment_before' => array(
        'title' => t('Attachment before'),
        'field_type' => DS_FIELD_TYPE_PREPROCESS,
      ),
      'rows' => array(
        'title' => t('Views content'),
        'field_type' => DS_FIELD_TYPE_PREPROCESS,
      ),
      'empty' => array(
        'title' => t('Empty text'),
        'field_type' => DS_FIELD_TYPE_PREPROCESS,
      ),
      'pager' => array(
        'title' => t('Pager'),
        'field_type' => DS_FIELD_TYPE_PREPROCESS,
      ),
      'attachment_after' => array(
        'title' => t('Attachment after'),
        'field_type' => DS_FIELD_TYPE_PREPROCESS,
      ),
      'more' => array(
        'title' => t('More'),
        'field_type' => DS_FIELD_TYPE_PREPROCESS,
      ),
      'footer' => array(
        'title' => t('Views footer'),
        'field_type' => DS_FIELD_TYPE_PREPROCESS,
      ),
      'feed_icon' => array(
        'title' => t('Feed icon'),
        'field_type' => DS_FIELD_TYPE_PREPROCESS,
      ),
    );
  }

  if (!empty($fields)) {
    return $fields;
  }
}
