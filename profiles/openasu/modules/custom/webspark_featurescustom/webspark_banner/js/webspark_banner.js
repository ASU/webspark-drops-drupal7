/**
 * JavaScript file for Webspark Hero module.
 *
 */

(function ($, Drupal) {
	Drupal.behaviors.webspark_banner = {
		attach: function(context, settings) {

		  $(".pane-bundle-banner").addClass( "title-banner" );
		  
		}
	};
})(jQuery, Drupal);
