(function (RLD, $) {
  // Temp location.
  RLD['LayoutList'] = (function () {

    var plugin = 'LayoutList';

    function LayoutList() {
      this.items = [];
      // Initialize the object.
      this.init.apply(this, arguments);
    }
    /**
     * Extend the InitClass Object.
     */
    LayoutList.prototype = new RLD.InitClass();
    /**
     *
     */
    LayoutList.prototype.setup = function () {
      // Process list items.
      if ('layouts' in this) {
        this.processList(this.layouts);
        delete this.layouts;
      }
      else {
        this.log('[RLD | ' + plugin + '] The list has no items at setup.');
      }
    };
    /**
     *
     */
    LayoutList.prototype.processList = function (items) {
      // The broadcaster just pipes events through.
      var handlers = {};
      var newSet = [];
      var i, layoutStep, listener, fn;
      // Create obects for each composite.
      for (i = 0; i < items.length; i++) {
        // Save the layout elements into a unit.
        layoutStep = new RLD.LayoutStep({
          'regionList': items[i].regionList,
          'step': items[i].step,
          'grid': items[i].grid
        });
        // Pust the layoutStep into the list.
        this.items.push(layoutStep);
        newSet.push(layoutStep);
        
      }
      // Register pass-through topics.
      this.transferSubscriptions(this.items);
      // Return the items that were added.
      return newSet;
    };
    /**
     *
     */
    LayoutList.prototype.addItem = function (layout) {
      var items = this.processList([layout]);
      return items;
    }
    /**
     *
     */
    LayoutList.prototype.update = function (type, list) {
      this.items = list;
    };

    return LayoutList;
    
  }());
}(ResponsiveLayoutDesigner, jQuery));
