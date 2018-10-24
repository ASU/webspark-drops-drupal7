(function ($) {
  Drupal.behaviors.asu_events_button_fix = {
    attach: function (context, settings) {
      $(document).ready(function () {
        $event_cta_text = $('div.field-name-field-asuevent-ticketing-url a').text();
        $event_cta_url = $('div.field-name-field-asuevent-ticketing-url a').attr('href');
        if ($event_cta_text == $event_cta_url) {
          $('div.field-name-field-asuevent-ticketing-url a').text("Learn more");
        }
      })
    }
  };
})(jQuery);