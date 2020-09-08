<?php
/**
 * Implements callback_webform_options().
 *
 * Option list containing all available ASU campuses.
 */
function webform_options_campuses_all($component, $flat, $arguments) {
  return array(
    'TEMPE' => t('Tempe'),
    'DTPHX' => t('Downtown'),
    'POLY' => t('Polytechnic'),
    'WEST' => t('West'),
    'ONLNE' => t('Online'),
    'CALHC' => t('ASU@Lake Havasu'),
    'EAC' => t('ASU@The Gila Valley'),
    'TUCSN' => t('ASU@Tucson'),
    'CAC' => t('ASU@Pinal'),
    'YAVAP' => t('ASU@Yavapai'),
    'AWC' => t('ASU@Yuma'),
    'MXCTY' => t('ASU@MexicoCity'),
    'COCHS' => t('ASU@Cochise'),
    'WASHD' => t('ASU@Washington, D.C.'),
    'PIMA' => t('ASU@Pima'),
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
    'DTPHX' => t('Downtown'),
    'POLY' => t('Polytechnic'),
    'WEST' => t('West'),
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
    'DTPHX' => t('Downtown'),
    'POLY' => t('Polytechnic'),
    'WEST' => t('West'),
    'ONLNE' => t('Online'),
  );
}
