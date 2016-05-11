<?php
/**
 * @file
 * Template for Radix Rolph.
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

<div class="panel-display rolph clearfix <?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <section class="section alt" id="promo">
    <div class="container">
      <div class="row row-full">
        <div class="col-md-12 rolph-header-area radix-layouts-header panel-panel">
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
        <div class="col-md-3 rolph-column-content-region-1 radix-layouts-quarter1 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['quarter1']; ?>
          </div>
        </div>
        <div class="col-md-3 rolph-column-content-region-2 radix-layouts-quarter2 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['quarter2']; ?>
          </div>
        </div>
        <div class="col-md-3 rolph-column-content-region-3 radix-layouts-quarter3 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['quarter3']; ?>
          </div>
        </div>
        <div class="col-md-3 rolph-column-content-region-4 radix-layouts-quarter4 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['quarter4']; ?>
          </div>
        </div>
      </div>
    </div>
  </section>
   <footer class="section" id="footer">
    <div class="container">
      <div class="row row-full">
        <div class="col-md-12 rolph-footer-area radix-layouts-footer panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['footer']; ?>
          </div>
        </div>
      </div>
    </div>
  </footer>
</div><!-- /.rolph -->
