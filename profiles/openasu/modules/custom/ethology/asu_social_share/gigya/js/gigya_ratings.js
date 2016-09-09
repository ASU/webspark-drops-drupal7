/**
 * @file
 * Gigya ratings
 */
(function ($) {
    /**
     * @todo Undocumented Code!
     */
    Drupal.gigya = Drupal.gigya || {};
    Drupal.gigya.showRatings = function (params) {
      gigya.socialize.showRatingUI(params);

    };
    Drupal.behaviors.gigyaRatings = {
      attach: function (context, settings) {
        if (typeof gigya !== 'undefined') {
          if (typeof Drupal.settings.gigyaRaitingsInstances !== 'undefined') {
            $.each(Drupal.settings.gigyaRaitingsInstances, function (index, rating) {
              Drupal.gigya.showRatings(rating);
            });

          }
        }
      }
    };
})(jQuery);

