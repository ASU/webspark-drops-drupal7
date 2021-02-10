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
    'COCHS' => t('ASU@Cochise'),
    'CALHC' => t('ASU@Lake Havasu'),
    'LOSAN' => t('ASU@Los Angeles'),
    'MXCTY' => t('ASU@MexicoCity'),
    'NEAZ' => t('ASU@Northeastern Arizona'),
    'PIMA' => t('ASU@Pima'),
    'CAC' => t('ASU@Pinal'),
    'EAC' => t('ASU@The Gila Valley'),
    'TUCSN' => t('ASU@Tucson'),
    'YAVAP' => t('ASU@Yavapai'),
    'WASHD' => t('ASU@Washington, D.C.'),
    'AWC' => t('ASU@Yuma'),
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
