 /**
 * @file - asu_brand.js
 */

(function ($) {

Drupal.behaviors.asuBrandSetupHeader = {
  attach: function (context, settings) {
    $('body', context).once('asu_brand', function () {
      // ASUHeader should already be initialized by the provided header files but we should verify.
      if (ASUHeader) {
        ASUHeader.user_signedin = (settings.asu_brand.asu_sso_signedin === 'true');
        ASUHeader.signin_url = settings.asu_brand.asu_sso_signinurl;
        ASUHeader.signout_url = settings.asu_brand.asu_sso_signouturl;
      }
    });
  }
};

})(jQuery);
