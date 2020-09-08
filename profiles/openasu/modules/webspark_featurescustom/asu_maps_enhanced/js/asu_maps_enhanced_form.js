/**
 * ASU Enhanced Maps Form
 *
 * ASU Enhanced Map JS
 * - Enables campus selection bar at the top of map
 *
 * @author Colton Testamarck ( colt@asu.edu )
 */
(function($, React, ReactDOM, AsuGisFeaturePicker) {
  Drupal.behaviors.asu_maps_enhanced_form = {
    attach: function(context, settings) {
      if (settings.asu_maps_enhanced_form != null) {
        var configs = settings.asu_maps_enhanced_form;
        var form = document.getElementById(configs.form_field_id);
        var map_items = configs.map_items;
        var saved = {};

        // stringify the saved items to
        if (Array.isArray(map_items) && map_items.length > 0 && map_items[0].hasOwnProperty('parent')) {
          saved = map_items[0];
        }

        var props = {
          layers: configs.tree,
          onChange: function(val) {
            var text = document.querySelector('#asu_map_enhanced textarea');
            text.value = '[' + val + ']';
          },
          selected: saved
        };


        if (form) {
          ReactDOM.render(React.createElement(AsuGisFeaturePicker, props), form);
        }
      }
    }
  };
})(jQuery, React, ReactDOM, AsuGisFeaturePicker);
