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
    $sku = $program_code.$plan_code.'-RFI';
    $ga_id = variable_get('asu_rfi_google_analytics_key').'-'.$nid ;
    
    //Build array to be used in google analytics coding
    $trans = array('id'=>$ga_id, 'affiliation'=>$program_name,
                'revenue'=>'100');
    
    $items = array('sku'=>$sku, 'name'=>$college, 'category'=>'RFI', 'price'=>'100', 'quantity'=>'1');
   
    $confirm_message = "<div style='padding:8% 0 8% 0;'>Thank you for your interest in ASU. An ASU representative will contact you soon!</div>";
   
 
    //GTM transaction variables
    //drupal_add_js("(function ($) {  SI_dataLayer.push({ 'ecommerce': { 'purchase': { 'actionField': { 'transactionId': '$ga_id', 'transactionAffiliation': '$program_name','revenue': '100', }, 'transactionProducts': [{ 'sku':'$sku','name': '$college', 'id': '$ga_id', 'price': '100','quantity': '1',}]}}})})(jQuery)", array('type' => 'inline', 'scope' => 'header','weight' => 0));
    
    //drupal_add_js("(function ($) { window.SI_dataLayer = window.SI_dataLayer || []; SI_dataLayer.push({'transactionId': '$ga_id', 'transactionAffiliation': '$program_name', 'transactionTotal': 100.00,'transactionProducts': ({'sku': '$sku', 'name': '$college','price': '100.00','quantity': '1'})})})(jQuery)", array('type' => 'inline', 'scope' => 'header','weight' => 0));
    
    //drupal_add_js("(function ($) { var SI_dataLayer =  []; SI_dataLayer.push({'transactionId': '$ga_id', 'transactionAffiliation': '$program_name', 'transactionTotal': 100.00,'transactionProducts': ({'sku': '$sku', 'name': '$college','price': '100.00','quantity': '1'})})})(jQuery)", array('type' => 'inline', 'scope' => 'header','weight' => 0));
    
    /* $script = <<<EOS
    <script type="text/javascript">
    function ($) {
     window.SI_dataLayer = window.SI_dataLayer || [];
     SI_dataLayer.push({
      'transactionId': '$ga_id',
      'transactionAffiliation': '$program_name',
      'transactionTotal': 100.00,
      'transactionProducts': ({
         'sku': '$sku',
         'name': '$college',
         'price': '100.00',
         'quantity': '1'}
         )}
         )}
         )(jQuery);
    </script>
    EOS;
    */
    /*drupal_add_js("(function ($) { 
    var SI_dataLayer = [{
        'transactionId': '$ga_id',
        'transactionAffiliation': '$program_name',
        'transactionTotal': 200.00, //hardcoded
        'transactionProducts': [{
            'sku': '$sku', // DYNAMIC - Plan code with -RFI appended
            'name': '$college',  // DYNAMIC - Program name with -RFI appended
            'price': 100.00, //hardcoded
            'quantity': 1
        }]
    }];
    })(jQuery)", array('type' => 'inline', 'scope' => 'header','weight' => 0));
     */
    /*drupal_add_js("(function ($) { 
    SI_dataLayer = [{
        'transactionId': '1234-john-test',
        'transactionAffiliation': 'W.P. Carey School of Business',
        'transactionTotal': 100.00, //hardcoded
        'transactionProducts': [{
            'sku': 'Plancode TEST-RFI', // DYNAMIC - Plan code with -RFI appended
            'name': 'Online MBA TEST-RFI',  // DYNAMIC - Program name with -RFI appended
            'price': 100.00, //hardcoded
            'quantity': 1
        }]
    }];
    })(jQuery)", array('type' => 'inline', 'scope' => 'body','weight' => 0));
    
    */



    return $confirm_message;

 
}


?>