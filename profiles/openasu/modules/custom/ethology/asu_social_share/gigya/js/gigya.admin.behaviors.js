/**
 * @file
 * Drupal behaviors for admin pages.
 */

(function ($) {
  /**
   * @todo Undocumented Code!
   */
  Drupal.behaviors.gigyaFieldSettingHideShow = {
    attach: function (context, settings) {
      $('.reactions-override').each( function () {
        if (!$(this).is(':checked')) {
          $(this).parent().next('.gigya-reaction-field-settings').hide();
        }
      });
      $('.reactions-override').once().click(function() {
        $(this).parent().next('.gigya-reaction-field-settings').slideToggle();
      });
      $('.follow-bar-override').each( function () {
        if (!$(this).is(':checked')) {
          $(this).parent().next('.gigya-follow-bar-field-settings').hide();
        }
      });
      $('.follow-bar-override').once().click(function() {
        $(this).parent().next('.gigya-follow-bar-field-settings').slideToggle();
      });
      $('.sharebar-override').each( function () {
        if (!$(this).is(':checked')) {
          $(this).parent().next('.gigya-sharebar-field-settings').hide();
        }
      });
      $('.sharebar-override').once().click(function() {
        $(this).parent().next('.gigya-sharebar-field-settings').slideToggle();
      });
      }
  };
    Drupal.behaviors.gigyaAdmin = {
      attach: function (context, settings) {
          Drupal.gigya.checkAdminRadio();
        $('#edit-gigya-login-mode input:radio').once().change( function (e) {
          Drupal.gigya.checkAdminRadio();
        });
      }
    };
    Drupal.gigya.checkAdminRadio = function () {
      $('#edit-gigya-login-mode input:radio').each( function () {
        var val = $(this).val();
        if ((val === 'drupal_and_gigya') || (val === 'gigya') ) {
          if  ($(this).is(':checked') === true){
            $(this).siblings('.description').find('.warnning').removeClass('gigya-hidden');
            $('#edit-gigya-social-login, #edit-gigya-login-advanced, #edit-gigya-connect-advanced').show();
            if (val === 'drupal_and_gigya') {
              $(this).parent().next().find('.warnning').addClass('gigya-hidden');
            }
            return false;
          }
          else {
            $('#edit-gigya-social-login, #edit-gigya-login-advanced, #edit-gigya-connect-advanced').hide();
            $(this).siblings('.description').find('.warnning').addClass('gigya-hidden');
          }
          }
      })
    };
  Drupal.behaviors.gigyaDataCenter = {
    attach: function () {
      if ($('#edit-gigya-data-center').length > 0) {
        var otherDs = $("#gigya-other-data-center").val().substr(0, 3);
        var other = "<div class='data-center-other'><input type='text' name='data-center-other' class='form-text' size='5' maxlength='5' value='" + otherDs + "' /><span class='suffix'>.gigya.com</span></div>"
        var sel = $('#edit-gigya-data-center');
        sel.after(other);
        if (sel.val() != 'other') {
          $(".data-center-other").hide();
        }
        sel.once().change( function(e) {
          if (sel.val() == 'other') {
            $(".data-center-other").show();
          } else {
            $(".data-center-other").hide();
          }
        });
      }
    }
  };
  Drupal.behaviors.gigyaCiRules = {
    attach: function () {
      if ($("#edit-parameter-gigya-ci-class").length > 0) {
        $("#edit-parameter-gigya-ci-class-settings-gigya-ci-class").once().change(function (e) {
          var val = $(this).val();
          var select = $('#edit-parameter-gigya-ci-path-settings-gigya-ci-path');
          if (val == '_pageviews') {
            if (select.val() == '/') {
              select.find("option:selected").prev().attr("selected", true);
            }
            select.find('option[value="/"]').attr('disabled','disabled');
          } else {
            select.find('option[value="/"]').attr('disabled','');
          }
        })
      }
    }
  }
})(jQuery);
