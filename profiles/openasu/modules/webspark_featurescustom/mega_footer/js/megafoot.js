(function ($, Drupal) {
	Drupal.behaviors.webspark_mega_footer = {
		attach: function(context, settings) {

				if ($(window).innerWidth() >= 768) {
						$('.big-foot-nav').not('.in').addClass('in');
						$('.big-foot-head').removeAttr("data-toggle");
				} else {
					$('.big-foot-nav').removeClass('in');
				}

				$(window).resize(function() {
						if ($(window).innerWidth() >= 768) {
								$('.big-foot-nav').not('.in').addClass('in');
								$('.big-foot-head').removeAttr("data-toggle");
					} else {
								$('.big-foot-nav').removeClass('in');
								$('.big-foot-head').attr("data-toggle","collapse");
					}

				});
		}
	};
})   (jQuery, Drupal);
