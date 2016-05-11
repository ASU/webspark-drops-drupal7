<?php
/**
 * @file
 * Template for Radix Sutro Double.
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

<div class="panel-display sutro-double clearfix <?php if (!empty($classes)) { print $classes; } ?><?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <section class="section">
    <div class="container">
      <div class="row row-full">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FULL); ?> sutro-double-header-area radix-layouts-header panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['header']; ?>
          </div>
        </div>
      </div>
    </div>
  </section>
  <section class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_HALF); ?> sutro-double-column-content-region-1 radix-layouts-column1 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['column1']; ?>
          </div>
        </div>
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_HALF); ?> sutro-double-column-content-region-2 radix-layouts-column2 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['column2']; ?>
          </div>
        </div>
      </div>
      <div class="row row-full">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FULL); ?> sutro-double-middle-area radix-layouts-middle panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['middle']; ?>
          </div>
        </div>
      </div>
      <div class="row">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_HALF); ?> sutro-double-column-content-region-3 radix-layouts-secondcolumn1 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['secondcolumn1']; ?>
          </div>
        </div>
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_HALF); ?> sutro-double-column-content-region-4 radix-layouts-secondcolumn2 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['secondcolumn2']; ?>
          </div>
        </div>
      </div>
    </div>
  </section>
  <footer class="section" id="footer">
    <div class="container">
      <div class="row row-full">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FULL); ?> sutro-double-footer-area radix-layouts-footer panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['footer']; ?>
          </div>
        </div>
      </div>
    </div>
  </footer>
</div><!-- /.sutro-double -->
