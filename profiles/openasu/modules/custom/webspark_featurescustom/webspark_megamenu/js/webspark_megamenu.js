(function ($) {
    Drupal.behaviors.webspark_megamenu_hidden = {
        attach : function(context, settings) {

            if ($('.tb-megamenu-block.tb-block.tb-megamenu-block').length) {
                $('.tb-megamenu-block.tb-block.tb-megamenu-block').closest('.tb-megamenu-row.row-fluid').addClass('hide-extra-padding');
                $('.tb-megamenu-block.tb-block.tb-megamenu-block').closest('.tb-megamenu-block.tb-block.tb-megamenu-block').addClass('adding-padding');
            }

        }
    }
}(jQuery));