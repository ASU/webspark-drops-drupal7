(function (RLD, $) {
  // Temp location.
  RLD['Step'] = (function () {

    var plugin = 'Step';
    
    function Step() {
      this.options = {
        'breakpoint': '0'
      };
      // Initialize the object.
      this.init.apply(this, arguments);
    }
    /**
     * Extend the InitClass Object.
     */
    Step.prototype = new RLD.InitClass();
    /**
     *
     */
    Step.prototype.setup = function () {
      this.topic('stepRegionOverridden');
    }
    /**
     *
     */
    Step.prototype.supplantRegion = function (region) {
      var items = this.regionList.info('items');
      var i, index;
      for (i = 0; i < items.length; i++) {
        if (items[i].machine_name === region.machine_name) {
          index = i;
          break;
        }
      }
      if (index !== undefined) {
        this.regionList.info('items').splice(index, 1, region);
      }
      else {
        this.regionList.addItem(region);
      }
      this.topic('stepRegionOverridden').publish(region); 
    };
    /**
     *
     */
    Step.prototype.removeRegion = function (region) {
      
    };

    return Step;
    
  }());
}(ResponsiveLayoutDesigner, jQuery));