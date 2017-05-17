<?php
/**
 * @file
 * Field-related functions for the Commerce Event Ticket module.
 */

/**
 * Ensure that this module's required fields and instances exist.
 */
function commerce_event_ticket_install_fields() {
  field_info_cache_clear();

  // Create default fields.
  module_load_include('inc', 'commerce_event_ticket', 'includes/commerce_event_ticket.field_bases');
  $field_bases = _commerce_event_ticket_field_bases();
  foreach ($field_bases as $field_base) {
    if (!field_info_field($field_base['field_name'])) {
      field_create_field($field_base);
    }
  }

  // Create default instances.
  module_load_include('inc', 'commerce_event_ticket', 'includes/commerce_event_ticket.field_instances');
  $field_instances = _commerce_event_ticket_product_field_instances();
  foreach (array_keys(commerce_product_types()) as $bundle) {
    foreach ($field_instances as $instance) {
      if (!field_info_instance($instance['entity_type'], $instance['field_name'], $bundle)) {
        $instance['bundle'] = $bundle;
        field_create_instance($instance);
      }
    }
  }
}

/**
 * Delete any installed field instances belonging to this module.
 */
function commerce_event_ticket_delete_field_instances() {
  module_load_include('inc', 'commerce_event_ticket', 'includes/commerce_event_ticket.field_instances');
  $field_instances = _commerce_event_ticket_product_field_instances();
  foreach (array_keys(commerce_product_types()) as $bundle) {
    foreach ($field_instances as $instance) {
      if (field_info_instance($instance['entity_type'], $instance['field_name'], $bundle)) {
        $instance['bundle'] = $bundle;
        field_delete_instance($instance);
      }
    }
  }
}
