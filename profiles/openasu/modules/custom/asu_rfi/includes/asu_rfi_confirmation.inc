<?php
// $Id: asu_rfi_confirmation.inc 

/**
 * @file
 * Request info form generation using form API
 */

 /**** Confirmation page code**/
function asu_rfi_confirmation($nid){
    $decoded_nid = base64_decode($nid);
    //get the node data 
     $query = new EntityFieldQuery();
     $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'asu_rfi')
    ->propertyCondition('nid', $decoded_nid)
    ->addMetaData('account', user_load(1)); // Run the query as user 1.
   
   $result = $query->execute();
   if (isset($result['node'])) {
    $items_nids = array_keys($result['node']);
    $items = entity_load('node', $items_nids);
   }
 
  $out = array();
  foreach ($items as $nid => $submissions) {
 
    $sub_wrapper = entity_metadata_wrapper('node', $submissions);
    $plan_code = $sub_wrapper->field_rfi_program->value();
    $program_code = $sub_wrapper->field_rfi_college_code->value();
    $program_name = $sub_wrapper->field_rfi_college_name->value();
    $prospect_level = $sub_wrapper->field_rfi_prospect_level->value();
  }
   $college = $program_code.' - RFI';
   $sku = $program_code.$plan_code;
   $ga_id = variable_get('asu_rfi_google_analytics_key').'-'.$nid ;
   
   //Build array to be used in google analytics coding
   $trans = array('id'=>$ga_id, 'affiliation'=>$program_name,
               'revenue'=>'100');
   
   $items = array('sku'=>$sku, 'name'=>$college, 'category'=>'RFI', 'price'=>'100', 'quantity'=>'1');
  
   $message = "<div style='padding:8% 0 8% 0;'>Thank you for your interest in ASU. An ASU representative will contact you soon!</div>";
   
  $undergrad_confirm_nid = variable_get('asu_rfi_undergrad_confirm_node');
  if($prospect_level == "Undergraduate"){
    if(isset($undergrad_confirm_nid)){
      $unode = node_load($undergrad_confirm_nid);
      $undergrad_body = $unode->body['und'][0]['value'];
      $confirm_message = $message.$undergrad_body;
    }
    else{
     $confirm_message = $message;
    }
   }
   
   elseif($prospect_level == "Graduate"){
    $grad_confirm_nid = variable_get('asu_rfi_grad_confirm_node'); 
    if(isset($grad_confirm_nid)){
      $gnode = node_load($grad_confirm_nid);
      $grad_body = $gnode->body['und'][0]['value'];
      $confirm_message = $message.$grad_body;
    }
    else{
     $confirm_message = $message;
    }
   }
   else{
    $confirm_message = $message;
   }
    
//GMT transaction variables
drupal_add_js("(function ($) {  SI_dataLayer.push({ 'ecommerce': { 'purchase': { 'actionField': { 'id': '$ga_id', 'affiliation': '$program_name','revenue': '100', },'products': [{ 'name': '$college', 'id': '$ga_id', 'price': '100','quantity': '1',}]}}})})(jQuery)", array('type' => 'inline', 'scope' => 'footer','weight' => 5));
 
return $confirm_message;

 
}
?>