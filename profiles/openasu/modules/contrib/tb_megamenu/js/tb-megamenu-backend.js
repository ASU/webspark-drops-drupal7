Drupal.TBMegaMenu = Drupal.TBMegaMenu || {};

(function ($) {
  Drupal.behaviors.tbMegaMenuBackendAction = {
    attach: function(context) {
      $('select[name="tb-megamenu-animation"]').change(function() {
        $('#tb-megamenu-duration-wrapper').css({'display': ($(this).val() == 'none' ? 'none' : 'inline-block')});
        $('#tb-megamenu-delay-wrapper').css({'display': ($(this).val() == 'none' ? 'none' : 'inline-block')});
      });
      $(".tb-megamenu-column-inner .close").click(function() {
        $(this).parent().html("");
      });
      $("#tb-megamenu-admin select").chosen({
        disable_search_threshold : 15,
        allow_single_deselect: true
      });
    }
  }
})(jQuery);

