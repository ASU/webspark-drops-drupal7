<?php

/**
 * @file
 * Home of the FeedsCrawler.
 */

/**
 * Fetches data via HTTP.
 */
class FeedsCrawler extends FeedsHTTPFetcher {

  /**
   * Implements FeedsFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    $config = $source_config['crawler'];

    if ($this->config['use_pubsubhubbub'] && ($raw = $this->subscriber($source->feed_nid)->receive())) {
      return new FeedsFetcherResult($raw);
    }
    $state = $source->state(FEEDS_FETCH);
    if ($state->total == 0) {
      $state->total = ($config['num_pages'] == 0) ? 100000 : $config['num_pages'];
      $state->count = $state->total;
      $url = $source_config['source'];
    }
    else {
      $url = $state->next_url;
    }
    $result = new FeedsHTTPFetcherResult($url);

    if ($config['first_run'] && $source->config['FeedsCrawler']['crawled']) {
      $state->progress($state->total, $state->total);
      return $result;
    }
    sleep($config['delay']);
    if (($config['auto'] && ($href = $this->parseAuto($result, $source_config)) != FALSE) ||
        ($config['url']['url_pattern'] && ($href = $this->parseUrl($config, $state)) != FALSE) ||
        ($config['xpath'] && ($href = $this->parseXPath($result, $source_config)) != FALSE)) {
      $state->next_url = $href;
      $state->count--;
      $state->progress($state->total, $state->total - $state->count);
      if ($state->count <= 0) {
        $source->config['FeedsCrawler']['crawled'] = TRUE;
      }
    }
    else {
      $state->progress($state->total, $state->total);
    }
    return $result;
  }

  /**
   * Increments a pager using a URL pattern.
   */
  protected function parseUrl($config, $state) {
    if (!isset($state->inc)) {
      $state->inc = $config['url']['initial'];
    }
    else {
      $state->inc += $config['url']['increment'];
    }
    return str_replace('$index', $state->inc, $config['url']['url_pattern']);
  }

  /**
   * Paginates using Atom's rel=next link automatically.
   */
  protected function parseAuto($result, $source_config) {
    $errors = $this->errorStart();

    $xml = new SimpleXMLElement($result->getRaw());
    feeds_include_library('common_syndication_parser.inc', 'common_syndication_parser');
    $format = _parser_common_syndication_feed_format_detect($xml);
    if ($format) {
      $xml->registerXpathNamespace('atom', 'http://www.w3.org/2005/Atom');
      $xpath = 'atom:link[@rel="next"]/@href';
    }
    else {
      $xpath = 'link[@rel="next"]/@href';
    }
    $href = $xml->xpath($xpath);
    unset($xml);

    $this->errorStop($errors, FALSE);

    return $this->parseHref($href, $source_config['source']);
  }

  /**
   * Finds the "next" link on a page via XPath.
   */
  protected function parseXPath($result, $source_config) {
    $errors = $this->errorStart();

    $dom = new DOMDocument();
    $dom->loadHTML($result->getRaw());
    $xml = simplexml_import_dom($dom);
    unset($dom);
    $href = $xml->xpath($source_config['crawler']['xpath']);
    unset($xml);

    $this->errorStop($errors, FALSE);
    return $this->parseHref($href, $source_config['source']);
  }

  /**
   * Builds a fully qualified URL from the source URL if necessary.
   */
  protected function parseHref($href, $source_url) {
    if ($href === FALSE || empty($href)) {
      return FALSE;
    }
    foreach ($href as $h) {
      $h = trim((string) $h);
      if (!empty($h)) {
        $href = $h;
        break;
      }
    }
    if (strpos($href, 'http://') !== 0 && strpos($href, 'https://') !== 0) {
      if (substr($href, 0, 1) == '/') {
        $href = ltrim($href, '/');
        $href = $this->baseUrl($source_url) . '/' . $href;
      }
      else {
        $href = $this->baseUrl($source_url, TRUE) . '/' . $href;
      }
    }
    return $href;
  }

