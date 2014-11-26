(function ($) {

	Drupal.behaviors.webspark_newsevents = {
		attach: function (context, settings) {			

      /** 
       * Hide image if news article doesn't have its image and is using default image.
       */
			if( $("body").hasClass("node-type-asu-news") ) {
				$(document).ready(function() {
          src = $('.field-name-field-asunews-image img').attr('src');
          if(src.indexOf("asunews_default_image.png") > -1) {
            $('.pane-node-field-asunews-image').remove();
          }
				});
			}
		 
		}  
	}

})(jQuery);
	 
	 
	 
