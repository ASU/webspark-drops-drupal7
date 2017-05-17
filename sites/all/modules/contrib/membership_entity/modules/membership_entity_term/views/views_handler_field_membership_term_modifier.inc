<?php

/**
 * @file
 * Definition of views_handler_field_membership_term_modifier.
 */

/**
 * Field handler to provide a list of term modifiers.
 */
class views_handler_field_membership_term_modifier extends views_handler_field_serialized {
  /**
   * {@inheritdoc}
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['format'] = array('default' => 'list');
    $options['list_type'] = array('default' => 'separator');
    $options['separator'] = array('default' => '<br />');
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['format']['#options'] = array_merge(array('list' => t('As a list')), $form['format']['#options']);

    $form['list_type'] = array(
      '#type' => 'radios',
      '#title' => t('List type'),
      '#options' => array(
        'ul' => t('Unordered list'),
        'ol' => t('Ordered list'),
        'separator' => t('Simple separator'),
      ),
      '#default_value' => $this->options['list_type'],
      '#dependency' => array('edit-options-format' => array('list')),
    );

    $form['separator'] = array(
      '#type' => 'textfield',
      '#title' => t('Separator'),
      '#default_value' => $this->options['separator'],
      '#dependency' => array(
        'radio:options[list_type]' => array('separator'),
        'edit-options-format' => array('list'),
      ),
    );
  }

  /**
   * {@inheritdoc}
   */
  function render($values) {
    if ($this->options['format'] != 'list') {
      return parent::render($values);
    }

    $items = unserialize($values->{$this->field_alias});
    if (is_array($items) && !empty($items)) {
      if ($this->options['list_type'] == 'separator') {
        return implode($this->sanitize_value($this->options['separator'], 'xss_admin'), $items);
      }
      else {
        return theme('item_list', array(
          'items' => $items,
          'title' => NULL,
          'type' => $this->options['list_type'],
        ));
      }
    }
  }
}
