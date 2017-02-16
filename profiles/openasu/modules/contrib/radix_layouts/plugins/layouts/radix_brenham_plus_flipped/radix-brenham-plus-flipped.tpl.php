<?php
/**
 * @file
 * Template for Radix Brenham Plus Flipped.
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

<div class="panel-display brenham-plus-flipped clearfix <?php if (!empty($classes)) { print $classes; } ?><?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div class="section alt" id="promo">
    <div class="container">
      <div class="row row-full">
        <div class="col-md-12 brenham-plus-flipped-promo radix-layouts-header panel-panel">
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

        <div class="col-md-8 brenham-plus-flipped-column-content-region-area">
          <div class="col-md-12 brenham-plus-flipped-main-contenttop radix-layouts-contenttop panel-panel">
            <div class="panel-panel-inner">
              <?php print $content['contenttop']; ?>
            </div>
          </div>

          <div class="col-md-12 brenham-plus-flipped-main-contentmain radix-layouts-contentmain panel-panel">
            <div class="panel-panel-inner">
              <?php print $content['contentmain']; ?>
            </div>
          </div>

          <div class="col-md-12 brenham-plus-flipped-main-contentbottom radix-layouts-contentbottom panel-panel">
            <div class="panel-panel-inner">
              <?php print $content['contentbottom']; ?>
            </div>
          </div>
        </div>
        
        <div class="col-md-4 brenham-plus-flipped-main-side radix-layouts-sidebar panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['sidebar']; ?>
          </div>
        </div>
        
      </div>
    </div>
  </div>
</div><!-- /.brenham-plus-flipped -->