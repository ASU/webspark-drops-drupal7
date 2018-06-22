(function ($) {
  Drupal.behaviors.asu_news_select_share = {
    attach: function (context, settings) {
      $('p').once().selectionSharer();
    }
  };

})(jQuery);
