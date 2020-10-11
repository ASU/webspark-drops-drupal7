<?php
/**
 * @file
 * Template for custom Panopoly layout Beast.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div class="panel-display beast clearfix <?php !empty($class) ? print $class : ''; ?>" <?php !empty($css_id) ? print "id=\"$css_id\"" : ''; ?>>

  <div class="section section-post-header">
    <div class="container">
      <div class="row row-1 beast-single-column row-full">
        <div class="column col-md-12 beast-post-header-row1">
          <?php print $content['postheaderrow1']; ?>
        </div>
      </div>
    </div><!-- /.container -->
  </div><!-- /.section-post-header -->

  <div class="section section-top">
    <div class="container">
      <div class="row row-1 beast-single-column row-full">
        <div class="column col-md-12 beast-top-row1">
          <?php print $content['toprow1']; ?>
        </div>
      </div>
      <div class="row row-1b beast-single-column">
        <div class="column col-md-12 beast-top-row1b">
          <?php print $content['toprow1b']; ?>
        </div>
      </div>      
      <div class="row row-2 beast-double-column">
        <div class="column col-md-6 beast-top-row2-column1">
          <?php print $content['toprow2col1']; ?>
        </div>
        <div class="column col-md-6 beast-top-row2-column2">
          <?php print $content['toprow2col2']; ?>
        </div>
      </div>
      <div class="row row-3 beast-two-column">
        <div class="column col-sm-12 col-md-7 col-lg-8 beast-top-row3-column1">
          <?php print $content['toprow3col1']; ?>
        </div>
        <div class="column col-sm-6 col-md-5 col-lg-4 beast-top-row3-column2">
          <?php print $content['toprow3col2']; ?>
        </div>
      </div>
      <div class="row row-4 beast-two-column">
        <div class="column col-sm-6 col-md-5 col-lg-4 beast-top-row4-column1">
          <?php print $content['toprow4col1']; ?>
        </div>
        <div class="column col-sm-12 col-md-7 col-lg-8 beast-top-row4-column2">
          <?php print $content['toprow4col2']; ?>
        </div>
      </div>
      <div class="row row-5 beast-triple-column">
        <div class="column col-md-4 col-sm-6 beast-top-row5-column1">
          <?php print $content['toprow5col1']; ?>
        </div>
        <div class="column col-md-4 col-sm-6 beast-top-row5-column2">
          <?php print $content['toprow5col2']; ?>
        </div>
        <div class="column col-md-4 col-sm-6 beast-top-row5-column3">
          <?php print $content['toprow5col3']; ?>
        </div>
      </div>
      <div class="row row-5b beast-single-column">
        <div class="column col-md-12 beast-top-row5b">
          <?php print $content['toprow5b']; ?>
        </div>
      </div>       
			<div class="row row-6 beast-single-column row-full">
				<div class="column col-md-12 beast-top-row6">
					<?php print $content['toprow6']; ?>
				</div>
			</div>
    </div><!-- /.container -->
  </div><!-- /.section-top -->


  <div class="section section-middle">
    <div class="container">
      <div class="row row-1 beast-single-column row-full">
        <div class="column col-md-12 beast-middle-row1">
          <?php print $content['middlerow1']; ?>
        </div>
      </div>
      <div class="row row-1b beast-single-column">
        <div class="column col-md-12 beast-middle-row1b">
          <?php print $content['middlerow1b']; ?>
        </div>
      </div>
      <div class="row row-2 beast-double-column">
        <div class="column col-md-6 beast-middle-row2-column1">
          <?php print $content['middlerow2col1']; ?>
        </div>
        <div class="column col-md-6 beast-middle-row2-column2">
          <?php print $content['middlerow2col2']; ?>
        </div>
      </div>
      <div class="row row-3 beast-two-column">
        <div class="column col-sm-12 col-md-7 col-lg-8 beast-middle-row3-column1">
          <?php print $content['middlerow3col1']; ?>
        </div>
        <div class="column col-sm-6 col-md-5 col-lg-4 beast-middle-row3-column2">
          <?php print $content['middlerow3col2']; ?>
        </div>
      </div>
      <div class="row row-4 beast-two-column">
        <div class="column col-sm-6 col-md-5 col-lg-4 beast-middle-row4-column1">
          <?php print $content['middlerow4col1']; ?>
        </div>
        <div class="column col-sm-12 col-md-7 col-lg-8 beast-middle-row4-column2">
          <?php print $content['middlerow4col2']; ?>
        </div>
      </div>
      <div class="row row-5 beast-triple-column">
        <div class="column col-md-4 col-sm-6 beast-middle-row5-column1">
          <?php print $content['middlerow5col1']; ?>
        </div>
        <div class="column col-md-4 col-sm-6 beast-middle-row5-column2">
          <?php print $content['middlerow5col2']; ?>
        </div>
        <div class="column col-md-4 col-sm-6 beast-middle-row5-column3">
          <?php print $content['middlerow5col3']; ?>
        </div>
      </div>
      <div class="row row-5b beast-single-column">
        <div class="column col-md-12 beast-middle-row5b">
          <?php print $content['middlerow5b']; ?>
        </div>
      </div>
			<div class="row row-6 beast-single-column row-full">
				<div class="column col-md-12 beast-middle-row6">
					<?php print $content['middlerow6']; ?>
				</div>
			</div>
    </div><!-- /.container -->
  </div><!-- /.section-middle -->


  <div class="section section-bottom">
    <div class="container">
      <div class="row row-1 beast-single-column row-full">
        <div class="column col-md-12 beast-bottom-row1">
          <?php print $content['bottomrow1']; ?>
        </div>
      </div>
      <div class="row row-1b beast-single-column">
        <div class="column col-md-12 beast-bottom-row1b">
          <?php print $content['bottomrow1b']; ?>
        </div>
      </div>
      <div class="row row-2 beast-double-column">
        <div class="column col-md-6 beast-bottom-row2-column1">
          <?php print $content['bottomrow2col1']; ?>
        </div>
        <div class="column col-md-6 beast-bottom-row2-column2">
          <?php print $content['bottomrow2col2']; ?>
        </div>
      </div>
      <div class="row row-3 beast-two-column">
        <div class="column col-sm-12 col-md-7 col-lg-8 beast-bottom-row3-column1">
          <?php print $content['bottomrow3col1']; ?>
        </div>
        <div class="column col-sm-6 col-md-5 col-lg-4 beast-bottom-row3-column2">
          <?php print $content['bottomrow3col2']; ?>
        </div>
      </div>
      <div class="row row-4 beast-two-column">
        <div class="column col-sm-6 col-md-5 col-lg-4 beast-bottom-row4-column1">
          <?php print $content['bottomrow4col1']; ?>
        </div>
        <div class="column col-sm-12 col-md-7 col-lg-8 beast-bottom-row4-column2">
          <?php print $content['bottomrow4col2']; ?>
        </div>
      </div>
      <div class="row row-5 beast-triple-column">
        <div class="column col-md-4 col-sm-6 beast-bottom-row5-column1">
          <?php print $content['bottomrow5col1']; ?>
        </div>
        <div class="column col-md-4 col-sm-6 beast-bottom-row5-column2">
          <?php print $content['bottomrow5col2']; ?>
        </div>
        <div class="column col-md-4 col-sm-6 beast-bottom-row5-column3">
          <?php print $content['bottomrow5col3']; ?>
        </div>
      </div>
      <div class="row row-5b beast-single-column">
        <div class="column col-md-12 beast-bottom-row5b">
          <?php print $content['bottomrow5b']; ?>
        </div>
      </div>
			<div class="row row-6 beast-single-column row-full">
				<div class="column col-md-12 beast-bottom-row6">
					<?php print $content['bottomrow6']; ?>
				</div>
			</div>
    </div><!-- /.container -->
  </div><!-- /.section-bottom -->

  <div class="section section-pre-footer">
    <div class="container">
      <div class="row row-1 beast-single-column row-full">
        <div class="column col-md-12 beast-pre-footer-row1">
          <?php print $content['prefooterrow1']; ?>
        </div>
      </div>
    </div><!-- /.container -->
  </div><!-- /.section-pre-footer -->

</div><!-- /.beast -->