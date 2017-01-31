<?php
/**
 * @file
 * Template for iSearch Profile 2 Column layout.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>
<div
        class="panel-display isearch-profile-2col clearfix <?php !empty($class) ? print $class : ''; ?>" <?php !empty($css_id) ? print "id=\"$css_id\"" : ''; ?>>
    <section class="section profile-header clearfix">
        <div class="container">
            <div class="row">
              <?php print $content['header']; ?>
            </div>
        </div>
        <div class="container">
            <div class="row">
                <div class="col-sm-2 isearch-profile-photo">
                  <?php print $content['photo']; ?>
                </div>
                <div class="col-sm-10 isearch-profile-contact">
                    <div class="contact-region">
                      <?php print $content['contact']; ?>
                    </div>
                    <div class="social-region">
                      <?php print $content['social']; ?>
                    </div>
                    <div class="affiliations-region">
                      <?php print $content['affiliations']; ?>
                    </div>
                </div>
            </div>
        </div>
    </section>
    <section class="section clearfix">
        <div class="container">
            <div class="row">
                <div class="col-md-8 isearch-profile-content">
                  <?php print $content['maincontent']; ?>
                </div>
                <div class="col-md-4 isearch-profile-sidebar">
                  <?php print $content['sidebar']; ?>
                </div>
            </div>
        </div>
    </section>
</div><!-- /.isearch-profile-2col -->
