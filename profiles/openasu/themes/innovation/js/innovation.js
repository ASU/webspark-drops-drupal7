/**
 * JavaScript file for theme.
 *
 */
(function ($, Drupal) {
	Drupal.behaviors.asu_standard = {
		attach: function(context, settings) {

			$( "#asu_mobile_hdr" ).wrapInner("<div class='asu_mobile_hdr_wrapper'></div>");			
			$( "#asu_mobile_menu" ).wrapInner("<div class='asu_mobile_menu_wrapper'></div>");	
		
			// Add header to Ctools Modal menu to improve UI
			$( ".panels-add-content-modal .panels-categories-box" ).after( "<h2 class=\"widget-list\">More Content Panes</h2>" );

		}
	};

	$('#ASUNavMenu').affix({offset:{top:$('#ASUNavMenu').offset().top}});
	$(window).on('resize',function(){
		var w = $(window).width();
		if(w > 929 && !$('#ASUNavMenu').hasClass('navmenu affix-top')){
			$('#ASUNavMenu').affix({offset:{top:$('#ASUNavMenu').offset().top}});
		}else if(w < 930){
			$('#ASUNavMenu').removeClass('affix');
		}
	});
	//Used to determine if RFI form is on the page.
	// Go to div if it is go to URL if it isn't #block-asu-rfi-asu-rfi-form-block
	$('#take-me-to-rfi').on('click',function(e){
		e.preventDefault();
		if($('#block-asu-rfi-asu-rfi-form-block').length==0){
			location.href='https://students.asu.edu/typeofstudent';
		}
	});
	//Fixes all anchor tags with hashes
	$('a').on('click',function(e){
		var $this = $(this);
		var url = $this.attr('href');
		var cls = $this.attr('class');
		if (!$this.hasClass('accordion-toggle') && !$this.closest('ui-tabs').length == 0 && $this.closest('nav-tabs').length == 0) {
			if (url.slice(0,1)=='#') {
				e.preventDefault();
				smoothScroll(url);
			}
		}
	});
	//Fixes onload scroll to the hash that originates from page URL
	if (location.hash) {
		smoothScroll(location.hash);
	}
	//Function to calculate current offset with respect to scroll position
	function offsetTop() {
		var hh = $('#header').height();
		var sp = $(document).scrollTop();
		var fx = $('#ASUNavMenu').height();
		if(sp < hh) {
			fx = fx*2;
		}
		fx+=15;
		return fx;
	}
	//Actually does the hash smooth scrolling
	function smoothScroll(hash) {
		$('html,body').animate({scrollTop: $(hash).offset().top - offsetTop()},'slow');
		window.location.hash = hash;
	}

	// Override mobile table function in panopoly_widgets.js
	Drupal.behaviors.panopolyWidgetTables.attach = function (context, settings) {
		// Leave empty to override
	};
})(jQuery, Drupal);
