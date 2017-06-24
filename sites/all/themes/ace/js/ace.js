/**
 * JavaScript file for theme.
 *
 */
(function ($, Drupal) {
  Drupal.behaviors.aceSubTheme = {
    attach: function (context, settings) {

      $("p#simple-gmap-address-link").css({"text-decoration":"underline", "color":"#8c1d40"})
        .click(function() {
         $(this).siblings("iframe").toggle("300");
      });

    }
  };

})(jQuery, Drupal);
