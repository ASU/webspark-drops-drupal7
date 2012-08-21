(function (RLD, $) {
  
  RLD['LayoutStep'] = (function () {

    var plugin = 'LayoutStep';

    // Layout Class
    function LayoutStep() {
      this.deltaColumns = 0;
      // Initialize the object.
      this.init.apply(this, arguments);
    }
    /**
     * Extend the InitClass Object.
     */
    LayoutStep.prototype = new RLD.InitClass();
    
    LayoutStep.prototype.setup = function () {
      // Define topics that will pass-through.
      this.topic('regionOrderUpdated');
      this.topic('regionAdded');
      this.topic('regionRemoved');
      this.topic('regionResized');
      this.topic('regionResizing');
      this.topic('regionResizeStarted');
    };
    
    LayoutStep.prototype.build = function (options, items) {
      this.$editor = $('<div>', {});
      var regions = items || this.regionList.info('items');
      this.$editor.append(this.buildRows(regions).contents());
      // Bind behaviors.
      fn = $.proxy(this.sortRows, this);
      this.$editor.sortable({
        // Make a placeholder visible when dragging.
        placeholder: "ui-state-highlight",
        // When the dragging and dropping is done, save updated region
        // list in our local list.
        deactivate: fn
      });
      // Return the $editor as a jQuery object.
      return this.$editor;
    };
    
    LayoutStep.prototype.sortRows = function (event, data) {
      var regionList = [];
      var i;
      // Get the region objects in their new order.
      var $regions = data.sender.find('.rld-region');
      for (i = 0; i < $regions.length; i++) {
        regionList.push($($regions[i]).data('RLD/Region'));
      }
      this.regionList.update(regionList);
      // 
      this.topic('regionOrderUpdated').publish(this);
    };
    LayoutStep.prototype.modifyRegionBuild = function ($region) {
      var region = $region.data('RLD/Region');
      var fn;
      // Add splittrs to the regions.
      $region
      .prepend(
        $('<div>', {
          'class': 'rld-splitter rld-splitter-left'
        })
        .data('RLD/Region/Splitter-side', 'left')
      )
      .append(
        $('<div>', {
          'class': 'rld-splitter rld-splitter-right'
        })
        .data('RLD/Region/Splitter-side', 'right')
      )
      .append(
        $('<a>', {
          'class': 'rld-region-close',
          'href': '#',
          'text': 'X',
          'title': 'Close',
        })
      );
      // Region resize.
      fn = $.proxy(this.startRegionResize, this);
      $region
      .on({
        'mousedown.ResponsiveLayoutDesigner': fn
      }, '.rld-splitter', {'region': region});
      // Region remove.
      $region.on({
        'click.ResponsiveLayoutDesigner': this.removeRegion
      },'.rld-region-close', {'manager': this});
      // Return the editor as a DOM fragment.
      return $region
    };
    /**
     *
     */
    LayoutStep.prototype.startRegionResize = function (event) {
      this.$editor.sortable('disable');
      event.stopImmediatePropagation();
      var data = event.data;
      var region = data.region;
      var $region = region.info('$editor');
      var $splitter = $(event.target);
      // @todo eventually the row should be stored in state, not structure.
      var $row = $region.closest('.rld-row');
      var i, widthOffset, originalColumn;
      // Mark the region as active.
      region.info('active', true);
      // Mark the splitter active.
      $splitter.addClass('splitter-active');
      // Since the resize function will be called on mousemove, we don't want
      // to calculate the state of the row's region more than once. So we
      // pass this information into the handlers.
      // Determine if the splitter is on the left or right side of region.
      data.$row = $row;
      data.side = $splitter.data('RLD/Region/Splitter-side');
      data.width = $region.outerWidth(true);
      // Find all the regions/placeholders in this row.
      data.units = $row.find('.rld-unit').map(function (index, element) {
        return $(this).data('RLD/Region');
      });
      // Calculate the column size so regions can be snapped to grid columns.
      data.totalColumns = Number(this.grid.info('columns'));
      data.frame = Math.floor(Number(this.step.info('size')) / data.totalColumns);
      // Store the X origin of the original click.
      data.originX = event.pageX;
      // Get the column the resize started in.
      widthOffset = (data.side === 'right') ? data.width : 0;
      originalColumn = Math.floor(($region.position().left + widthOffset) / data.frame);
      data.originColumn = (data.side === 'left') ? ++originalColumn : originalColumn;
      // Calculate the left and right bounds for the resizing.
      data.rightMaxTraversal = data.totalColumns - data.originColumn;
      data.leftMaxTraversal = (data.originColumn -1) * -1;
      // Add behaviors.
      fn = $.proxy(this.resizeRegion, this);
      $(document).bind('mousemove.regionResize', data, fn);
      fn = $.proxy(this.finishRegionResize, this);
      $(document).bind('mouseup.regionResize', data, fn);
      // Call listeners.
      this.topic('regionResizeStarted').publish(this);
    };
    /**
     *
     */
    LayoutStep.prototype.resizeRegion = function (event) {
      event.stopImmediatePropagation();
      var data = event.data;
      var region = data.region;
      var bypass= false;
      // Calculate the number of grid columns the mouse has traversed.
      var columnsTraversed = Math.floor((event.pageX - data.originX) / data.frame);
      // We want regions resized from the right to resize on the trailing
      // edge of the column, not the leading edge.
      if (columnsTraversed < 0 ) {
        columnsTraversed += 1;
      }
      // Get the difference between the distance we know we've covered in previous loops,
      // and where the mouse is in this loop.
      var traversedChunk = columnsTraversed - this.deltaColumns;
      // This is the amount that the region might be changed by.
      var proposedDelta = this.deltaColumns + traversedChunk;
      // Check to see if the region needs to be sized up to the edge.
      if ((proposedDelta === data.leftMaxTraversal || proposedDelta === data.rightMaxTraversal) && proposedDelta !== 0) {
        bypass = true;
      }
      // Check to see if we are totally off the screen.
      if (proposedDelta <= data.leftMaxTraversal || proposedDelta >= data.rightMaxTraversal) {
        proposedDelta = (proposedDelta > 0) ? data.rightMaxTraversal : (proposedDelta < 0) ? data.leftMaxTraversal : proposedDelta;
      }
      // Only resize the region if the frame changes.
      if (bypass || columnsTraversed !== this.deltaColumns) {
        this.deltaColumns = proposedDelta;
        // Get an object of two regions: the one to be expanded and the one to be contracted.
        var affectedRegions = this.getAffectedRegions(region, data, traversedChunk);
        // Resize the affected regions by the amount traversed chunk of columns.
        if (affectedRegions.right) {
          affectedRegions.right.alterSpan((traversedChunk * -1), true);
        }
        if (affectedRegions.left) {
          affectedRegions.left.alterSpan(traversedChunk, true);
        }
      }
      // this.topic('regionResizing').publish(this);
    };
    /**
     *
     */
    LayoutStep.prototype.finishRegionResize = function (event) {
      this.$editor.sortable('enable');
      event.stopImmediatePropagation();
      var layout = this;
      var data = event.data;
      var region = data.region;
      var $region = region.info('$editor');
      // Perform a final resize.
      this.resizeRegion.apply(this, arguments);
      // Move the next available region up to the placeholder.
      var placeholder = this.getActivePlaceholder(data);
      if (placeholder) {
        var layout = this; // hack, hack, hack...
        var $placeholder = placeholder.info('$editor');
        var $nextRow = data.$row.next('.rld-row');
        var $candidateRegion = $nextRow.find('.rld-region:first');
        if ($candidateRegion.length > 0) {
          var size = placeholder.info('span');
          $candidateRegion.animate({
            width: 0
          });
          $candidateRegion.queue(function (next) {
            var $shiftedRegion = $candidateRegion.detach();
            var shiftedRegion = $shiftedRegion.data('RLD/Region');
            $placeholder.animate({
              width: 0
            });
            $placeholder.queue(function (next) {
              var $this = $(this);
              $this.data('RLD/Region').alterSpan(0);
              $this.removeAttr('style');
              next();
            });
            $placeholder.queue(function (next) {
              $shiftedRegion[(data.side === 'left') ? 'insertAfter' : 'insertBefore']($placeholder);
              $shiftedRegion.animate({
                'width': size * data.frame
              });
              $shiftedRegion.queue(function (next) {
                var $this = $(this);
                $this.data('RLD/Region').alterSpan(size);
                $this.removeAttr('style');
                next();
              });
              $shiftedRegion.queue(function (next) {
                var $regions = $nextRow.find('.rld-region');
                if ($regions.length === 0) {
                  $nextRow.slideUp(function () {$(this).remove()});
                }
                if ($regions.length === 1) {}
                if ($regions.length > 1) {}
                // Save any changes to regions.
                // This doesn't belong here at all, but it's what we've got for the moment.
                var r;
                var regionList = layout.regionList.info('items');
                for (r in regionList) {
                  if (regionList.hasOwnProperty(r)) {
                    // If the region already has an override, update it.
                    if ('span' in regionList[r] && regionList[r].span > 0 && regionList[r].span < data.totalColumns) {
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
                // Call listeners for this event.
                layout.topic('regionResized').publish(layout);
                next();
              });
              next();
            });
            next();
          });
        }
      }      
      // Clean up state.
      region.info('active', null);
      this.deltaColumns = 0;
      $region.find('.splitter').removeClass('splitter-active');
      $(document).unbind('.regionResize');
    }
    /**
     *
     */
    LayoutStep.prototype.removeRegion = function (event) {
      event.preventDefault();
      var $region = $(this).closest('.rld-region');
      var region = $region.data('RLD/Region');
      event.data.manager.topic('regionRemoved').publish(event, event.data.manager, region);
    };
    /**
     *
     */
    LayoutStep.prototype.getAffectedRegions = function (region, data, traversedChunk) {
      var units = data.units;
      var activeSide = (data.side === 'left') ? 'right' : 'left';
      var candidateSide = (data.side === 'left') ? 'left' : 'right';
      var regions = {};
      // Expanding and contracting checks for the active and candidate regions.
      var isActiveContracting = ((activeSide === 'left' && traversedChunk < 0) || (activeSide === 'right' && traversedChunk > 0));
      var isActiveExpanding = ((activeSide === 'left' && traversedChunk > 0) || (activeSide === 'right' && traversedChunk < 0));
      var isCandidateContracting = ((candidateSide === 'left' && traversedChunk < 0) || (candidateSide === 'right' && traversedChunk > 0));
      var isCandidateExpanding = ((candidateSide === 'left' && traversedChunk > 0) || (candidateSide === 'right' && traversedChunk < 0));
      var i, index, candidate;
      // Assume nothing is changing.
      regions[activeSide] = null;
      regions[candidateSide] = null;
      // Don't allow the active region to contract smaller than one column or expand more than the total number of columns.
      if ((region.columns === 1 && isActiveContracting) || ((region.columns === data.totalColumns) && isActiveExpanding)) {
        return regions;
      }
      // If the active region can be altered, then determine which unit will be the passive unit.
      // This is a zero-sum game. Someone has to make room or take room.
      // Get the index of the active region from the units.
      index = this.getActiveRegionIndex(units);
      // Try candidate units until one can be manipulated.
      for (i = (data.side === 'left') ? (index - 1) : (index + 1); i >= 0 && i < units.length; (data.side === 'left') ? i-- : i++) {
        // The try-catch is here to make sure we don't access an index of units
        // that doesn't exist and blow up the application.
        try {
          candidate = units[i];
          // If the candidate is a placeholder, just use it.
          if (candidate.type === 'placeholder') {
            regions[candidateSide] = candidate;
            break;
          }
          // Don't allow the candidate region to contract smaller than one column or expand more than the total number of columns.
          if ((candidate.columns === 1 && isCandidateContracting) || ((candidate.columns === data.totalColumns) && isCandidateExpanding)) {
            return regions;
          }
          // The candidate can be manipulated.
          regions[candidateSide] = candidate;
          break;
        }
        catch (error) {
          regions[candidateSide] = null;
        }
      }
      // The region can be resized. We should have a candidate as well.
      regions[activeSide] = region;
      return regions;
    }
    /**
     *
     */
    LayoutStep.prototype.getActivePlaceholder = function (data) {
      var units = data.units;
      var activeRegionIndex = this.getActiveRegionIndex(units);
      var placeHolderIndex = (activeRegionIndex === 1 && data.side === 'left') ? 0 : (units.length - 1);
      var placeholder = units[placeHolderIndex];
      if (placeholder.type === 'placeholder') {
        if (units[placeHolderIndex].span > 0) {
          return units[placeHolderIndex];
        }
      }
      return null;
    };
    /**
     *
     */
    LayoutStep.prototype.getActiveRegion = function (units) {
      return units[this.getActiveRegionIndex(units)];
    };
    /**
     *
     */
    LayoutStep.prototype.getActiveRegionIndex = function (units) {
      var i;
      for (i = 0; i < units.length; i++) {
        if ('active' in units[i] && units[i].active) {
          return i;
        }
      }
      return null;
    };
    /**
     *
     */
    LayoutStep.prototype.buildRows = function (regions, options) {
      var $container = $('<div>', {});
      var step = this.step;
      var grid = this.grid;
      var count = 0;
      // The size of a region may be overridden in this step.
      var regionOverrides = step.info('regionList').info('items');
      var $row;
      var i, k, fn, region, $region, span;
      // Build rows and regions.
      for (i = 0; i < regions.length; i++) {
        var override = undefined;
        var classes = ['rld-col rld-unit'];
        // Start a new row if the spans in the previous row are sufficient or exceed the allotment.
        if ((count === 0) || (count >= grid.columns)) {
          // Append a placeholder to the end of a row.
          if (count >= grid.columns) {
            $row.append(
              new RLD.Region({
                'type': 'placeholder'
              })
              .build({
                'classes': classes
              })
            );
          }
          // Create a new row.
          $row = $('<div>', {
            'class': 'rld-row clearfix'
          })
          // Append a placeholder to the start of the row.
          .append(
            new RLD.Region({
              'type': 'placeholder'
            })
            .build({
              'classes': classes
            })
          )
          // Append the row to the editor.
          .appendTo($container);
          // Restart the row span count.
          count = 0;
        }
        region = regions[i];
        // If this step has region overrides, get the override that matches this region, if any.
        if (regionOverrides.length > 0) {
          for (k = 0; k < regionOverrides.length; k++) {         
            if (region.info('machine_name') === regionOverrides[k]['machine_name']) {
              override = regionOverrides[k];
              break;
            }
          }
        }
        // If an override for this region exists, use it.
        if (override !== undefined) {
          span = override.columns;
          count += override.columns;
        }
        // Otherwise the region is assumed to be full width.
        else {
          span = grid.columns;
          count = grid.columns;
        }
        // Build the region.
        $region = regions[i].build({
          'classes': classes
        });
        // Alter its span.
        $region
        .data('RLD/Region')
        // Get the Region object and update its span.
        .alterSpan(span)
        // Append it to the row.
        $row.append(
          this.modifyRegionBuild($region)
        );
        // Append a placeholder to the end of a row if this is the last item processed.
        if (i === (regions.length - 1)) {
          $row.append(
            new RLD.Region({
              'type': 'placeholder'
            })
            .build({
              'classes': classes
            })
          );
        }
      }
      return $container;
    };
    /**
     *
     */
    LayoutStep.prototype.insertRows = function (items, location) {
      var $editor = this.$editor;
      // Get a well-formed region, ready to insert into a layout.
      var $rows = this.buildRows(items).contents();
      // Insert the wrapped region into the editor.
      $rows.hide()
      [(location !== undefined && location === 'top') ? 'prependTo' : 'appendTo']($editor);
      // Reveal the wrapped regions in a pretty way.
      $editor
      .find($rows)
      .slideDown(500);
    };
    return LayoutStep;
    
  }());
}(ResponsiveLayoutDesigner, jQuery));
