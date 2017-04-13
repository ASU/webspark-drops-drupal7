/**
* JavaScript file for Webspark Hero module.
*
*/

(function ($, Drupal) {
	Drupal.behaviors.webspark_hero = {
		attach: function(context, settings) {

			$(".pane-bundle-hero").wrapInner( "<div class='hero-wrapper'></div>");
			$(".pane-bundle-hero").addClass( "hero-bg-img");



			$(function() {
					$('.form-item-field-webspark-hero-bgimg-und-0 :file').change(function() {

							if (this.files && this.files[0]) {
									var reader = new FileReader();
									reader.onload = imageIsLoaded;
									reader.readAsDataURL(this.files[0]);
							}
					});
			});

				//adds background image to preview
			function imageIsLoaded(e){
					$("#panopoly-form-widget-preview").before("<style> .hero-bg-img {background-image: url("+e.target.result+");}</style>");

			};




		}
	};
})(jQuery, Drupal);
