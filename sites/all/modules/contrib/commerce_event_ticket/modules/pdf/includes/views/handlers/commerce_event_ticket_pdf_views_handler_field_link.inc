<?php

/**
 * @file
 * Views field handler to display a download link for ticket PDF(s).
 */

class commerce_event_ticket_pdf_views_handler_field_link extends views_handler_field {

  protected $entity_type;

  /**
   * Overides parent::init().
   */
  public function init(&$view, &$options) {
    parent::init($view, $options);
    $this->entity_type = isset($this->definition['entity type']) ? $this->definition['entity type'] : 'commerce_event_ticket';
  }

  /**
   * Overrides parent::option_definition().
   */
  public function option_definition() {
    $options = parent::option_definition();
    $default_plural = 'Tickets (PDF)';
    $default_singular = 'Ticket (PDF)';
    $options['op'] = array(
      'default' => 'view',
    );
    $options['text_plural'] = array(
      'default' => format_plural(2, $default_singular, $default_plural),
      'translatable' => TRUE,
    );
    $options['text'] = array(
      'default' => format_plural(1, $default_singular, $default_plural),
      'translatable' => TRUE,
    );
    return $options;
  }

  /**
   * Overrides parent::options_form().
   */
  public function options_form(&$form, &$form_state) {
    $form['op'] = array(
      '#type' => 'select',
      '#title' => t('Link type'),
      '#default_value' => $this->options['op'],
      '#options' => array(
        'view' => t('View (open PDF in browser)'),
        'download' => t('Force download'),
      ),
    );
    $form['text_plural'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display (plural)'),
      '#default_value' => $this->options['text_plural'],
    );
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display (singular)'),
      '#default_value' => $this->options['text'],
    );
    parent::options_form($form, $form_state);
  }

  /**
   * Overrides parent::render().
   */
  public function render($values) {
    $entity_id = $this->get_value($values);
    $entity_type = $this->entity_type;

    $op = !empty($this->options['op']) ? $this->options['op'] : 'view';

    $link = commerce_event_ticket_pdf_get_link($entity_id, $entity_type, $op);
    if (!$link) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter'] = array_merge($this->options['alter'], $link);

    $plural = TRUE;
    if ($entity_type == 'commerce_event_ticket') {
      $plural = FALSE;
    }
    elseif ($entity_type == 'commerce_line_item' || $entity_type == 'commerce_order') {
      $entities = entity_load($entity_type, array($entity_id));
      $entity = reset($entities);
      if ($entity) {
        if ($entity_type == 'commerce_line_item') {
          $plural = $entity->quantity > 1;
        }
        else {
          $tickets = commerce_event_ticket_create_from_order($entity);
          $plural = count($tickets) > 1;
        }
      }
    }

    $text = $plural ? $this->options['text_plural'] : $this->options['text'];
    return $text;
  }
}
