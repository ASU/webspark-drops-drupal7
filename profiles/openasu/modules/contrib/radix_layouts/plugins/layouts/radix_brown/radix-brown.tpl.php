<?php
/**
 * @file
 * Template for Radix Brown.
 * 
 * Patched to support the classes and tags from the old, comparably named Panopoly layout for Webspark.
 *
 * Functions:
 * kalatheme_grid_size (from kalatheme theme) - returns (int) Number of Bootstrap columns.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div class="panel-display brown clearfix <?php if (!empty($classes)) { print $classes; } ?><?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <section class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD * 2); ?> brown-header-2 radix-layouts-slider panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['slider']; ?>
          </div>
        </div>
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD); ?> brown-header-1 radix-layouts-slidergutter panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['slidergutter']; ?>
          </div>
        </div>
      </div>
    </div>
  </section>
  <section class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD, 3); ?> brown-middle-region-1 radix-layouts-column1 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['column1']; ?>
          </div>
        </div>
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD, 3); ?> brown-middle-region-2 radix-layouts-column2 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['column2']; ?>
          </div>
        </div>
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD, 3); ?> brown-middle-region-3 radix-layouts-column3 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['column3']; ?>
          </div>
        </div>
      </div>
    </div>
  </section>
  <footer class="section" id="footer">
    <div class="container">
      <div class="row">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD, 3); ?> brown-footer-region1 radix-layouts-footercolumn1 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['footercolumn1']; ?>
          </div>
        </div>
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD, 3); ?> brown-footer-region2 radix-layouts-footercolumn2 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['footercolumn2']; ?>
          </div>
        </div>
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD, 3); ?> brown-footer-region3 radix-layouts-footercolumn3 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['footercolumn3']; ?>
          </div>
        </div>
      </div>
    </div>
  </footer>
</div><!-- /.brown -->
