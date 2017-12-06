<?php ?>
<!-- Web Standards - Webspark FlexSlider -->
<div class="container">
  <div class="row row-padding-top row-padding-bottom">
    <div class="col-md-12">
      <div class="flexslider-ws">
        <ul class="slides">
          <?php foreach ($variables['items'] as $item) { ?>
            <?php
            $thisItem = $item['item'];
            $thumbnailUri = image_style_url('uto_carousel_thumbnail', $thisItem['uri']);
            $carouselLink = $thisItem['link'];
            ?>
            <li>
              <div class="col-sm-6 text-center">
                <a href="<?php print $thisItem['link'] ?>"><img
                    src="<?php print $thumbnailUri ?>"
                    class="img-responsive img-link"></a>
              </div>
              <div class="col-sm-6">
                <?php if (!empty($thisItem['link'])): ?>
                  <h4><a
                      href="<?php print $thisItem['link'] ?>"><?php print $thisItem['title'] ?></a>
                  </h4>
                <?php else: ?>
                  <h4><?php print $thisItem['title'] ?></h4>
                <?php endif; ?>
                <p><?php print $thisItem['description'] ?>
                </p>
              </div>
            </li>
          <?php } ?>
        </ul>
      </div>
    </div>
  </div>
</div>

<script type="text/javascript">
  (function ($) {
    $(document).ready(function () {
      $('.flexslider-ws').flexslider({
        animation: "slide",
        animationLoop: true,
        controlsContainer: jQuery('#flex-controls-ws'),
        controlNav: false,
        directionNav: true,
        slideshow: true,
        slideshowSpeed: 7000,
        randomize: true,
        startAt: 0 // Could add a random number here to start at
      });
    });
  })(jQuery);
</script>
