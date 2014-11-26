<?php
/**
 * @file
 * Definition of views_bootstrap_plugin_style.
 */

/**
 * Class to define a style plugin handler.
 */
class ViewsBootstrapTabPluginStyle extends views_plugin_style {
  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['tab_field'] = array('default' => NULL);
    $options['tab_type'] = array('default' => 'tabs');
    $options['justified'] = array('default' => FALSE);
    return $options;
  }

  /**
   * Options form.
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

      $form['tab_field'] = array(
        '#type' => 'select',
        '#title' => t('Tab field'),
        '#options' => $options,
        '#required' => TRUE,
        '#default_value' => $this->options['tab_field'],
        '#description' => t('Select the field that will be used as the tab.'),
      );

      $form['tab_type'] = array(
        '#type' => 'select',
        '#title' => t('Tab Type'),
        '#options' => array(
          'tabs' => t('Tabs'),
          'pills' => t('Pills'),
          'list' => t('List'),
        ),
        '#required' => TRUE,
        '#default_value' => $this->options['tab_type'],
      );

      $form['justified'] = array(
        '#type' => 'checkbox',
        '#title' => t('Justified'),
        '#default_value' => $this->options['justified'],
        '#description' => t('Make tabs equal widths of their parent'),
      );
    }
  }
}
