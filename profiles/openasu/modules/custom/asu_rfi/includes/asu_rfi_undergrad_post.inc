<?php

function asu_rfi_undergrad_post($data)
{
  global $base_url;
 dpm($data);
  $mw_auth_key = variable_get('asu_rfi_form_auth_key');
  $fname = $data['first_name'];
  $lname = $data['last_name'];
  $email = $data['email'];
  $phone = preg_replace('[\D]', '',$data['phone']);
  if(!empty($data['start_date'])){
    $term = $data['start_date'];
  }
  else{
    $term = '';
  }
  
  $state = $data['state'];
  $prog_code = $data['program_code'];
  $nodeid = $data['submission_nodeid'];
  $form_mode = variable_get('asu_rfi_form_mode');
  $hashkey = sha1($mw_auth_key.'+'.$nodeid); 
  
  //check if the submission values are empty
  if(isset($state)){
    if($state == 0){
      $state_province = '';
    }
    else{
      $state_province = $state;
    }
    
  }
  else{
    $state_province = '';
  }
  
  //modile phone
  if(isset($data['mobile_check'])){
    $mobile = str_replace('-', '', $data['mobile_check']);
  }
  else{
    $mobile = '';
  }
  
  //date of birth
  if(isset($data['birthdate'])){
    $dob = $data['birthdate'];
  }
  else{
    $dob = '';
  }
  
  //Military
  if(isset($data['military'])){
    $military = $data['military'];
  }
  else{
    $military =  '';
  }
 
 //Comment
  if(isset($data['questions'])){
    $comment = $data['questions'];
  }
  else{
    $comment = '';
  }
  
  //city
  if(isset($data['city'])){
    $city = $data['city'];
  }
  else{
    $city = '';
  }
  
  //address
  if(isset($data['address'])){
    $address = $data['address'];
  }
  else{
    $address = '';
  }
  
  //international
  /*if($data['citizenship'] == 'FALSE')
  {
    $intnl_student = TRUE;
  }
   else
   {
    $intnl_student = FALSE;
  }*/
  
  //country
  if(isset($data['country'])){
    $country = $data['country'];
  }
  else{
    $country = '';
  }

  //Get siteDomain variable to see if it's dev or qa site.
  $site = variable_get('siteDomain');

   // Salesforce URL to post data to
  if(($site == "dev") || ($site == "qa") || ($form_mode == "test"))
  {
    $url = "https://webforms-qa.asu.edu/asu_rfi_dedupe/submit_rfi/$hashkey/$nodeid";
  }
  else
  {
    $url = "https://webforms.asu.edu/asu_rfi_dedupe/submit_rfi/$hashkey/$nodeid";
  }
  
  $source = '';
   
  $fields = array(
    'first_name' => $fname,
    'last_name' => $lname,
    'prospect_level' => 'Undergraduate',
    'student_type' => $data['student_type'],
    'program' => $prog_code,
    'starting_semester' => $data['start_date'],
    'email' => $email,
    'zip' => $data['zipcode'],
    'phone' => $phone,
    'birth_date' => $dob,
    'country' => $country,
    'sms' => $mobile,
    'comments' => $comment,
    'prod_test_flag' => $form_mode,
    'street' => $address,
    'city' => $city,
    'state' => $state_province,
    'intnl_student' => $data['citizenship'] ,
    'veteran_status' => $military,
  );

  $body = json_encode($fields);


   

  try 
  {
    $ch = curl_init();
    $options = array(
      CURLOPT_URL => $url,
      CURLOPT_POST => 1,
      CURLOPT_POSTFIELDS => $body,
      CURLOPT_RETURNTRANSFER => 1,
      CURLOPT_HTTPHEADER => array('Content-Type: text/json'),
      CURLOPT_SSLVERSION => 1,
      CURLOPT_SSL_VERIFYPEER => FALSE,
    );  

    curl_setopt_array($ch, $options);

    $response = curl_exec($ch);
    curl_close($ch);

    if (FALSE === $response)
    {
      throw new Exception(curl_error($ch), curl_errno($ch));
    }
  } 
  catch(Exception $e) 
  {
    trigger_error(sprintf(
        'Curl failed with error #%d: %s',
        $e->getCode(), $e->getMessage()),
        E_USER_ERROR);
  }   
}
