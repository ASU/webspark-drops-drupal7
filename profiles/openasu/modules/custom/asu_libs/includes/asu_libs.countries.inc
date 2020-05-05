<?php

/**
 * Convert countries between Peoplesoft and Salesforce values.
 *
 * @param array $results - Query results with countries. @see asu_rfi_get_form_select_options()
 */
function asu_libs_get_sf_country_mapping(&$results) {
  $map = array(
    'Bahamas, The' => 'Bahamas',
    'Bolivia' => 'Bolivia, Plurinational State of',
    'British Virgin Islands' => 'Virgin Islands, British',
    'Brunei' => 'Brunei Darussalam',
    'Burma' => 'Myanmar',
    'Congo, Democratic Republic of' => 'Congo, The Democratic Republic of the',
    'French Southern & Antarc Lands' => 'French Southern Territories',
    'Gambia, The' => 'Gambia',
    'Iran' => 'Iran, Islamic Republic of',
    'Laos' => "Lao People's Democratic Republic",
    'Libya' => 'Libyan Arab Jamahiriya',
    'Macedonia' => 'Macedonia, the former Yugoslav Republic of',
    'Moldova' => 'Moldova, Republic of',
    'North Korea' => "Korea, Democratic People's Republic of",
    'Palestinian Territory, Occupie' => 'Palestinian Territory, Occupied',
    'Pitcairn Island' => 'Pitcairn',
    'Vietnam' => 'Viet Nam',
    'Russia' => 'Russian Federation',
    'Saint Helena' => 'Saint Helena, Ascension and Tristan da Cunha',
    'Saint Martin' => 'Saint Martin (French part)',
    'Saint Vincent & the Grenadines' => 'Saint Vincent and the Grenadines',
    'South Georgia & S Sandwich Is' => 'South Georgia and the South Sandwich Islands',
    'South Korea' => 'Korea, Republic of',
    'Syria' => 'Syrian Arab Republic',
    'Taiwan' => 'Chinese Taipei',
    'Tanzania' => 'Tanzania, United Republic of',
    'Vatican City' => 'Holy See (Vatican City State)',
    'Venezuela' => 'Venezuela, Bolivarian Republic of',
    'Wallis and Futuna Islands' => 'Wallis and Futuna',
  );

  $count = 0;
  foreach ($results as $result) {
    $current = $result->label;
    if (array_key_exists($current, $map)) {
      $results[$count]->label = $map[$current];
    }
    $count++;
  }
}
