(function (RLD, $) {
  /**
   * LayoutPreviewer editor provides functionality to display, add and remove
   * layout representations across arbitrary, user-defined breakpoint limits.
   */
  RLD['LayoutPreviewer'] = (function build() {

    var plugin = 'LayoutPreviewer';
    
    function LayoutPreviewer() {
      // Ui components.
      this.options = {
        'ui': {
          'class-layout': 'rld-stepmanager',
          'class-layout-tabs': 'rld-steps'
        }
      };
      this.$editor = $();
      this.$stepSelector = $();
      this.activeLayoutStep;
      // Setup
      this.init.apply(this, arguments);
    }
    /**
     * Extend the InitClass Object.
     */
    LayoutPreviewer.prototype = new RLD.InitClass();
    /**
     * Integrate instantiation options.
     */
    LayoutPreviewer.prototype.setup = function () {
      var fn, steps;
      // Instantiate classes.
      this.stepManager = new RLD.StepManager();
      this.layoutList = new RLD.LayoutList();
      // Define topics that will pass-through.
      // -- none.
      // Transfer pass-through subscriptions.
      this.transferSubscriptions([
        this.stepManager,
        this.layoutList
      ]);
      // Register for events on the stepManager.
      fn = $.proxy(this.switchStep, this);
      this.stepManager.topic('stepActivated').subscribe(fn);
      // Assemble the editor managers and containers.
      this.$stepSelector = $('<div>', {
        'class': this.ui['class-layout']
      });
      this.$steps = $('<ul>', {
        'class': this.ui['class-layout-tabs']
      });
      this.$layouts = $('<div>', {
        'class': this.ui['class-layout-content']
      });
      // Register Layouts into the layoutList
      // For every step we'll register a layout.
      steps = this.stepList.info('items');
      // Create obects for each composite.
      for (i = 0; i < steps.length; i++) {
        // Save the composition elements into a unit.
        this.registerLayoutStep(steps[i]);
      }
      // Register a DOM ready handler.
      $(document).on('ready', $.proxy(this.injectPreviewDOM, this));
    };
    /**
     *
     */
    LayoutPreviewer.prototype.build = function () {
      // Assemble the editor fraemwork.
      this.$editor = $('<div>', {
        'class': 'rld-layout-previewer'
      })
      .append(
        this.$stepSelector
        .append(
          this.stepManager.build(this.$steps)
        )
      );
      /*this.$editor
      .delegate('button.save', 'click.ResponsiveLayoutDesigner', {'type': 'save'}, this.update); */
      return this.$editor;
    };
    /**
     *
     */
    LayoutPreviewer.prototype.switchStep = function (event, step) {
      var width, frame, $frame, fn;
      var $editor = this.$editor;
      var grid = this.gridList.getItem(step.grid['machine_name']);
      var $frame = $('.rld-previewer');
      if ($frame.length === 0) {
        var preview = $('<div>', {}).load( window.location.href, function (data, status, jqXHR) {
          var $html = $(this);
          var $head = $html.find('meta, link, title, style, script');
          var $body = $html.find('#page-wrapper');
          $head = $('<div>', {
            'html': $head
          });
          $body = $('<div>', {
            'html': $body
          });
          frame = document.createElement('iframe');
          // Hard-coded offset. This is bad bad bad. 
          frame.height = document.documentElement.clientHeight - 120;
          frame.className = 'rld-modal rld-previewer';
          document.body.appendChild(frame);
          var content = '<!DOCTYPE html><html><head>' + $head.html() + '</head><body>' + $body.html() + '</body></html>';
          
          frame.contentWindow.document.open('text/html', 'replace');
          frame.contentWindow.document.write(content);
          frame.contentWindow.document.close();
          var $frame = $('.rld-previewer');
          width = Number(step.info('size'));
          $frame.animate({
            width: width,
            left: (document.documentElement.clientWidth - width ) / 2
          });
        });
        $('.rld-previewer');
        $('<div>', {
          'class': 'rld-modal rld-modal-screen'
        })
        .css({
          'display': 'none'
        })
        .appendTo('body')
        .fadeIn();
        $('<div>', {
          'class': 'rld-modal rld-modal-close',
          'html': $('<a>', {
            'href': '#',
            'text': 'Close'
          })
          .on({
            'click': function (event) {
              // The following functions are acting globally on the page. This is bad bad bad.
              // They should only apply with the application or the editor.
              $('.rld-steps .rld-active').removeClass('rld-active');
              $('.rld-modal').fadeOut(function () {
                $(this).remove();
              });
            }
          })
        })
        .prependTo($editor);
      }
      width = Number(step.info('size'));
      $frame.animate({
        width: width,
        left: (document.documentElement.clientWidth - width ) / 2
      });
      this.topic('stepActivated').publish(step);
    };
    /**
     *
     */
    LayoutPreviewer.prototype.injectPreviewDOM = function (event) {
      var steps = this.stepList.info('items');
      var grids = this.gridList.info('items')
      var breakUpPayload = {};
      var step;
      for (step in steps) {
        if (steps.hasOwnProperty(step)) {
          // breakUpPayload[step.machine_name] = $.proxy(this.switchStep, this, step, );
        }
      }
    };
    /**
     *
     */
    LayoutPreviewer.prototype.getActiveLayout = function () {
      var activeStep = this.stepManager.info('activeStep');
      var layout;
      for (i = 0; i < this.layoutList.info('items').length; i++) {
        layout = this.layoutList.info('items')[i];
        if (layout.step.info('machine_name') === activeStep.info('machine_name')) {
          return layout;
        }
      }
    };
    /**
     *
     */
    LayoutPreviewer.prototype.buildGridUnderlay = function (columns, height) {
      var $overlay = $('<div>', {
        'class': 'rld-grid-underlay clearfix'
      });
      var cols = Number(columns);
      var fn;
      while (cols) {
        $overlay.append(
          $('<div>', {
            'class': 'rld-span_1 rld-col rld-grid-col'
          })
        );
        cols -= 1;
      }
      return $overlay;
    };
    /**
     * A layout is a set of regions, in the context of a step, laid out on a grid.
     */
    LayoutPreviewer.prototype.registerLayoutStep = function (step) {
      // Add the LayoutSteps to the LayoutList.
      this.layoutList.addItem({
        'step': step,
        'regionList': this.regionList,
        'grid': this.gridList.getItem(step.grid.info('machine_name'))
      });
      // Add the Step to the StepManager.
      this.stepManager.addItem(step);
    };

    return LayoutPreviewer;
    
  }());

}(ResponsiveLayoutDesigner, jQuery));