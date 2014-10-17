/**
 * JavaScript file for Webspark Panels Styles module.
 *
 */

(function ($, Drupal) {
	Drupal.behaviors.customstyles = {
		attach: function(context, settings) {
		
		/* Gray background colors on rows */
		$( ".js-lightgraybg" ).parents( ".container" ).removeClass( "container" ).addClass( "container-fluid" );
		if(!$( ".js-lightgraybg" ).parents( "div" ).hasClass( "fullbgcolor" )) {
			$( ".js-lightgraybg" ).parents( ".row" ).addClass( "bg-lightgray" ).wrapInner("<div class='col-md-12 fullbgcolor'><div class='row'></div></div>");			
		}

		$( ".js-darkgraybg" ).parents( ".container" ).removeClass( "container" ).addClass( "container-fluid" );
		if(!$( ".js-darkgraybg" ).parents( "div" ).hasClass( "fullbgcolor" )) {
			$( ".js-darkgraybg" ).parents( ".row" ).addClass( "bg-darkgray" ).wrapInner("<div class='col-md-12 fullbgcolor'><div class='row'></div></div>");			
		}
		
		/* Padding on rows */
		$( ".js-paddingabove" ).parents( ".section > .container > .row, .section > .container-fluid > .row" ).addClass( "row-padding-top" );
		$( ".js-paddingbelow" ).parents( ".section > .container > .row, .section > .container-fluid > .row" ).addClass( "row-padding-bottom" );
		$( ".js-remove2above" ).parents( ".section > .container > .row, .section > .container-fluid > .row" ).addClass( "remove-2-above" );
		$( ".js-remove6above" ).parents( ".section > .container > .row, .section > .container-fluid > .row" ).addClass( "remove-6-above" );
		$( ".js-remove2below" ).parents( ".section > .container > .row, .section > .container-fluid > .row" ).addClass( "remove-2-below" );
		$( ".js-remove6below" ).parents( ".section > .container > .row, .section > .container-fluid > .row" ).addClass( "remove-6-below" );
		
		}
	};
})(jQuery, Drupal);