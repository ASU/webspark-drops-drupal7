<?php

/**
 * @file
 * Module's admin forms.
 */

/**
 * General configuration form.
 *
 * @return Assoc
 *   renderable form.
 */
function _easy_breadcrumb_general_settings_form() {

  drupal_add_js(drupal_get_path('module', 'easy_breadcrumb') . '/js/easy_breadcrumb.admin.js');

  // Fieldset for grouping general settings fields.
  $fieldset_general = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_DISABLE_DEFAULT_DRUPAL_BREADCRUMB] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable the system breadcrumbs in site theme.'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_DISABLE_DEFAULT_DRUPAL_BREADCRUMB, FALSE),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_DISABLE_ADMIN_BREADCRUMB] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable the system breadcrumbs in admin theme.'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_DISABLE_ADMIN_BREADCRUMB, FALSE),
    '#description' => t('Default drupal breadcrumb is only disabled when the admin theme is different to site theme. If both themes are the same, this option has no effect.'),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_SEGMENTS_SEPARATOR] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#title' => t('Breadcrumb separator:'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_SEGMENTS_SEPARATOR, '»'),
  );

  $fieldset_general[EasyBreadcrumbConstants::DB_VAR_SEPERATOR_ENDING] = array(
    '#type' => 'checkbox',
    '#title' => t('Show breadcrumb separator after the final breadcrumb.'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_SEPERATOR_ENDING, FALSE),
  );

  // Fieldset for grouping text settings.
  $fieldset_general['first'] = array(
    '#type' => 'fieldset',
    '#title' => t('First Breadcrumb'),
    '#collapsible' => FALSE,
  );

  $fieldset_general['first'][EasyBreadcrumbConstants::DB_VAR_INCLUDE_HOME_SEGMENT] = array(
    '#type' => 'checkbox',
    '#title' => t('Include the a link to the home page as the first breadcrumb.'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_HOME_SEGMENT, TRUE),
  );

  $fieldset_general['first'][EasyBreadcrumbConstants::DB_VAR_HOME_SEGMENT_TITLE] = array(
    '#type' => 'textfield',
    '#title' => t('Home page link text:'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_HOME_SEGMENT_TITLE, t('Home')),
    '#attributes' => array('placeholder' => 'Home'),
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_INCLUDE_HOME_SEGMENT . '"]' => array('checked' => TRUE),
      ),
    ),
  );

  $fieldset_general['final'] = array(
    '#type' => 'fieldset',
    '#title' => t('Final Breadcrumb'),
    '#collapsible' => FALSE,
  );

  $fieldset_general['final'][EasyBreadcrumbConstants::DB_VAR_INCLUDE_TITLE_SEGMENT] = array(
    '#type' => 'checkbox',
    '#title' => t('Include the current page as the final breadcrumb.'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_TITLE_SEGMENT, TRUE),
  );

  $fieldset_general['final'][EasyBreadcrumbConstants::DB_VAR_TITLE_SEGMENT_AS_LINK] = array(
    '#type' => 'checkbox',
    '#title' => t('Make the current page breadcrumb into a link (not recommended).'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_TITLE_SEGMENT_AS_LINK, FALSE),
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_INCLUDE_TITLE_SEGMENT . '"]' => array('checked' => TRUE),
      ),
    ),
  );

  $fieldset_general['paths'] = array(
    '#type' => 'fieldset',
    '#title' => t('Path settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $fieldset_general['paths'][EasyBreadcrumbConstants::DB_VAR_INCLUDE_INVALID_PATHS] = array(
    '#type' => 'checkbox',
    '#title' => t('Include invalid paths as plain-text breadcrumbs (not recommended).'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_INCLUDE_INVALID_PATHS, TRUE),
  );

  // Formats the excluded paths array as line separated list of paths
  // before displaying them.
  $excluded_paths_arr = variable_get(EasyBreadcrumbConstants::DB_VAR_EXCLUDED_PATHS,
    EasyBreadcrumbConstants::defaultExcludedPaths());
  $excluded_paths = @implode("\r\n", $excluded_paths_arr);
  $fieldset_general['paths'][EasyBreadcrumbConstants::DB_VAR_EXCLUDED_PATHS] = array(
    '#type' => 'textarea',
    '#title' => t('Breadcrumb paths to be excluded:'),
    '#description' => t('Enter paths or simple regular expressions. Place one on each line. Example: <em>report</em> or <em>report/2[0-9][0-9][0-9].</em>'),
    '#default_value' => $excluded_paths,
  );

  $form = array();

  // Inserts the fieldset for grouping general settings.
  $form[EasyBreadcrumbConstants::MODULE_NAME] = $fieldset_general;

  // Fieldset for grouping text settings.
  $form['text'] = array(
    '#type' => 'fieldset',
    '#title' => t('Breadcrumb text settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['text'][EasyBreadcrumbConstants::DB_VAR_HTML_TAGS] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow HTML tags in breadcrumb text.'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_HTML_TAGS, TRUE),
  );

  $form['text'][EasyBreadcrumbConstants::DB_VAR_TITLE_FROM_PAGE_WHEN_AVAILABLE] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the page title (when available) instead of the text from the URL.'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_TITLE_FROM_PAGE_WHEN_AVAILABLE, TRUE),
  );

  $form['text'][EasyBreadcrumbConstants::DB_VAR_SEGMENT_TEXT_AS_TITLE] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the text from the URL instead of the page title.'),
    '#description' => t("This setting is usefull for views page displays with contextual filters."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_SEGMENT_TEXT_AS_TITLE, FALSE),
  );

  $form['text'][EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_MODE] = array(
    '#type' => 'checkbox',
    '#title' => t('Limit the breadcrumb text to a maximum number of characters.'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_MODE, FALSE),
  );

  $form['text'][EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_LENGTH] = array(
    '#type' => 'textfield',
    '#title' => t('Breadcrumb character Limit'),
    '#description' => t('Breaks at word boundaries. Example: When set to 10, <em>Long page title</em> will be <em>Long page...</em>'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_LENGTH, 20),
    '#attributes' => array('placeholder' => '20'),
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_MODE . '"]' => array('checked' => TRUE),
      ),
      'invisible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_MODE . '"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['text'][EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_DOTS] = array(
    '#type' => 'checkbox',
    '#title' => t('Add an elipsis (...) to shortened titles.'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_DOTS, TRUE),
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_MODE . '"]' => array('checked' => TRUE),
      ),
      'invisible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_TRUNCATOR_MODE . '"]' => array('checked' => FALSE),
      ),
    ),
  );

  $replaced_titles = variable_get(EasyBreadcrumbConstants::DB_VAR_REPLACED_TITLES);
  $form['text'][EasyBreadcrumbConstants::DB_VAR_REPLACED_TITLES] = array(
    '#type' => 'textarea',
    '#title' => t('Breadcrumb text to be replaced'),
    '#description' => t('Enter current breadcrumb and replacement text seperated by two colons (::). Place one breadcrumb on each line.'),
    '#attributes' => array('placeholder' => 'Administration::Admin'),
    '#default_value' => $replaced_titles,
  );

  // Fieldset for grouping capitalization settings.
  $form['caps'] = array(
    '#type' => 'fieldset',
    '#title' => t('Capitalization'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['caps'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE] = array(
    '#type' => 'select',
    '#title' => t('Breadcrumb capitalization'),
    '#options' => array(
      'none' => t('None'),
      'ucfirst' => t('Only capitalize the first letter'),
      'ucwords' => t('Capitalize the first letter of each word'),
      'ucall' => t('Capitalize all the letters'),
      'ucforce' => t('Only capitalize all the letters in the words defined below'),
    ),
    '#description' => t("Example: 'blog/once-upon-a-time' -> 'Home » Blog » Once upon a time'."),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE, 'ucwords'),
  );

  // Formats the ignored-words array as space separated list of words
  // (word1 word2 wordN) before displaying them.
  $capitalizator_ignored_words_arr = variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_IGNORED_WORDS,
    EasyBreadcrumbConstants::defaultIgnoredWords());
  $capitalizator_ignored_words = @implode(' ', $capitalizator_ignored_words_arr);

  $form['caps'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_IGNORED_WORDS] = array(
    '#type' => 'textfield',
    '#size' => '180',
    '#title' => t('Words that should not be capitalized'),
    '#description' => t('Separate each word with a space. Note: The first word of each breadcrumb will always be capitalized.'),
    '#default_value' => $capitalizator_ignored_words,
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('value' => 'ucwords'),
      ),
      'invisible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('!value' => 'ucwords'),
      ),
    ),
  );

  // Formats the forced-words array as space separated list of words
  // (word1 word2 wordN) before displaying them.
  $capitalizator_forced_words_arr = variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS, '');
  $capitalizator_forced_words = @implode(' ', $capitalizator_forced_words_arr);

  $form['caps'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS] = array(
    '#type' => 'textfield',
    '#size' => '180',
    '#title' => t('Words that should have all letters capitalized'),
    '#description' => t('Separate each word with a space. Useful for capitalizing your organization or brand name.'),
    '#default_value' => $capitalizator_forced_words,
    '#attributes' => array('placeholder' => 'NASA'),
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('value' => 'ucforce'),
      ),
      'invisible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('!value' => 'ucforce'),
      ),
    ),
  );

  $form['caps'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS_CASE_SENSITIVITY] = array(
    '#type' => 'checkbox',
    '#title' => t('Compare case when matching words'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS_CASE_SENSITIVITY, FALSE),
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('value' => 'ucforce'),
      ),
      'invisible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('!value' => 'ucforce'),
      ),
    ),
    '#description' => t('When unchecked, drupal will match both Drupal and drupaL.'),
  );

  $form['caps'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS_FIRST_LETTER] = array(
    '#type' => 'checkbox',
    '#title' => t('Capitalize the first letters of each breadcrumb.'),
    '#default_value' => variable_get(EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS_FIRST_LETTER, TRUE),
    '#states' => array(
      'visible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('value' => 'ucforce'),
      ),
      'invisible' => array(
        ':input[name="' . EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_MODE . '"]' => array('!value' => 'ucforce'),
      ),
    ),
  );

  // Adds buttons for processing the form.
  $form['buttons'] = array(
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save'),
    ),
  );

  // Specifies the callback function for processing the form submission.
  $form['#submit'] = array('_easy_breadcrumb_admin_submit');

  // Specifies the theme for the form.
  $form['#theme'] = 'system_settings_form';

  return $form;
}

