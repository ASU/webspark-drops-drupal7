<?php
/**
 * @file
 * Class for the Panelizer taxonomy term entity plugin.
 */

/**
 * Panelizer Entity taxonomy term plugin class.
 *
 * Handles term specific functionality for Panelizer.
 */
class FieldablePanelsPaneEntity extends PanelizerEntityDefault {
// @todo this path is too deep to handle.
//  public $entity_admin_root = 'admin/structure/panels/entity/manage/%';
//  public $entity_admin_bundle = 5;
  public $views_table = 'fieldable_panels_panes';

  public function entity_access($op, $entity) {
    return fieldable_panels_panes_access($op, $entity);
  }

  /**
   * Implement the save function for the entity.
   */
  public function entity_save($entity) {
    return fieldable_panels_panes_save($entity);
  }

  public function entity_identifier($entity) {
    return t('This pane');
  }

  public function entity_bundle_label() {
    return t('Pane bundle');
  }

  function get_default_display($bundle, $view_mode) {
    return parent::get_default_display($bundle, $view_mode);
  }

  /**
   * Implements a delegated hook_form_alter.
   *
   * We want to add Panelizer settings for the bundle to the node type form.
   */
  public function hook_form_alter(&$form, &$form_state, $form_id) {
    if ($form_id == 'taxonomy_form_vocabulary') {
      if (isset($form['#vocabulary'])) {
        $bundle = $form['#vocabulary']->machine_name;
        $this->add_bundle_setting_form($form, $form_state, $bundle, array('machine_name'));
      }
    }
  }
}
