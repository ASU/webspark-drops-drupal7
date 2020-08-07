/**
 * Author:  Colton Testamarck <colt@asu.edu>
 *
 */
(function ($, Drupal) {
    Drupal.behaviors.webspark_mega_footer_WS2L = {
        attach: function (context, settings) {
            if ($('#edit-show-contact-info').is(':checked')) {
                $('.mega-dep-group').show();
            }

            $('#edit-show-contact-info').change(function (e) {
                if ($(this).is(':checked')) {
                    $('.mega-dep-group').show();
                } else {
                    $('.mega-dep-group').hide();
                }
            });

        }
    };
})(jQuery, Drupal);