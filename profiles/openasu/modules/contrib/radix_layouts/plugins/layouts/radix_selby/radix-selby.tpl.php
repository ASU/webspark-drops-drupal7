<?php
/**
 * @file
 * Template for Radix Selby.
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

<div class="panel-display selby clearfix <?php if (!empty($classes)) { print $classes; } ?><?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <section class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD); ?> selby-sidebar-main-area radix-layouts-sidebar panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['sidebar']; ?>
          </div>
        </div>
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD * 2); ?> selby-column-content-region-area panel-panel">
          <div class="row">
            <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FULL); ?> selby-column-content-region-area radix-layouts-contentheader panel-panel">
              <?php print $content['contentheader']; ?>
            </div>
          </div>
          <div class="row">
            <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_HALF); ?> selby-column-content-region-1 radix-layouts-contentcolumn1 panel-panel">
              <?php print $content['contentcolumn1']; ?>
            </div>
            <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_HALF); ?> selby-column-content-region-2 radix-layouts-contentcolumn2 panel-panel">
              <?php print $content['contentcolumn2']; ?>
            </div>
          </div>
          <div class="row">
            <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FULL); ?> selby-content-footer-area radix-layouts-contentfooter panel-panel">
              <?php print $content['contentfooter']; ?>
            </div>
          </div>
        </div><!-- /.selby-content-container -->
      </div><!-- /.selby-content-container row-->
    </div>
  </section>
</div><!-- /.selby -->
