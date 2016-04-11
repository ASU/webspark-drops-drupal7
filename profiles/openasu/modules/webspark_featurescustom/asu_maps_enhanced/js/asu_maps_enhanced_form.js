/**
 * ASU Enhanced Maps Form
 *
 * ASU Enhanced Map JS
 * - Enables campus selection bar at the top of map
 *
 * @author Colton Testamarck ( colt@asu.edu )
 */
(function ($) {
    Drupal.behaviors.asu_maps_enhanced = {
        attach: function (context, settings) {
            //document.domain = 'asu.edu';
            var map_defaults = {
                campus: "TEMPE",
                display_campus_select: "NO",
                map_height: "650",
                name: "maps_enhanced_settings"
            };

            $(document).on('input', '#map-height-field input', function (event) {

                var data = $(this).val();
                var map_field = $('#map_items_hidden input');
                var map_items = JSON.parse(map_field.val());

                if (!asu_maps_enhanced_isInt(data)) {

                    $(this).val('');

                    if (map_items.length == 0 || map_items[0].name != 'maps_enhanced_settings') {
                        map_items[0] = map_defaults;
                        map_field.val(JSON.stringify(map_items));
                    } else {
                        map_items[0].map_height = "650";
                        map_field.val(JSON.stringify(map_items));
                    }
                } else {
                    if ($(this).val() < 425 || $(this).val() > 1100) {
                        $('.height-valid').remove();
                        $('<span class="height-valid invalid-style" >Invalid</span>').insertAfter('#map-height-field input');
                    } else {
                        $('.height-valid').remove();
                        $('<span class="height-valid valid-style" >Valid</span>').insertAfter('#map-height-field input');

                        if (map_items.length == 0 || map_items[0].name != 'maps_enhanced_settings') {
                            map_defaults.map_height = $(this.val());
                            map_items[0] = map_defaults;
                            map_field.val(JSON.stringify(map_items));
                        } else {
                            map_items[0].map_height = $(this).val();
                            map_field.val(JSON.stringify(map_items));
                        }
                    }
                }
            });
        }
    }
}(jQuery));


function asu_maps_enhanced_isInt(value) {
    return !isNaN(value) &&
        parseInt(Number(value)) == value && !isNaN(parseInt(value, 10));
}
