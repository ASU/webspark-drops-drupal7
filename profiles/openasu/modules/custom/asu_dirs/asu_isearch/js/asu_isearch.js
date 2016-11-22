/**
 * ASU iSearch module
 *
 * Custom behavior for iSearch admin
 *
 * @author Sebastian Nievas ( snievas@asu.edu )
 */

(function ($) {
    Drupal.behaviors.asu_isearch = {
        attach: function (context, settings) {

            $(document).ready(function () {
                var profile_photo_pane = $(".node-asu-isearch-profile .profile-header .isearch-profile-photo");
                var first_affil = $(".view-isearch-affiliations .accordion-toggle").get(0);

                if (profile_photo_pane.length && $.trim(profile_photo_pane.html()) == '') {
                    profile_photo_pane.hide();
                }

                // open first affiliation
                if (first_affil != null) {
                    first_affil.click();
                }
            });
        }
    }
})(jQuery);
