(function (RLD, $) {
  // Temp location.
  RLD['StepList'] = (function () {

    var plugin = 'StepList';

    function StepList() {
      this.items = [];
      // Initialize the object.
      this.init.apply(this, arguments);
    }
    /**
     * Extend the InitClass Object.
     */
    StepList.prototype = new RLD.InitClass();
    /**
     *
     */
    StepList.prototype.setup = function () {
      // Process list items.
      if ('steps' in this) {
        this.processList(this.steps);
        delete this.steps;
      }
      else {
        this.log('[RLD | ' + plugin + '] The list has no items at setup.');
      }
      // Calculate the step sizes.
      this.processStepSizes();
      
    };
    /**
     *
     */
     StepList.prototype.processList = function (items) {
      var i;
      for (i = 0; i < items.length; i++) {
        this.items.push(new RLD.Step({
          'label': items[i].label,
          'machine_name': items[i].machine_name,
          'breakpoint': items[i].breakpoint,
          'regionList': new RLD.RegionList({
            'regions': items[i].regions
          }),
          'grid': new RLD.Grid({
            'machine_name': items[i].grid
          })
        }));
      }
    };
    /**
     *
     */
    StepList.prototype.update = function (type, list) {
      this.stepItems = type;
      this.topic('stepOrderUpdated').publish(this);
    };
    /**
     * @Todo, the steps will need to be sorted by breakpoint
     * before the sizes can be calculated.
     */
    StepList.prototype.processStepSizes = function () {
      var i;
      if ('items' in this) {
        var i, k, step, breakMin, breakMax, size;
        for (i = 0; i < this.items.length; i++) {
          step = this.items[i];
          breakMin = Number(step.info('breakpoint')) || 0;
          if (this.items[i + 1] !== undefined) {
            breakMax = Number(this.items[i + 1].info('breakpoint'));
            size = breakMax - breakMin;
            // Add all of the previous breakpoint sizes to this step size.
            if (i > 0) {
              size += this.items[i - 1].info('size');
            }
          }
          else {
            // The largest step should be at least 600. If it exceeds 600, it needs
            // an uppder bound, so we add 100 to its breakpoint size.
            size = (breakMin < 600) ? 600 : breakMin + 250;
          }
          this.items[i].info('size', size);
        }
      }
    };

    return StepList;
    
  }());
}(ResponsiveLayoutDesigner, jQuery));
