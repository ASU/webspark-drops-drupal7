(function ($, Drupal) {
	Drupal.behaviors.asu_spotlight = {
		attach: function(context, settings) {
		$( ".pane-bundle-asu-spotlight" ).parents( ".container" ).removeClass( "container" ).addClass( "container-fluid" );
		$( ".pane-bundle-asu-spotlight" ).parents( ".column" ).attr( "style", "width: 100%;");
		$( ".pane-bundle-asu-spotlight" ).parents( ".col-md-12" ).attr( "style", "width: 100%;");
		}
	};
})(jQuery, Drupal);
