/**
 * @file
 * Gigya reactions.
 */
(function ($) {
    /**
     * @todo Undocumented Code!
     */
    Drupal.gigya = Drupal.gigya || {};
    Drupal.gigya.showReactionbar = function (settings) {
      //build a media object
      var reactions_str = '[' + settings.gigyaReactions.reactions + ']';
      var reactions =  JSON.parse(reactions_str);
      delete settings.gigyaReactions.reactions;
      var mediaObj = {type: 'image', href: settings.gigyaReactions.ua.linkBack};
      if ((settings.gigyaReactions.ua.imageBhev === 'url') && (settings.gigyaReactions.ua.imageUrl !== '')) {
        mediaObj.src = settings.gigyaReactions.ua.imageUrl;
      }
      else if (settings.gigyaReactions.ua.imageBhev === 'default') {
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
      if (typeof settings.gigyaReactions.ua.userMessage !== 'undefined') {
        ua.setUserMessage(settings.gigyaReactions.ua.userMessage);
      }
      if (typeof settings.gigyaReactions.ua.linkBack !== 'undefined') {
        ua.setLinkBack(settings.gigyaReactions.ua.linkBack);
        ua.addActionLink(settings.gigyaReactions.ua.title, settings.gigyaReactions.ua.linkBack);
      }
      if (typeof settings.gigyaReactions.ua.title !== 'undefined') {
        ua.setTitle(settings.gigyaReactions.ua.title);
      }
      if (typeof settings.gigyaReactions.ua.subtitle !== 'undefined') {
        ua.setSubtitle(settings.gigyaSharebar.ua.subtitle);
      }
      if (typeof settings.gigyaReactions.ua.description !== 'undefined') {
        ua.setDescription(settings.gigyaReactions.ua.description);
      }
      ua.addMediaItem(mediaObj);
      // Step 2: Define the Share Bar Plugin's params object.
      var params = jQuery.extend(true, {}, settings.gigyaReactions);
      delete params.ua;

      params.reactions = reactions;
      params.userAction = ua;
      // Step 3: Load the Share Bar Plugin.
      gigya.socialize.showReactionsBarUI(params);

    };
    Drupal.behaviors.gigyaReactions = {
      attach: function (context, settings) {
        if (typeof gigya !== 'undefined') {
          if (typeof Drupal.settings.gigyaReactionsBars != 'undefined') {
            $.each(Drupal.settings.gigyaReactionsBars, function (index, reactionbar) {
              Drupal.gigya.showReactionbar(reactionbar);
            });
          }
        }
      }
    };
})(jQuery);

