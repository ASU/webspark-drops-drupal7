/**
 * JavaScript file for Webspark Hero module.
 *
 */

(function ($, Drupal) {
	Drupal.behaviors.webspark_hero = {
		attach: function(context, settings) {
		
		  $(".pane-bundle-hero").wrapInner( "<div class='hero-wrapper'></div>");
		  
		}
	};
})(jQuery, Drupal);