  /**
   * Breaks a url up removing everything but the http://example.com.
   *
   * @param string $url
   *   The url string to return the base path for.
   * @param bool $relative
   *   (Optional) If TRUE, returns the base path as well fir relative urls.
   *   Defaults to FALSE.
   */
  protected function baseUrl($url, $relative = FALSE) {
    $p = parse_url($url);
    $output = '';
    $output .= isset($p['scheme']) ? $p['scheme'] : 'http';
    $output .= '://';
    $output .= isset($p['user']) ? $p['user'] : '';
    $output .= isset($p['pass']) ? ':' . $p['pass'] : '';
    $output .= isset($p['user']) ? '@' : '';
    $output .= $p['host'];
    $output .= isset($p['port']) ? ':' . $p['port'] : '';

    if ($relative) {
      $output .= isset($p['path']) ? substr($p['path'], 0, strrpos($p['path'], '/')) : '';
    }

    return $output;
  }

  /**
   * Overrides parent::sourceDefaults().
   */
  public function sourceDefaults() {
    return $this->config;
  }

  /**
   * Overrides parent::sourceForm().
   */
  public function sourceForm($source_config) {
    $form = parent::sourceForm($source_config);
    $form['crawler'] = array(
      '#type' => 'fieldset',
      '#title' => t('Feeds Crawler settings'),
      '#collapsed' => TRUE,
      '#collapsible' => TRUE,
      '#tree' => TRUE,
    );
    $form['crawler']['num_pages'] = array(
      '#type' => 'textfield',
      '#title' => t('Number of pages'),
      '#description' => t('The number of pages to fetch. 0 for unlimited'),
      '#default_value' => isset($source_config['crawler']['num_pages']) ? $source_config['crawler']['num_pages'] : 10,
      '#maxlength' => 10,
    );
    $form['crawler']['delay'] = array(
      '#type' => 'textfield',
      '#title' => t('Delay'),
      '#description' => t('Number of seconds to delay in between fetches.'),
      '#default_value' => isset($source_config['crawler']['delay']) ? $source_config['crawler']['delay'] : 1,
    );
    $form['crawler']['first_run'] = array(
      '#type' => 'checkbox',
      '#title' => t('Crawl on first run only'),
      '#description' => t('Only crawl on initial run. Use regular import afterword.'),
      '#default_value' => isset($source_config['crawler']['first_run']) ? $source_config['crawler']['first_run'] : FALSE,
    );
    $form['crawler']['auto'] = array(
      '#type' => 'checkbox',
      '#title' => t('Auto detect next link'),
      '#description' => t('Attempt to autodetect the next link for RSS and ATOM feeds.'),
      '#default_value' => isset($source_config['crawler']['auto']) ? $source_config['crawler']['auto'] : FALSE,
    );
    $form['crawler']['xpath'] = array(
      '#type' => 'textfield',
      '#title' => t('XPath selector for next link'),
      '#description' => t('The XPath selector for the next link.'),
      '#default_value' => isset($source_config['crawler']['xpath']) ? $source_config['crawler']['xpath'] : '',
      '#maxlength' => NULL,
    );
    $form['crawler']['url'] = array(
      '#type' => 'fieldset',
      '#title' => t('URL replacement options'),
    );
    $form['crawler']['url']['url_pattern'] = array(
      '#type' => 'textfield',
      '#title' => t('URL pattern'),
      '#description' => t('A URL with the variable $index replaced with an increnting number. For example: http://example.com?page=$index.'),
      '#default_value' => isset($source_config['crawler']['url']['url_pattern']) ? $source_config['crawler']['url']['url_pattern'] : '',
      '#maxlength' => NULL,
    );
    $form['crawler']['url']['initial'] = array(
      '#type' => 'textfield',
      '#title' => t('Initial value of $index'),
      '#description' => t('The initial value of the $index variable.'),
      '#default_value' => isset($source_config['crawler']['url']['initial']) ? $source_config['crawler']['url']['initial'] : '',
    );
    $form['crawler']['url']['increment'] = array(
      '#type' => 'textfield',
      '#title' => t('Increment $index by'),
      '#description' => t('The increment the value of $index variable.'),
      '#default_value' => isset($source_config['crawler']['url']['increment']) ? $source_config['crawler']['url']['increment'] : '',
    );
    $form['crawled'] = array(
      '#type' => 'hidden',
      '#value' => isset($source_config['crawled']) ? $source_config['crawled'] : FALSE,
    );
    return $form;
  }

