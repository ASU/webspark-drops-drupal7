/**
 * Webspark Panels Styles: Custom Styles
 */

(function ($, Drupal) {
	Drupal.behaviors.customstyles = {
		attach: function(context, settings) {

			// Adding row-full and bgcolor CSS classes for rows with 2 or more columns
			var a = document.getElementsByClassName('js-lightgraybg');
			doIt(a,'lightgraybg');
			var b = document.getElementsByClassName('js-darkgraybg');
			doIt(b,'darkgraybg');
			function doIt(a,color){
				for(i = 0; i < a.length; i++){
					if(!$(a[i]).closest('.row').hasClass('row-full')){
						$(a[i]).closest('.row').addClass('row-full '+color).wrapInner('<div class="pane-content"></div>');
					}
				}
			}

		}
	};
})(jQuery, Drupal);

