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
	// Override mobile table function in panopoly_widgets.js
	Drupal.behaviors.panopolyWidgetTables.attach = function (context, settings) {
		// Leave empty to override
	};
})(jQuery, Drupal);
