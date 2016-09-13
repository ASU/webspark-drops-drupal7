<?php
/**
 * @file
 * Class GigyaAccount
 *
 * A class to deal with Gigya RaaS account.
 */

class GigyaAccount {

  /**
   * Gigya profile object.
   *
   * @var
   */
  private $profile;
  /**
   * Gigya data object.
   *
   * @var
   */
  private $data;

  /**
   * Class constructor.
   *
   * @param int $uid
   *   User uid.
   */
  public  function __construct($uid) {
    $res = _gigya_api('accounts.getAccountInfo', array('UID' => $uid));
    if (is_array($res)) {
      $this->profile = $res['profile'];
      $this->data = $res['data'];
    }
  }

  /**
   * Gets the data object.
   *
   * @return mixed
   *   The data object.
   */
  public function getData() {
    return $this->data;
  }

  /**
   * Gets the Gigya profile object.
   *
   * @return mixed
   *   The Gigya profile object
   */
  public function getProfile() {
    return $this->profile;
  }

  /**
   * Gets the a value from the profile object.
   *
   * @param string $field_name
   *   The field name.
   *
   * @return string|null
   *   The field value or null.
   */
  public function getProfileField($field_name) {
    return !empty($this->profile[$field_name]) ? $this->profile[$field_name] : NULL;
  }

  /**
   * Gets a value from the data object.
   *
   * @param string $field_name
   *   The field name.
   *
   * @return string|null
   *   The data field name or null.
   */
  public function getDataField($field_name) {
    $path = explode('.', $field_name);
    $branch = array();
    foreach ($path as $p) {
      if (isset($this->data[$p])) {
        if (is_array($this->data[$p])) {
          $branch = $this->data[$p];
        }
        else {
          return $this->data[$p];
        }
      }
      elseif (isset($branch[$p])) {
        if (is_array($branch[$p])) {
          $branch = $branch[$p];
        }
        else {
          return $branch[$p];
        }
      }
      else {
        return NULL;
      }
    }
  }
}
