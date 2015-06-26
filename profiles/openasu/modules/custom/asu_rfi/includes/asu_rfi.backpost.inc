<?php

/* Callback service function sent for success posting to SF  */

function asu_rfi_success_post($hash, $nid)
{
    header('text/json');
    $mw_auth_key = variable_get('asu_rfi_form_auth_key');
    $real_hash = sha1($mw_auth_key . '+' . $nid);
    if($real_hash == $hash)
    {
        $node = node_load($nid);
        $node_wrapper = entity_metadata_wrapper('node', $node);
        $node_wrapper->field_rfi_submission_status->set('SF_Complete');
        $node_wrapper->save();
        $cid = 'field:node:' . $nid;
        cache_clear_all($cid, 'cache_field');
        print('Success');
    }
    else
    {
        print('Not a valid Hash / Nid combination');
    }
}


/* Fialed posts submissions update */

function asu_rfi_fail_post($hash, $nid)
{
    header('text/json');
    $mw_auth_key = variable_get('asu_rfi_form_auth_key');
    $real_hash = sha1($mw_auth_key . '+' . $nid);
    if($real_hash == $hash)
    {
        $request_body = @file_get_contents('php://input');
        $error_message = $request_body;
    
        $node = node_load($nid);
        $node_wrapper = entity_metadata_wrapper('node', $node);
        $node_wrapper->field_rfi_submission_status->set('Pending');
        $node_wrapper->field_rfi_error_message->set($error_message);
        $node_wrapper->save();
      
        $cid = 'field:node:' . $nid;
        cache_clear_all($cid, 'cache_field');
        print('Posted error message');
    }
    else
    {
        print('Not a valid Hash / Nid combination');
    }
}


/* Test submissions post data update */

function asu_rfi_test_post($hash, $nid)
{
    header('text/json');
    $mw_auth_key = variable_get('asu_rfi_form_auth_key');
    $real_hash = sha1($mw_auth_key . '+' . $nid);
    if($real_hash == $hash)
    {
        $request_body = @file_get_contents('php://input');
        $error_message = $request_body;
    
        $node = node_load($nid);
        $node_wrapper = entity_metadata_wrapper('node', $node);
        $node_wrapper->field_rfi_submission_status->set('SF_Complete');
        $node_wrapper->field_rfi_error_message->set($error_message);
        $node_wrapper->save();
      
        $cid = 'field:node:' . $nid;
        cache_clear_all($cid, 'cache_field');
        print('Posted success message for test submission');
    }
    else
    {
      print('Not a valid Hash / Nid combination');
    }
}

/* The function to save middleware key in the admin settings page App key field */
function asu_rfi_middle_key($key){
    //Check if middleware key is already set. If set, don't update the key, else set the varable with key value
    global $conf;
    
    if(empty($conf['asu_rfi_form_auth_key'])){
        $middle_key = base64_decode($key);
        variable_set('asu_rfi_form_auth_key', $middle_key);
    }
}
