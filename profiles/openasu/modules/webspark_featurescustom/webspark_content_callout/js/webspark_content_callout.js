/**
 * JavaScript file for webspark_seven admin theme.
 *
 */

(function ($, Drupal) {
	Drupal.behaviors.websparkSeven = {
		attach: function(context, settings) {

			// Show/hide the media inputs on content callouts add form
			$("select#edit-field-callout-media-und").change(function(){
				$( "select#edit-field-callout-media-und option:selected").each(function(){

					if($(this).attr("value")=="image"){
							$(".group-callout-opts .field-type-video-embed-field").hide();
							$(".group-callout-opts .field-type-image").show();
					}
					if($(this).attr("value")=="video"){
							$(".group-callout-opts .field-type-image").hide();
							$(".group-callout-opts .field-type-video-embed-field").show();
					}
				});
			}).change();

		}
	};
})(jQuery, Drupal);




