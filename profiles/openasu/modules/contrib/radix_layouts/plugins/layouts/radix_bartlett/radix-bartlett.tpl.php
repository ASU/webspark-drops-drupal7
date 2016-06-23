<?php
/**
 * @file
 * Template for Radix Bartlett.
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

<div class="panel-display bartlett clearfix <?php if (!empty($classes)) { print $classes; } ?><?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <section class="section">
    <div class="container">
      <div class="row">
        <div class="col-md-4 bartlett-side radix-layouts-sidebar panel-panel">
          <div class="panel-panel-inner">
            <?php print $content['sidebar']; ?>
          </div>
        </div>
        <div class="col-md-8 bartlett-main panel-panel">
          <div class="row">
            <div class="col-md-12 bartlett-main-header radix-layouts-contentheader panel-panel">
              <div class="panel-panel-inner">
                <?php print $content['contentheader']; ?>
              </div>
            </div>
          </div>
          <div class="row">
            <div class="col-md-6 bartlett-main-col-1 radix-layouts-contentcolumn1 panel-panel">
              <div class="panel-panel-inner">
                <?php print $content['contentcolumn1']; ?>
              </div>
            </div>
            <div class="col-md-6 bartlett-main-col-2 radix-layouts-contentcolumn2 panel-panel">
              <div class="panel-panel-inner">
                <?php print $content['contentcolumn2']; ?>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div><!-- /.container -->
  </section><!--  /.section -->
</div><!-- /.bartlett -->
