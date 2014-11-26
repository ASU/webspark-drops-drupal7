(function ($) {
    Drupal.behaviors.asu_degrees_feature = {
        attach : function(context, settings) {

            $(".view-asu-degrees-feature div.col-lg-6").addClass("col-md-6 col-sm-12");
            $("table.table-class.responsive-table.table.table-striped.table-bordered.table-hover").removeClass("table-bordered");

        }
    }
}(jQuery));