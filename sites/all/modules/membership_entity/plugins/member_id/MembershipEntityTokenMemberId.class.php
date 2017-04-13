<?php

/**
 * @file
 * Contains the MembershipEntityTokenMemberId class.
 */

class MembershipEntityTokenMemberId extends MembershipEntityMemberIdAbstract {
  /**
   * Returns the next available member id.
   */
  public function next($membership) {
    $settings = $this->settings + array(
      'pattern' => '',
      'suffix' => 1,
      'length' => 5,
      'advanced' => array(),
    );
    $settings['advanced'] += array(
      'separator' => '-',
      'maxlength' => '',
      'case' => 'none',
      'ignore_words' => '',
    );

    // Build the member id.
    $member_id = token_replace($settings['pattern'], array('membership_entity' => $membership), array(
      'sanitize' => TRUE,
      'clear' => TRUE,
      'callback' => '_membership_entity_token_member_id_token_callback',
      'settings' => $settings['advanced'],
    ));

    // Empty member_ids do not need any cleaning.
    if ($member_id !== '' && $member_id !== NULL) {
      $member_id = _membership_entity_token_clean_separator($member_id, $settings['advanced']['separator']);
    }

    // Optionally add a unique suffix.
    if (!empty($settings['suffix'])) {
      $length = $settings['length'];
      $suffix = 1;

      // Find the most recent matching member id.
      $query = db_select('membership_entity', 'm');
      $query->addExpression('MAX(member_id)', 'member_id');
      $id = $query->condition('member_id', db_like($member_id) . '%', 'LIKE')
        ->execute()
        ->fetchField();

      // If a member id already exists increment suffix by 1.
      if (!empty($id)) {
        $id = (int) str_replace($member_id, '', $id);
        $suffix = $id + 1;
      }

      $member_id .= str_pad($suffix, $length, '0', STR_PAD_LEFT);
    }

    return $member_id;
  }

