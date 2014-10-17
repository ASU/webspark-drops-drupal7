/**
 * JavaScript file for theme.
 *
 */

(function ($, Drupal) {
	Drupal.behaviors.asu_standard = {
		attach: function(context, settings) {

		$( "#asu_mobile_hdr" ).wrapInner("<div class='asu_mobile_hdr_wrapper'></div>");			
		$( "#asu_mobile_menu" ).wrapInner("<div class='asu_mobile_menu_wrapper'></div>");		

		}
	};
	
	// Override mobile table function in panopoly_widgets.js
	Drupal.behaviors.panopolyWidgetTables.attach = function (context, settings) {
		// Leave empty to override
	};
	
})(jQuery, Drupal);
