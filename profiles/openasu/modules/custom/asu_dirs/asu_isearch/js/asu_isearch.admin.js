/**
 * ASU iSearch module
 *
 * Custom behavior for iSearch admin
 *
 * @author Sebastian Nievas ( snievas@asu.edu )
 */

(function ($) {
    Drupal.behaviors.asu_isearch_admin = {
        attach: function (context, settings) {
            initIsearchConfig();
        }
    }
})(jQuery);