<?php

/**
 * @file
 * Provides a base class for CommerceFileLicenseEntity.
 */

/**
 * A Commerce File License entity class.
 *
 * It's suggested, but not required, to extend this class and to override
 * __construct() in order to specify a fixed entity type.
 *
 * For providing an entity label and URI it is suggested to override the
 * defaultLabel() and defaultUri() methods, and to specify the
 * entity_class_label() and entity_class_uri() as respective callbacks in
 * hook_entity_info(). That way modules are able to override your defaults
 * by altering the hook_entity_info() callbacks, while $entity->label() and
 * $entity->uri() reflect this changes as well.
 */
class CommerceFileLicenseEntity extends Entity {
  const DATA_UNLIMITED = COMMERCE_FILE_FIELD_UNLIMITED;

  public $license_id;

  // database fields
  public $uid, $type, $status;
  public $created, $changed, $granted;

  // derived fields
  protected $state;
  protected $owner, $file, $line_item_ids;
  protected $limits, $addresses;
  protected $download_allowed = FALSE;


  /**
   * Determine if a value is set to UNLIMITED
   */
  public static function limit_is_unlimited($value) {
    return strcmp($value, self::DATA_UNLIMITED) === 0;
  }

  /**
   * Overridden __construct()
   *  - set fixed entity type
   *  - initialize fields
   */
  public function __construct($values = array(), $entityType = NULL) {
    parent::__construct($values, COMMERCE_FILE_LICENSE_ENTITY_NAME);
    $this->_init_fields();
  }

  /**
   * Initialize all unset fields for default field langauage
   */
  private function _init_fields() {
    $fieldNames = $this->get_fieldNames();

    if (!empty($fieldNames)) {
      foreach ($fieldNames as $field_name) {
        if (!isset($this->{$field_name})) {
          $this->_init_field_value($field_name);
        }
      }
    }
  }


  // -----------------------------------------------------------------------
  // Expose static properties and methods

  /**
   * Return license property unlimited value
   */
  public function get_data_unlimited_value() {
    return self::DATA_UNLIMITED;
  }

  public function check_limit_is_unlimited($value) {
    return self::limit_is_unlimited($value);
  }


  // -----------------------------------------------------------------------
  // Base Class overridden methods

  /**
   * Implements save()
   */
  public function save() {
    return parent::save();
  }

  /**
   * Implements buildContent()
   *  - add custom fields to the output.
   */
  public function buildContent($view_mode = 'full', $langcode = NULL) {
    return $this->get_controller()->buildContent($this, $view_mode, $langcode, $content);
  }

  /**
   * Specifies the default label, which is picked up by label() by default.
   */
  protected function defaultLabel() {
    $parts = array();
    $file = $this->get_file();
    $owner = $this->get_owner();
    if (!empty($file['filename'])) {
      $parts[] = $file['filename'];
    }
    if (!empty($owner->name)) {
      $parts[] = ' ' . t('owned by ') . $owner->name;
    }

    if (!empty($parts)) {
      return implode(' ', $parts);
    }

    return $this->entityInfo['label'] . ' ' . $this->internalIdentifier();
  }

  /**
   * Specifies the default uri, which is picked up by uri() by default.
   */
  protected function defaultURI() {
    $path = '';
    if (isset($this->entityInfo['admin ui']['path'])) {
      $path = $this->entityInfo['admin ui']['path'] . '/manage/' . $this->internalIdentifier();
    }
    else {
      $path = 'admin/commerce/file-licenses/manage/' . $this->internalIdentifier();
    }

    return array('path' => $path);
  }


  // -----------------------------------------------------------------------
  // Class Methods

  /**
   * Access callback
   */
  public function access($op = 'view', $account = NULL) {
    return entity_access($op, $this->entityType, $this, $account);
  }

  /**
   * Invoke hook
   */
  public function invoke($hook) {
    $this->get_controller()->invoke($hook, $this);
    return $this;
  }

  /**
   * Returns true if license can be downloaded
   */
  public function can_download($account = NULL) {
    global $user;
    $account = isset($account) ? $account : $user;
    return $this->is_allowed() && $this->access('view', $account) && ($this->invoke('download')->download_allowed);
  }

