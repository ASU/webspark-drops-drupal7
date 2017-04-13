/**
 * ASU Enhanced Maps Form
 *
 * ASU Enhanced Map JS
 * - Enables campus selection bar at the top of map
 *
 * @author Colton Testamarck ( colt@asu.edu )
 */
(function ($) {
    Drupal.behaviors.asu_maps_enhanced_form = {
        attach: function (context, settings) {

            if (settings.asu_maps_enhanced_form != null) {
                var configs = settings.asu_maps_enhanced_form;
                var data = JSON.parse(configs.tree);
                var tree_div = $(configs.form_field_id);
                var map_items = [];
                var map_field = $('#map_items_hidden textarea');

                if (configs.map_items != null) {
                    map_items = JSON.parse(configs.map_items);
                }

                //data needs to be array at top level
                data = [data];

                if (tree_div.length > 0) {
                    // Build Department Hierarchy tree list for display in block
                    tree_div.tree({
                        closedIcon: $('<span tabindex="0" class="fa fa-plus-square"></span>'),
                        openedIcon: $('<span tabindex="0" class="fa fa-minus-square"></span>'),
                        data: data,
                        // First level open
                        autoOpen: 0,
                        selectable: true,
                        keyboardSupport: false,
                        // Assign dept_id attribute to each tree <li>
                        onCreateLi: function (node, $li) {

                            var id = null;

                            if(node.hasOwnProperty('mrkId')) {
                                id = node.mrkId;
                            } else if (node.hasOwnProperty('catId')) {
                                id = node.catId;
                            }

                            if (id != null) {
                                $li.attr('id', id);
                            }

                            //$li.attr('dept_id', node.dept_id);
                            $li.find('.glyphicon').attr('name', node.name);

                            if (id != 0) {
                                if (!node.hasChildren()) {
                                    $li.find('.jqtree-element').prepend('<span tabindex="0" class="jqtree-folder-icon fa fa-bookmark" name="' + node.name + '"></span>');
                                }

                                $li.find('.jqtree-element').append('<input class="asu-maps-enhanced-check" type="checkbox"></input>');
                            }
                        }
                    });
                }


                for (var i = 0; i < map_items.length; i++) {
                    var item = map_items[i];

                    if (item.hasOwnProperty('mrkId')) {
                        $('#' + item.mrkId + '>div .asu-maps-enhanced-check').click();
                    } else if (item.hasOwnProperty('catId') && !item.hasOwnProperty('mrkId')) {
                        $('#' + item.catId + '>div .asu-maps-enhanced-check').click();
                    }
                }

                $('.asu-maps-enhanced-check').change(function() {
                    var parent = $(this).closest('li');
                    var node = tree_div.tree('getNodeByHtmlElement', parent);

                    if ($(this).is(':checked')) {

                        if (asu_maps_enhanced_containsObject(node, map_items) == -1) {
                            asu_maps_enhanced_insertObject(node, map_items);
                            map_field.val(JSON.stringify(map_items));
                        }

                    } else {
                        var index = asu_maps_enhanced_containsObject(node, map_items);

                        if (index != -1) {
                            map_items.splice(index, 1);
                            map_field.val(JSON.stringify(map_items));
                        }
                    }
                });

                $(document).on('input', '#map-height-field input', function (event) {

                    var data = $(this).val();

                    if (!asu_maps_enhanced_isInt(data)) {
                        $(this).val('');
                    } else {
                        if ($(this).val() < 425 || $(this).val() > 1100) {
                            $('.height-valid').remove();
                            $('<span class="height-valid invalid-style" >Invalid</span>').insertAfter('#map-height-field input');
                        } else {
                            $('.height-valid').remove();
                            $('<span class="height-valid valid-style" >Valid</span>').insertAfter('#map-height-field input');
                        }
                    }
                });
            }
        }
    }
}(jQuery));


function asu_maps_enhanced_isInt(value) {
    return !isNaN(value) &&
        parseInt(Number(value)) == value && !isNaN(parseInt(value, 10));
}

function asu_maps_enhanced_containsObject(obj, list) {

    for (i = 0; i < list.length; i++) {

        if (obj.hasOwnProperty('mrkId')) {
            if (obj.mrkId == list[i].mrkId) {
                return i;
            }
        } else if (obj.hasOwnProperty('catId') && !list[i].hasOwnProperty('mrkId')) {
            if (obj.catId == list[i].catId) {
                return i;
            }
        }
    }

    return -1;
}

function asu_maps_enhanced_insertObject(obj, list) {

    var newnode = {};
    var thetype = asu_maps_enhanced_get_type(obj);

    newnode.item_type = thetype;

    if (obj.hasOwnProperty('catId')) {
        newnode.catId = obj.catId;
    }

    if (obj.hasOwnProperty('description')) {
        newnode.description = obj.description;
    }

    if (obj.hasOwnProperty('keywords')) {
        newnode.keywords = obj.keywords;
    }

    if (obj.hasOwnProperty('name')) {
        newnode.name = obj.name;
    }

    if (obj.hasOwnProperty('labels')) {
        newnode.labels = obj.labels;
    }

    if (obj.hasOwnProperty('lat')) {
        newnode.lat = obj.lat;
    }

    if (obj.hasOwnProperty('lng')) {
        newnode.lng = obj.lng;
    }

    if (obj.hasOwnProperty('mrkId')) {
        newnode.mrkId = obj.mrkId;
    }

    if (obj.hasOwnProperty('id')) {
        newnode.id = obj.id;
    }

    list.push(newnode);
}

function asu_maps_enhanced_get_type(obj) {
    if (obj.hasOwnProperty('mrkId')) {
        return 'location';
    } else {
        return 'category';
    }
}
