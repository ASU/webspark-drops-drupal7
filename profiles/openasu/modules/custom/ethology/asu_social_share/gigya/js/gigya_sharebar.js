/**
 * Gigya sharebar.
 */
(function ($) {
    /**
     * @todo Undocumented Code!
     */
    Drupal.gigya = Drupal.gigya || {};
    Drupal.gigya.showSharebar = function (settings) {
      //build a media object
      var mediaObj = {type: 'image', href: settings.gigyaSharebar.ua.linkBack};
      if ((settings.gigyaSharebar.ua.imageBhev === 'url') && (settings.gigyaSharebar.ua.imageUrl !== '')) {
        mediaObj.src = settings.gigyaSharebar.ua.imageUrl;
      }
      else if (settings.gigyaSharebar.ua.imageBhev === 'default') {
        if ($('meta[property="og:image"]').length > 0) {
          mediaObj.src = $('meta[property="og:image"]').attr('content');
        }
        else {
          mediaObj.src = $('#block-system-main img').eq(0).attr('src') || $('img').eq(0).attr('src');
        }
      }
      else {
        mediaObj.src = $('#block-system-main img').eq(0).attr('src') || $('img').eq(0).attr('src');
      }
      // Step 1: Construct a UserAction object and fill it with data.
      var ua = new gigya.services.socialize.UserAction();
      if (typeof settings.gigyaSharebar.ua.userMessage !== 'undefined') {
        ua.setUserMessage(settings.gigyaSharebar.ua.userMessage);
      }
      if (typeof settings.gigyaSharebar.ua.linkBack !== 'undefined') {
        ua.setLinkBack(settings.gigyaSharebar.ua.linkBack);
        ua.addActionLink(settings.gigyaSharebar.ua.title, settings.gigyaSharebar.ua.linkBack);
      }
      if (typeof settings.gigyaSharebar.ua.title !== 'undefined') {
        ua.setTitle(settings.gigyaSharebar.ua.title);
      }
      if (typeof settings.gigyaSharebar.ua.subtitle !== 'undefined') {
        ua.setSubtitle(settings.gigyaSharebar.ua.subtitle);
      }
      if (typeof settings.gigyaSharebar.ua.description !== 'undefined') {
        ua.setDescription(settings.gigyaSharebar.ua.description);
      }
      ua.addMediaItem(mediaObj);
      // Step 2: Define the Share Bar Plugin's params object.
      var params = jQuery.extend(true, {}, settings.gigyaSharebar);
      delete params.ua;
      params.userAction = ua;
      // Step 3: Load the Share Bar Plugin.
      gigya.services.socialize.showShareBarUI(params);

    };
    Drupal.behaviors.gigyaShareBar = {
      attach: function (context, settings) {
        if (typeof gigya !== 'undefined') {
          if (typeof Drupal.settings.gigyaSharebars != 'undefined') {
            $.each(Drupal.settings.gigyaSharebars, function (index, sharebar) {
              Drupal.gigya.showSharebar(sharebar);

            });
          }
        }
      }
    };
})(jQuery);

