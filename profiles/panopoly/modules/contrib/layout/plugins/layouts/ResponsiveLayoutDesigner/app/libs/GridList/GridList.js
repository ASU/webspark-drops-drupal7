(function (RLD, $) {
  // Temp location.
  RLD['GridList'] = (function () {

    var plugin = 'GridList';

    function GridList() {
      this.items = [];
      // Initialize the object.
      this.init.apply(this, arguments);
    }
    /**
     * Extend the InitClass Object.
     */
    GridList.prototype = new RLD.InitClass();
    /**
     *
     */
    GridList.prototype.setup = function () {
      // Process list items.
      if ('grids' in this) {
        this.processList(this.grids);
        delete this.grids;
      }
      else {
        this.log('[RLD | ' + plugin + '] The list has no items at setup.');
      }
    };
    /**
     *
     */
    GridList.prototype.build = function () {
      return this.$editor;
    };
    /**
     *
     */
    GridList.prototype.processList = function (items) {
      var i;
      for (i = 0; i < items.length; i++) {
        this.items.push(new RLD.Grid({
          'machine_name': items[i].machine_name,
          'columns': items[i].columns,
          'classes': items[i].classes
        }));
      }
    };
    /**
     *
     */
    GridList.prototype.update = function (type, list) {
      this.items = type;
    };

    return GridList;
    
  }());
}(ResponsiveLayoutDesigner, jQuery));