  /**
   * Returns true if license is in the allowed state
   */
  public function is_allowed() {
    return $this->get_state() == 'allowed';
  }

  /**
   * Returns true if license is in the active status
   */
  public function is_active() {
    return $this->status == 'active';
  }

  /**
   * Returns true if all limits are unlimited
   */
  public function is_unlimited() {
    $limits = $this->get_limits();

    // if no limits, then technically unlimited
    if (empty($limits)) {
      return TRUE;
    }

    // check if all limits are unlimited
    $unlimited_count = 0;
    foreach ($limits as $limit_value) {
      if ($this->check_limit_is_unlimited($limit_value)) {
        $unlimited_count++;
      }
    }

    return $unlimited_count == count($limits);
  }

  /**
   * ALLOW - sets state to 'allowed' with the default status
   */
  public function allow() {
    if (!$this->is_allowed()) {
      $this->set_state('allowed');
    }
    return $this;
  }

  /**
   * DENY - sets state to 'denied' with the default status
   */
  public function deny() {
    if ($this->is_allowed()) {
      $this->set_state('denied');
    }
    return $this;
  }

  /**
   * Log access to the license by the owner
   */
  public function log() {
    global $user;

    // log only if current user is owner
    if ($this->uid == $user->uid) {
      commerce_file_license_log_save(array($this->idKey => $this->internalIdentifier()));
    }

    return $this;
  }


  // -----------------------------------------------------------------------
  // Properties

  /**
   * Entity controller
   *  - Read only
   */
  public function get_controller() {
    return entity_get_controller($this->entityType);
  }

  /**
   * Wrapper
   *  - Read only
   */
  public function get_wrapper() {
    return entity_metadata_wrapper(COMMERCE_FILE_LICENSE_ENTITY_NAME, $this);
  }

  /**
   * Current request time
   */
  public function get_request_time() {
    return REQUEST_TIME;
  }

  /**
   * Status
   *  - Read / Write
   */
  public function set_status($value) {
    $statuses = commerce_file_license_statuses();
    if (!isset($statuses[$value])) {
      throw new Exception("Invalid Status: Attempted to set license status to an invalid value of '$value'.");
    }

    // update status
    $this->status = $value;

    // update state to corresponding state of status
    $this->set_state($statuses[$value]['state']);

    return $this;
  }

  /**
   * State
   *  - Read / Write
   */
  public function get_state() {
    if (!isset($this->state)) {
      $state = FALSE;
      if (isset($this->status)) {
        $status = commerce_file_license_status_load($this->status);
        $state = $status['state'];
      }

      $this->state = $state;
    }

    return $this->state;
  }
  /**
   * Set state
   * @param $value
   *   State name
   */
  public function set_state($value) {
    $state = commerce_file_license_state_load($value);
    if (empty($state)) {
      throw new Exception("Invalid State: Attempted to set license state to an invalid value of '$value'.");
    }
    if (empty($state['default_status'])) {
      throw new Exception("Invalid State: Attempted to set license state to '$value' which does not define a default status.");
    }

    // update state
    $original_state = $this->get_state();
    $this->state = $state['name'];

    // only update status if we're changing states
    if ($original_state != $state['name']) {
      $this->status = $state['default_status'];
    }

    return $this;
  }


  /**
   * uid
   *  - Read / Write
   */
  public function set_uid($value) {
    if ($this->uid != $value) {
      $this->uid = $value;
      unset($this->owner);
    }
  }

  /**
   * Owner
   *  - Read / Write
   */
  public function get_owner() {
    if (!isset($this->owner)) {
      $this->owner = NULL;
      if (isset($this->uid)) {
        $this->owner = user_load($this->uid);
      }
    }
    return $this->owner;
  }

