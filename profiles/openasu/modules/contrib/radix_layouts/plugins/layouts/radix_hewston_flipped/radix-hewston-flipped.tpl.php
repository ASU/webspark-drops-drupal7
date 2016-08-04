<?php
/**
 * @file
 * Template for Radix Hewston Flipped.
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

<div class="panel-display hewston-flipped clearfix <?php if (!empty($classes)) { print $classes; } ?><?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <section class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-4 hewston-flipped-slider-gutter-area radix-layouts-slidergutter panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['slidergutter']; ?>
          </div>
        </div>
        <div class="col-md-8 hewston-flipped-slider-area radix-layouts-slider panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['slider']; ?>
          </div>
        </div>
      </div>
    </div>
  </section>
  <section class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-4 hewston-flipped-middle-region-1 radix-layouts-column1 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['column1']; ?>
          </div>
        </div>
        <div class="col-md-4 hewston-flipped-middle-region-2 radix-layouts-column2 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['column2']; ?>
          </div>
        </div>
        <div class="col-md-4 hewston-flipped-middle-region-3 radix-layouts-column3 panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['column3']; ?>
          </div>
        </div>
      </div>
    </div>
  </section>
</div><!-- /.hewston-flipped -->
