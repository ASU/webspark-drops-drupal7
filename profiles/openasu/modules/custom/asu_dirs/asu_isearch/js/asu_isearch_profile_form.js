/**
 * ASU iSearch module
 *
 * Custom behavior for profile node form
 *
 * @author Sebastian Nievas ( snievas@asu.edu )
 */

(function ($) {
    Drupal.behaviors.asu_isearch_profile_form = {
        attach: function (context, settings) {

            if (settings.hasOwnProperty('asu_isearch_profile_form')) {

                settings = settings.asu_isearch_profile_form;

                $(document).ready(function () {
                    $('.asu-isearch-dept-select-wrap select').change(function (event) {

                        var name = $(this).val();
                        var nid = $('option:selected', this).attr('deptnid');
                        var nidfield = $(this).parent().find('.field-name-field-isearch-affil-dept-id input');
                        var namefield = $(this).parent().find('.field-name-field-isearch-affil-dept-name input');

                        if (name != "Select Department to Autofill") {
                            nidfield.val(nid);
                            namefield.val(name);
                        }
                    });

                    $('.asu-isearch-empl-type-select select').change(function (event) {

                        var name = $(this).val();
                        var namefield = $(this).parent().find('.field-name-field-isearch-affil-empl-type input');
                        var keyfield = $(this).parent().find('.field-name-field-isearch-affil-empl-key input');

                        if (name != "Select Employee Type to Autofill") {
                            keyfield.val(name);
                            namefield.val(name);
                        }
                    });

                    $('.asu-isearch-e-type-select select').change(function (event) {
                        var name = $(this).val();

                        if (name != "Select Employee Type to Autofill") {
                            var namefield = $(this).parent().find('.field-name-field-isearch-employee-type input');
                            namefield.val(name);
                        }
                    });
                });

            }
        }
    }
})(jQuery);