  public function set_owner($value) {
    $owner = NULL;
    if (is_numeric($value)) {
      // load value as uid
      $owner = @user_load($value);
    }
    elseif (is_object($value) && isset($value->uid)) {
      // load fresh user object for uid
      $owner = user_load($value->uid);
    }

    // Set owner if found a user object
    if (isset($owner->uid)) {
      $this->owner = $owner;
      $this->uid = $owner->uid;
    }
    else {
      throw new Exception('Commerce File License: invalid owner input provided. To set owner, provide a valid uid or user object.');
    }

    return $this->owner;
  }

  /**
   * File
   *  - Read / Write
   */
  public function get_file() {
    if (!isset($this->file)) {
      $this->file = array();

      // aggregate file fields on this license
      $files = _commerce_file_field_aggregate_files($this, COMMERCE_FILE_LICENSE_ENTITY_NAME);
      if (!empty($files)) {
        // there can be only 1
        $this->file = reset($files);
      }
    }
    return $this->file;
  }

  /**
   * Set file field item values
   *  - Only can set if no line item references
   *  - Ensures fid is provided
   *  - 'data' is merged with the current file and field instance's defaults
   */
  public function set_file($field_value = array()) {
    if (!empty($field_value)) {
      $wrapper = $this->get_wrapper();
      $license_line_items_field_name = _commerce_file_get_field_names('license_line_items');

      if (!empty($field_value['fid']) && (empty($wrapper->{$license_line_items_field_name}) || !$wrapper->{$license_line_items_field_name}->count())) {
        // allow changing only if no line items
        $field_name = _commerce_file_get_field_names('license_file');
        $field_instance = field_info_instance($this->entityType, $field_name, $this->bundle());
        $current_file = $this->get_file();

        $default_data = array();
        if (!empty($current_file['data'])) {
          $default_data += $current_file['data'];
        }
        if (!empty($field_instance['settings']['data'])) {
          $default_data += $field_instance['settings']['data'];
        }

        // ensure data is set
        if (empty($field_value['data'])) {
          $field_value['data'] = array();
        }

        // merge data defaults
        $field_value['data'] += $default_data;

        // set file field value
        $this->_set_field_value($field_name, $field_value, 'fid');
        $this->file = NULL;

        return TRUE;
      }
    }

    return FALSE;
  }

  /**
   * File Entity
   *  - Read Only
   */
  public function get_file_entity() {
    $item = $this->get_file();
    return isset($item['fid']) ? file_load($item['fid']) : NULL;
  }

  /**
   * Line item ids
   * - Read Only
   *
   * @return
   *   An array of referenced line item ids
   */
  public function get_line_item_ids() {
    if (!isset($this->line_item_ids)) {
      $ids = array();

      $field_name = _commerce_file_get_field_names('license_line_items');
      $field_value = $this->_get_field_value($field_name);
      if (!empty($field_value)) {
        foreach ($field_value as $item) {
          $ids[] = $item['line_item_id'];
        }
      }

      $this->line_item_ids = $ids;
    }

    return $this->line_item_ids;
  }


  // -----------------------------------------------------------------------
  // Field handling

  /**
   * Get field value
   */
  protected function _get_field_value($field_name, $langcode = NULL) {
    $field_items = field_get_items($this->entityType, $this, $field_name, $langcode);
    return $field_items !== FALSE ? $field_items : NULL;
  }

  /**
   * Initialize a field value array
   */
  protected function _init_field_value($field_name, $langcode = LANGUAGE_NONE) {
    if (empty($this->{$field_name})) {
      $this->{$field_name} = array($langcode => array());
    }
    elseif (empty($this->{$field_name}[$langcode])) {
      $this->{$field_name}[$langcode] = array();
    }
  }

  /**
   * Set field value
   *
   * @return
   *   TRUE if set
   */
  protected function _set_field_value($field_name, $field_value = array()) {
    // ensure field is initialized
    $this->_init_field_value($field_name);

    // set value via wrapper to ensure proper setting
    $wrapper = $this->get_wrapper();
    $wrapper->{$field_name} = $field_value;
  }

