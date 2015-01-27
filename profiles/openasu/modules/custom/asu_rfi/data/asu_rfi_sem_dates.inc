<?php

  $type = 'select';
  $name = 'rfi_dedupe_list_terms';
  
  //get environment variable fro variables table
  $environment = variable_get('siteDomain');
  if(($environment == "qa") || ($environment == "dev")){
    $middleware_host = "webforms-dev.asu.edu";
  }
  else{
    $middleware_host = "webforms.asu.edu";
  }
  $url = "https://$middleware_host/asu_salesforce_query/api/$type/$name";

  $fields = array(
    'condition_Term_Status__c' => TRUE,
  );

  $body = json_encode($fields);

  $ch = curl_init();
  $options = array(
    CURLOPT_URL => $url,
    CURLOPT_POST => 1,
    CURLOPT_POSTFIELDS => $body,
    CURLOPT_RETURNTRANSFER => 1,
    CURLOPT_HTTPHEADER => array('Content-Type: text/json', 'Authorization: Basic ' . base64_encode('apuliroj:3UIzHi6vMNXDTV9p')),
  );  

  curl_setopt_array($ch, $options);

  $response = curl_exec($ch);
  $result = json_decode($response);
  curl_close($ch);

  if(count($result)){
    foreach($result as $serres){
         db_query("INSERT INTO {asu_rfi_sem_dates} (semId, semLabel) VALUES (:sem_id, :sem_label)", array(':sem_id' => $serres->Id, ':sem_label' => $serres->Name));
     }
  }
  
  else{
$sem_sql = "INSERT INTO {asu_rfi_sem_dates} (semId, semLabel) VALUES
('a0Jd000000CpGccEAF', '2014 Spring'),
('a0Jd000000CpGchEAF', '2014 Summer'),
('a0Jd000000CpGnVEAV', '2014 Fall'),
('a0Jd000000CpGzlEAF', '2015 Spring'),
('a0Jd000000CpH91EAF', '2015 Summer'),
('a0Jd000000CpH96EAF', '2015 Fall'),
('a0Jd000000CpH9GEAV', '2016 Spring'),
('a0Jd000000CpH9HEAV', '2016 Fall'),
('a0Jd000000CpH9QEAV', '2016 Summer'),
('a0Jd000000CxjENEAZ', '2013 Fall'),
('a0Jd000000CycI5EAJ', '2013 Summer'),
('a0Jd000000GZCxkEAH', '2017 Fall'),
('a0Jd000000GZCxQEAX', '2017 Spring'),
('a0Jd000000GZCxVEAX', '2017 Summer'),
('a0Jd000000GZFqAEAX', '2018 Spring'),
('a0Jd000000GZFqKEAX', '2018 Summer'),
('a0Jd000000GZFqZEAX', '2018 Fall')";

db_query($sem_sql);

}
  

?>