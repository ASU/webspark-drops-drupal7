<?php

$type = 'select';
$name = 'rfi_dedupe_list_terms';
$middleware_host = "webforms.asu.edu";

$url = "https://$middleware_host/salesforce_query/api/$type/$name";

https://webforms.asu.edu/salesforce_query/api/select/rfi_dedupe_list_terms

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
  CURLOPT_HTTPHEADER => array(
    'Content-Type: text/json',
    'Authorization: Basic 7755:e7acf2e698751f4cac11718d97df6ebf64b94372'
  ),
);
curl_setopt_array($ch, $options);

$response = curl_exec($ch);
$result = json_decode($response);
curl_close($ch);

if (count($result)) {
  foreach ($result as $semes) {
    db_query("INSERT INTO {asu_rfi_sem_dates} (semId, semLabel) VALUES (:sem_id, :sem_label)", array(
      ':sem_id' => $semes->Id,
      ':sem_label' => $semes->Name
    ));
  }
}

else {
  $sem_sql = "INSERT INTO {asu_rfi_sem_dates} (semId, semLabel) VALUES
    ('a0Jd000000GZFqKEAX', '2018 Summer'),
    ('a0Jd000000GZFqZEAX', '2018 Fall'),
    ('a0Jd000000OH742EAD', '2019 Fall'),
    ('a0Jd000000OH743EAD', '2019 Spring'),
    ('a0Jd000000OH744EAD', '2019 Summer'),
    ('a0Jd000000OH746EAD', '2020 Fall'),
    ('a0Jd000000OH747EAD', '2020 Spring'),
    ('a0Jd000000OH748EAD', '2020 Summer'),
    ('a0Jd000000OH74BEAT', '2021 Spring')";

  db_query($sem_sql);
}
