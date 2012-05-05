<?php

/**
 * Views field handler for rendering node links that point to panelizer tabs.
 */
class panelizer_handler_panelizer_status extends views_handler_field_entity {
  function option_definition() {
    $options = parent::option_definition();
    $options['not_panelized'] = array('default' => 'Not panelized', 'translatable' => TRUE);
    $options['custom'] = array('default' => 'Custom', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['custom'] = array(
      '#type' => 'textfield',
      '#title' => t('Customized text'),
      '#default_value' => $this->options['custom'],
      '#description' => t('Text to display if the entity has a custom panel.'),
    );
    $form['not_panelized'] = array(
      '#type' => 'textfield',
      '#title' => t('Not panelized text'),
      '#default_value' => $this->options['not_panelized'],
      '#description' => t('Text to display if the entity is not panelized.'),
    );
  }

  function render($values) {
    if ($entity = $this->get_value($values)) {
      if (!empty($entity->panelizer->name)) {
        $panelizer = ctools_export_crud_load('panelizer_defaults', $entity->panelizer->name);
        $status = !empty($panelizer->title) ? check_plain($panelizer->title) : t('Default');
      }
      else if (!empty($entity->panelizer->did)) {
        $status = $this->options['custom'];
      }
      else {
        $status = $this->options['not_panelized'];
      }

      return $status;
    }
  }

}
