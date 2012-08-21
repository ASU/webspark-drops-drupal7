(function (RLD, $) {

  RLD['Grid'] = (function () {

    var plugin = 'Grid';
    
    function Grid() {
      // Initialize the object.
      this.init.apply(this, arguments);
    }
    /**
     * Extend the InitClass Object.
     */
    Grid.prototype = new RLD.InitClass();
    /**
     *
     */
    Grid.prototype.setup = function () {
      
    };
    
    return Grid;
    
  }());
}(ResponsiveLayoutDesigner, jQuery));