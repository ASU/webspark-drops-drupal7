(function ($) {
    Drupal.behaviors.asu_ap_feature = {
        attach : function(context, settings) {

            $(".view-asu-ap-view div.col-lg-6").addClass("col-md-6 col-sm-12");
            $("table.table-class.responsive-table.table.table-striped.table-bordered.table-hover").removeClass("table-bordered");

        }
    }
}(jQuery));