  /**
   * Add field value
   *
   * @return
   *   TRUE if added
   */
  protected function _add_field_value($field_name, $new_item = NULL, $id_key = NULL) {
    // ensure field is initialized
    $this->_init_field_value($field_name);

    // add new item if it doesn not exist already
    if (!empty($new_item)) {
      if (!empty($id_key)) {
        // exit if item exists
        $field_items = $this->_get_field_value($field_name);
        if (!empty($field_items)) {
          foreach ($field_items as $delta => $item) {
            if (isset($item[$id_key]) && isset($new_item[$id_key]) && $item[$id_key] == $new_item[$id_key]) {
              return FALSE;
            }
          }
        }
      }

      // add it if we got here
      $langcode = field_language($this->entityType, $this, $field_name);
      if (empty($langcode)) {
        $langcode = LANGUAGE_NONE;
      }
      $this->{$field_name}[$langcode][] = $new_item;
    }

    return TRUE;
  }

  /**
   * Get a read only field wrapper
   */
  protected function _get_field_wrapper($field_name) {
    $wrapper = $this->get_wrapper();
    if (!empty($wrapper->{$field_name})) {
      return $wrapper->{$field_name};
    }

    return NULL;
  }

  /**
   * Field Instances
   *  - Read only
   */
  public function get_fieldNames() {
    $instances = field_info_instances($this->entityType, $this->bundle());
    return !empty($instances) ? array_keys($instances) : array();
  }


  // -----------------------------------------------------------------------
  // Line Item handling

  /**
   * Add a line item
   *
   * @return
   *   TRUE if a new line item was linked
   */
  public function link_line_item($new_line_item_id) {
    $field_name = _commerce_file_get_field_names('license_line_items');
    return $this->_add_field_value($field_name, array('line_item_id' => $new_line_item_id), 'line_item_id');
  }

  /**
   * Remove a line item
   *
   * @return
   *   TRUE if the line item was unlinked
   */
  public function unlink_line_item($line_item_id) {
    $field_name = _commerce_file_get_field_names('license_line_items');
    $line_item_field = $this->_get_field_value($field_name);

    $changed = FALSE;
    foreach ($line_item_field as $k => $line_item_field_item) {
      if ($line_item_field_item->line_item_id == $line_item_id) {
        unset($line_item_field[$k]);
        $changed = TRUE;
      }
    }

    if ($changed) {
      $this->_set_field_value($field_name, $line_item_field);
    }

    return $changed;
  }


  // -----------------------------------------------------------------------
  // Limits handling

  /**
   * Aggregated Limits
   *
   * @return
   *   An array of aggregated limits for this license
   */
  public function get_limits() {
    if (!isset($this->limits)) {
      $this->limits = array();

      $native = $this->get_file();
      if (empty($native)) {
        return $this->limits;
      }

      // get license wrapper
      $wrapper = $this->get_wrapper();

      // initialize items and add native as trunk
      $items = array($native);
      $native_fid = $native['fid'];

      // line item entity fields
      $line_item_file_field_name = _commerce_file_get_field_names('line_item_files');

      // license fields
      $license_line_items_field_name = _commerce_file_get_field_names('license_line_items');

      // process license line items
      if (!empty($wrapper->{$license_line_items_field_name})) {
        foreach ($wrapper->{$license_line_items_field_name} as $delta => $line_item_wrapper) {
          // exit if no file fiel on line item
          if (empty($line_item_wrapper->{$line_item_file_field_name})) {
            continue;
          }

          // set qty and exit if there is no qty
          $line_qty = $line_item_wrapper->quantity->value();
          if (empty($line_qty)) {
            continue;
          }

          // aggregate files on the line item
          $line_aggregated = _commerce_file_field_aggregate_files($line_item_wrapper->value(), 'commerce_line_item');

          // only add files for our license fid
          if (isset($line_aggregated[$native_fid])) {
            // multiply by quantity if setting is aggregated
            foreach ($line_item_wrapper->{$line_item_file_field_name} as $file_field_wrapper) {
              foreach ($file_field_wrapper->data as $k => $data) {
                if (isset($line_aggregated[$native_fid]['data'][$k]) && !$this->check_limit_is_unlimited($line_aggregated[$native_fid]['data'][$k])) {
                  $data_info = $data->info();
                  if (!empty($data_info) && !empty($data_info['aggregated'])) {
                    $line_aggregated[$native_fid]['data'][$k] *= $line_qty;
                  }
                }
              }
            }

            // store in all items
            $items[] = $line_aggregated[$native_fid];
          }
        }
      }

      // aggregated = native field + sum of all (line item fields X quantity)
      $aggregated = call_user_func_array('_commerce_file_field_aggregate_field_items', $items);

      // store in license
      if (!empty($aggregated['data'])) {
        $this->limits = $aggregated['data'];
      }
    }

    return $this->limits;
  }

