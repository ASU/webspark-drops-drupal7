<?php
/**
 * @file
 * Request info form generation using form API
 */

/**
 * Confirmation page code
 * @param $nid
 * @return string $confirm_message
 */
function asu_rfi_confirmation($nid) {
  $decoded_nid = base64_decode($nid);
  // get the node data
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'asu_rfi')
    ->propertyCondition('nid', $decoded_nid)
    ->addMetaData('account', user_load(1)); // Run the query as user 1.

  $result = $query->execute();
  if (isset($result['node'])) {
    $items_node_ids = array_keys($result['node']);
    $items = entity_load('node', $items_node_ids);
  }

  foreach ($items as $nid => $submissions) {
    $sub_wrapper = entity_metadata_wrapper('node', $submissions);
    $plan_code = $sub_wrapper->field_rfi_program->value();
    $program_code = $sub_wrapper->field_rfi_college_code->value();
    $program_name = $sub_wrapper->field_rfi_college_name->value();
    $prospect_level = $sub_wrapper->field_rfi_prospect_level->value();
  }
  $college = $program_code . ' - RFI';
  $sku = $program_code . $plan_code . '-RFI';
  $ga_id = variable_get('asu_rfi_google_analytics_key') . '-' . $nid;

  // Build array to be used in google analytics coding
  // GA code has been removed for now - leaving for future use.
  $trans = array('id' => $ga_id, 'affiliation' => $program_name,
    'revenue' => '100');

  $items = array('sku' => $sku, 'name' => $college, 'category' => 'RFI', 'price' => '100', 'quantity' => '1');

  $confirm_message = "<div style='padding:8% 0 8% 0;'>Thank you for your interest in ASU. An ASU representative will contact you soon!</div>";

  return $confirm_message;
}
