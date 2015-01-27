
// This code is not being used at this time. May be useful in future, so left it here.


(function ($) {
    Drupal.behaviors.asuo_rfi = {
        attach: function (context, settings) {
         
          $('html, body').animate({ scrollTop: $('#rfi_second_form').offset().top - 100}, 1000);
         //$('html, body').animate({ scrollTop: $('#rfi_second_form_top_div').offset().top}, 1000);
        // $('#rfi_second_form').scroll();
      }
   }
})
(jQuery);
