jQuery(document).ready(function ($) {

	$( ".megafoot" ).parents( ".container" ).removeClass( "container" ).addClass( "container-fluid" );
	$( ".megafoot" ).children( ".row" ).attr( "style", "max-width: 1170px; margin: auto;");


	if ($(window).innerWidth() >= 768) {
	    $('.big-foot-nav').not('.in').addClass('in');
	    $('.big-foot-head').removeAttr("data-toggle");
	} else {
		$('.big-foot-nav').removeClass('in');
		$('.big-foot-head span').addClass('caret');
		$('.megafoot .row .space-bot-md').addClass('megafoot-border');

	}

	$(window).resize(function() {
  		if ($(window).innerWidth() >= 768) {
			$('.big-foot-nav').not('.in').addClass('in');
			$('.big-foot-head').removeAttr("data-toggle");
			$('.big-foot-head span').removeClass('caret');
			$('.megafoot .row .space-bot-md').removeClass('megafoot-border');

		} else {
			$('.big-foot-nav').removeClass('in');
			$('.big-foot-head').attr("data-toggle","collapse");
			$('.big-foot-head span').addClass('caret');
			$('.megafoot .row .space-bot-md').addClass('megafoot-border');
		}

	});


});
