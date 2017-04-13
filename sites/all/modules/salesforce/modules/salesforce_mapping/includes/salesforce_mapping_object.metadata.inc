<?php

/**
 * @see hook_entity_property_info()
 */
class SalesforceMappingObjectMetadataController extends EntityDefaultMetadataController {

  /**
   * Define entity metadata for SalesforceMappingObject.
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['revision_id'] = array_merge($properties['revision_id'], array(
      'label' => t('Revision Id'),
    ));

    $properties['salesforce_id'] = array_merge($properties['salesforce_id'], array(
      'label' => t('Salesforce Id'),
    ));

    $properties['entity_id'] = array_merge($properties['entity_id'], array(
      'label' => t('Entity Id'),
    ));

    $properties['entity_type'] = array_merge($properties['entity_type'], array(
      'label' => t('Entity type'),
    ));

    $properties['created'] = array_merge($properties['created'], array(
      'label' => t('Created'),
      'type' => 'date',
    ));

    $properties['entity_updated'] = array_merge($properties['entity_updated'], array(
      'label' => t('Entity updated'),
      'type' => 'date',
    ));

    $properties['last_sync'] = array_merge($properties['last_sync'], array(
      'label' => t('Last sync'),
      'type' => 'date',
    ));

    $properties['last_sync_action'] = array_merge($properties['last_sync_action'], array(
      'label' => t('Last sync action'),
    ));

    $properties['last_sync_status'] = array_merge($properties['last_sync_status'], array(
      'label' => t('Last sync status'),
    ));

    $properties['last_sync_message'] = array_merge($properties['last_sync_message'], array(
      'label' => t('Last sync message'),
    ));

    // URL for the Salesforce object.
    $properties['salesforce_url'] = array(
      'label' => t('Salesforce object URL'),
      'description' => t('URL for the Salesforce object'),
      'type' => 'uri',
      'getter callback' => 'salesforce_mapping_object_property_salesforce_url_get',
      'computed' => TRUE,
    );

    // Drupal entity.
    $properties['entity'] = array(
      'label' => t("Entity"),
      'type' => 'entity',
      'schema field' => 'entity',
      'description' => t("The Drupal entity."),
      'getter callback' => 'salesforce_mapping_object_property_entity_get',
      'setter callback' => 'salesforce_mapping_object_property_entity_set',
    );

    return $info;
  }

}