/**
 * Process the submitting of the administration form of this module.
 *
 * @param array $form
 *   Renderable form.
 * @param array $form_state
 *   Form state.
 */
function _easy_breadcrumb_admin_submit(array $form, array &$form_state) {

  // Pre-processes the list of ignored words for storing them as an array.
  // Replaces line-endings by spaces and splits words by spaces.
  // E.g.: array('of','and').
  $ignored_words_arr = array();
  $ignored_words = $form_state['values'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_IGNORED_WORDS];
  $ignored_words = preg_replace('/\r*\n+/', ' ', $ignored_words);
  $ignored_words = trim($ignored_words);
  $ignored_words_arr_aux = $ignored_words === '' ? array() : preg_split('/\s+/', $ignored_words);
  foreach ($ignored_words_arr_aux as $word) {
    $ignored_words_arr[$word] = $word;
  }

  $excluded_paths_arr = array();
  $excluded_paths = $form_state['values'][EasyBreadcrumbConstants::DB_VAR_EXCLUDED_PATHS];
  $excluded_paths = trim($excluded_paths);
  $excluded_paths = preg_replace('/\s+/', "\r\n", $excluded_paths);
  $excluded_paths_arr_aux = $excluded_paths === '' ? array() : preg_split('/\r*\n+/', $excluded_paths);
  foreach ($excluded_paths_arr_aux as $path) {
    $path = trim($path, "/");
    $excluded_paths_arr[$path] = $path;
  }

  $forced_words_arr = array();
  $forced_words = $form_state['values'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS];
  $forced_words = preg_replace('/\r*\n+/', ' ', $forced_words);
  $forced_words = trim($forced_words);
  $forced_words_arr_aux = $forced_words === '' ? array() : preg_split('/\s+/', $forced_words);
  foreach ($forced_words_arr_aux as $word) {
    $forced_words_arr[$word] = $word;
  }
  // Updates the $form_state before passing it to the Drupal system.
  $form_state['values'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_IGNORED_WORDS] = $ignored_words_arr;
  $form_state['values'][EasyBreadcrumbConstants::DB_VAR_EXCLUDED_PATHS] = $excluded_paths_arr;
  $form_state['values'][EasyBreadcrumbConstants::DB_VAR_CAPITALIZATOR_FORCED_WORDS] = $forced_words_arr;

  // Delegates persistence to the existing Drupal system.
  system_settings_form_submit($form, $form_state);
}
