<?php

/**
 * @file
 * Default rules configuration for Commerce Files.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_file_default_rules_configuration() {
  $rules = array();

  // file download access
  $rule = rules_reaction_rule();
  $rule->label = t('Control access to licensed file downloads');
  $rule->tags = array('commerce_file');
  $rule->active = TRUE;
  $rule->event('commerce_file_license_download')
    ->condition(rules_or()
        ->condition('commerce_file_license_condition_limit_is_unlimited', array(
          'value:select' => 'commerce-file-license:limits:download-limit',
        ))
        ->condition('data_is', array(
          'data:select' => 'commerce-file-license:download-count',
          'op' => '<',
          'value:select' => 'commerce-file-license:limits:download-limit',
        ))
    )
    ->condition(rules_or()
        ->condition('commerce_file_license_condition_limit_is_unlimited', array(
          'value:select' => 'commerce-file-license:limits:address-limit',
        ))
        ->condition('data_is', array(
          'data:select' => 'commerce-file-license:address-count',
          'op' => '<',
          'value:select' => 'commerce-file-license:limits:address-limit',
        ))
        ->condition('commerce_file_license_condition_address_exists', array(
          'license:select' => 'commerce-file-license',
        ))
    )
    ->condition(rules_or()
        ->condition('data_is_empty', array(
          'data:select' => 'commerce-file-license:expiration',
        ))
        ->condition('data_is', array(
          'data:select' => 'commerce-file-license:request-time',
          'op' => '<',
          'value:select' => 'commerce-file-license:expiration',
        ))
    )
    ->action('commerce_file_license_allow_download', array(
      'license:select' => 'commerce-file-license',
    ));

  $rules['commerce_file_license_download_access'] = $rule;


  // Log access for a file download
  $rule = rules_reaction_rule();
  $rule->label = t('Log download of a licensed file');
  $rule->tags = array('commerce_file');
  $rule->active = TRUE;
  $rule->event('commerce_file_license_log_download')
    ->action('commerce_file_license_log_download', array(
      'license:select' => 'commerce-file-license',
    ));

  $rules['commerce_file_license_log_download'] = $rule;


  // Issue licenses as 'active' on checkout complete
  $rule = rules_reaction_rule();
  $rule->label = t('Issue licenses on checkout complete');
  $rule->tags = array('commerce_file');
  $rule->active = TRUE;
  $rule->weight = 10; // trigger after others
  $rule->event('commerce_checkout_complete')
    ->condition(rules_condition('data_is_empty', array(
      'data:select' => 'commerce-order:uid',
    ))->negate())
    ->action('commerce_file_license_issue_order', array(
      'order:select' => 'commerce-order',
      'license_status' => 'active',
      'product_refresh' => FALSE,
    ));

  $rules['commerce_file_issue_checkout_licenses'] = $rule;


  return $rules;
}
