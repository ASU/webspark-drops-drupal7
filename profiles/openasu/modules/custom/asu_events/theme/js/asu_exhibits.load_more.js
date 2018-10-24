(function ($) {
  Drupal.behaviors.asu_events_load_more = {
    attach: function (context, settings) {
      // Make sure that autopager plugin is loaded
      if($.autopager) {
        // define autopager parameters
        var content_selector = '.asu-events-exhibitions-listing-wrapper';
        var items_selector = content_selector + ' article.node';
        var next_selector = '.pager-next a';
        var pager_selector = '.pager';
        var throb = Throbber({
            size: 20, // this will also be applied to the gif
            padding: 10
        });


        $(pager_selector).hide();

        var handle_exhibit = $.autopager({
          autoLoad: false,
          appendTo: content_selector,
          content: items_selector,
          link: next_selector,
          page: 0,
          load: function() {
            $(content_selector).trigger('change');
            throb.stop();
            var nextHash = handle_exhibit.autopager('getNextHash');
            if(pager_total == nextHash.page){
              $('.asu-exhibit-load-more-btn').hide();
            }
            Drupal.attachBehaviors();
          }
        });
        if (typeof Drupal.settings.asu_exhibits !== 'undefined') {
          var pager_total = Drupal.settings.asu_exhibits.pager_total;
          // if (Drupal.settings.asu_events.view_mode != 'calendar') {
            throb.appendTo($('.asu-exhibit-load-more-btn')[0]);
            $('.asu-exhibit-load-more-btn canvas').css('margin-left', '7px');
            if(pager_total == 1) {
              $('.asu-exhibit-load-more-btn').hide();
            }
            $('.asu-exhibit-load-more-btn').once('load-more', function() {
              $(this).bind('click', function(e) {
                e.preventDefault();
                handle_exhibit.autopager('load');
                throb.start();
                $('.asu-exhibit-load-more-btn canvas').css('display', 'inline');
              });
            });
          // }
        }
      }
    }
  };

})(jQuery);
