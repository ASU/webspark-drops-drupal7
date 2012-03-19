
(function($) {

Drupal.DisplaySuite = Drupal.DisplaySuite || {};
Drupal.DisplaySuite.fieldopened = '';
Drupal.DisplaySuite.layout_original = '';

/**
 * Layout change.
 */
Drupal.behaviors.layoutChange = {
  attach: function (context) {
    if ($('#edit-additional-settings-layout').length > 0 && $('#edit-additional-settings-ds-layout-apply').length > 0) {
      Drupal.DisplaySuite.layout_original = $('#edit-additional-settings-layout').val();
      $('#edit-additional-settings-layout').change(function() {
        layout = $('#edit-additional-settings-layout').val();
        if (layout != '' && Drupal.DisplaySuite.layout_original != '' && Drupal.DisplaySuite.layout_original != layout) {
          entity_type = $('input[name="ds_entity_type"]').val();
          bundle = $('input[name="ds_bundle"]').val();
          view_mode = $('input[name="ds_view_mode"]').val();
          args = entity_type + '/' + bundle + '/' + view_mode + '/' + layout;
          $('#edit-additional-settings-ds-layout-apply').attr('disabled', '');
          $('#edit-additional-settings-ds-layout-apply').removeClass('form-button-disabled');
        }
        else {
          $('#edit-additional-settings-ds-layout-apply').attr('disabled', 'disabled');
          $('#edit-additional-settings-ds-layout-apply').addClass('form-button-disabled');
        }
      });

      // Bind on apply button.
      $('#edit-additional-settings-ds-layout-apply').click(function() {
        window.location = $('input[name="ds_source"]').val() + 'admin/structure/ds/change-layout/' + args + '?destination=' + $('input[name="ds_destination"]').val();
        return false;
      });
    }
  }
};

/**
 * Ctools selection content.
 */
Drupal.behaviors.CToolsSelection = {
  attach: function (context) {
    if ($('#ctools-content-selection').length > 0) {
      $('#ctools-content-selection .section-link').click(function() {
        $('#ctools-content-selection .content').hide();
        container = $(this).attr('id') + '-container';
        $('#' + container).show();
        return false;
      });
    }
  }
};

/**
 * Save the Dynamic field content configuration.
 */
$.fn.dsCtoolsContentConfiguration = function (configuration) {
  $(this[0]).val(configuration);
}

/**
 * Update the select content text.
 */
$.fn.dsCtoolsContentUpdate = function () {
  $(this[0]).html(Drupal.t('Click update to save the configuration'));
}

/**
 * Field template.
 */
Drupal.behaviors.settingsToggle = {
  attach: function (context) {

    // Bind on click.
    $(context).find('#field-display-overview').find('.ft-link').once('ds-ft').bind('click', function(e) {

      e.preventDefault();

      var fieldTemplate = $(this).next();

      // Bind update button.
      fieldTemplate.find('.ft-update').click(function() {

        // Close the settings.
        var settings = $(this).parents('.field-template');
        settings.hide();
        $(this).parents('tr').removeClass('field-formatter-settings-editing');

        // Check the label.
        var row = $(this).parents('tr');
        var label = $('.label-change', settings).val();
        var original = $('.original-label', row).val();
        if (label != '') {
          new_label = label + ' (Original: ' + original + ')<input type="hidden" class="original-label" value="' + original + '">';
          $('.field-label-row', row).html(new_label);
        }
        else {
          new_label = original + '<input type="hidden" class="original-label" value="' + original + '">';
          $('.field-label-row', row).html(new_label);
        }
        return false;
      });

      // Bind on field template select button.
      fieldTemplate.find('.ds-extras-field-template').change(function() {
        ds_show_expert_settings(this);
      })

      $(this).parents('tr').siblings().removeClass('field-formatter-settings-editing');
      $(this).parents('tr').addClass('field-formatter-settings-editing');

      var settings = $(this).siblings('.field-template');
      if (Drupal.DisplaySuite.fieldopened != '' && Drupal.DisplaySuite.fieldopened != settings.attr('id')) {
        $('#' + Drupal.DisplaySuite.fieldopened).hide();
      }

      if (settings.is(':visible')) {
        $(this).parents('tr').removeClass('field-formatter-settings-editing');
        settings.hide();
      }
      else {
        // Slide down.
        ds_show_expert_settings(settings, true);
        settings.slideDown('normal');
      }
      // Store the opened setting.
      Drupal.DisplaySuite.fieldopened = settings.attr('id');
    });

    // Show / hide settings on field template form.
    function ds_show_expert_settings(element, open) {
      if (undefined == open) {
        var field = $(element).parents('.field-template');
      }
      else {
        field = element;
      }
      ft = $('.ds-extras-field-template', field).val();
      if (ft == 'theme_ds_field_expert') {
        // Show second and third label.
        if ($('.lb .form-item:nth-child(1)', field).is(':visible')) {
          $('.lb .form-item:nth-child(2), .lb .form-item:nth-child(3)', field).show();
        }
        // Remove margin from update button.
        $('.ft-update', field).css({'margin-top': '-10px'});
        // Show wrappers.
        $('.ow, .fis, .fi', field).show();
      }
      else {
        // Hide second and third label.
        $('.lb .form-item:nth-child(2), .lb .form-item:nth-child(3)', field).hide();
        // Add margin on update button.
        $('.ft-update', field).css({'margin-top': '10px'});
        // Hide wrappers.
        $('.ow, .fis, .fi', field).hide();
      }

      // Colon.
      if (ft == 'theme_field' || ft == 'theme_ds_field_reset') {
        $('.colon-checkbox', field).parent().hide();
      }
      else if ($('.lb .form-item:nth-child(1)', field).is(':visible')) {
        $('.colon-checkbox', field).parent().show();
      }

      // Styles.
      if (ft != 'theme_ds_field_expert' && ft != 'theme_ds_field_reset') {
        $('.field-styles', field).show();
      }
      else {
        $('.field-styles', field).hide();
      }
    }

    $('.label-change').change(function() {
      var field = $(this).parents('tr');
      if ($('.field-template', field).length > 0) {
        ft = $('.ds-extras-field-template', field).val();
        if (ft == 'theme_field' || ft == 'theme_ds_field_reset') {
          $('.colon-checkbox', field).parent().hide();
        }
      }
    });
  }
};

/**
 * Save the page after saving a new field.
 */
$.fn.dsRefreshDisplayTable = function () {
  $('#edit-submit').click();
}

/**
 * Row handlers for the 'Manage display' screen.
 */
Drupal.fieldUIDisplayOverview = Drupal.fieldUIDisplayOverview || {};

Drupal.fieldUIDisplayOverview.ds = function (row, data) {

  this.row = row;
  this.name = data.name;
  this.region = data.region;
  this.tableDrag = data.tableDrag;

  this.$regionSelect = $('select.ds-field-region', row);
  this.$regionSelect.change(Drupal.fieldUIOverview.onChange);

  return this;
};

Drupal.fieldUIDisplayOverview.ds.prototype = {

  /**
   * Returns the region corresponding to the current form values of the row.
   */
  getRegion: function () {
    return this.$regionSelect.val();
  },

  /**
   * Reacts to a row being changed regions.
   *
   * This function is called when the row is moved to a different region, as a
   * result of either :
   * - a drag-and-drop action
   * - user input in one of the form elements watched by the
   *   Drupal.fieldUIOverview.onChange change listener.
   *
   * @param region
   *   The name of the new region for the row.
   * @return
   *   A hash object indicating which rows should be AJAX-updated as a result
   *   of the change, in the format expected by
   *   Drupal.displayOverview.AJAXRefreshRows().
   */
  regionChange: function (region) {

     // Replace dashes with underscores.
     region = region.replace('-', '_');

     // Set the region of the select list.
     this.$regionSelect.val(region);

     // Prepare rows to be refreshed in the form.
     var refreshRows = {};
     refreshRows[this.name] = this.$regionSelect.get(0);

     // If a row is handled by field_group module, loop through the children.
     if ($(this.row).hasClass('field-group') && $.isFunction(Drupal.fieldUIDisplayOverview.group.prototype.regionChangeFields)) {
       Drupal.fieldUIDisplayOverview.group.prototype.regionChangeFields(region, this, refreshRows);
     }

     return refreshRows;
  }
};

})(jQuery);