  /**
   * Builds the settings form for the member id.
   */
  public function settingsForm(&$form_state) {
    $settings = $this->settings + array(
      'pattern' => '',
      'suffix' => 1,
      'length' => 5,
      'advanced' => array(),
    );
    $settings['advanced'] += array(
      'separator' => '-',
      'maxlength' => '',
      'case' => 'none',
      'ignore_words' => '',
    );

    $form['pattern'] = array(
      '#type'=> 'textfield',
      '#title' => t('Member ID Pattern.'),
      '#description' => t('The pattern to use to create the member id. You may enter data from the "Replacement patterns" below.'),
      '#required' => TRUE,
      '#default_value' => $settings['pattern'],
      '#size' => 65,
      '#maxlength' => 1280,
      '#element_validate' => array('token_element_validate'),
      '#after_build' => array('token_element_validate'),
      '#token_types' => array('membership_entity'),
      '#min_tokens' => 1,
    );

    $form['token_help'] = array(
      '#title' => t('Replacement patterns'),
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['token_help']['help'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('membership_entity'),
    );

    $form['suffix'] = array(
      '#type' => 'checkbox',
      '#title' => t('Add an incrementing numeric suffix'),
      '#description' => t('Member ids must be unique. Check this box to append a unique suffix to the pattern above. You should check this box if the pattern entered above does not contain enough information to guarantee uniqueness.'),
      '#default_value' => $settings['suffix'],
    );

    $form['length'] = array(
      '#type' => 'textfield',
      '#title' => t('Suffix Length'),
      '#description' => t("The minimum number of digits numeric suffix. The suffix will be filed with leading '0's (eg. 00001)."),
      '#size' => 5,
      '#states' => array(
        'required' => array(
          'input[name="member_id_settings[suffix]"]' => array('checked' => TRUE)
        ),
        'visible' => array(
          'input[name="member_id_settings[suffix]"]' => array('checked' => TRUE)
        ),
      ),
      '#default_value' => $settings['length'],
      '#element_validate' => array('element_validate_integer_positive'),
    );

    $form['advanced'] = array(
      '#type' => 'fieldset',
      '#title' => t('Advanced settings'),
      '#collapsed' => TRUE,
      '#collapsible' => TRUE,
    );

    $form['advanced']['separator'] = array(
      '#type' => 'textfield',
      '#title' => t('Separator'),
      '#size' => 1,
      '#maxlength' => 1,
      '#default_value' => $settings['advanced']['separator'],
      '#description' => t('Character used to separate words in tokens. This will replace any spaces and punctuation characters.'),
    );

    $form['advanced']['maxlength'] = array(
      '#type' => 'textfield',
      '#title' => t('Maximum token length'),
      '#size' => 3,
      '#maxlength' => 3,
      '#default_value' => $settings['advanced']['maxlength'],
      '#description' => t('Maximum text length of any one token in the member id (e.g., [title]).'),
      '#element_validate' => array('element_validate_integer_positive'),
    );

    $form['advanced']['case'] = array(
      '#type' => 'radios',
      '#title' => t('Character case'),
      '#default_value' => $settings['advanced']['case'],
      '#options' => array(
        'none' => t('Leave case the same as source token values.'),
        'lower' => t('Change to lower case'),
        'upper' => t('Change to upper case'),
      ),
    );

    $form['advanced']['ignore_words'] = array(
      '#type' => 'textfield',
      '#title' => t('Strings to remove'),
      '#default_value' => $settings['advanced']['ignore_words'],
      '#description' => t('Words to strip out of the token values, separated by commas.'),
    );

    return $form;
  }
}

/**
 * Token callback to clean a replacement value.
 */
function _membership_entity_token_member_id_token_callback(&$replacements, $data = array(), $options = array()) {
  foreach ($replacements as $token => $value) {
    $replacements[$token] = _membership_entity_token_clean_string($value, $options['settings']);
  }
}

/**
 * Apply advanced options to a generated member id string.
 */
function _membership_entity_token_clean_string($string, $settings) {
  // Remove all HTML tags from the string.
  $return = strip_tags(decode_entities($string));

  // Get rid of words that are on the ignore list
  $ignore_words = $settings['ignore_words'];
  $ignore_words_regex = preg_replace(array('/^[,\s]+|[,\s]+$/', '/[,\s]+/'), array('', '\b|\b'), $ignore_words);
  if ($ignore_words_regex) {
    $ignore_words_regex = '/\b' . $ignore_words_regex . '\b/i';
    $words_removed = preg_replace($ignore_words_regex, '', $return);
    if (drupal_strlen(trim($words_removed)) > 0) {
      $return = $words_removed;
    }
  }

  // Replace whitespace with the separator.
  $return = _membership_entity_token_clean_separator($return, $settings['separator']);

  // Convert to lower or upper case.
  if ($settings['case'] == 'lower') {
    $return = drupal_strtolower($return);
  }
  else if ($settings['case'] == 'upper') {
    $return = drupal_strtoupper($return);
  }

  // Shorten to maxlength.
  if (!empty($settings['maxlength'])) {
    $return = truncate_utf8($return, $settings['maxlength']);
  }

  return $return;
}

/**
 * Replace whitespace and punctuation with a separator.
 */
function _membership_entity_token_clean_separator($string, $separator) {
  $return = $string;
  if (strlen($separator)) {
    $return = preg_replace('/\s+/', $separator, $return);

    // Replace punctuation.
    $punctuation = array('"', '\'', '`', ',', '.', '-', '_', ':', ';', '|', '{', '[', '}', ']', '+', '=', '*', '&', '%', '^', '$', '#', '@', '!', '~', '(', ')', '?', '<', '>', '/', '\\');
    $return = str_replace($punctuation, $separator, $return);

    // Escape the separator.
    $pattern = preg_quote($separator, '/');

    // Trim any leading or trailing separators.
    $return = preg_replace("/^$pattern+|$pattern+$/", '', $return);

    // Replace multiple separators with a single one.
    $return = preg_replace("/$pattern+/", $separator, $return);
  }
  return $return;
}
