/**
 * Created with PhpStorm.
 * User:
 * Date: 7/30/14
 * Time: 2:28 PM
 */
(function ($) {
  Drupal.gigya = Drupal.gigya || {};
  Drupal.gigya.showFollowBar = function (settings) {
    var buttons = JSON.parse(settings.follow_bar);
    delete settings.follow_bar;
    settings.buttons = buttons;
    gigya.socialize.showFollowBarUI(settings);
  }

    Drupal.behaviors.gigyaFollowBar = {
      attach: function (context, settings) {
        if (typeof gigya !== 'undefined') {
          if (typeof Drupal.settings.gigyaFollowBars != 'undefined') {
            $.each(Drupal.settings.gigyaFollowBars, function (index, followbar) {
              Drupal.gigya.showFollowBar(followbar.gigyaFollowBar);
            });
          }
        }
      }
    };
})(jQuery);
