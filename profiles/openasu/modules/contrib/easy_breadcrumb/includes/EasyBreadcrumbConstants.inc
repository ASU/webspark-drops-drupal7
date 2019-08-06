<?php

/**
 * @file
 * Module's contants.
 */

/**
 * EasyBreadcrumb module's contants.
 */
class EasyBreadcrumbConstants {

  /**
   * Module's name.
   */
  const MODULE_NAME = 'easy_breadcrumb';

  /**
   * Flag for disabling or not the default admin theme breadcrumb.
   */
  const DB_VAR_DISABLE_ADMIN_BREADCRUMB = 'easy_breadcrumb-disable_admin_breadcrumb';

  /**
   * Flag for disabling or not the default Drupal's breadcrumb.
   */
  const DB_VAR_DISABLE_DEFAULT_DRUPAL_BREADCRUMB = 'easy_breadcrumb-disable_drupal_breadcrumb';

  /**
   * Flag for including invalid paths while generating the breadcrumb segments.
   */
  const DB_VAR_INCLUDE_INVALID_PATHS = 'easy_breadcrumb-include_invalid_paths';

  /**
   * List of paths to be excluded from the generated segments.
   */
  const DB_VAR_EXCLUDED_PATHS = 'easy_breadcrumb-excluded_paths';

  /**
   * List of titles to be replaced.
   */
  const DB_VAR_REPLACED_TITLES = 'easy_breadcrumb-replaced_titles';

  /**
   * Separator between segments.
   */
  const DB_VAR_SEGMENTS_SEPARATOR = 'easy_breadcrumb-segments_separator';

  /**
   * Flag for including or not the front page as a segment.
   */
  const DB_VAR_INCLUDE_HOME_SEGMENT = 'easy_breadcrumb-include_home_segment';

  /**
   * Title for the front page segment.
   */
  const DB_VAR_HOME_SEGMENT_TITLE = 'easy_breadcrumb-home_segment_title';

  /**
   * Flag for including or not the page's title as a segment.
   */
  const DB_VAR_INCLUDE_TITLE_SEGMENT = 'easy_breadcrumb-include_title_segment';

  /**
   * Flag for printing the page's title as a link, or printing it as a text.
   */
  const DB_VAR_TITLE_SEGMENT_AS_LINK = 'easy_breadcrumb-title_segment_as_link';

  /**
   * Use the page's title when it is available.
   *
   * Instead of always trying to deduce it from the URL.
   */
  const DB_VAR_TITLE_FROM_PAGE_WHEN_AVAILABLE = 'easy_breadcrumb-title_from_page_when_available';

  /**
   * Transformation mode to apply to the segments.
   */
  const DB_VAR_CAPITALIZATOR_MODE = 'easy_breadcrumb-capitalizator_mode';

  /**
   * List of words to be ignored by the 'capitalizator'. E.g.: of and.
   */
  const DB_VAR_CAPITALIZATOR_IGNORED_WORDS = 'easy_breadcrumb-capitalizator_ignored_words';

  /**
   * List of words to be forced by the 'capitalizator'. E.g.: your brand's name.
   */
  const DB_VAR_CAPITALIZATOR_FORCED_WORDS = 'easy_breadcrumb-capitalizator_forced_words';

  /**
   * List of words to be forced by the 'capitalizator'. E.g.: your brand's name.
   */
  const DB_VAR_CAPITALIZATOR_FORCED_WORDS_FIRST_LETTER = 'easy_breadcrumb-capitalizator_forced_words_first_letter';

  /**
   * Logical value to 'Make the first letters of each segment capitalized'.
   */
  const DB_VAR_CAPITALIZATOR_FORCED_WORDS_CASE_SENSITIVITY = 'easy_breadcrumb-capitalizator_forced_words_case_sensitivity';

  /**
   * Flag for printing the page's title as a link, or printing it as a text.
   */
  const DB_VAR_SEPERATOR_ENDING = 'easy_breadcrumb-seperator_ending';

  /**
   * Use the segment text as the title instead of main page title.
   */
  const DB_VAR_SEGMENT_TEXT_AS_TITLE = 'easy_breadcrumb-segment_text_as_title';

  /**
   * Transformation mode for crumbs without HTML tags.
   */
  const DB_VAR_HTML_TAGS = 'easy_breadcrumb-html_tags';

  /**
   * Variables for truncator.
   */
  const DB_VAR_TRUNCATOR_MODE = 'easy_breadcrumb_truncator_mode';
  const DB_VAR_TRUNCATOR_LENGTH = 'easy_breadcrumb_truncator_length';
  const DB_VAR_TRUNCATOR_DOTS = 'easy_breadcrumb_truncator_dots';

  /**
   * Default list of excluded paths.
   *
   * @return array
   *   Default list of ignored paths.
   */
  public static function defaultExcludedPaths() {
    static $default_excluded_paths = array(
      'search',
      'search/node',
    );
    return $default_excluded_paths;
  }

  /**
   * Default list of ignored words.
   *
   * @return array
   *   Default list of ignored words.
   */
  public static function defaultIgnoredWords() {
    static $default_ignored_words = array(
      'of',
      'and',
      'or',
      'de',
      'del',
      'y',
      'o',
    );
    return $default_ignored_words;
  }

}
