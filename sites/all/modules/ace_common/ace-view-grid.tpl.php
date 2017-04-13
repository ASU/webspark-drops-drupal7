<?php
/**
 * @file ace-view-grid.tpl.php
 * Basic accordion-topped grid style plugin for views.
 *
 * @ingroup views_templates
 */
  $ace_theme = drupal_get_path('theme', 'ace');
  drupal_add_css($ace_theme . '/styles/grid.css');
  drupal_add_js($ace_theme . '/scripts/viewsAjaxAccordion.js', 'module', 'footer');
?>
<script type="text/javascript" src="/sites/all/libraries/jquery.ui/ui/minified/ui.datepicker.min.js?j"></script>

<?php
  foreach (taxonomy_get_vocabularies() as $vocabs) {
    if ($vocabs->name == "Focus Area") {
      $vocab = $vocabs;
      break;
    }
  }
  if (empty($vocab)) {
    watchdog('ace_common', 'ace-view-grid.tpl.php unable to locate taxonomy vocabulary with name "Focus Area".', array(), WATCHDOG_ERROR);
  }

  $accordionNodes = array();
  
  $accordionNodes[] = array(
    'title' => 'All',
    'content' => '',
    'selected' => ($view->exposed_input == null || $view->exposed_input['type'] == 'All'),
    'type' => '',
  );
  
  foreach ($vocab->nodes as $nodeType) {
    $accordionNodes[] = array(
      'title' => ace_labelfy($nodeType, 30),
      'content' => '',
      'selected' => ($view->exposed_input != null && $view->exposed_input['type'] == $nodeType),
      'type' => $nodeType,
    );
  }
?>

<?php print theme('ace_accordion', $accordionNodes, empty($rows)); ?>

<?php print theme('focus_area_menu', $view); ?>

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
