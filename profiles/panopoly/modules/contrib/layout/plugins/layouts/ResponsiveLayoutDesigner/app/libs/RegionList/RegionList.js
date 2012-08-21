(function (RLD, $) {
  // Temp location.
  RLD['RegionList'] = (function () {

    var plugin = 'RegionList';

    function RegionList() {
      this.items = [];
      // Initialize the object.
      this.init.apply(this, arguments);
    }
    /**
     * Extend the InitClass Object.
     *
     * Options passed into the constructor are assigned as
     * properties of the instance.
     */
    RegionList.prototype = new RLD.InitClass();
    /**
     * Called by the InitClass prototype.
     */
    RegionList.prototype.setup = function () {
      // Format the regions.
      if ('regions' in this) {
        this.processList(this.regions);
        delete this.regions;
      }
      else {
        this.log('[RLD | RegionList] The RegionList instance has no Regions at setup.');
      }
    };
    /**
     *
     */
    RegionList.prototype.processList = function (items, location) {
      var newSet = [];
      var i, item, region;
      for (i = 0; i < items.length; i++) {
        item = items[i];
        // Check if this item is already an item.
        if ('init' in item && typeof item['init'] === 'function') {
          region = item;
        }
        else {
          region = new RLD.Region({
            'label': ('label' in item) ? item['label'] : 'No label',
            'machine_name': ('machine_name' in item) ? item['machine_name'] : 'no_machine_name',
            'classes': ('classes' in item) ? item['classes'] : [],
            'columns': ('columns' in item) ? item['columns'] : null
          });
        };
        // Add the new region to the list.
        this.items[(location !== undefined && location === 'top') ? 'unshift' : 'push'](region);
        newSet.push(region);
      }
      // Transfer pass-through subscriptions.
      this.transferSubscriptions(this.items);
      // Return the items that were added.
      return newSet;
    };
    /**
     * @todo, this method needs better argument type handling. It could
     * be either an array or an object.
     *
     * @todo this should be a private method.
     */
    RegionList.prototype.addItem = function (items, location) {
      if (typeof items === 'object' && !('length' in items)) {
        var items = [items];
      }
      return this.processList(items, location)
    };
    /**
     * This is public method, an interface for this.addItem().
     *
     * @todo, this method needs better argument type handling. It could
     * be either an array or an object.
     */
    RegionList.prototype.insertItem = function (item, location) {
      var newItems = this.addItem(item, location);
      this.topic('regionAdded').publish(this.items, newItems, location);
    };
    /**
     *
     */
    RegionList.prototype.removeItem = function (region) {
      var items = this.items;
      var i;
      for (i = 0; i < items.length; i++) {
        if (items[i].machine_name === region.machine_name) {
          this.items.splice(i, 1);
        }
      }
      this.topic('regionRemoved').publish(region);
    };
    /**
     *
     */
    RegionList.prototype.update = function (type, list) {
      this.items = type;
    };
    /**
     *
     */
    RegionList.prototype.guaranteeMachineName = function (name) {
      var regions = this.items;
      var i;
      for (i = 0; i < regions.length; i++) {
        if (regions[i].machine_name === name) {
          return false;
        }
      }
      return true;
    };

    return RegionList;
    
  }());
}(ResponsiveLayoutDesigner, jQuery));
