<!-- Web Standards - Webspark FlexSlider -->
<div class="container">
  <div class="row row-padding-top row-padding-bottom">
    <div class="col-md-12">
      <div class="flexslider-ws">
        <ul class="slides">
        <?php foreach ($variables['items'] as $item):

        $thisItem = $item['item'];
        $thumbnailUri = image_style_url('uto_carousel_thumbnail', $thisItem['uri']);
        $carouselLink = $thisItem['link'];

        if(!empty($thisItem['link'])): ?>

          <li>
            <div class="col-sm-6 text-center">
              <a href="<?php print $thisItem['link'] ?>">
                <img src="<?php print $thumbnailUri ?>" class="img-responsive img-link">
              </a>
            </div>
            <div class="col-sm-6">
              <h4><a href="<?php print $thisItem['link'] ?>"><?php print $thisItem['title'] ?></a></h4>
              <p><?php print $thisItem['description'] ?></p>
            </div>
          </li>

          <?php else: ?>

          <li>
            <div class="col-sm-6 text-center">
                <img src="<?php print $thumbnailUri ?>" class="img-responsive img-link">
            </div>
            <div class="col-sm-6">
                <h4><?php print $thisItem['title'] ?></h4>
                <p><?php print $thisItem['description'] ?></p>
            </div>
          </li>

          <?php endif; ?>

          <?php endforeach; ?>
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
      randomize: false,
      startAt: 0 // Could add a random number here to start at
    });
  });
})(jQuery);
</script>
