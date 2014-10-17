
// TODO Probably drop this file. Lots of ASUOnline specific stuff here, and
// complicated. Left in for now since we may want to borrow some logic for
// validation.

/**
 *  Fix &amp; in select list https://drupal.org/comment/8507309#comment-8507309
 */
(function ($) {
    Drupal.behaviors.asuo_rfi = {
        attach: function (context, settings) {
            // Need to clear form values on page load, per AOL-323
            var $block_forms = $('body:not(.page-entityform-edit) .entitytype-rfi_form-form');
            $block_forms.find('input:[type="text"]').val('');

            // RFI Form select box disabling behavior.

            // If select list only has one option...  (Optional)
            if ($('#edit-field-rfi-program-und option').size() == 1) {

                // Disable select list, and trigger Chosen to register that change.
                $('#edit-field-rfi-program-und').prop('disabled', true).trigger("chosen:updated");

                // When the form is submitted, reenable the select list, otherwise the browser will
                // not submit a select list value, and we’ll lose it and/or fail validation
                $('form#rfi-form-entityform-edit-form').bind('submit', function() {
                    $(this).find('#edit-field-rfi-program-und').removeProp('disabled');
                });

            }
            else {
              // Only clear out the Program field if more than one program is available.
              // Otherwise, you end up with some forms having disabled Program and no way to select.
              $block_forms.find('select').val("_none").trigger("chosen:updated");
            }


            // RFI Form validation. Success and Error messages.

            // Indicates valid user input.
            function isValid(rfi_input, inputId, spanId, msg) {

                // Note rfi_input can be a select element as well as inputs.

                var program_field_id = 'edit-field-program-und';

                if ($("#" + inputId).closest("div").hasClass("form-item")) {

                    // append() the messages into the prev() sibling, which is
                    // <label>.

                    // Reset.
                    $('#' + spanId).remove();

                    // Feedback message.
                    if (msg == "not-required") {
                        rfi_input.prev().append("<span class='okMsg' id='" + spanId + "'>Not Required</span>");
                    }
                    else {
                        rfi_input.prev().append("<span class='okMsg' id='" + spanId + "'>OK</span>");
                    }
                    //$("#" + spanId).addClass("okMsg");
                    //$("#" + spanId).removeClass("errMsg");

                    // Field highlighting.
                    if (inputId == program_field_id || inputId == "degree_type_select") {
                        $("select[id='" + inputId + "']").removeClass("error");
                    }
                    else {
                        $("input[id='" + inputId + "']").removeClass("error");
                    }
                }
                else {
                    if (inputId == program_field_id) {
                        $("select[id='" + inputId + "']").css({
                            "background-color":"#fff",
                            "border":"1px solid #848589"
                        });
                    }
                    else {
                        $("input[id='" + inputId + "']").css({
                            "background-color":"#fff",
                            "border":"1px solid #848589"
                        });
                    }
                }
            }

            // Function to call indicating invalid user input.
            function isInvalid(rfi_input, inputId, spanId, errType) {

                var program_field_id = 'edit-field-program-und';

                if ($("#" + inputId).closest("div").hasClass("form-item")) {

                    // Reset.
                    $('#' + spanId).remove();

                    // Feedback message.
                    if (errType.toLowerCase() == "invalid") {
                        rfi_input.prev().append("<span class='errMsg' id='" + spanId + "'>Invalid</span>");
                    }
                    else {
                        rfi_input.prev().append("<span class='errMsg' id='" + spanId + "'>Required</span>");
                    }
                    //$("#" + spanId).addClass("errMsg");
                    //$("#" + spanId).removeClass("okMsg");

                    // Field highlighting.
                    if (inputId == program_field_id || inputId == "degree_type_select") {
                        $("select[id='" + inputId + "']").addClass("error");
                    }
                    else {
                        $("input[id='" + inputId + "']").addClass("error");
                    }
                }
                else {
                    if (inputId == program_field_id) {
                        $("select[id='" + inputId + "']").css({
                            "border":"1px solid #ff0000"
                        });
                    }
                    else {
                        $("input[id='" + inputId + "']").css({
                            "border":"1px solid #ff0000"
                        });
                    }
                }
            }


            // Fix &amp; in select list https://drupal.org/comment/8507309#comment-8507309
            // Apply against core select widget.
            $('select option').each(function () {
                var text = $(this).text();
                if (text.indexOf('&amp;') >= 0) {
                    text = text.replace("&amp;", "&");
                }
                $(this).text(text);
            });
            // Apply against selected item, for Chosen, on initial load, in
            // case we have a preselected &amp; item. More Chosen logic
            // for &amp; further down where we have a click() listener.
            // Apply to selection.
            $('a.chosen-single span').each(function () {
                var text = $(this).text();
                if (text.indexOf('&amp;') >= 0) {
                    text = text.replace("&amp;", "&");
                }
                $(this).text(text);
            });


            // Check our form(s) inputs and selects.

            // Shouldn't ever have to listen for more than two, but just to be
            // safe, we add a third.
            // TODO There's probably an obvious, elegant way to handle the fact
            // that we can have multiple versions of this form.
            var rfi_form_ids = ["rfi-form-entityform-edit-form","rfi-form-entityform-edit-form--2", "rfi-form-entityform-edit-form--3"];
            var arrayLength = rfi_form_ids.length;
            for (var i = 0; i < arrayLength; i++) {

                // Don't bother with the rest, if we don't have a match for this
                // rfi form id.
                if ($("#" + rfi_form_ids[i]).length != 0) {

                    // Debug.
                    //console.log('iterator ' + i);
                    //console.log(rfi_form_ids[i]);

                    // IMPORTANT: Be careful when acting on forms to target the
                    // current onein your selectors.
                    // Use it like so: '#' + rfi_form_ids[i]

                    var program_field_id = 'edit-field-program-und';

                    // Select list checks.
                    // If we're using Chosen.
                    if ($("#" + rfi_form_ids[i] + " select[name='field_rfi_program[und]'].chosen-widget:hidden").length > 0) { // if chosen is active the select is hidden

                        // Not able to use .blur, but this works when a click or
                        // keyup happens in the .chosen-container .next() to
                        // original select list.
                        $("#" + rfi_form_ids[i] + " select[name='field_rfi_program[und]']").chosen().next().bind("click keyup", function() {

                            // Since Chosen is tweaky, we don't use the
                            // isValid() and isInvalid() functions, and just
                            // handle them inline here.

                            // No selection.
                            if ($(this).find(".chosen-single").text() == "Select Desired Program") {

                                // Add Drupal's standard error class.
                                $(this).addClass('error');
                                // For reference: $("#" + rfi_form_ids[i] + " .chosen-container").addClass('error');
                                $("span.rfiSelectMsg").remove(); // TODO Better target this. There's some innocuous bleedover.
                                $(this).prev().prev().append('<span class="errMsg rfiSelectMsg">Required</span>');
                            }
                            // Selection okay.
                            else {

                                // Remove Drupal's standard error class.
                                $(this).removeClass('error');
                                // For reference: $("#" + rfi_form_ids[i] + " .chosen-container").removeClass('error');
                                $("span.rfiSelectMsg").remove(); // TODO Better target this. There's some innocuous bleedover.
                                $(this).prev().prev().append('<span class="okMsg rfiSelectMsg">OK</span>');
                            }

                            // Fix &amp; in select list https://drupal.org/comment/8507309#comment-8507309
                            // Apply to Chosen list items.
                            $(this).find('ul.chosen-results li.active-result').each(function () {
                                var text = $(this).text();
                                if (text.indexOf('&amp;') >= 0) {
                                    text = text.replace("&amp;", "&");
                                }
                                $(this).text(text);
                            });
                            // Apply to selection.
                            $(this).find('a.chosen-single span').each(function () {
                                var text = $(this).text();
                                if (text.indexOf('&amp;') >= 0) {
                                    text = text.replace("&amp;", "&");
                                }
                                $(this).text(text);
                            });

                        });
                    }
                    // Else, standard form select without Chosen.
                    else {
                        // Degree program select change handler.
                        $("select[id='" + program_field_id + "']").change(function () {

                            // Not used.

                        });

                        // Degree program blur (select box, only).
                        $("select[id='" + program_field_id + "']").blur(function () {

                            var rfi_input = $("select[id='" + program_field_id + "']");

                            $("#programMsg").remove();
                            if ($(this).val() == "_none" || $(this).val() == "" || $(this).val() == null) { isInvalid(rfi_input, program_field_id, "programMsg", "required"); }
                            else { isValid(rfi_input, program_field_id, "programMsg", ""); }

                        });

                    }


                    // Blur handlers for all text/email/tel input fields using instant validation and feedback
                    $("form#" + rfi_form_ids[i]).find("input[type!='submit']").each(function(e) {

                        $(this).blur(function() {
                            // The current input.
                            var rfi_input = $("input[id='" + $(this).attr("id") + "']");

                            // remove any message already being displayed
                            $("#" + $(this).attr("id") + "Msg").remove();

                            // 1. check for a blank value
                            if ($.trim($(this).val()) == "") {
                                isInvalid(rfi_input, $(this).attr("id"), $(this).attr("id") + "Msg", "required");
                            }
                            else {
                                // 2. check specific format for email and phone number fields
                                switch ($(this).attr("name"))
                                {
                                    case "field_email_address[und][0][value]": // Email Address field.
                                    {
                                        var format = /^([a-zA-Z0-9\+_.-])+@([a-zA-Z0-9_.-])+\.([a-zA-Z])+([a-zA-Z])+/;
                                        if (!$.trim($(this).val()).toLowerCase().match(format)) { isInvalid(rfi_input, $(this).attr("id"), $(this).attr("id") + "Msg", "invalid"); }
                                        else { isValid(rfi_input, $(this).attr("id"), $(this).attr("id") + "Msg", ""); }
                                        break;
                                    }
                                    case "field_phone[und][0][value]": // Phone field.
                                    {
                                       var format = /^((\+\d{1,3}(-| )?\(?\d\)?(-| )?\d{1,5})|(\(?\d{2,6}\)?))(-| )?(\d{3,4})(-| )?(\d{4})(( x| ext)\d{1,5}){0,1}$/;
                                       if (!$.trim($(this).val()).match(format)) { isInvalid(rfi_input, $(this).attr("id"), $(this).attr("id") + "Msg", "invalid"); }
                                       else  { isValid(rfi_input, $(this).attr("id"), $(this).attr("id") + "Msg", ""); }
                                       // var $phoneField = $(this);
                                        // var phoneNumber = parsePhone($phoneField.val().replace(/\D*/g, ''));
                                        // if(phoneNumber != null && phoneNumber.countryISOCode != 'nothing')  {
                                          // // if(typeof console == 'object') {
                                            // // console.log(JSON.stringify(phoneNumber));
                                          // // }
//
                                          // $phoneField.val(phoneNumber.countryCode + ' ' + phoneNumber.areaCode + ' ' + phoneNumber.number);
                                          // isValid(rfi_input, $phoneField.attr("id"), $phoneField.attr("id") + "Msg", "");
                                        // }
                                        // else {
                                          // phoneNumber = parsePhone('1' + $phoneField.val().replace(/\D*/g, ''));
                                          // if(phoneNumber != null && phoneNumber.countryISOCode != 'nothing')  {
                                            // // if(typeof console == 'object') {
                                              // // console.log(JSON.stringify(phoneNumber));
                                            // // }
//
                                            // $phoneField.val(phoneNumber.countryCode + ' ' + phoneNumber.areaCode + ' ' + phoneNumber.number);
                                            // isValid(rfi_input, $phoneField.attr("id"), $phoneField.attr("id") + "Msg", "");
                                          // }
                                          // else {
                                            // isInvalid(rfi_input, $phoneField.attr("id"), $phoneField.attr("id") + "Msg", "invalid");
                                          // }
                                        // }
                                       break;
                                    }
                                    default:
                                    {
                                        isValid(rfi_input, $(this).attr("id"), $(this).attr("id") + "Msg", "");
                                    }
                                }
                            }
                        }); // End blur

                    }); // End each


                    // Submit click handler.
                    $("form#" + rfi_form_ids[i]).submit(function() {
                        // Error counter
                        var errCt = 0;

                        // First name
                        if ($.trim($(this).find("input[name='field_first_name[und][0][value]']").val()) == "") {
                            errCt += 1;
                        }
                        // Last name
                        if ($.trim($(this).find("input[name='field_last_name[und][0][value]']").val()) == "") {
                            errCt += 1;
                        }
                        // Email address
                        if ($.trim($(this).find("input[name='field_email_address[und][0][value]']").val()) == "") {
                            errCt += 1;
                        } else {
                            var format = /^([a-zA-Z0-9\+_.-])+@([a-zA-Z0-9_.-])+\.([a-zA-Z])+([a-zA-Z])+/;
                            if (!$.trim($(this).find("input[name='field_email_address[und][0][value]']").val()).toLowerCase().match(format)) {
                                errCt += 1;
                            }
                        }
                        // Phone number
                        // if ($.trim($(this).find("input[name='field_phone[und][0][value]']").val()) == "") {
                            // errCt += 1;
                        // }
                        // else {
                          // Original validation
                          var format = /^((\+\d{1,3}(-| )?\(?\d\)?(-| )?\d{1,5})|(\(?\d{2,6}\)?))(-| )?(\d{3,4})(-| )?(\d{4})(( x| ext)\d{1,5}){0,1}$/;
                          if (!$.trim($(this).find("input[name='field_phone[und][0][value]']").val()).match(format)) {
                              errCt += 1;
                          }
                          // phoneNumber = parsePhone($(this).find("input[name='field_phone[und][0][value]']").val().replace(/\D*/g, ''));
                          // console.log(phoneNumber);
                          // if(phoneNumber == null || phoneNumber.countryCode == 'nothing')  {
                            // errCt += 1;
                          // }
                        // }

                        // Check Program selection.
                        // Using Chosen.
                        if ($(this).find("select[name='field_rfi_program[und]']").hasClass('chosen-widget')) {
                            // Check that a degree program was selected.
                            if ($(this).find(".chosen-single").text() == 'Select Desired Program') {
                                errCt += 1;
                            }
                        }
                        // Using standard select widget.
                        else {
                            // Check that a degree program selector exists and
                            // was selected.
                            if ( $(this).find("select[name='field_rfi_program[und]']") && ($(this).find("select[name='field_rfi_program[und]']").val() == "_none" || $(this).find("select[name='field_rfi_program[und]']").val() == "" || $(this).find("select[name='field_rfi_program[und]']").val() == null)) {
                                errCt += 1;
                            }
                        }

                        // return false if error count is greater than zero
                        if (errCt > 0) {
                            alert ("Missing fields are required!");
                            return false; // Prevent submit.
                        }

                        // If successful, don't allow another submit through
                        // ANY entityform.
                        $("form.entityform input[type='submit']").attr('disabled','disabled');

                    }); // end of submit handler

                }

            }

        }

    }
})
(jQuery);
