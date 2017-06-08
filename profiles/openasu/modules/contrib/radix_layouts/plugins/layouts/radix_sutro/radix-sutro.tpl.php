<?php
/**
 * @file
 * Template for Radix Sutro.
 *
 * Patched to support the classes and tags from the old, comparably named
 * Panopoly layouts ported into Kalatheme (and used by Webspark).
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div class="panel-display sutro clearfix <?php if (!empty($classes)) { print $classes; } ?><?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div class="section">
    <div class="container">
      <div class="row row-full">
        <div class="col-md-12 sutro-header-area radix-layouts-header panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['header']; ?>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-6 sutro-column-content-region-1 radix-layouts-column1 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['column1']; ?>
          </div>
        </div>
        <div class="col-md-6 sutro-column-content-region-2 radix-layouts-column2 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['column2']; ?>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div class="section" id="footer">
    <div class="container">
      <div class="row row-full">
        <div class="col-md-12 sutro-footer-area radix-layouts-footer panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['footer']; ?>
          </div>
        </div>
      </div>
    </div>
  </div>
</div><!-- /.sutro -->
