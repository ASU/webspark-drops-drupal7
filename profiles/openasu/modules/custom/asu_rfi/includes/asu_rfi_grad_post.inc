<?php

function asu_rfi_grad_post($data){
 
  global $base_url;

  $fname = $data['first_name'];
  $lname = $data['last_name'];
  $email = $data['email'];
  $phone = preg_replace('[\D]', '',$data['phone']);
  $term = $data['semester_name'];
  $state = $data['state'];
  $form_mode = variable_get('asu_rfi_form_mode');
  $nodeid = $data['submission_nodeid'];
 
  //mobile number
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
  
  //country
  if(isset($data['country'])){
    $country = $data['country'];
  }
  else{
    $country = '';
  }
  //get athentication key
  $mw_auth_key = variable_get('asu_rfi_form_auth_key');
  
  //Get siteDomain variable to see if it's dev or qa site.
  global $base_url;
 
  if ((strpos($base_url, 'https://localhost') > 0) || (strpos($base_url, 'http://localhost') > 0)) {
    $environ = 'dev';
  }
  if ((strpos($base_url, 'https://dev-') > 0) || (strpos($base_url, 'http://dev-') > 0) || (strpos($base_url, '-dev') > 0)) {
    $environ = 'dev';
  }
  if ((strpos($base_url, 'https://qa-') > 0) || (strpos($base_url, 'http://qa-') > 0) || (strpos($base_url, '-qa') > 0) ) {
    $environ = 'qa';
  }
  if ((strpos($base_url, 'https://test-') > 0) || (strpos($base_url, 'http://test-') > 0)) {
    $environ = 'qa';
  }

   // Salesforce URL to post data to
 if(($environ == "dev") || ($environ == "qa")){
     $url = 'https://requestinfo-qa.asu.edu/prospect_form_post'; 
 }
 else{
    if($form_mode == 'test'){
      $url = 'https://requestinfo-qa.asu.edu/prospect_form_post'; 
    }
    else{
      $url = 'https://requestinfo.asu.edu/prospect_form_post'; 
    }
 }
 
 $source = $mw_auth_key;
  
 $headers = array('Content-Type' => 'application/x-www-form-urlencoded');  
  
  // build data array to post
  $submission_data = array (
		'source'=> $source,
		'firstName'=> $data['first_name'],
		'lastName'=> $data['last_name'],
		'emailAddress'=> $data['email'],
		'phoneNumber'=> $phone,
		'projectedEnrollment'=> $data['semester_name'],
                'addressLine1' => $data['address'],
                'city' => $city,
                'state' => $state,
                'countryOfResidence' => $country,
                'birthdate' => $dob,
                'militaryStatus' => $military,
                'questions' => $comment,
		'poiCode' => $data['program_code'],
		'zip' => $data['zipcode'],
		'iStudent' => $data['citizenship'],
		'smsNumber' => $mobile,
		
	);
 
  foreach($submission_data as $key_value => $result_array){
    if(($result_array == "None")){
        unset($submission_data[$key_value]);
     }
 }


      //url to post data to salesforce
 $curl = curl_init($url);
	curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE); //If you don't want to use any of the return information, set to false
	curl_setopt($curl, CURLOPT_HEADER, FALSE); //Set this to false to remove informational headers
	curl_setopt($curl, CURLOPT_CUSTOMREQUEST, 'POST');
        curl_setopt($curl, CURLOPT_POSTFIELDS, $submission_data); //data mapping
	curl_setopt($curl, CURLOPT_SSLVERSION, 1); //This will set the security protocol to TLSv1
	curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);
	
	
	$response = curl_exec($curl);
	
	$info = curl_getinfo($curl); //Used by your drupal messages below
	
	curl_close($curl);

	if(strpos($response, "-1 ") == 0){
	  $message = explode(':',$response);
        }
     
//Get the response from Salesforce. If the submission is not successfull, update the previous submission status to Incomplete
if(($info['http_code'] == 400) || ($info['http_code'] == 500)){
   
    //update error message
    $node = node_load($nodeid);
    $node_wrapper = entity_metadata_wrapper('node', $node);
    $node_wrapper->field_rfi_submission_status->set("Pending");
    $node_wrapper->field_rfi_error_message->set($message[1]);
    $node_wrapper->save();
  
}

if(($info['http_code'] == 200)){
 
    $node = node_load($nodeid);
    $node_wrapper = entity_metadata_wrapper('node', $node);
    $node_wrapper->field_rfi_submission_status->set('SF_Complete');
    $node_wrapper->field_rfi_error_message->set('');
    $node_wrapper->save();
   //if succesfully to post to SF, the set "last_failure_SF_posting" variable to current time
  variable_set('last_success_SF_posting', time());
}

//if failed to post to SF, the set "last_failure_SF_posting" variable to current time
if(($info['http_code'] != 200)){
  variable_set('last_failure_SF_posting', time());
}


}

?>