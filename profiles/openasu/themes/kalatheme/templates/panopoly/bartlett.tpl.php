<?php
/**
 * @file
 * Template for Panopoly Bartlett.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div class="panel-display bartlett clearfix <?php !empty($class) ? print $class : ''; ?>" <?php !empty($css_id) ? print "id=\"$css_id\"" : ''; ?>>
  <section class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FULL); ?> bartlett-everything">
          <div class="row">
            <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD); ?> bartlett-side">
              <?php print $content['sidebar']; ?>
            </div>
            <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_THIRD * 2); ?> bartlett-main">
              <div class="row">
                <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_FULL); ?> bartlett-main-header">
                  <?php print $content['contentheader']; ?>
                </div>
              </div>
              <div class="row">
                <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_HALF); ?> bartlett-main-col-1">
                  <?php print $content['contentcolumn1']; ?>
                </div>
                <div class="col-md-<?php print kalatheme_grid_size(KALATHEME_GRID_HALF); ?> bartlett-main-col-1">
                  <?php print $content['contentcolumn2']; ?>
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div><!-- /.container -->
  </section><!--  /.section -->
</div><!-- /.bartlett -->
