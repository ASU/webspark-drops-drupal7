(function ($) {
  Drupal.behaviors.asu_events_calendar = {
    attach: function (context, settings) {
      dates = JSON.parse('['+Drupal.settings.asu_events_dates+']');
      $('#calendar').fullCalendar({
        // put your options and callbacks here
        selectable: true,
        events: dates,
        eventRender: function(event, element) {
            $(element).tooltip({title: event.title});
        },
        eventClick: function(event) {
          if (event.url) {
              window.open(event.url);
              return false;
          }
        },
        timezone: 'UTC'
      });


    }
  };

  Drupal.behaviors.asu_events_view = {
    attach: function (context, settings) {

      var display = Drupal.settings.asu_events.view_mode;

      if (display == 'full') {
        $('#calendar').hide();
        $('.asu-news-load-more-btn').show();
        $('.asu-list-toggle').addClass('active');
        $('.asu-calendar-toggle').removeClass('active');
      }
      else {
        $('.asu-events-list').hide();
        $('.asu-news-load-more-btn').hide();
        $('.upcoming-title').hide();
        $('.asu-calendar-toggle').addClass('active');
        $('.asu-list-toggle').removeClass('active');
      }

      $('.asu-list-toggle').once('list-toggle', function() {
        $(this).bind('click', function(e) {
          e.preventDefault();
          $('.asu-events-list').show();
          $('.upcoming-title').show();
          $('#calendar').hide();
          $('.asu-news-load-more-btn').show();
          $('.asu-list-toggle').addClass('active');
          $('.asu-calendar-toggle').removeClass('active');
          Drupal.settings.asu_events.view_mode = 'calendar';
          // Drupal.attachBehaviors('.asu-news-load-more-btn');
          // // var throb = Throbber({
          // //     size: 20, // this will also be applied to the gif
          // //     padding: 10
          // // });
          // // throb.appendTo($('.asu-news-load-more-btn')[0]);
          // // $('.asu-news-load-more-btn canvas').css('margin-left', '7px');
          // // if(pager_total == 1) {
          // //   $('.asu-news-load-more-btn').hide();
          // // }
          // // $('.asu-news-load-more-btn').once('load-more', function() {
          // //   $(this).bind('click', function(e) {
          // //     e.preventDefault();
          // //     handle.autopager('load');
          // //     throb.start();
          // //     $('.asu-news-load-more-btn canvas').css('display', 'inline');
          // //   });
          // // });
        });
      });

      $('.asu-calendar-toggle').once('calendar-toggle', function() {
        $(this).bind('click', function(e) {
          e.preventDefault();
          $('#calendar').show();
          $('.upcoming-title').hide();
          $('.asu-events-list').hide();
          $('.asu-news-load-more-btn').hide();
          $('.asu-calendar-toggle').addClass('active');
          $('.asu-list-toggle').removeClass('active');
          Drupal.settings.asu_events.view_mode = 'full';
          // Drupal.attachBehaviors('.asu-news-load-more-btn');
        });
      });
    }
  };
})(jQuery);
