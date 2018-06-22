(function ($) {
  Drupal.behaviors.asu_events_load_more = {
    attach: function (context, settings) {
      $('.pane-asu-news-listing').once('events-load-more', function() {
        // Make sure that autopager plugin is loaded
        if($.autopager) {
          // define autopager parameters
          var content_selector = '.asu-news-listing-wrapper';
          var items_selector = content_selector + ' article.node';
          var next_selector = '.pager-next a';
          var pager_selector = '.pager';
          var throb = Throbber({
              size: 20, // this will also be applied to the gif
              padding: 10
          });


          $(pager_selector).hide();

          var handle = $.autopager({
            autoLoad: false,
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
              Drupal.attachBehaviors();
            }
          });
          if (typeof Drupal.settings.asu_news !== 'undefined') {
            var pager_total = Drupal.settings.asu_news.pager_total;
            // if (Drupal.settings.asu_events.view_mode != 'calendar') {

              $('.asu-news-load-more-btn canvas').css('margin-left', '7px');
              if(pager_total == 1) {
                $('.asu-news-load-more-btn').hide();
              }
              $('.asu-news-load-more-btn').once('load-more', function() {
                throb.appendTo($('.asu-news-load-more-btn')[0]);
                $(this).bind('click', function(e) {
                  e.preventDefault();
                  handle.autopager('load');
                  throb.start();
                  $('.asu-news-load-more-btn canvas').css('display', 'inline');
                });
              });
            // }
          }
        }
      });
    }
  };

})(jQuery);
