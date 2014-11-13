/**
 * JavaScript file for Webspark banner module.
 *
 */

(function ($, Drupal) {
	Drupal.behaviors.webspark_banner = {
		attach: function(context, settings) {

		//$( ".pane-bundle-banner" ).parents( ".container" ).removeClass( "container" ).addClass( "container-fluid" );
		$( ".pane-bundle-banner" ).addClass( "title-banner" );

		}
	};
})(jQuery, Drupal);
