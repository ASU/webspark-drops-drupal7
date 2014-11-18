/**
 * JavaScript file for Webspark Hero module.
 *
 */

(function ($, Drupal) {
	Drupal.behaviors.webspark_hero = {
		attach: function(context, settings) {
		  //$(".pane-bundle-hero" ).parents( ".container" ).removeClass( "container" ).addClass( "container-fluid" );
      //$(".pane-bundle-hero").parents( ".container" ).removeClass( "container" ).addClass( "container-fluid" );
		  //$( ".pane-bundle-hero" ).parents( ".row" ).addClass( "hero-bg-img" );
		  $(".pane-bundle-hero").addClass( "hero-bg-img" );
		}
	};
})(jQuery, Drupal);
