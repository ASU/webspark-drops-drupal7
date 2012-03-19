(function ($) {
Drupal.behaviors.office_hours = {
  attach: function(context,settings) {
  $(".oh-hide", context).parent().hide();
  $(".oh-add-more-link", context).each(function (i) {
   $(this).parent().children("div.office-hours-block").hide();
    })
    .click(function () {
    $(this).hide();
    $(this).parent().children("div.office-hours-block").fadeIn("slow");
    return false;
  });
}
};
})(jQuery);
