 /**
 * @file - asu_brand.js
 */

(function ($) {
  Drupal.behaviors.asuBrandSetupHeader = {
    attach: function (context, settings) {
      $("body", context).once("asu_brand", function () {
        // ASUHeader should already be initialized by the provided header files but we should verify. Also need to verify
        // that the hostname is not listed in the override list, in which case we do not pass the /cas login path
        var overrides = settings.asu_brand.overrides ? settings.asu_brand.overrides : [];
        var hostname = window.location.hostname;

        if (overrides.indexOf(hostname) == -1 && ASUHeader) {
          ASUHeader.user_signedin = (settings.asu_brand.asu_sso_signedin === "true");
          ASUHeader.signin_url = settings.asu_brand.asu_sso_signinurl;
          ASUHeader.signout_url = settings.asu_brand.asu_sso_signouturl;
        }
      });
    }
  };
})(jQuery);
