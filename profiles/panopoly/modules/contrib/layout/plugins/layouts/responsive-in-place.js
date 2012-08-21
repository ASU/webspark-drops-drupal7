/**
 * Ultimately I'd like to combine responsive-admin.js with this file, but
 * I'm not quite sure how to do that yet.
 */

(function ($, ResponsiveLayoutDesigner, JSON) {

  /**
   * Responsive layout previewer class.
   */  
  var ResponsiveLayoutPreview = (function () {
    
    function ResponsiveLayoutPreview () {
      // Init the class.
      this.init.apply(this, arguments);
    }
    ResponsiveLayoutPreview.prototype.init = function () {
      // Build a list of grids for the editor.
      var gridList = [];
      var stepList = [];
      var index;
      for (index in Drupal.settings.layout.grids) {
        gridList.push({
          'machine_name': Drupal.settings.layout.grids[index].name,
          'columns': Drupal.settings.layout.grids[index].columns,
          'classes': ['rld-container-' + Drupal.settings.layout.grids[index].name]
        });
      }
    
      // Build a list of breakpoints for the editor.
      for (index in Drupal.settings.layout.breakpoints) {
        stepList.push({
          'label': Drupal.settings.layout.breakpoints[index].admin_title,
          'machine_name': Drupal.settings.layout.breakpoints[index].name,
          'breakpoint': parseInt(Drupal.settings.layout.breakpoints[index].width),
          'grid': Drupal.settings.layout.breakpoints[index].grid_name
        });
      }
    
      // Instantiate a layout designer.
      this.editor = new ResponsiveLayoutDesigner({
        'steps': stepList,
        'grids': gridList,
      });
      // Save a reference to the editor to the DOM for development.
      window.RLDEditor = this.editor;
    };
    
    return ResponsiveLayoutPreview;
  }());
  /**
   * Attach the Drupal Behavior.
   */
  Drupal.behaviors.responsiveLayoutPreview = {
    attach: function(context) {
      // Get an instance of a previewer.
      Drupal.responsiveLayoutPreview = new ResponsiveLayoutPreview(context);
      // Initialize responsive layout previewer.
      var $previewer = Drupal.responsiveLayoutPreview
      .editor
      .layoutPreviewer
      .build();
      $('#navbar-drawer').once('rld-layout-previewer',function (index, element) {
        $(this).append($previewer);
      });
    }
  };
})(jQuery, ResponsiveLayoutDesigner, JSON);
