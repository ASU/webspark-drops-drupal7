(function (RLD, $) {
  /**
   * LayoutManager editor provides functionality to display, add and remove
   * layout representations across arbitrary, user-defined breakpoint limits.
   */
  RLD['LayoutManager'] = (function build() {

    var plugin = 'LayoutManager';

    function LayoutManager() {
      // Ui components.
      this.options = {
        'ui': {
          'class-layout': 'rld-stepmanager',
          'class-layout-tabs': 'rld-steps',
          'class-layout-content': 'rld-layouts'
        }
      };
      this.$editor = $();
      this.$stepSelector = $();
      this.$steps = $();
      this.$layouts = $();
      this.activeLayoutStep;
      // Setup
      this.init.apply(this, arguments);
    }
    /**
     * Extend the InitClass Object.
     */
    LayoutManager.prototype = new RLD.InitClass();
    /**
     * Integrate instantiation options.
     */
    LayoutManager.prototype.setup = function () {
      var fn, steps;
      // Instantiate classes.
      this.stepManager = new RLD.StepManager();
      this.layoutList = new RLD.LayoutList();
      // Define topics that will pass-through.
      this.topic('regionOrderUpdated');
      this.topic('layoutSaved');
      this.topic('regionResized');
      this.topic('regionResizing');
      this.topic('regionResizeStarted');
      // Transfer pass-through subscriptions.
      this.transferSubscriptions([
        this.stepManager,
        this.regionList,
        this.layoutList
      ]);
      // Register for events on the stepManager.
      fn = $.proxy(this.switchStep, this);
      this.stepManager.topic('stepActivated').subscribe(fn);
      // Register for events on the regionList.
      fn = $.proxy(this.insertRegion, this);
      this.regionList.topic('regionAdded').subscribe(fn);
      fn = $.proxy(this.removeRegion, this);
      this.regionList.topic('regionRemoved').subscribe(fn);
      // Register for events on the layoutList
      fn = $.proxy(this.requestRegionRemove, this);
      this.layoutList.topic('regionRemoved').subscribe(fn);
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
    };
    /**
     *
     */
    LayoutManager.prototype.build = function () {
      // Assemble the editor fraemwork.
      this.$editor = $('<div>', {
        'class': 'rld-layout-manager'
      })
      .append(
        this.$stepSelector
        .append(
          this.stepManager.build(this.$steps)
        )
      )
      .append(
        this.$layouts
        .append(
          $('<div>', {
            'class': 'rld-screen clearfix',
          })
        )
      );
      /*this.$editor
      .delegate('button.save', 'click.ResponsiveLayoutDesigner', {'type': 'save'}, this.update); */
      return this.$editor;
    };
    /**
     * A layout is a set of regions, in the context of a step, laid out on a grid.
     */
    LayoutManager.prototype.registerLayoutStep = function (step) {
      // Add the LayoutSteps to the LayoutList.
      this.layoutList.addItem({
        'step': step,
        'regionList': this.regionList,
        'grid': this.gridList.getItem(step.grid.info('machine_name'))
      });
      // Add the Step to the StepManager.
      this.stepManager.addItem(step);
    };
    /**
     *
     */
    LayoutManager.prototype.switchStep = function (event, step) {
      var args = arguments;
      var id = this.stepManager.info('activeStep').info('breakpoint');
      var $screen = this.$layouts.find('.rld-screen');
      var $layout = $('<div>', {
        'class': 'rld-layout'
      });
      var layout = this.getActiveLayout();
      var i, grid, gridColumns, gridClasses;
      // Clear out the current screen.
      $screen.children('.rld-layout').hide(0, function () {
        $(this).remove();
      });
      grid = layout.info('grid');
      gridColumns = grid.info('columns');
      gridClasses = grid.info('classes') || [];
      if (gridClasses.length > 0) {
        $screen.addClass();
      }
      $screen.animate({
        width: layout.step.info('size')
      });
      // Append the frame to the screen.
      $screen
      .append(
        $layout
        .empty()
        .addClass('rld-container-' + gridColumns)
        .append(this.buildAddRegionButton('top'))
        .append(this.buildGridUnderlay(gridColumns))
        .append(layout.build())
        .append(this.buildAddRegionButton('bottom'))
      );

      this.topic('stepActivated').publish(step);
    };
    /**
     *
     */
    LayoutManager.prototype.getActiveLayout = function () {
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
    LayoutManager.prototype.buildGridUnderlay = function (columns, height) {
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
     *
     */
    LayoutManager.prototype.buildAddRegionButton = function (location) {
      var handler = $.proxy(this.addRegionHandler, this);
      var $controls = $('<div>', {
        'class': 'rld-layoutstep-controls' + ' ' + location
      })
      .append(
        $('<button>', {
          'text': 'Add region to ' + location
        })
        .bind('click', {'location': location}, handler)
      );
      return $controls;
    };
    /**
     *
     */
    LayoutManager.prototype.addRegionHandler = function (event) {
      event.preventDefault();
      var regionList = this.regionList;
      this.candidateRegionName = '';
      this.candidateRegionMachineName = '';
      // Dialog pieces.
      var $input = $('<input>', {
        'type': 'text'
      });
      var $machineName = $('<div>', {
        'text': '',
        'class': 'rld-description'
      });
      var $availableRegionSelectbox = $('<select>', {
        'name': 'available-region-select'
      })
      .append(
        $('<option>', {
          'text': 'No selection',
          'value': 'null',
          'selected': 'selected'
        })
      );
      // Populate the available regions select box with a list of regions.
      var availableRegions = this.availableRegionList.info('items');
      var i;
      for (i = 0; i < availableRegions.length; i++) {
        $('<option>', {
          'text': availableRegions[i].label || 'No label',
          'value': availableRegions[i].machine_name
        })
        .appendTo($availableRegionSelectbox);
      }
      // Machine name checking callback.
      var machineNameCheck = $.proxy(this.regionList.guaranteeMachineName, this.regionList);
      // Machine name writing callback.
      var machineNamePrint = $.proxy(function machineNamePrintProxy(checker, $input, $display, event) {
        var candidate = this.candidateRegionName = $input.val() || '';
        var machine_name = candidate.replace(/\s+/g, '_').toLowerCase();
        // Confine the machine name to 24 characters.
        if (machine_name.length > 24) {
          machine_name = machine_name.slice(0, 24);
        }
        this.candidateRegionMachineName = machine_name;
        var isUnique = checker(machine_name);
        if (isUnique) {
          $display
          .text(machine_name)
          .css({
            'color': 'black'
          });
        }
        else {
          $display
          .text(machine_name)
          .css({
            'color': 'red'
          });
        }
      }, this, machineNameCheck, $input, $machineName);
      // Create and insert the dialog.
      var $dialog = $('<div>', {
        'class': 'rld-dialog'
      });
      if (availableRegions.length > 0) {
        $dialog
        .append($('<label>', {
          'text': 'Existing region'
        }))
        .append($availableRegionSelectbox);
      };
      $dialog
      .append($('<label>', {
        'text': 'New region'
      }))
      .append($input)
      .append($machineName)
      .on({
        'keydown': RLD.Utils.keyManager,
        'keyup': machineNamePrint
      },
      'input',
      {
        'callback': machineNamePrint,
        'pattern': /^[_]*[A-Za-z0-9\_\-\+\s]*$/
      })
      .dialog({
        'title': 'Add a region',
        'resizable': true,
        'modal': true
      });
      // This is a touch circular, but we need the callback to have the context of the application,
      // not the dialog box.
      // Create the dialog callbacks.
      var buttons = {};
      var saveCallback = $.Callbacks();
      var save = $.proxy(this.requestRegionAdd, this, event.data.location, $dialog);
      // This here is expected to be the div#dialog, which it will be
      // when the cancel function is called by the dialog.
      var cancel = function () {
        $(this).dialog('destroy');
      };
      saveCallback.add(save);
      saveCallback.add(cancel);
      buttons['Save'] = saveCallback.fire;
      buttons['Cancel'] = cancel;
      $dialog.dialog('option', 'buttons', buttons);
    };
    /**
     *
     */
    LayoutManager.prototype.requestRegionAdd = function (location, $dialog, event) {
      // If an available region is selected, add it.
      var region;
      var $selectedAvailableRegion = $dialog.find('[name="available-region-select"]').find('option').filter(':selected');
      if ($selectedAvailableRegion.length > 0 && $selectedAvailableRegion.val() !== 'null') {
        var region = this.availableRegionList.getItem($selectedAvailableRegion.val());
        this.regionList.insertItem({
          'machine_name': region.machine_name,
          'label': region.label
        }, location);
        // Remove the region from the list of available regions.
        this.availableRegionList.removeItem(region);
        return; // This isn't the best interaction. It's just stub code for now.
      }
      // this.availableRegionList.removeItem(region.machine_name);
      // If a new region is named, add it.
      this.regionList.insertItem({
        'machine_name': this.candidateRegionMachineName,
        'label': this.candidateRegionName
      }, location);
    };
    /**
     *
     */
    LayoutManager.prototype.insertRegion = function (event, updatedRegionList, newRegionItems, location) {
      this.getActiveLayout().insertRows(newRegionItems, location);
      // Publish the regionAdded topic.
      this.topic('regionAdded').publish(event, this);
    };
    /**
     *
     */
    LayoutManager.prototype.requestRegionRemove = function (event, layoutStep, region) {
      // Remove the item from the regionList.
      this.regionList.removeItem(region);
      // Add the region to the list of available regions.
      this.availableRegionList.addItem(region);
    };
    /**
     *
     */
    LayoutManager.prototype.removeRegion = function (event, region) {
      var $region = region.info('$editor');
      var $prev = $region.prev('.rld-region');
      var $next = $region.next('.rld-region');
      var span = region.info('span');
      var activeStep = this.stepManager.info('activeStep');
      var layoutManager = this;
      var layout = this.getActiveLayout();
      var passiveRegion, replacementRegion;
      // If region has no siblings, hide row. Otherwise, hide region.
      if ($prev.length === 0 && $next.length === 0) {
        $region.closest('.rld-row').slideUp(function () {
          $(this).remove();
        });
      }
      else {
        $region.slideUp(function () {
          $(this).remove();
          if ($prev.length > 0) {
            passiveRegion = $prev.data('RLD/Region');
          }
          else if ($next.length > 0) {
            passiveRegion = $next.data('RLD/Region');
          }
          if (passiveRegion !== undefined) {
            span = passiveRegion.alterSpan(span, true);
            // Save any changes to regions.
            // This doesn't belong here at all, but it's what we've got for the moment.
            var r;
            var regionList = layout.regionList.info('items');
            for (r in regionList) {
              if (regionList.hasOwnProperty(r)) {
                // If the region already has an override, update it.
                if ('span' in regionList[r] && regionList[r].span > 0) {
                  var item = layout.step.regionList.getItem(regionList[r].info('machine_name'))
                  if (item) {
                    item.alterColumns(regionList[r].span);
                  }
                  // If the region doesn't have an override yet, create one. This can't be a reference to the
                  // canonical regionList regions, it needs to be a new object.
                  else {
                    var temp = regionList[r].snapshot();
                    temp.columns = temp.span;
                    layout.step.regionList.addItem(temp);
                  }
                }
              }
            }
          }
          layoutManager.topic('regionRemoved').publish(event, layoutManager);
        });
      }
    };
    /**
     *
     */
    LayoutManager.prototype.hideRegion = function (event) {
      this.topic('regionHidden').publish(event, this);
    };

    return LayoutManager;

  }());

}(ResponsiveLayoutDesigner, jQuery));