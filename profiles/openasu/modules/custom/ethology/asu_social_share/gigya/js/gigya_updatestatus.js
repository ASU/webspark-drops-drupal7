/**
 * Gigya update user status.
 */
(function ($) {
  /**
   * Limits update status to 140 characters.
   */
  Drupal.behaviors.gigyaUpdateStatus = {
    attach: function(context, settings) {
    $("#gigya-textfield").keyup(function () {
      var charsLeft = (140 - $(this).val().length);
      var descDiv = $(this).parent().parent().parent().children(".description");
      $(descDiv).html("<strong>" + charsLeft + "</strong> characters remaining");
      if (charsLeft < 0) {
        $(descDiv).addClass("negative");
        $("#gigya-post-button").attr('disabled', 'true');
      }
      else {
        $(descDiv).removeClass("negative");
        $("#gigya-post-button").removeAttr('disabled');
      }
    });
  
    if (!$("#gigya-toggle").attr("checked")) {
      $("#gigya-textfield-wrapper").hide();
      $("#gigya-account-wrapper").hide();
    }
  
    $("#gigya-toggle").bind("click", function () {
      if ($("#gigya-toggle").attr("checked")) {
        $("#gigya-textfield-wrapper").show();
        $("#gigya-account-wrapper").show();
      }
      else {
        $("#gigya-textfield-wrapper").hide();
        $("#gigya-account-wrapper").hide();
      }
    });
    }
  };
})(jQuery);
