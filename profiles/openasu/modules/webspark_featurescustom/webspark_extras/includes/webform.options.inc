<?php
/**
 * Implements callback_webform_options().
 *
 * Option list containing all available ASU campuses.
 */
function webform_options_campuses_all($component, $flat, $arguments) {
  return array(
    'TEMPE' => t('Tempe'),
    'POLY' => t('Polytechnic'),
    'WEST' => t('West'),
    'DTPHX' => t('Downtown'),
    'AWC' => t('Arizona Western College'),
    'EAC' => t('Eastern Arizona College'),
    'CALHC' => t('Lake Havasu'),
    'ONLNE' => t('Online'),
  );
}

/**
 * Implements callback_webform_options().
 *
 * Option list containing local ASU campuses.
 */
function webform_options_campuses_local($component, $flat, $arguments) {
  return array(
    'TEMPE' => t('Tempe'),
    'POLY' => t('Polytechnic'),
    'WEST' => t('West'),
    'DTPHX' => t('Downtown'),
  );
}

/**
 * Implements callback_webform_options().
 *
 * Option list containing local + online campuses.
 */
function webform_options_campuses_local_online($component, $flat, $arguments) {
  return array(
    'TEMPE' => t('Tempe'),
    'POLY' => t('Polytechnic'),
    'WEST' => t('West'),
    'DTPHX' => t('Downtown'),
    'ONLNE' => t('Online'),
  );
}
