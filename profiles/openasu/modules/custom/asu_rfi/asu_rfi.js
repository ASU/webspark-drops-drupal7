
// TODO Probably drop this file. Lots of ASUOnline specific stuff here, and
// complicated. Left in for now since we may want to borrow some logic for
// validation.

/**
 *  Fix &amp; in select list https://drupal.org/comment/8507309#comment-8507309
 */
(function ($) {
    Drupal.behaviors.asuo_rfi = {
        attach: function (context, settings) {
            //Get the for types selected from RFI block settings page
            $('input[name="asu_rfi_form_block_type"]').change(function(){
                alert($(this).val());
            })
     
        }

    }
})
(jQuery);
