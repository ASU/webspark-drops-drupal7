<?php

/**
 * @file
 * Provides Rules integration for entities provided via the CRUD API.
 *
 * Rules automatically provides us with actions for CRUD and a suiting entity
 * data type. For events the controller automatically invokes Rules events once
 * Rules is active, so we just have to provide the appropriate info.
 */

/**
 * Default controller for generating Rules integration.
 */
class CommerceFileLicenseEntityRulesController extends EntityDefaultRulesController {

  protected $type, $info;

  public function __construct($type = NULL) {
    parent::__construct(COMMERCE_FILE_LICENSE_ENTITY_NAME);
  }

  public function eventInfo() {
    $info = $this->info;
    $type = $this->type;

    $label = $info['label'];
    $tokens = array('@entity' => drupal_strtolower($label));

    $defaults = array(
      'module' => isset($info['module']) ? $info['module'] : 'entity',
      'group' => $label,
      'access callback' => 'entity_rules_integration_event_access',
    );

    // intialize with standard events
    $items = parent::eventInfo();

    // Update event - add an unchanged variable
    $items[$type . '_update']['variables']["{$type}_unchanged"] = array(
      'type' => $type,
      'label' => t('Unchanged @entity', $tokens),
      'skip save' => TRUE,
      'handler' => 'rules_events_entity_unchanged',
    );

    // File download event
    $items[$type . '_download'] = $defaults + array(
      'label' => t('Requesting a download for a licensed file', $tokens),
      'variables' => array(
        $type => array('type' => $type, 'label' => t('active @entity', $tokens)),
      ),
    );

    // Access denied event
    $items[$type . '_access_denied'] = $defaults + array(
      'label' => t('Before denying access to a licensed file', $tokens),
      'variables' => array(
        $type => array('type' => $type, 'label' => t('active @entity', $tokens)),
      ),
    );

    // Log file download event
    $items[$type . '_log_download'] = $defaults + array(
      'label' => t('Logging access to a licensed file', $tokens),
      'variables' => array(
        $type => array('type' => $type, 'label' => t('active @entity', $tokens)),
      ),
    );

    return $items;
  }

}

/**
 * Implements hook_rules_condition_info().
 */
function commerce_file_rules_condition_info() {
  $group = _commerce_file_translatables('license_label');
  $license_label = $group;

  $conditions = array();
  $conditions['commerce_file_license_condition_address_exists'] = array(
    'label' => t("User's current IP address has been used to access the licensed file"),
    'parameter' => array(
      'license' => array(
        'type' => COMMERCE_FILE_LICENSE_ENTITY_NAME,
        'label' => $license_label,
        'restriction' => 'selector',
      ),
    ),
    'group' => $group,
    'callbacks' => array(
      'execute' => 'commerce_file_license_rules_condition_address_exists',
    ),
  );

  $conditions['commerce_file_license_condition_limit_is_unlimited'] = array(
    'label' => t("Determine if a limit value is unlimited"),
    'parameter' => array(
      'value' => array(
        'type' => 'text',
        'label' => t('Value'),
        'description' => t('The limit value of the license to compare.'),
        'restriction' => 'selector',
      ),
    ),
    'group' => $group,
    'callbacks' => array(
      'execute' => 'commerce_file_license_rules_condition_limit_is_unlimited',
    ),
  );


  return $conditions;
}

/**
 * Implements hook_rules_action_info().
 */
