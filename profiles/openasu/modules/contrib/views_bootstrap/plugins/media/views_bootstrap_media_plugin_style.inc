<?php
/**
 * @file
 * Definition of views_bootstrap_plugin_style.
 */

/**
 * Class to define a style plugin handler.
 */
class ViewsBootstrapMediaPluginStyle extends views_plugin_style {
  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['image_field'] = array('default' => NULL);
    $options['heading_field'] = array('default' => NULL);
    $options['body_field'] = array('default' => NULL);
    return $options;
  }

  /**
   * Form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    if (isset($form['grouping'])) {
      $options = array();
      foreach (element_children($form['grouping']) as $key => $value) {
        if (!empty($form['grouping'][$key]['field']['#options']) && is_array($form['grouping'][$key]['field']['#options'])) {
          $options = array_merge($options, $form['grouping'][$key]['field']['#options']);
        }
      }

      // Delete grouping.
      unset($form['grouping']);

      $form['image_field'] = array(
        '#type' => 'select',
        '#title' => t('Image field'),
        '#options' => $options,
        '#default_value' => $this->options['image_field'],
        '#description' => t('Select the field that will be used as the image.'),
      );

      $form['heading_field'] = array(
        '#type' => 'select',
        '#title' => t('Heading field'),
        '#options' => $options,
        '#default_value' => $this->options['heading_field'],
        '#description' => t('Select the field that will be used as the heading.'),
      );

      $form['body_field'] = array(
        '#type' => 'select',
        '#title' => t('Body field'),
        '#options' => $options,
        '#default_value' => $this->options['body_field'],
        '#description' => t('Select the field that will be used as the body.'),
      );
    }
  }
}
