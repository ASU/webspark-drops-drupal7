<?php
/**
 * @file
 * Template for Radix Taylor Flipped.
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

<div class="panel-display taylor-flipped clearfix <?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
   <section class="section">
    <div class="container">
      <?php if ($content['header']): ?>
        <div class="row row-full">
          <div class="col-md-12 taylor-flipped-header-area radix-layouts-header panel-panel">
            <div class="panel-panel-inner">
              <?php print $content['header']; ?>
            </div>
          </div>
        </div>
      <?php endif; ?>
    </div>
  </section>
  <section class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-3 taylor-flipped-quarter-1-area radix-layouts-quarter1 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['quarter1']; ?>
          </div>
        </div>
        <div class="col-md-3 taylor-flipped-quarter-2-area radix-layouts-quarter2 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['quarter2']; ?>
          </div>
        </div>
        <div class="col-md-6 taylor-flipped-half-area radix-layouts-half panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['half']; ?>
          </div>
        </div>
      </div>
    </div>
  </section>
  <?php if ($content['footer']): ?>
  <footer class="section" id="footer">
    <div class="container">
      <div class="row row-full">
        <div class="col-md-12 taylor-flipped-footer-area radix-layouts-footer panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['footer']; ?>
          </div>
        </div>
      </div>
    </div>
  </footer>
  <?php endif; ?>
</div><!-- /.taylor -->