  /**
   * Returns current value for a given limit property
   */
  public function get_limit_current_value($property) {
    return _commerce_file_license_invoke_callback('current', $property, $this);
  }

  /**
   * Returns remaining value for a given limit property
   */
  public function get_limit_remaining_value($property) {
    $limits = $this->get_limits();
    if (isset($limits[$property]) && !$this->check_limit_is_unlimited($limits[$property])) {
      return _commerce_file_license_invoke_callback('remaining', $property, $this, $limits[$property]);
    }

    // default to unlimited
    return $this->get_data_unlimited_value();
  }

  /**
   * Returns check access for a given limit property
   */
  public function get_limit_check_access($property) {
    $limits = $this->get_limits();
    if (isset($limits[$property])) {
      // return TRUE if property is unlimited
      if ($this->check_limit_is_unlimited($limits[$property])) {
        return TRUE;
      }

      // invoke check callback
      $result = _commerce_file_license_invoke_callback('check_access', $property, $this, $limits[$property]);
      if (isset($result)) {
        return $result;
      }
    }

    // default to FALSE
    return FALSE;
  }


  // -----------------------------------------------------------------------
  // Specific access limit handling

  /**
   * Duration
   */
  public function get_duration() {
    $limits = $this->get_limits();
    if (isset($limits['duration'])) {
      return $limits['duration'];
    }
  }

  /**
   * Expiration
   */
  public function get_expiration() {
    $duration = $this->get_duration();

    if (!empty($this->granted) && isset($duration) && !$this->check_limit_is_unlimited($duration)) {
      return $this->granted + $duration;
    }
  }


  // -----------------------------------------------------------------------
  // Access stats

  public function get_download_count() {
    return $this->get_limit_current_value('download_limit');
  }

  public function get_address_count() {
    return $this->get_limit_current_value('address_limit');
  }

  public function get_time_remaining() {
    $rem = $this->get_limit_remaining_value('duration');
    if (!$this->check_limit_is_unlimited($rem) && is_numeric($rem) && $rem < 0) {
      // truncate to 0
      $rem = 0;
    }

    return $rem;
  }


  // -----------------------------------------------------------------------
  // Logs extensions

  public function get_logs() {
    $id = $this->internalIdentifier();
    if (!empty($id)) {
      return commerce_file_license_log_load_multiple(FALSE, array($this->idKey => $id));
    }
    return array();
  }

  public function get_addresses() {
    if (!isset($this->addresses)) {
      $addrs = array();
      foreach ($this->get_logs() as $log) {
        $addrs[$log->hostname] = $log->hostname;
      }
      $this->addresses = $addrs;
    }

    return $this->addresses;
  }


  // -----------------------------------------------------------------------
  // Magic Methods

  /**
   * Get / Set
   *  - method is preferred with lazy fallback to object property
   */
  public function __get($name) {
    $method = "get_$name";
    if (method_exists($this, $method)) {
      return $this->{$method}();
    }

    // allow lazy get
    if (isset($this->{$name})) {
      return $this->{$name};
    }
    return NULL;
  }

  public function __set($name, $value) {
    $method = "set_$name";
    if (method_exists($this, $method)) {
      $this->{$method}($value);
    }
    elseif (!method_exists($this, "get_$name")) {
      // allow lazy setting for non read only properties
      $this->{$name} = $value;
    }
  }

  public function __isset($name) {
    $value = $this->__get($name);
    return isset($value);
  }

  public function __unset($name) {
    unset($this->{$name});
  }

}
