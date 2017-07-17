<?php

/**
 * @file
 * Contains the basic license field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to an entity.
 */
class commerce_file_handler_field_license extends views_handler_field {
  function init(&$view, &$options) {
    parent::init($view, $options);

    $this->additional_fields['license_id'] = 'license_id';

    if (!empty($this->options['link_to_entity']) && $this->_valid_link_to_entity_option($this->options['link_to_entity'])) {
      $this->additional_fields['uid'] = 'uid';
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['link_to_entity'] = array('default' => 'none');
    return $options;
  }

  /**
   * Provide the link to order option.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['link_to_entity'] = array(
      '#type' => 'radios',
      '#title' => t('Link this field to'),
      '#description' => t('If User or Administrator are selected, this will override any other link you have set.'),
      '#options' => array(
        'none' => t('Nothing, unless specified in <em>Rewrite results</em>'),
        'user' => t('The user view page'),
        'admin' => t('The administrator view page'),
      ),
      '#default_value' => $this->options['link_to_entity'],
    );
  }

  /**
   * Return TRUE if a valid link to entity option
   */
  protected function _valid_link_to_entity_option($key) {
    return in_array($this->options['link_to_entity'], array('user', 'admin'));
  }

  /**
   * Render whatever the data is as a link to the license.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_entity']) && $this->_valid_link_to_entity_option($this->options['link_to_entity']) && $data !== NULL && $data !== '') {
      $uid = $this->get_value($values, 'uid');
      $entity_id = $this->get_value($values, 'license_id');

      if (!empty($uid) && !empty($entity_id)) {
        $entity = commerce_file_license_load($entity_id);

        if ($entity->access('view')) {
          if ($this->options['link_to_entity'] == 'user' && !empty($uid)) {
            $this->options['alter']['make_link'] = TRUE;
            $this->options['alter']['path'] = 'user/' . $uid . '/licensed-files/' . $entity_id;
          }
          elseif ($this->options['link_to_entity'] == 'admin' && ($uri = $entity->uri())) {
            $this->options['alter']['make_link'] = TRUE;
            $this->options['alter']['path'] = url($uri['path'], array('query' => drupal_get_destination()) + $uri);
            $this->options['alter']['path'] = $uri['path'] . '?' . drupal_http_build_query(drupal_get_destination());
          }
        }
      }
    }

    return $data;
  }

  function render($values) {
    $value = $this->get_value($values);
    return $this->render_link($this->sanitize_value($value), $values);
  }
}
