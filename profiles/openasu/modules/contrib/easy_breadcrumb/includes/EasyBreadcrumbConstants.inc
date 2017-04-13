<?php
/**
 * @file
 * Module's contants.
 */

/**
 * EasyBreadcrumb module's contants
 */
class EasyBreadcrumbConstants {

  /**
   * Module's name.
   */
  const MODULE_NAME = 'easy_breadcrumb';

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
   *  Separator between segments.
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
   * Use the page's title when it is available instead of always trying to
   * deduce it from the URL.
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
