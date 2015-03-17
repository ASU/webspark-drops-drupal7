<?php

  $type = 'fieldinfo';
  $name = 'state_province';
  
  
  $middleware_host = "webforms.asu.edu";
  
  
  $url = "https://$middleware_host/asu_salesforce_query/api/$type/$name";

  $ch = curl_init();
  $options = array(
    CURLOPT_URL => $url,
    CURLOPT_RETURNTRANSFER => 1,
    CURLOPT_HTTPHEADER => array('Content-Type: text/json', 'Authorization: Basic 7755:e7acf2e698751f4cac11718d97df6ebf64b94372'),

  );  

  curl_setopt_array($ch, $options);

  $response = curl_exec($ch);

  $result = json_decode($response);
  curl_close($ch);
  //if results exist, insert values in db for webservice call
  if(count($result)){
   foreach($result as $state){
     db_query("INSERT INTO {asu_rfi_states_list} (stateCode, stateDesc) VALUES (:state_value, :state_label)", array(':state_value' => $state->value, ':state_label' => $state->label));
   }
  }
  
  //else insert values into db
  else{
    $sql =   "INSERT INTO {asu_rfi_states_list} (stateCode, stateDesc) VALUES
('AA', 'Armed Forces Americas'),
('AB', 'Alberta'),
('AE', 'Armed Forces Europe'),
('AK', 'Alaska'),
('AL', 'Alabama'),
('AP', 'Armed Forces Pacific'),
('AR', 'Arkansas'),
('AS', 'American Samoa'),
('AZ', 'Arizona'),
('BC', 'British Columbia'),
('CA', 'California'),
('CO', 'Colorado'),
('CT', 'Connecticut'),
('DC', 'District of Columbia'),
('DE', 'Delaware'),
('FL', 'Florida'),
('GA', 'Georgia'),
('GU', 'Guam'),
('HI', 'Hawaii'),
('IA', 'Iowa'),
('ID', 'Idaho'),
('IL', 'Illinois'),
('IN', 'Indiana'),
('KS', 'Kansas'),
('KY', 'Kentucky'),
('LA', 'Louisiana'),
('MA', 'Massachusetts'),
('MB', 'Manitoba'),
('MD', 'Maryland'),
('ME', 'Maine'),
('MH', 'Marshall Islands'),
('MI', 'Michigan'),
('MN', 'Minnesota'),
('MO', 'Missouri'),
('MP', 'Northern Mariana Islands'),
('MS', 'Mississippi'),
('MT', 'Montana'),
('NB', 'New Brunswick'),
('NC', 'North Carolina'),
('ND', 'North Dakota'),
('NE', 'Nebraska'),
('NH', 'New Hampshire'),
('NJ', 'New Jersey'),
('NL', 'Newfoundland and Labrador'),
('NM', 'New Mexico'),
('NS', 'Nova Scotia'),
('NT', 'Northwest Territories'),
('NU', 'Nunavut'),
('NV', 'Nevada'),
('NY', 'New York'),
('OH', 'Ohio'),
('OK', 'Oklahoma'),
('ON', 'Ontario'),
('OR', 'Oregon'),
('PA', 'Pennsylvania'),
('PE', 'Prince Edward Island'),
('PR', 'Puerto Rico'),
('QC', 'Quebec'),
('RI', 'Rhode Island'),
('SC', 'South Carolina'),
('SD', 'South Dakota'),
('SK', 'Saskatchewan'),
('TN', 'Tennessee'),
('TX', 'Texas'),
('UM', 'United States Minor Outlying Islands'),
('UT', 'Utah'),
('VA', 'Virginia'),
('VI', 'US Virgin Islands'),
('VT', 'Vermont'),
('WA', 'Washington'),
('WI', 'Wisconsin'),
('WV', 'West Virginia'),
('WY', 'Wyoming'),
('YT', 'Yukon Territories')"; 

db_query($sql);
  }
  
  

?>