<?php
/**
 * @file
 * Definition of views_bootstrap_plugin_rows.
 */

/**
 * Class to define a row plugin handler.
 */
class ViewsBootstrapThumbnailPluginRows extends views_plugin_row {
  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['image'] = array('default' => '');
    $options['title'] = array('default' => '');
    $options['content'] = array('default' => array());
    return $options;
  }

  /**
   * Form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Pre-build all of our option lists for the dials and switches that follow.
    $fields = array();
    foreach ($this->display->handler->get_handlers('field') as $field => $handler) {
      if ($label = $handler->label()) {
        $fields[$field] = $label;
      }
      else {
        $fields[$field] = $handler->ui_name();
      }
    }

    $form['image'] = array(
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Image'),
      '#options' => array('' => t('<None>')) + $fields,
      '#default_value' => $this->options['image'],
    );

    $form['title'] = array(
      '#type' => 'select',
      '#title' => t('Title'),
      '#options' => array('' => t('<None>')) + $fields,
      '#default_value' => $this->options['title'],
    );

    $form['content'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Content'),
      '#options' => $fields,
      '#default_value' => $this->options['content'],
    );
  }
}
