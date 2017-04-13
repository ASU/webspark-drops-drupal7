<?php

/**
 * @file
 * Contains SalesforceMappingObjectController.
 */

/**
 * Salesforce Mapping UI controller.
 */
class SalesforceMappingObjectController extends EntityAPIController {

  /**
   * Override to include revision history and select properties.
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $build = parent::buildContent($entity, $view_mode, $langcode, $content);

    $render_props = array(
      'salesforce_id',
      'last_sync_message',
      'last_sync_action',
      'last_sync_status',
      'last_sync',
    );
    $wrapper = entity_metadata_wrapper('salesforce_mapping_object', $entity);
    foreach ($render_props as $name) {
      $info = $wrapper->$name->info();

      $markup = salesforce_mapping_object_render_property($wrapper, $name, $wrapper->$name);

      if ($markup) {
        $build[$name] = array(
          '#type' => 'item',
          '#title' => $info['label'] . ':',
          '#markup' => $markup,
        );
      }
    }

    // Get historical/revision info:
    module_load_include('inc', 'salesforce_mapping', 'includes/salesforce_mapping_object.admin');

    $header = array(
      'revision_id' => array(
        'data' => t('Revision'),
        'field' => 'revision_id',
        'sort' => 'desc',
      ),
      'salesforce_id' => array(
        'data' => t('Salesforce object'),
        'field' => 'salesforce_id',
      ),
      'last_sync_action' => array(
        'data' => t('Action'),
        'field' => 'last_sync_action',
      ),
      'last_sync_status' => array(
        'data' => t('Sync status'),
        'field' => 'last_sync_status',
      ),
      'last_sync_message' => array(
        'data' => t('Message'),
        'field' => 'last_sync_message',
      ),
      'last_sync' => array(
        'data' => t('Last sync'),
        'field' => 'last_sync',
      ),
      'entity_updated' => array(
        'data' => t('Entity updated'),
        'field' => 'entity_updated',
      ),
    );

    $build['history'] = array(
      '#type' => 'item',
      'table' => salesforce_mapping_object_overview_table($header, $entity->salesforce_mapping_object_id),
    );

    return $build;
  }
}
