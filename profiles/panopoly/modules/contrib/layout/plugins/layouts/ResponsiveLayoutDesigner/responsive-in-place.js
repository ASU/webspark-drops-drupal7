(function ($, ResponsiveLayoutDesigner, JSON) {

/**
 * Safe logging function.
 */
function log (message, type) {
  if ('console' in window) {
    var type = type || 'log';
    if (type in console) {
      console[type](message);
    }
  }
}

Drupal.responsiveLayout = new Drupal.responsiveLayout();

Drupal.behaviors.responsiveLayoutPreview = {
  attach: function(context) {
    // Initialize responsive layout editor.
    Drupal.responsiveLayout.init();
  }
}

/**
 * Initialize responsive layout editor.
 */
Drupal.responsiveLayout.init = function() {
  // Initialize region list and per-breakpoint columns.
  var regionList = [];
  var layoutConfig = JSON.parse($('#edit-layout-settings-layout-responsive-regions').val());
  for (var regionIndex in layoutConfig.regions) {
    regionList.push({
      'machine_name': layoutConfig.regions[regionIndex].name,
      'label': layoutConfig.regions[regionIndex].admin_title,
    });
  }
  // Regions that are available for this layout to use.
  var availableRegionList = [
    {
      'machine_name': 'triptych_a',
      'label': 'Triptych Left'
    },
    {
      'machine_name': 'triptych_b',
      'label': 'Triptych Center'
    },
    {
      'machine_name': 'triptych_c',
      'label': 'Triptych Right'
    }
  ];

  // Build a list of grids for the editor.
  var gridList = [];
  for (var gridIndex in Drupal.settings.responsiveLayout.defaultGrids) {
    gridList.push({
      'machine_name': Drupal.settings.responsiveLayout.defaultGrids[gridIndex].name,
      'columns': Drupal.settings.responsiveLayout.defaultGrids[gridIndex].columns,
      'classes': ['rld-container-' + Drupal.settings.responsiveLayout.defaultGrids[gridIndex].name],
    });
  }

  // Build a list of breakpoints for the editor.
  var breakpointList = [];
  for (var breakpointIndex in Drupal.settings.responsiveLayout.defaultBreakpoints) {
    var overrideList = [];
    var name = Drupal.settings.responsiveLayout.defaultBreakpoints[breakpointIndex].name;
    for (var overrideIndex in layoutConfig.overrides[name]) {
      overrideList.push({
        'machine_name': layoutConfig.overrides[name][overrideIndex].name,
        'columns': layoutConfig.overrides[name][overrideIndex].columns,
      });
    }
    breakpointList.push({
      'label': Drupal.settings.responsiveLayout.defaultBreakpoints[breakpointIndex].admin_title,
      'machine_name': name,
      // @todo: make sure that em/px based breakpoints work alike.
      'breakpoint': parseInt(Drupal.settings.responsiveLayout.defaultBreakpoints[breakpointIndex].width),
      'grid': Drupal.settings.responsiveLayout.defaultBreakpoints[breakpointIndex].grid_name,
      'regions': overrideList,
    });
  }

  // Instantiate a layout designer.
  this.editor = new ResponsiveLayoutDesigner({
    'regions': {
      'active': regionList,
      'available': availableRegionList
    },
    'steps': breakpointList,
    'grids': gridList,
  });

  // var save = $.proxy(this.save, this);

  // Register event listeners. Just update our representation of the layout
  // for any event for now.
  this.editor.topic('regionOrderUpdated').subscribe(Drupal.responsiveLayout.recordState);
  this.editor.topic('regionAdded').subscribe(Drupal.responsiveLayout.recordState);
  this.editor.topic('regionRemoved').subscribe(Drupal.responsiveLayout.recordState);
  this.editor.topic('regionHidden').subscribe(Drupal.responsiveLayout.recordState);
  this.editor.topic('regionResized').subscribe(Drupal.responsiveLayout.recordState);

  // Insert the editor in the DOM.
  this.editor.build().appendTo('#responsive-layout-designer');

  // Save a reference to the editor to the DOM for development.
  window.RLDEditor = this.editor;
}

/**
 * Respond to app updates.
 *
 * This is generic so we don't have to have a callback for each event we'd like
 * to track during prototyping.
 */
Drupal.responsiveLayout.recordState = function(event) {

  var layoutSettings = {'regions' : [], 'overrides': {}};
  // Get a dump of the state of the application.
  var layoutManager = Drupal.responsiveLayout.editor.snapshot();
  var regionList = layoutManager.info('regionList');
  var regions = regionList.info('items');
  for (var i = 0; i < regions.length; i++) {
    layoutSettings.regions.push({'name': regions[i].info('machine_name'), 'admin_title': regions[i].info('label')});
  }

  var stepList = layoutManager.info('stepList');
  var steps = stepList.info('items');
  for (var i = 0; i < steps.length; i++) {
    layoutSettings.overrides[steps[i].machine_name] = [];
    if (steps[i].regionList.items.length) {
      for (var r = 0; r < steps[i].regionList.items.length; r++) {
        layoutSettings.overrides[steps[i].machine_name].push({
          'name': steps[i].regionList.items[r].machine_name,
          'columns': steps[i].regionList.items[r].columns
        });
      }
    }
  }

  // The value of the textarea is saved to the server when the whole layout is
  // saved. We do not have live AJAX communication because the interaction is
  // built with rapid changes in mind (ordering, adding new regions, resizing),
  // and we don't have a live preview needed given the useful builder view
  // itself.
  $('#edit-layout-settings-layout-responsive-regions').val(JSON.stringify(layoutSettings));
}

})(jQuery, ResponsiveLayoutDesigner, JSON);
