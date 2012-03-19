
(function($) {

Drupal.behaviors.PanelViewModes = {
  attach: function (context) {
    if ($('#edit-layout-remove').length > 0) {
      $('#edit-layout-remove').click(function() {
        return confirm(Drupal.t('Are you sure you want to remove the layout ?'));
        return false;
      });
    }
  }
};

})(jQuery);