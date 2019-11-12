(function ($) {
  Drupal.behaviors.asu_rfi_form = {
    attach: function (context, settings) {
      // Used to determine if RFI form is on the page.
      // Go to div if it is go to URL if it isn't #block-asu-rfi-asu-rfi-form-block
      $('#take-me-to-rfi').on('click', function (e) {
        e.preventDefault();
        var forms = $('form[id^="asu-rfi-form-data"]');
        if (forms.length !== 0) {
          var form_target = forms.closest(".block-asu-rfi-asu_rfi_form_block-instance").attr('id');
          location.href = '#' + form_target;
        } else {
          location.href = 'https://students.asu.edu/typeofstudent';
        }
      });
    }
  };
})(jQuery);
