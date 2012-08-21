(function ($) {

Drupal.behaviors.gridBuilder = {
  attach: function(context) {
    // Initialize responsive layout editor.
    Drupal.gridBuilder.init();
  }
}

Drupal.gridBuilder = Drupal.gridBuilder || {};

/**
 * Initialize gridbuilder behavior.
 */
Drupal.gridBuilder.init = function() {
  // Set up container for grid demonstration.
  $('form').parent().append('<div id="griddemonstrator"></div>');
  $('input[name="grid_type"]').change(Drupal.gridBuilder.typeChange);

  Drupal.gridBuilder.gridType = $('input[name="grid_type"]:checked').val() == 1 ? '%' : 'px';
  if (Drupal.gridBuilder.gridType == '%') {
    // Fake a sensible previous value for fixed grid.
    Drupal.gridBuilder.prevValue = {
      'fullWidth': '960',
      'columns': '12',
      'paddingWidth': '20',
      'gutterWidth': '10',
    };
  }
  else {
    // Fake a sensible previous value for fluid grid.
    Drupal.gridBuilder.prevValue = {
      'fullWidth': '100',
      'columns': '12',
      'paddingWidth': '1.5',
      'gutterWidth': '2',
    };
  }

  // When any of the parameter values change, rebuild the demo.
  $('#edit-width').change(Drupal.gridBuilder.reBuildDemonstration);
  $('#edit-columns').change(Drupal.gridBuilder.reBuildDemonstration);
  $('#edit-padding-width').change(Drupal.gridBuilder.reBuildDemonstration);
  $('#edit-gutter-width').change(Drupal.gridBuilder.reBuildDemonstration);

  // Build the initial version of the demo.
  Drupal.gridBuilder.reBuildDemonstration();
}

/**
 * React to grid type changes.
 */
Drupal.gridBuilder.typeChange = function(event) {
  // Remember previous value, and restore the earlier value for this size.
  var prevValue = {
    'fullWidth': $('#edit-width').val(),
    'columns': $('#edit-columns').val(),
    'paddingWidth': $('#edit-padding-width').val(),
    'gutterWidth': $('#edit-gutter-width').val(),
  };
  $('#edit-width').val(Drupal.gridBuilder.prevValue.fullWidth);
  $('#edit-columns').val(Drupal.gridBuilder.prevValue.columns);
  $('#edit-padding-width').val(Drupal.gridBuilder.prevValue.paddingWidth);
  $('#edit-gutter-width').val(Drupal.gridBuilder.prevValue.gutterWidth);
  Drupal.gridBuilder.prevValue = prevValue;

  var newVal = 'px';
  if ($(this).val() == 1) {
    // User selected fluid layout, switch to % based sizes.
    newVal = '%';
  }
  Drupal.gridBuilder.gridType = newVal;

  // Switch the suffix helper field to proper value.
  $('.form-item-width .field-suffix, .form-item-padding-width .field-suffix, .form-item-gutter-width .field-suffix').html(newVal);

  // Rebuild our demonstration grid.
  Drupal.gridBuilder.reBuildDemonstration();
}

Drupal.gridBuilder.reBuildDemonstration = function() {
  // Retrieve all numeric values. All of them should be ints.
  var width = '100';
  if (Drupal.gridBuilder.gridType == 'px') {
    var width = parseInt($('#edit-width').val());
  }
  var columns = parseInt($('#edit-columns').val());
  var paddingWidth = parseInt($('#edit-padding-width').val());
  var gutterWidth = parseInt($('#edit-gutter-width').val());

  // Compute column widths.
  var coloumnWidth = (width - ((columns - 1) * gutterWidth)) / columns;
  var innerWidth = coloumnWidth - (paddingWidth * 2);

  // Add CSS style generated for this setup.
  var columnHTML =
    '<style type="text/css"> #griddemonstrator .col { ' +
    'width: ' + coloumnWidth + Drupal.gridBuilder.gridType + '; '+
    'margin-left: ' + gutterWidth + Drupal.gridBuilder.gridType + '; ' +
    'padding: 0 ' + paddingWidth + Drupal.gridBuilder.gridType + '; } ';

  if (Drupal.gridBuilder.gridType == '%') {
    // Use 960px as a sensible demonstration method for the fluid grid.
    width = '960px';
  }
  else {
    width += Drupal.gridBuilder.gridType;
  }
  columnHTML += '#griddemonstrator { width: ' + width + '; } </style>';

  // Add number of columns as needed.
  for (var i = 0; i < columns; i++) {
    columnHTML += '<div class="col' + (i == 0 ? ' first' : '') + '"><div class="inner"></div></div>';
  }

  $('#griddemonstrator').html(columnHTML);
}

})(jQuery);
