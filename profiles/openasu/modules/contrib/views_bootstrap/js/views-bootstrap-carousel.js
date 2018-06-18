(function ($) {
  Drupal.behaviors.viewsBootstrapCarousel = {
    attach: function(context, settings) {
      $.each(settings.viewsBootstrap.carousel, function(id, carousel) {
        try {
          // Does the view have more than 1 item?
          // If not, hide the indicators and controls.
          if ($('#views-bootstrap-carousel-' + carousel.id + ' .carousel-inner .item').length > 1) {
            $('#views-bootstrap-carousel-' + carousel.id, context).carousel(carousel.attributes);
          }
          else {
            $('#views-bootstrap-carousel-' + carousel.id, context).find('.carousel-indicators').hide();
            $('#views-bootstrap-carousel-' + carousel.id, context).find('.carousel-control').hide();
          }
        }
        catch(err) {
          console.log(err);
        }
      });
    }
  };
})(jQuery);
