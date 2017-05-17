/**
 * @file
 * Adds javascript for the membership_entity module.
 */

(function($) {

  /**
   * Field instance settings screen: force the 'Display on join form.'
   * checkbox checked whenever 'Required' is checked.
   */
  Drupal.behaviors.fieldMembershipEntityJoin = {
    attach: function (context, settings) {
      var $checkbox = $('form#field-ui-field-edit-form input#edit-instance-settings-membership-entity-join-form');
      if ($checkbox.length) {
        $('input#edit-instance-required', context).once('membership-entity-join-form-checkbox', function () {
          $(this).bind('change', function (e) {
            if ($(this).attr('checked')) {
              $checkbox.attr('checked', true);
            }
          });
        });
      }
    }
  };

  /**
   * Update button label if a membership is added when registering for a new
   * account.
   */
  Drupal.behaviors.MembershipEntityAddMembership = {
    attach: function (context, settings) {
      var $checkbox = $('form#user-register-form input#edit-membership-entity-add'),
          $submit = $('form#user-register-form input#edit-submit');
      if ($checkbox.length) {
        $($checkbox, context).once('membership-entity-add-checkbox', function () {
          $(this).bind('change', function (e) {
            if ($(this).attr('checked')) {
              $submit.attr('value', Drupal.t('Next: Membership Details'));
            }
            else {
              $submit.attr('value', Drupal.t('Create new account'));
            }
          });
        });
      }
    }
  };

})(jQuery);
