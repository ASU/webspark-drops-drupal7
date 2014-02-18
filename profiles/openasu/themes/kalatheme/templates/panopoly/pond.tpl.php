<?php
/**
 * @file
 * Template for Panopoly Pond.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div class="panel-display pond clearfix <?php !empty($class) ? print $class : ''; ?>" <?php !empty($css_id) ? print "id=\"$css_id\"" : ''; ?>>
  <section class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FULL); ?> pond-header-area">
          <?php print $content['header']; ?>
        </div>
      </div>
    </div>
  </section>
  <section class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD, 3); ?> pond-column-content-region-1">
          <?php print $content['column1']; ?>
        </div>
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD, 3); ?> pond-column-content-region-2">
          <?php print $content['column2']; ?>
        </div>
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD, 3); ?> pond-column-content-region-3">
          <?php print $content['column3']; ?>
        </div>
      </div>
    </div>
  </section>
  <section class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD, 3); ?> pond-secondary-column-content-region-1">
          <?php print $content['secondarycolumn1']; ?>
        </div>
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD, 3); ?> pond-secondary-column-content-region-2">
          <?php print $content['secondarycolumn2']; ?>
        </div>
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD, 3); ?> pond-secondary-column-content-region-3">
          <?php print $content['secondarycolumn3']; ?>
        </div>
      </div>
    </div>
  </section>
  <footer class="section" id="footer">
    <div class="container">
      <div class="row">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FULL); ?> pond-footer-area">
          <?php print $content['footer']; ?>
        </div>
      </div>
    </div>
  </footer>
</div><!-- /.pond -->
