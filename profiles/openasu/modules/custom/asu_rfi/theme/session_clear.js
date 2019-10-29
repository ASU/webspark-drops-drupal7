(function ($) {
  Drupal.behaviors.asu_rfi_disbutton = {
    attach: function (context, settings) {

      setTimeout(function () {
        var fname = $('#edit-first-name').val();

        if (fname.length > 0) {
          window.location = window.location;
          $("#asu-rfi-form-data")[0].reset();
          $("#asu-rfi-second_form")[0].reset();
          $('#asu-rfi-long-form-data')[0].reset();
        }
      }, 180000);

      $(window).bind("pageshow", function () {
        // let the browser natively reset defaults
        if ($('#asu-rfi-form-data').length) {
          $('#asu-rfi-form-data')[0].reset();
        }
        if ($('#asu-rfi-second-form').length) {
          $('#asu-rfi-second-form')[0].reset();
        }
      });


      // Hide empty date of birth <li> alert text
      if ($('#asu-rfi-long-form-data').length || $('#asu-rfi-form-data').length) {
        if ($('.alert-block').length) {
          $(".alert-block ul li").each(function () {
            if ($(this).text().length == 1) {
              $(this).hide();
            }
          })
        }
      }

      $('#asu-rfi-long-form-data').submit(function () {
        var type = $('#edit-student-type').val();
        var degree_type = $('input[name="degree_type"]').val();
        var program = $('#edit-program-code').val();
        var start_date = $('#edit-start-date').val();
        var fname = $('#edit-first-name').val();
        var lname = $('#edit-last-name').val();
        var email = $('#edit-email').val();
        var phone = $('#edit-phone').val();
        var country = $('#rfi-country').val();
        var dob = $('#edit-birthdate').val();

        if (dob == '') {
          $('#edit-dob-field label').css('padding-left', '2em');
        }

        if (type == '' || type == 'None' || fname == '' || lname == '' || start_date == '' || email == '' || phone == '' || country == '' || dob == '') {
          var all_true = 1;
        }
        else {
          all_true = 0;
        }

        if (all_true == 0) {
          $('#edit-submit').attr("disabled", "disabled");
          $('#edit-submit').val('Processing, please wait .....');

        }
        $(window).on('beforeunload', function () {
          $('#asu-rfi-long-form-data').trigger("reset");
        });
      });

      /* reset the form fields on browser back button page load */
      $('#asu-rfi-form-data').submit(function () {
        $(window).on('unload', function () {
          $('#asu-rfi-form-data')[0].reset();
          // $('#asu-rfi-second-form').trigger("reset");
        });
      });

      $('#asu-rfi-second-form').submit(function () {
        $(window).on('unload', function () {
          $('#asu-rfi-form-data')[0].reset();
          $('#asu-rfi-second-form').trigger("reset");
        });
      });

      /* Add CSS to date of birth field */
      $('#asu-rfi-form-data').submit(function () {
        var dobdata = $('#edit-birthdate').val();
        if (dobdata == '') {
          $('#edit-dob-field label').css('padding-left', '2em');
        }
      })

    }
  }
})(jQuery);
