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

  foreach(array_slice($rows, 0, 6) as $index => $row) {
    $node = node_load($row->nid);
    $accordionNodes[] = array(
      'title' => ace_labelfy($node->title),
      'content' => theme('ace_accordion_content', $node),
      'selected' => false,
      'type' => $node->type,
    );
  }
  if (!empty($accordionNodes))
    $accordionNodes[0]['selected'] = true;
?>
<script type="text/javascript" src="/sites/all/libraries/jquery.ui/ui/minified/ui.datepicker.min.js?j"></script>
<script type="text/javascript">
  function isFilterControlledByTab() {
    return false;
  }
</script>

<?php print theme('ace_accordion', $accordionNodes); ?>

<?php print theme('focus_area_menu'); ?>

<div class="grid-panel">
  <?php foreach (array_slice($rows, 6) as $index => $row): ?>
    <?php
      $node = node_load($row->nid);
      print theme('ace_grid_item', $node, (($index % 3) == 2));
    ?>
  <?php endforeach; ?>
</div>
