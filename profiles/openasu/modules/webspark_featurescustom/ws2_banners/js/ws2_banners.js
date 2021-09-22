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
  //implementing wrapper around bootstrap columns for innovation theme if banner exists.
  if(Drupal.settings.ajaxPageState.theme === "innovation" && $(".fpp-ws2-banner-content > .fieldable-panels-pane").length > 0) {
    $(".fpp-ws2-banner-content > .fieldable-panels-pane").wrapInner("<div class='row'></div>");
  }
})(jQuery, Drupal);
