<?php
/**
 * @file
 * Definition of views_bootstrap_plugin_style.
 */

/**
 * Class to define a style plugin handler.
 */
class ViewsBootstrapGridPluginStyle extends views_plugin_style {
  /**
   * Definition.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['alignment'] = array('default' => 'horizontal');
    $options['columns_horizontal'] = array('default' => -1);
    $options['columns_vertical'] = array('default' => 4);
    $options['clear_columns'] = array('default' => TRUE, 'bool' => TRUE);
    $options['columns_xs'] = array('default' => 12);
    $options['columns_sm'] = array('default' => 6);
    $options['columns_md'] = array('default' => 4);
    $options['columns_lg'] = array('default' => 3);
    $options['column_class'] = array('default' => '');
    return $options;
  }

  /**
   * Form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['alignment'] = array(
      '#type' => 'radios',
      '#title' => t('Alignment'),
      '#options' => array(
        'horizontal' => t('Horizontal'),
        'vertical' => t('Vertical'),
      ),
      '#required' => TRUE,
      '#description' => t('Horizontal alignment will place items starting in the upper left and moving right. Vertical alignment will place items starting in the upper left and moving down.'),
      '#default_value' => $this->options['alignment'],
    );

    $options = array(
      1 => 1,
      2 => 2,
      3 => 3,
      4 => 4,
      6 => 6,
      12 => 12,
    );

    // Number of columns wrapped in a views row for horizontal alignment.
    $form['columns_horizontal'] = array(
      '#type' => 'select',
      '#title' => t('Number of columns per views row'),
      '#options' => array(-1 => 'Single row', 0 => 'Auto') + $options,
      '#required' => TRUE,
      '#description' => t('Choose the number of columns that views will wrap in a single row. This will be reflected in the HTML structure rendered regardless of the device size. When the "Single row" value is selected, all columns will be wrapped in one row.'),
      '#default_value' => $this->options['columns_horizontal'],
      '#states' => array(
        'visible' => array(
          'input[name="style_options[alignment]"]' => array('value' => 'horizontal'),
        ),
      ),
    );

    // Number of columns for vertical alignment.
    $form['columns_vertical'] = array(
      '#type' => 'select',
      '#title' => t('Number of columns'),
      '#options' => $options,
      '#required' => TRUE,
      '#description' => t('Choose the number of columns that content will be split into'),
      '#default_value' => $this->options['columns_vertical'],
      '#states' => array(
        'visible' => array(
          'input[name="style_options[alignment]"]' => array('value' => 'vertical'),
        ),
      ),
    );

    // Whether to clear the columns; available only in horizontal alignment and
    // when the "Single row" option is selected.
    $form['clear_columns'] = array(
      '#type' => 'checkbox',
      '#title' => t('Clear columns per device size'),
      '#description' => t('When this option is selected, clearfix divs will be used to "clear" the columns as needed per device size (see <a href="@bootstrap_docs" target="_blank">Bootstrap Documentation</a>). Please note this option applies only when "Single row" is selected for the "Number of columns per view row" option.', array('@bootstrap_docs' => url('http://getbootstrap.com/css/#grid-example-mixed-complete'))),
      '#default_value' => $this->options['clear_columns'],
      '#states' => array(
        'visible' => array(
          'input[name="style_options[alignment]"]' => array('value' => 'horizontal'),
          'select[name="style_options[columns_horizontal]"]' => array('value' => -1),
        ),
      ),
    );

    // Number of columns per device size. To be used for generating css classes.
    // Options are the same for all device sizes.
    $options = array(
      12 => 1,
      6 => 2,
      4 => 3,
      3 => 4,
      2 => 6,
      1 => 12,
    );

    $form['columns_xs'] = array(
      '#type' => 'select',
      '#title' => t('Number of columns for extra small devices'),
      '#options' => $options,
      '#required' => TRUE,
      '#description' => t('Choose the number of columns for a particular device size and up. This affects the css classes that will be applied to the columns and not the actual HTML structure that will be rendered. Not defining the number of columns for a device size will result in inheriting the number of columns from one size below.'),
      '#default_value' => $this->options['columns_xs'],
    );

    // Add option to not define the number of columns for the rest.
    $options[0] = 'Do not define';

    $form['columns_sm'] = array(
      '#type' => 'select',
      '#title' => t('Number of columns for small devices'),
      '#options' => $options,
      '#required' => FALSE,
      '#description' => t('See the description on the number of columns for extra small devices.'),
      '#default_value' => $this->options['columns_sm'],
    );

    $form['columns_md'] = array(
      '#type' => 'select',
      '#title' => t('Number of columns for medium devices'),
      '#options' => $options,
      '#required' => FALSE,
      '#description' => t('See the description on the number of columns for extra small devices.'),
      '#default_value' => $this->options['columns_md'],
    );

    $form['columns_lg'] = array(
      '#type' => 'select',
      '#title' => t('Number of columns for large devices'),
      '#options' => $options,
      '#required' => FALSE,
      '#description' => t('See the description on the number of columns for extra small devices.'),
      '#default_value' => $this->options['columns_lg'],
    );

    $form['column_class'] = array(
      '#title' => t('Column class'),
      '#description' => t('Additional classes to provide on each column.'),
      '#type' => 'textfield',
      '#default_value' => $this->options['column_class'],
    );
  }
}
