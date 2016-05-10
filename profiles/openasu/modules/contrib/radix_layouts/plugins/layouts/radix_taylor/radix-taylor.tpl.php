<?php
/**
 * @file
 * Template for Radix Taylor.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 *
 * Patched to support the classes and tags from the old, comparably named Panopoly layout for Webspark.
 *
 * Functions:
 * kalatheme_grid_size (from kalatheme theme) - returns (int) Number of Bootstrap columns.
 */
?>

<div class="panel-display taylor clearfix <?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <section class="section">
    <div class="container">
      <div class="row row-full">
				<div class="col-md-12 radix-layouts-header panel-panel col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FULL); ?> taylor-header-area">
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
				<div class="col-md-6 radix-layouts-half panel-panel col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_HALF, 3); ?> taylor-half-area">
					<div class="panel-panel-inner">
						<?php print $content['half']; ?>
					</div>
				</div>
				<div class="col-md-3 radix-layouts-quarter1 panel-panel col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FOURTH, 3); ?> taylor-quarter-1-area">
					<div class="panel-panel-inner">
						<?php print $content['quarter1']; ?>
					</div>
				</div>
				<div class="col-md-3 radix-layouts-quarter2 panel-panel col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FOURTH, 3); ?> taylor-quarter-2-area">
					<div class="panel-panel-inner">
						<?php print $content['quarter2']; ?>
					</div>
				</div>
      </div>
    </div>
  </section>
    
  <footer class="section" id="footer">
    <div class="container">
      <div class="row row-full">
				<div class="col-md-12 radix-layouts-footer panel-panel col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FULL); ?> taylor-footer-area">
					<div class="panel-panel-inner">
						<?php print $content['footer']; ?>
					</div>
				</div>
      </div>
    </div>
  </footer>

</div><!-- /.taylor -->