  /**
   * Trims a string by reference.
   *
   * This is a helper method for use in array_walk_recursive().
   */
  public function trim(&$value) {
    $value = trim($value);
  }

  /**
   * Overrides parent::sourceFormValidate().
   */
  public function sourceFormValidate(&$values) {
    $vs = &$values['crawler'];
    array_walk_recursive($vs, array($this, 'trim'));
    if (empty($vs['num_pages'])) {
      $vs['num_pages'] = 0;
    }

    if (empty($vs['delay'])) {
      $vs['delay'] = 0;
    }

    if (!empty($vs['xpath'])) {
      $xml = new SimpleXMLElement('<?xml version="1.0" encoding="UTF-8"?>' . "\n<items></items>");
      $use_errors = libxml_use_internal_errors(TRUE);
      $result = $xml->xpath($vs['xpath']);
      $error = libxml_get_last_error();
      libxml_clear_errors();
      libxml_use_internal_errors($use_errors);
      if ($error) {
        form_set_error('crawler][xpath', t('There was an error with the XPath selector: ') . $error->message);
      }
    }

    if (!empty($vs['url']['url_pattern']) && !(stripos($vs['url']['url_pattern'], 'http://') === 0 || stripos($vs['url']['url_pattern'], 'https://') === 0)) {
      form_set_error('crawler][url][url_pattern', t('The url pattern must be an absolute url. It must start with http:// or https://'));
    }
    if (!empty($vs['num_pages']) && !is_int($vs['num_pages']) && !ctype_digit($vs['num_pages'])) {
      form_set_error('crawler][num_pages', t('Must be an integer.'));
    }
    if (!empty($vs['delay']) && !is_numeric($vs['delay'])) {
      form_set_error('crawler][delay', t('Must be a number.'));
    }
    if (!empty($vs['url']['initial']) && !is_numeric($vs['url']['initial'])) {
      form_set_error('crawler][url][initial', t('Must be a number.'));
    }
    if (!empty($vs['url']['increment']) && !is_numeric($vs['url']['increment'])) {
      form_set_error('crawler][url][increment', t('Must be a number.'));
    }
  }

  /**
   * Overrides parent::configDefaults().
   */
  public function configDefaults() {
    $defaults = parent::configDefaults();
    $defaults['crawler'] = array(
      'num_pages' => 10,
      'first_run' => TRUE,
      'delay' => 1,
      'auto' => FALSE,
      'xpath' => '',
      'url' => array(
        'url_pattern' => '',
        'initial' => 0,
        'increment' => 1,
      ),
    );
    $defaults['crawled'] = FALSE;
    return $defaults;
  }

  /**
   * Overrides parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = $this->sourceForm($this->config);
    unset($form['source']);
    unset($form['crawled']);
    $form['crawler']['#title'] = t('Feeds Crawler default settings');

    return parent::configForm($form_state) + $form;
  }

  /**
   * Overrides parent::configFormValidate().
   */
  public function configFormValidate(&$values) {
    $this->sourceFormValidate($values);
  }

  /**
   * Starts custom error handling.
   *
   * @return bool
   *   The previous value of use_errors.
   */
  protected function errorStart() {
    return libxml_use_internal_errors(TRUE);
  }

  /**
   * Stops custom error handling.
   *
   * @param bool $use
   *   The previous value of use_errors.
   * @param bool $print
   *   (Optional) Whether to print errors to the screen. Defaults to TRUE.
   */
  protected function errorStop($use, $print = TRUE) {

    if ($print) {

      foreach (libxml_get_errors() as $error) {
        switch ($error->level) {
          case LIBXML_ERR_WARNING:
          case LIBXML_ERR_ERROR:
            $type = 'warning';
            break;

          case LIBXML_ERR_FATAL:
            $type = 'error';
            break;

        }

        $args = array(
          '%error' => trim($error->message),
          '%num' => $error->line,
          '%code' => $error->code,
        );
        $message = t('%error on line %num. Error code: %code', $args);
        drupal_set_message($message, $type, FALSE);
      }
    }

    libxml_clear_errors();
    libxml_use_internal_errors($use);
  }

}
