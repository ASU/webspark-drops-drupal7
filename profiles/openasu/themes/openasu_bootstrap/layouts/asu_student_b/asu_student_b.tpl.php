<?php
/**
 * @file
 * Template for ASU Student Layout B.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div class="panel-display asu-b clearfix <?php !empty($class) ? print $class : ""; ?>" <?php !empty($css_id) ? print "id=\"$css_id\"" : ""; ?>>

  <section class="section" id="picture">
    <div class="container">
      <div class="asu-b-container asu-b-header clearfix panel-panel">
        <div class="asu-b-container-inner asu-b-header-inner panel-panel-inner">
          <?php print $content['header']; ?>
        </div>
      </div>
    </div>
  </section>
  
  <section class="section" id="menu">
    <div class="container">
      <div class="asu-a-container asu-a-header clearfix panel-panel">
        <div class="asu-a-container-inner asu-a-header-inner panel-panel-inner">
          <nav class='navbar navbar-fixed-top'>
            <div class='navbar-inner'>
              <a class='btn btn-navbar' data-target='.nav-collapse' data-toggle='collapse'>
                <span class='icon-bar'></span>
                <span class='icon-bar'></span>
                <span class='icon-bar'></span>
              </a>
              <div class='nav-collapse'>
                <?php print $content['menu'];?>
              </div>
            </div>
          </nav>
      </div>
    </div>
  </section>
  
  <section class="section" id="content">
    <div class="container">
      <div class="asu-b-container asu-b-column-content clearfix row-fluid">
        <div class="asu-b-column-content-region asu-b-sidebar panel-panel span4">
          <div class="asu-b-column-content-region-inner asu-b-sidebar-inner panel-panel-inner">
            <?php print $content['sidebar']; ?>
          </div>
        </div>
        <div class="asu-b-column-content-region asu-b-content panel-panel span8">
          <div class="asu-b-column-content-region-inner asu-b-content-inner panel-panel-inner">
            <?php print $content['contentmain']; ?>
          </div>
        </div>
      </div>
    </div>
  </section>
   
</div><!-- /.asu-b -->
