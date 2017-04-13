<?php
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
  $ace_theme = drupal_get_path('theme', 'ace');
  drupal_add_css($ace_theme . '/styles/grid.css');
  drupal_add_js($ace_theme . '/scripts/viewsAjaxAccordion.js', 'module', 'footer');
  
  $sqlParamForChild = $variables['view']->argument['type']->options['wildcard'];
  $resultTask = db_query("select title, nid from node where status = 1 and type = '".$sqlParamForChild."'");
  
  $accordionNodes = array(
    array(
      'title' => 'All',
      'value' => 'All',
      'content' => '',
      'selected' => ($view->exposed_input == null || $view->exposed_input['filter_id'] == 'All'),
      'type' => 'all',
    ),
  );
  
  while ($row = db_fetch_object($resultTask)) {
    $node = node_load($row->nid);
    $accordionNodes[] = array(
      'title' => ace_labelfy($node->title, 30),
      'value' => $node->nid,
      'content' => '',
      'selected' => ($view->exposed_input != null && $view->exposed_input['filter_id'] == $node->nid),
      'type' => $node->type,
    );
  }
?>
<style type="text/css">
  .views-widget-filter-field_taskforce_nid {
  	display: none;
  }
</style>
<script type="text/javascript" src="/sites/all/libraries/jquery.ui/ui/minified/ui.datepicker.min.js?j"></script>
<script type="text/javascript">
  function getAccordionFilterId() {
    return '#edit-filter-id';
  }
</script>

<?php print theme('ace_accordion', $accordionNodes, empty($rows)); ?>

<?php print theme('focus_area_menu'); ?>

<div class="grid-panel">
  <?php foreach ($rows as $index => $row): ?>
    <?php $node = node_load($row->nid); ?>
    <?php if ($index == 0): ?>
      <div id="mainContentNode" style="display: none;">
        <?php print theme('ace_accordion_content', $node); ?>
      </div>
    <?php else: ?>
      <?php print theme('ace_grid_item', $node, (($index % 3) == 0)); ?>
    <?php endif; ?>
  <?php endforeach; ?>
</div>
