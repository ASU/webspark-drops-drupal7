(function ($, Drupal) {
  Drupal.behaviors.ws2Banners = {
    attach: function (context, settings) {
      $(function () {
        $(".pane-bundle-banners-ws2 .banner-close > a.close", context).once().click(function () {
          $(this).closest(".pane-bundle-banners-ws2").remove();
        });
      });
    }
  };
})(jQuery, Drupal);
