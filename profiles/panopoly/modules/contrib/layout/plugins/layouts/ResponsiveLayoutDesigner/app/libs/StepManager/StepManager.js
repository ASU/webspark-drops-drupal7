(function (RLD, $) {

  RLD['StepManager'] = (function () {

    var plugin = 'StepManager';

    function StepManager() {
      this.steps = [];
      this.activeStep;
      // Initialize the object.
      this.init.apply(this, arguments);
    }
    /**
     * Extend the InitClass Object.
     */
    StepManager.prototype = new RLD.InitClass();
    /**
     *
     */
    StepManager.prototype.setup = function (options) {
      // UI objects.
      this.$stepContainer = $('<div>', {});
      this.activeStep = this.activeStep || this.steps[0];
    };
    /**
     *
     */
    StepManager.prototype.build = function ($stepContainer) {
      this.$editor = $('<div>', {});
      var handler, i, step, breakpoint, size, label, id;
      this.$stepContainer = ($stepContainer.length > 0) ? $stepContainer : this.$stepContainer;
      // Clear the UI.
      this.$stepContainer.children().remove();
      // Build the list of steps.
      for (i = 0; i < this.steps.length; i++) {
        step = this.steps[i];
        breakpoint = step.info('breakpoint');
        size = step.info('size');
        label = step.info('label');
        id = 'breakpoint-' + breakpoint;
        this.$stepContainer
        .append(
          $('<li>', {
            'class': 'rld-tab'
          })
          .append(
            $('<a>', {
              'class': 'rld-link',
              'href': '#' + id,
              'text': size + 'px'
            })
            .data('RLD/Step', step)
          )
        );
      }
      // Attach behaviors.
      this.$stepContainer.delegate('a', 'click.RLD.StepManager', {'manager': this}, this.activateStep);
      // Attach the steps and layouts to the $editor and return it.
      return this.$editor
      .append(this.$stepContainer);
    };
    /**
     *
     */
    StepManager.prototype.addItem = function (step) {
      this.steps.push(step);
    };
    /**
     *
     */
    StepManager.prototype.activateStep = function (event) {
      event.preventDefault();
      var $stepLink = $(this);
      var manager = event.data.manager;
      var step = $stepLink.data('RLD/Step');
      if (step === undefined) {
        step = manager.steps[0];
      }
      manager.activeStep = step;
      manager.info('$editor').find('a').removeClass('rld-active');
      $stepLink.addClass('rld-active');
      manager.topic('stepActivated').publish(event, step);
    };
    
    return StepManager;
    
  }());
}(ResponsiveLayoutDesigner, jQuery));