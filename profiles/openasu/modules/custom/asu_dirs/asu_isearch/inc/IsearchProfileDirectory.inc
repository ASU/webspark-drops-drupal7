<?php

/**
 * IsearchProfileDirectory
 *
 * This class creates and renders a directory from a set of
 * configuration options as an effort to refactor the current
 * working code.
 */
class IsearchProfileDirectory {
  private $instanceId = NULL;
  private $directoryListView;
  private $directoryGridView;
  private $exposedFilters;
  private $contextualFilters;
  private $sortingOptions;
  private $view = NULL;
  private $viewConfig = NULL;

  private static $currentInstance = 1;

  public function __construct() {
    $this->view = views_get_view('isearch_directory', TRUE);

    $this->instanceId = self::$currentInstance++;
    $this->view->isearch_instance_id = $this->instanceId;
  }

  public function setViewConfig($view_config) {
    $this->viewConfig = $view_config;
  }

  public function render() {

  }

  public function renderIndex() {

    /*
    $display_id = 'isearch_a_z';
    $this->view->set_display($display_id);
    $this->view->init_display(TRUE);
    $this->view->init_handlers(TRUE);

    $this->view->display_handler->handlers['argument']['field_isearch_lastname_value']->options['summary']['format'] = 'unformatted_summary';
    $this->view->display_handler->handlers['argument']['field_isearch_lastname_value']->options['summary_options']['count'] = 0;
    $this->view->display_handler->handlers['argument']['field_isearch_lastname_value']->options['summary_options']['inline'] = 1;
    $this->view->display_handler->handlers['argument']['field_isearch_lastname_value']->options['default_action'] = 'summary';

    $contextual_filters = $this->contextualFilters;
    // reset to null to show the entire index
    $contextual_filters[0] = NULL;
    $this->view->set_arguments($contextual_filters);


    if (isset($this->viewConfig->filter_title)) {
      if ($this->viewConfig->filter_title == '') {
        $this->viewConfig->filter_title = '.*';
      }
      $this->view->filter['field_isearch_affil_title_value_1']->value = $this->viewConfig->filter_title;
    }

    $this->view->pre_execute();
    $this->view->execute();

    $lastname = $result->field_data_field_isearch_lastname_field_isearch_lastname_val;

    $items = array();*/


    /*
    foreach ($this->view->result as $key => $result) {

      $items[] = t('<a href="@url">@letter</a>', array(
        '@url' => url(current_path(), array(
          'query' => array(
            'isrch_index' => $index_letter,
            'isrch_id' => $this->instanceId,
          ),
        )),
        '@letter' => $index_letter,
      ));
    }

    return theme_item_list(array(
      'items' => $items,
      'title' => '',
      'type' => 'ul',
      'attributes' => array(
        'class' => 'isearch-a-z-index',
      ),
    ));*/

    return "<div id=\"asu-isearch-alpha-bar\">
              <div class=\"asu-isearch-alpha-bar row\">
            <ul class=\"alphabet\">
              <li>A</li>
              <li>B</li>
              <li>C</li>
              <li>D</li>
              <li>E</li>
              <li>F</li>
              <li>G</li>
              <li>H</li>
              <li>I</li>
              <li>J</li>
              <li>K</li>
              <li>L</li>
              <li>M</li>
              <li>N</li>
              <li>O</li>
              <li>P</li>
              <li>Q</li>
              <li>R</li>
              <li>S</li>
              <li>T</li>
              <li>U</li>
              <li>V</li>
              <li>W</li>
              <li>X</li>
              <li>Y</li>
              <li>Z</li>
              <li>ALL</li>
            </ul>
          </div></div>";
  }

  public function getInstanceId() {
    return $this->instanceId;
  }

  public function getTitleOptions() {
    $options = array();

    $display_id = 'isearch_directory_titles';

    if (isset($this->view->display[$display_id])) {

      $contextual_filters = $this->contextualFilters;
      $contextual_filters[0] = 'all';

      $view = views_get_view('isearch_directory', TRUE);
      $view->set_display($display_id);
      $view->init_handlers();
      $view->set_arguments($contextual_filters);

      $view->execute();

      foreach ($view->result as $item) {
        if (isset($item->field_field_isearch_affil_title)) {
          $title = $item->field_field_isearch_affil_title[0]['raw']['value'];
          $options[$title] = $title;
        }
      }
    }

    return $options;
  }

  public function setIndexView() {

  }

  public function setDirectoryListView() {

  }

  public function setDirectoryGridView() {

  }

  public function setContextualFilters($filters) {
    $this->contextualFilters = $filters;
  }

  public function setExposedFilters($filters) {
    $this->exposedFilters = $filters;
  }

  public function setSortingOptions() {

  }
}
