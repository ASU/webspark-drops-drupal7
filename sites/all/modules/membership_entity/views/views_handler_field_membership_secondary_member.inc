<?php

/**
 * @file
 * Definition of views_handler_field_membership_secondary_member.
 */

/**
 * Field handler to provide a list of secondary members.
 */
class views_handler_field_membership_secondary_member extends views_handler_field_prerender_list {
  /**
   * {@inheritdoc}
   */
  public function init(&$view, $options) {
    parent::init($view, $options);
    $this->additional_fields['mid'] = array('table' => 'membership_entity', 'field' => 'mid');
  }

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['display'] = array('default' => 'label');
    $options['link_to_user'] = array('default' => TRUE, 'bool' => TRUE);
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['type']['#options'] += array(
      'first' => t('Show first (if present)'),
      'count' => t('Show item count'),
    );

    $form['display'] = array(
      '#type' => 'radios',
      '#title' => t('Display format'),
      '#description' => t('Decide how this field will be displayed.'),
      '#options' => array(
        'label' => t('Show username'),
        'id' => t('Show user ID'),
      ),
      '#default_value' => $this->options['display'],
    );

    $form['link_to_user'] = array(
      '#type' => 'checkbox',
      '#title' => t('Link to user'),
      '#description' => t('Link this field to the user.'),
      '#default_value' => $this->options['link_to_user'],
    );
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    $this->add_additional_fields();
    $this->field_alias = $this->aliases['mid'];
  }

  /**
   * {@inheritdoc}
   */
  public function pre_render(&$values) {
    if (empty($values)) {
      return;
    }

    $mids = array();
    $this->items = array();

    foreach ($values as $result) {
      $mids[] = $this->get_value($result, NULL, TRUE);
    }

    if ($mids) {
      $result = db_query("SELECT s.mid, s.uid FROM {membership_entity_secondary_member} s WHERE s.mid IN (:mids) ORDER BY s.weight ASC", array(':mids' => $mids));
      foreach ($result as $item) {
        $this->items[$item->mid][$item->uid]['uid'] = $item->uid;
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function render_item($count, $item) {
    return $item['uid'];
  }

  /**
   * {@inheritdoc}
   */
  public function render_items($values) {
    if (empty($values)) {
      return;
    }

    if ($this->options['type'] == 'count') {
      return count($values);
    }

    foreach ($values as $delta => $value) {
      $values[$delta] = $this->render_link($value);
    }

    switch ($this->options['type']) {
      case 'separator':
        return implode($this->sanitize_value($this->options['separator'], 'xss_admin'), $values);

      case 'first':
        return count($values) ? array_shift($values) : NULL;

      case 'ul':
      case 'ol':
        $type = $this->options['type'];
        // Fall through.
      default:
        return theme('item_list', array(
          'title' => NULL,
          'items' => $values,
          'type' => isset($type) ? $type : 'ul',
        ));
    }
  }

  /**
   * {@inheritdoc}
   */
  public function render_link($value) {
    $account = user_load($value);
    if ($this->options['display'] == 'label') {
      $value = format_username($account);
    }
    $render = $this->sanitize_value($value);

    if ($this->options['link_to_user'] && ($uri = entity_uri('user', $account))) {
      return l($render, $uri['path'], array('html' => TRUE) + $uri['options']);
    }
    return $render;
  }
}
