(function ($) {

	Drupal.behaviors.webspark_newsevents = {
		attach: function (context, settings) {			

      /* ASU News node */
			if( $("body").hasClass("node-type-asu-news") ) {
				$(document).ready(function() {
          
          /** 
           * Hide image if news article doesn't have its image and is using default image.
           */
          src = $('.field-name-field-asunews-image img').attr('src');
          if(src.indexOf("asunews_default_image.png") > -1) {
            $('.pane-node-field-asunews-image').remove();
          }
          
          /** 
           * Change right side bar to be col-md-4. The rest will be col-md-8.
           */
          $("div.bryant-flipped-content-region").removeClass("col-md-9");
          $("div.bryant-flipped-content-region").addClass("col-md-8");
          
          $("div.bryant-flipped-sidebar-region").removeClass("col-md-3");
          $("div.bryant-flipped-sidebar-region").addClass("col-md-4");
				});
			}
		 
		}  
	}

})(jQuery);
	 
	 
	 
