(function($) {
  Drupal.behaviors.addtocal = {
    attach: function(context) {
      // Handle toggle event to position the menu properly
      jQuery('.addtocal').toggle(function(e) {
        var offset = jQuery(this).position();
        var button_id = jQuery(this).attr('id');
        var $menu = jQuery('#' + button_id + '_menu');
        
        $menu.show();

        $menu.css({
          'top': offset.top + 20,
          'left': offset.left
        });
        
        //Clicking outside the menu will hide it
        jQuery(document).bind('click', function() {
          $menu.hide();
        });
      }, function() {
        $menu.hide();
      });
    }
  } 
})(jQuery);