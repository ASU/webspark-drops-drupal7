<?php

$type = 'select';
$name = 'rfi_dedupe_list_terms';
$middleware_host = "webforms.asu.edu";

$url = "https://$middleware_host/salesforce_query/api/$type/$name";

// https://webforms.asu.edu/salesforce_query/api/select/rfi_dedupe_list_terms

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
  foreach ($result as $semester) {
    $id = (!empty($semester->Id)) ? check_plain($semester->Id) : 'NA';
    $name = (!empty($semester->Name)) ? check_plain($semester->Name) : 'NA';
    if ($id !== 'NA' && $name !== 'NA') {
      db_merge('asu_rfi_sem_dates')
        ->key(array('semId' => $id))
        ->fields(array(
          'semId' => $id,
          'semLabel' => $name,
        ))
        ->execute();
      $message = $name . ' with key ID ' . $id . ' inserted into (or updated in ) the semester options list for ASU RFI forms.';
      watchdog('asu_rfi', $message, array(), WATCHDOG_NOTICE);
    }
    else {
      $message = t('Semester ID or name returned from asu_rfi_sem_dates DB table was empty. Returned values == ID - :id, Name - :name ', array(':id' => $id, ':name'));
      watchdog('asu_rfi', $message, array(), WATCHDOG_NOTICE);
    }
  }
}

else {
  $message = 'No semester IDs/names for RFI forms could be pulled from ' . $url .
    ' to insert into asu_rfi_sem_dates DB table. Check the feed to make sure it is returning values.';
  drupal_set_message($message, 'warning');
  watchdog('asu_rfi', $message, array(), WATCHDOG_WARNING);
}