function commerce_file_rules_action_info() {
  $actions = array();
  $group = _commerce_file_translatables('license_label');
  $license_label = $group;

  $actions['commerce_file_license_update_state'] = array(
    'label' => t('Update the license state'),
    'parameter' => array(
      'license' => array(
        'type' => COMMERCE_FILE_LICENSE_ENTITY_NAME,
        'label' => $license_label,
        'restriction' => 'selector',
      ),
      'license_state' => array(
        'type' => 'text',
        'label' => t('License state'),
        'options list' => 'commerce_file_license_state_options_list',
      ),
    ),
    'group' => $group,
    'callbacks' => array(
      'execute' => 'commerce_file_license_rules_action_update_state',
    ),
  );

  $actions['commerce_file_license_update_status'] = array(
    'label' => t('Update the license status'),
    'parameter' => array(
      'license' => array(
        'type' => COMMERCE_FILE_LICENSE_ENTITY_NAME,
        'label' => $license_label,
        'restriction' => 'selector',
      ),
      'license_status' => array(
        'type' => 'text',
        'label' => t('License status'),
        'options list' => 'commerce_file_license_status_options_list',
      ),
    ),
    'group' => $group,
    'callbacks' => array(
      'execute' => 'commerce_file_license_rules_action_update_status',
    ),
  );

  $actions['commerce_file_license_issue_order'] = array(
    'label' => t('Issue licenses for files in the order'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('Commerce order'),
        'restriction' => 'selector',
      ),
      'license_status' => array(
        'type' => 'text',
        'label' => t('Issued license status'),
        'options list' => 'commerce_file_license_status_options_list',
        'default value' => 'pending',
      ),
      'product_refresh' => array(
        'type' => 'boolean',
        'label' => t('Refresh line item files based on the product files'),
        'description' => t('Enabling this refresh will update the as-purchased snapshot of the files on the line items with the current product files and access limits.'),
        'default value' => FALSE,
      ),
    ),
    'group' => $group,
    'callbacks' => array(
      'execute' => 'commerce_file_rules_action_issue_order_licenses',
    ),
  );

   $actions['commerce_file_license_revoke_order'] = array(
    'label' => t('Revoke licenses for files in the order'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('Commerce order'),
        'restriction' => 'selector',
      ),
    ),
    'group' => $group,
    'callbacks' => array(
      'execute' => 'commerce_file_rules_action_revoke_order_licenses',
    ),
  );

  $actions['commerce_file_license_order_update_state'] = array(
    'label' => t('Update the state of all licenses associated with the order'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('Commerce order'),
        'restriction' => 'selector',
      ),
      'license_state' => array(
        'type' => 'text',
        'label' => t('License state'),
        'options list' => 'commerce_file_license_state_options_list',
        'default value' => 'denied',
      ),
    ),
    'group' => $group,
    'callbacks' => array(
      'execute' => 'commerce_file_rules_action_order_update_state',
    ),
  );

  $actions['commerce_file_license_order_update_status'] = array(
    'label' => t('Update the status of all licenses associated with the order'),
    'parameter' => array(
      'order' => array(
        'type' => 'commerce_order',
        'label' => t('Commerce order'),
        'restriction' => 'selector',
      ),
      'license_status' => array(
        'type' => 'text',
        'label' => t('License status'),
        'options list' => 'commerce_file_license_status_options_list',
        'default value' => 'pending',
      ),
    ),
    'group' => $group,
    'callbacks' => array(
      'execute' => 'commerce_file_rules_action_order_update_status',
    ),
  );

  $actions['commerce_file_license_allow_download'] = array(
    'label' => t('ALLOW download of a licensed file'),
    'parameter' => array(
      'license' => array(
        'type' => COMMERCE_FILE_LICENSE_ENTITY_NAME,
        'label' => $license_label,
        'restriction' => 'selector',
      ),
    ),
    'group' => $group,
    'callbacks' => array(
      'execute' => 'commerce_file_license_rules_action_allow_download',
    ),
  );

  $actions['commerce_file_license_log_download'] = array(
    'label' => t('Log download of a licensed file'),
    'parameter' => array(
      'license' => array(
        'type' => COMMERCE_FILE_LICENSE_ENTITY_NAME,
        'label' => $license_label,
        'restriction' => 'selector',
      ),
    ),
    'group' => $group,
    'callbacks' => array(
      'execute' => 'commerce_file_license_rules_action_log_download',
    ),
  );

  return $actions;
}


/**
 * Rules condition: user's IP address exists already in the access logs
 */
function commerce_file_license_rules_condition_address_exists($license) {
  $addresses = $license->addresses;
  $current_address = ip_address();
  return isset($addresses) && isset($addresses[$current_address]);
}

/**
 * Rules condition: Determine if a limit value is unlimited
 */
function commerce_file_license_rules_condition_limit_is_unlimited($value) {
  return CommerceFileLicenseEntity::limit_is_unlimited($value);
}

/**
 * Rules action: Allow a licensed file download
 */
function commerce_file_license_rules_action_allow_download($license) {
  $license->download_allowed = TRUE;
}

/**
 * Rules action: Log a licensed file download
 */
function commerce_file_license_rules_action_log_download($license) {
  $license->log();
}

/**
 * Rules action: Update a license state
 */
function commerce_file_license_rules_action_update_state($license, $status_name) {
  $state = commerce_file_license_state_load($name);
  commerce_file_license_status_update($license, $state['default_status']);
}

/**
 * Rules action: Update a license status
 */
function commerce_file_license_rules_action_update_status($license, $status_name) {
  commerce_file_license_status_update($license, $status_name);
}

/**
 * Rules action: Grant file licenses for order owner based on a line item
 */
function commerce_file_rules_action_issue_order_licenses($order, $license_status = 'pending', $product_refresh = FALSE) {
  commerce_file_license_issue_by_commerce_order($order, $license_status, $product_refresh);
}

/**
 * Rules action: Revoke file licenses' limits for order owner based on a line item
 */
function commerce_file_rules_action_revoke_order_licenses($order) {
  commerce_file_license_order_update_status($order, 'revoked');
}

/**
 * Rules action: Update state of all licenses associated with the order
 */
function commerce_file_rules_action_order_update_state($order, $license_state = 'denied') {
  commerce_file_license_order_update_state($order, $license_state);
}

/**
 * Rules action: Update state of all licenses associated with the order
 */
function commerce_file_rules_action_order_update_status($order, $license_status = 'pending') {
  commerce_file_license_order_update_status($order, $license_status);
}
