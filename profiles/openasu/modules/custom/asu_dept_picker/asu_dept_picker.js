/**
 * Provides an ASU department picker widget.
 */
(function ($, AsuDeptPicker) {
  Drupal.behaviors.asu_dept_picker = {
    attach: function(context, settings) {
      // setup any asu-dept-picker fields
      $('.asu-dept-picker:not([data-reactid])', context).each(function() {
        var delta = $(this).attr('data-delta');
        var config = settings.asu_dept_picker[delta];
        var input = $(this).siblings('input[data-delta="'+delta+'"]');

        config.onChange = function(data) {

          // save config options on the dept object
          if (data.hasOwnProperty('items')) {
              for (var i = 0; i < data.items.length; i++) {
                   var deptid = data.items[i].dept_id;
                   data.items[i].options = data.options[deptid];
              }
          }

          input.val(JSON.stringify(data));
        };

        config.key = delta;

        var asu_dept_picker = React.createElement(AsuDeptPicker, config);
        ReactDOM.render(asu_dept_picker, this);
      });
    }
  }
})(jQuery, AsuDeptPicker);
