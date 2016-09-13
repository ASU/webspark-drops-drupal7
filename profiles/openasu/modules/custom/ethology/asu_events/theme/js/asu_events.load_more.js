(function ($) {
  Drupal.behaviors.asu_events_load_more = {
    attach: function (context, settings) {
      // Make sure that autopager plugin is loaded
      if($.autopager) {
        // define autopager parameters
        var content_selector = '.asu-events-list';
        var items_selector = content_selector + ' article.node';
        var next_selector = '.pager-next a';
        var pager_selector = '.pager';
        var throb = Throbber({
            size: 20, // this will also be applied to the gif
            padding: 10
        });


        $(pager_selector).hide();

        var handle = $.autopager({
          autoLoad: true,
          appendTo: content_selector,
          content: items_selector,
          link: next_selector,
          page: 0,
          load: function() {
            $(content_selector).trigger('change');
            throb.stop();
            var nextHash = handle.autopager('getNextHash');
            if(pager_total == nextHash.page){
              $('.asu-news-load-more-btn').hide();
            }
          }
        });
        if (typeof Drupal.settings.asu_events !== 'undefined') {
          var pager_total = Drupal.settings.asu_events.pager_total;
          throb.appendTo($('.asu-news-load-more-btn')[0]);
          $('.asu-news-load-more-btn canvas').css('margin-left', '7px');
          if(pager_total == 1) {
            $('.asu-news-load-more-btn').hide();
          }
          $('.asu-news-load-more-btn').once('load-more', function() {
            $(this).bind('click', function(e) {
              e.preventDefault();
              handle.autopager('load');
              throb.start();
              $('.asu-news-load-more-btn canvas').css('display', 'inline');
            });
          });
        }
      }
    }
  };

})(jQuery);
