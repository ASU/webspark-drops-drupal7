(function ($) {
  Drupal.behaviors.viewsBootstrapCarousel = {
    attach: function(context, settings) {
      $(function () {
        $.each(settings.viewsBootstrap.carousel, function(id, carousel) {
          try {
            $('#views-bootstrap-carousel-' + carousel.id, context).carousel(carousel.attributes);
          }
          catch(err) {
            console.log(err);
          }
        });
      });
    }
  };
})(jQuery);
