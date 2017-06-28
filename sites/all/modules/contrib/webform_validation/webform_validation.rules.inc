<?php

/**
 * @file
 * provides API and management functions for the webform validation rules
 */

/**
 * Get a rule entry
 */
function webform_validation_get_rule($ruleid) {
  $result = db_query("SELECT ruleid, rulename, nid, validator, data, error_message, negate, weight FROM {webform_validation_rule} WHERE ruleid = :ruleid", array(':ruleid' => $ruleid), array('fetch' => PDO::FETCH_ASSOC));
  $rule = $result->fetchAssoc();
  $rule['components'] = webform_validation_get_rule_components($ruleid, $rule['nid']);
  $rule['negate'] = (bool) $rule['negate'];
  return $rule;
}

/**
 * Get an array of rules assigned to a webform node
 */
function webform_validation_get_node_rules($nid) {
  $rules = array();
  $result = db_query("SELECT ruleid, rulename, nid, validator, data, error_message, negate, weight FROM {webform_validation_rule} WHERE nid = :nid ORDER BY weight ASC, ruleid DESC", array(':nid' => $nid), array('fetch' => PDO::FETCH_ASSOC));
  foreach ($result as $rule) {
    $rule['components'] = webform_validation_get_rule_components($rule['ruleid'], $rule['nid']);
    $rule['negate'] = (bool) $rule['negate'];
    $rules[$rule['ruleid']] = $rule;
  }
  return $rules;
}

/**
 * Get an array of components linked to a rule
 */
function webform_validation_get_rule_components($ruleid, $nid) {
  $cids = array();
  $components = array();
  $result = db_query("SELECT cid FROM {webform_validation_rule_components} WHERE ruleid = :ruleid", array(':ruleid' => $ruleid));
  foreach ($result as $row) {
    $cids[] = $row->cid;
  }

  if ($cids) {
    $all_components = webform_validation_get_all_components($nid);
    $all_component_keys = array_keys($all_components);
    foreach ($cids as $cid) {
      if (in_array($cid, $all_component_keys)) {
        $components[$cid] = $all_components[$cid];
      }
    }
  }
  return $components;
}

/**
 * Get info on all components that are available on a webform
 */
function webform_validation_get_all_components($nid) {
  $components = array();
  $result = db_query("SELECT * FROM {webform_component} WHERE nid = :nid", array(':nid' => $nid), array('fetch' => PDO::FETCH_ASSOC));
  foreach ($result as $row) {
    $components[$row['cid']] = $row;
  }
  return $components;
}

/**
 * This helper function takes a list of full component info arrays and returns a basic representation of it for output purposes.
 */
function webform_validation_rule_components_basic($components) {
  $ret = array();
  if ($components) {
    foreach ($components as $cid => $component) {
      $ret[$cid] = _webform_filter_xss($component['name']);
    }
  }
  return $ret;
}

/**
 * Delete a rule and dependencies.
 *
 * @param int $ruleid
 *   The ruleid of the rule to delete.
 */
function webform_dynamic_delete_rule($ruleid) {
  // Delete rule.
  db_delete('webform_validation_rule')
    ->condition('ruleid', $ruleid)
    ->execute();
  // Delete rule components.
  db_delete('webform_validation_rule_components')
    ->condition('ruleid', $ruleid)
    ->execute();
}
