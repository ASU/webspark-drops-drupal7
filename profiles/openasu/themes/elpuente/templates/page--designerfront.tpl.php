<!-- ASU Brand Header -->
<div id="asu_hdr_imp_wrapper">
  <?php print render($page['asu_brand_header']); ?>
</div>
<!-- end ASU Brand Header -->
<!-- ASU Site title, menu -->
<?php
  if (isset($page['asu_main_menu'])) {
    print $page['asu_main_menu'];
  }
?>
<!-- end Site title -->
  <!-- Home Page Content -->
<div id="asu-os-hero" class="section">
  <div class="container">
    <div class="row">
      <div class="col-md-9 col-sm-9">
        <h2>
          <strong>Professional websites for all.</strong>
        </h2>
        <p>
          Simple. Powerful. No coding.
        </p>
        <div>
          <a href="<?php global $base_url; echo $base_url ?>/site/register" class="btn btn-gold btn-lg">
            <strong>Get Started</strong>
          </a>
        </div>
      </div>
    </div>
  </div>
</div>

<div id="asu-os-center" class="section">
  <div class="container">
    <!-- <div class="row" style="background: #white;"> -->
      <!-- Open Scholar + ASU-->
      <!-- <div class="col-md-12 align-center asu-global--inner">
        <div class="asu-os-logo-plus-asu">
          <img src="sites/all/themes/elpuente/images/logo-openscholar-plus-asu.png"/>
        </div>
        <div class="asu-os-center-maintext">
          <strong>The powerfully simple academic-oriented website builder.</strong>
        </div>
        <div class="asu-os-center-subtext">Now available for faculty at Arizona State University, for free.</div>
      </div>
    </div> -->
    <div class="row row-full" style="background: #fff;">
      <div class="asu-global--inner">
        <div style="row">
          <div class="col-md-6">
            <h1><strong>Welcome to Faculty Pages</strong></h1>
            <div>
              As an ASU faculty member Faculty Pages provides an easy way to create and manage your online presence.
              We put the power in your hands with ASU's very own customized OpenScholar solution!
            </div>
            <div>
              <a href="<?php global $base_url; echo $base_url ?>/site/register" class="btn btn-primary btn-lg">
                <strong>Learn More</strong>
              </a>
            </div>
          </div>
          <div class="col-md-6 col-sm-12 sellingpoints">
            <div class="row">
              <div class="col-md-3 col-sm-3 col-xs-3">
                <img src="sites/all/themes/elpuente/images/icon-brackets-maroon-lg.png" />
              </div>
              <div class="col-md-9 col-sm-9 col-xs-9">
                <div class="talkingpoint">
                  <strong>No coding required</strong>
                </div>
                <div>
                  Let the drag and drop interface do the coding for you.
                </div>
              </div>
            </div>
            <div class="row">
              <div class="col-md-3 col-sm-3 col-xs-3">
                <img src="sites/all/themes/elpuente/images/icon-key-maroon-lg.png" />
              </div>
              <div class="col-md-9 col-sm-9 col-xs-9">
                <div class="talkingpoint">
                  <strong>You're the admin</strong>
                </div>
                <div>
                  Control, layout, style, and content is all available to you in the backend.
                </div>
              </div>
            </div>
            <div class="row">
              <div class="col-md-3 col-sm-3 col-xs-3">
                <img src="sites/all/themes/elpuente/images/icon-tools-maroon-lg.png" />
              </div>
              <div class="col-md-9 col-sm-9 col-xs-9">
                <div class="talkingpoint">
                  <strong>Digital tools</strong>
                </div>
                <div>
                  Gear up with apps, widgets, analytics, and social media integrations.
                </div>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>

<div id="asu-os-foot" class="section">
  <div class="container">
    <div class="row">
      <div class="asu-global--inner">
        <div class="col-md-6 col-sm-12">
          <div>
            <div style="position: absolute;">
              <img src="sites/all/themes/elpuente/images/img-profile-demo.png">
            </div>
          </div>
        </div>
        <div class="col-md-6 col-sm-12 align-right">
          <h2>
            <strong>T-Minus 15 Minutes</strong>
          </h2>
          <div>
            Setup is a breeze. Just click "Get Started" and you'll have your own website in no time!
          </div>
          <div>
            <a href="<?php global $base_url; echo $base_url ?>/site/register" class="btn btn-gold btn-lg">
              <strong>Get Started</strong>
            </a>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>

  <!-- End Home Page Content -->

<div id="extradiv"></div>

<?php if ($branding_footer = render($page['branding_footer'])): ?>
  <!--FLEXIBLE ADMIN FOOTER FOR USE BY SELECT GROUPS USING OS-->
  <div id="branding_footer">
    <div class="branding-container">
      <?php print $branding_footer; ?>
    </div>
  </div>
<?php endif; ?>

<!-- ASU Brand Footer -->
<?php print render($page['asu_brand_footer']); ?>
<!-- end ASU Brand Footer -->
