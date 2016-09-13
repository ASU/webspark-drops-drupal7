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
        });
      });
    }
  };
})(jQuery);
