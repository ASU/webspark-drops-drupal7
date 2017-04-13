/**
 * @file
 * Adds javascript for the membership_entity_term module.
 */

(function($) {

  /**
   * Field instance settings screen: force the 'Display on renew form.'
   * checkbox checked whenever 'Required' is checked.
   */
  Drupal.behaviors.fieldMembershipEntityTermRenew = {
    attach: function (context, settings) {
      var $checkbox = $('form#field-ui-field-edit-form input#edit-instance-settings-membership-entity-term-renew-form');
      if ($checkbox.length) {
        $('input#edit-instance-required', context).once('membership-entity-term-renew-form-checkbox', function () {
          $(this).bind('change', function (e) {
            if ($(this).attr('checked')) {
              $checkbox.attr('checked', true);
            }
          });
        });
      }
    }
  };

})(jQuery);
