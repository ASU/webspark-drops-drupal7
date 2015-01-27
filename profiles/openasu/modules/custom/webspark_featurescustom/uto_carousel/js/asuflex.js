(function ($, Drupal) {
	Drupal.behaviors.uto_carousel = {
		attach: function(context, settings) {
		$( ".pane-bundle-asu-spotlight" ).parents( ".container" ).removeClass( "container" ).addClass( "container-fluid" );
		$( ".pane-bundle-asu-spotlight" ).parents( ".column" ).attr( "style", "width: 100%;");

		}
	};
})(jQuery, Drupal);


