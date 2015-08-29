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
        if($node->field_rfi_submission_status['und'][0]['value'] == "Pending"){
           $node_wrapper->field_rfi_submission_status->set('action_required');
           $to_email = variable_get('asu_rfi_error_email', NULL); //get error reporting email address from rfi admin settings page
           if(!empty($to_email)){
                //send email to admin reporting the issue
                $host = $_SERVER['HTTP_HOST'];
                $content = "The following <a href='https://$host/node/$nid'>submission</a> from ".$_SERVER['HTTP_HOST']." has some problem and hasn't been submitted to middleware";
                $subject = "Failed submissions to Sales Force from ".$_SERVER['HTTP_HOST'];
                $my_module = 'mimemail';
                $my_mail_token = '';
                $MimeMailSystem = drupal_mail_system($my_module, $my_mail_token);
                $default_from = variable_get('site_mail', ini_get('sendmail_from'));
                $message = array(
                    'id' => $my_module . '_' . $my_mail_token,
                    'from' => $default_from,
                    'key' => '',
                    'subject' => $subject,
                    'body' => array($content),
                    'to' => $to_email,
                    'module' => 'mimemail',
                    'headers' => array(
                        'From' => $default_from,
                        'Sender' => $default_from,
                        'Return-Path' => $default_from,
                        'Content-Type' => 'text/html; charset=UTF-8;',
                        'to' => $to_email 
                    ),
                );
	
                $emailmessage = $MimeMailSystem->format($message);
                if ($MimeMailSystem->mail($emailmessage)) {
                    watchdog('asu_rfi', 'SF Error message email sent to '.$to_email);
                    variable_set('SF_error_message_sent', time());
                }
            }
        }
        else{
            $node_wrapper->field_rfi_submission_status->set('Pending');
        }
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
    else{
         http_response_code(400);
    }
}

if (!function_exists('http_response_code'))
{
    function http_response_code($newcode = NULL)
    {
        static $code = 200;
        if($newcode !== NULL)
        {
            header('X-PHP-Response-Code: '.$newcode, true, $newcode);
            if(!headers_sent())
                $code = $newcode;
        }       
        return $code;
    }
}
