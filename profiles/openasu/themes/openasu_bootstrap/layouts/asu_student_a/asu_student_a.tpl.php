<?php
/**
 * @file
 * Template for ASU Student Layout A.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div
  class="panel-display asu-a clearfix <?php !empty($class) ? print $class : ""; ?>"
  <?php !empty($css_id) ? print "id=\"$css_id\"" : ""; ?>>

  <section class="section" id="picture">
    <div class="container">
      <div class="asu-a-container asu-a-header clearfix panel-panel">
        <div
          class="asu-a-container-inner asu-a-header-inner panel-panel-inner">
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
    </div>
  </section>

  <section class="section" id="content">
    <div class="container">
      <div
        class="asu-a-container asu-a-column-content clearfix row-fluid">
        <div
          class="asu-a-column-content-region asu-a-content panel-panel span8">
          <div
            class="asu-a-column-content-region-inner asu-a-content-inner panel-panel-inner">
            <?php print $content['contentmain']; ?>
          </div>
        </div>
        <div
          class="asu-a-column-content-region asu-a-sidebar panel-panel span4">
          <div
            class="asu-a-column-content-region-inner asu-a-sidebar-inner panel-panel-inner">
            <?php print $content['sidebar']; ?>
          </div>
        </div>
      </div>
    </div>
  </section>

</div>
<!-- /.asu-a -->
