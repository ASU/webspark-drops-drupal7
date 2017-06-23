/**
 * Created by bryan on 6/23/17.
 */

/**
 * JavaScript file for theme.
 *
 */
(function ($, Drupal) {
  Drupal.behaviors.asu_standard = {
    attach: function (context, settings) {

      $("p#simple-gmap-address-link").click(function() {
        $(this).siblings("iframe").toggle("400");
      });

    }
  };

})(jQuery, Drupal);
