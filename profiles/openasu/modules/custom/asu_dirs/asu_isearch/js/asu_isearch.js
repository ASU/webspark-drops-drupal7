/**
 * ASU iSearch module
 *
 * Custom behavior for iSearch admin
 *
 * @author Sebastian Nievas ( snievas@asu.edu )
 * @author Colton Testamarck ( colt@asu.edu )
 */

(function ($) {
    Drupal.behaviors.asu_isearch = {
        attach: function (context, settings) {

            $(document).ready(function () {
                var profile_photo_pane = $(".node-asu-isearch-profile .profile-header .isearch-profile-photo");
                var first_affil = $(".view-isearch-affiliations .accordion-toggle").get(0);
                var acts = $(".field-name-field-isearch-rsrch-activity a");

                if (profile_photo_pane.length && $.trim(profile_photo_pane.html()) == '') {
                    profile_photo_pane.hide();
                }

                // open first affiliation
                // todo: look into doing this from the views side
                if (first_affil != null) {
                    first_affil.click();
                }

                // add the complete/absolute url for the people links
                $.each(acts, function (index, value) {
                    var href = $(this).attr('href');
                    var isearch = href.indexOf("isearch.asu.edu");

                    if (isearch == -1) {
                        href = 'https://isearch.asu.edu' + href;
                        $(this).attr('href', href);
                    }
                });

            });
        }
    }
})(jQuery);
