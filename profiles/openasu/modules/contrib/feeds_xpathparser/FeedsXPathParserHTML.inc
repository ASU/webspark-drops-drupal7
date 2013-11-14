<?php

/**
 * @files
 * Provides the FeedsXPathParserHTML class.
 */
class FeedsXPathParserHTML extends FeedsXPathParserBase {

  protected $hasSaveHTML = FALSE;

  /**
   * Overrides parent::__construct().
   */
  public function __construct($id) {
    parent::__construct($id);

    // DOMDocument::saveHTML() cannot take $node as an argument prior to 5.3.6.
    if (version_compare(phpversion(), '5.3.6', '>=')) {
      $this->hasSaveHTML = TRUE;
    }
  }

  /**
   * Implements FeedsXPathParserBase::setup().
   */
  protected function setup($source_config, FeedsFetcherResult $fetcher_result) {

    if (!empty($source_config['exp']['tidy'])) {
      $config = array(
        'merge-divs'       => FALSE,
        'merge-spans'      => FALSE,
        'join-styles'      => FALSE,
        'drop-empty-paras' => FALSE,
        'wrap'             => 0,
        'tidy-mark'        => FALSE,
        'escape-cdata'     => TRUE,
        'word-2000'        => TRUE,
      );
      // Default tidy encoding is UTF8.
      $encoding = $source_config['exp']['tidy_encoding'];
      $raw = tidy_repair_string(trim($fetcher_result->getRaw()), $config, $encoding);
    }
    else {
      $raw = $fetcher_result->getRaw();
    }
    $doc = new DOMDocument();
    // Use our own error handling.
    $use = $this->errorStart();
    $success = $doc->loadHTML($raw);
    unset($raw);
    $this->errorStop($use, $source_config['exp']['errors']);
    if (!$success) {
      throw new Exception(t('There was an error parsing the HTML document.'));
    }
    return $doc;
  }

  protected function getRaw(DOMNode $node) {
    if ($this->hasSaveHTML) {
      return $this->doc->saveHTML($node);
    }

    return $this->doc->saveXML($node, LIBXML_NOEMPTYTAG);
  }
}
