/**
 * Webspark Hero JS
 */

(function ($, Drupal) {
  Drupal.behaviors.websparkHero = {
    attach: function (context, settings) {
      // image height and style name now availabe in settings for future use
      $('.pane-bundle-hero', context).once('websparkHero', function () {
        $(this).wrapInner("<div class='hero-wrapper'></div>");
        $(this).addClass("hero-bg-img");
      });

      $(function () {
        $('.form-item-field-webspark-hero-bgimg-und-0 :file').change(function () {
          if (this.files && this.files[0]) {
            var reader = new FileReader();
            reader.onload = imageIsLoaded;
            reader.readAsDataURL(this.files[0]);
          }
        });
      });

      // Adds background image to preview
      function imageIsLoaded(e) {
        $("#panopoly-form-widget-preview").before("<style> .hero-bg-img {background-image: url(" + e.target.result + ");}</style>");

      }
    }
  };
})(jQuery, Drupal);
