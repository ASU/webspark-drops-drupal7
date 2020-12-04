// Hydrate and render components with Preact

(function ($) {
  Drupal.behaviors.asu_brand = {
    attach: function (context, settings) {
      // console.log(JSON.parse(Drupal.settings.asu_brand.navTree));

      var loginInfo = AsuWebcore.checkSSOCookie();

      AsuWebcore.RenderPreact(AsuWebcore.Header, {
        navTree: JSON.parse(Drupal.settings.asu_brand.navTree),
        title: Drupal.settings.asu_brand.siteName,
        subtitle: Drupal.settings.asu_brand.siteSubtitle,
        loggedIn: Drupal.settings.asu_brand.isLoggedIn,
        userName: Drupal.settings.asu_brand.isLoggedIn == true ? loginInfo.userName : "",
        loginLink: Drupal.settings.asu_brand.casLoginLink,
        logoutLink: Drupal.settings.asu_brand.casLogoutLink,
        animateTitle: false
      }, document.getElementById("headerContainer"));
    }
  };
}(jQuery));
