/**
 * ASU Local Directory module
 * Department Hierarchy Block JavaScript
 *
 * Provides AJAX behavior, pagination, modal, and sort for Department block
 *
 * @author Colton Testamarck (colt@asu.edu)
 * @author Robert Jenkins ( rjenkins@eaglecrk.com )
 * @author Michael Samuelson ( mlsamuel@asu.edu / mlsamuelson@gmail.com )
 * @author Sebastian Nievas ( snievas@asu.edu )
 */

(function ($) {
    Drupal.behaviors.asu_isearch_dept_tree = {
        attach: function (context, settings) {

            if (settings.hasOwnProperty('asu_isearch_dept_tree')) {

                settings = settings.asu_isearch_dept_tree;

                var top_nid = null;
                var department = 'ASU';
                var whole_tree = false;
                var top_level_ids = settings.top_level_ids;
                var dept_nids = [top_level_ids.top_level_nid];
                var standalone = false;
                var standalone_ids = [];
                var allow_multiple = false;
                var config_target = false;

                // FIXME: some cleanup here of unused settings
                if (settings.hasOwnProperty('dept_nids')) {
                    dept_nids = settings.dept_nids;
                }

                if (settings.hasOwnProperty('standalone')) {
                    standalone = settings.standalone;
                }

                if (settings.hasOwnProperty('config_target')) {
                    config_target = settings.config_target;
                }

                if (settings.hasOwnProperty('field_configs') && settings.field_configs.hasOwnProperty('dept_id')) {
                    department = settings.field_configs.dept_id;
                } else {
                    department = settings.top_level_psid;
                }

                // Show the entire tree if whole_tree is set to true
                if (settings.hasOwnProperty('whole_tree')) {
                    whole_tree = settings.whole_tree;
                }

                // if we want the whole tree, use the top level (ASU),
                // else, the stored root department will be used
                if (whole_tree || dept_nids.length > 1) {
                    top_nid = top_level_ids.top_level_nid;
                } else {
                    top_nid = dept_nids[0];
                }

                var $people = $('#people');
                var tree = [];

                if (( top_nid != null) && (tree = JSON.parse(settings.tree))) {

                    // Set the root of the tree to the point defined by id -> set by asu_directory.module
                    temp = [];
                    temp.push(asu_isearch_dept_find_root(tree, top_nid));

                    if (temp[0] != null) {
                        tree = temp;
                        $people.data.tree_nids = asu_isearch_dept_get_tree_ids(asu_isearch_dept_find_root(tree, dept_nids[0]));
                    }
                }

                $tree_debug = tree;

                if (tree != null && tree.length > 0) {

                    if (standalone) {
                        $.each(dept_nids, function (index, dept_nid) {
                            standalone_ids = $.merge(standalone_ids, asu_isearch_dept_get_tree_path_ids(tree, dept_nid));
                        });

                        standalone_ids = array_unique(standalone_ids);
                    }

                    // Build Department Hierarchy tree list for display in block
                    $('#treediv').tree({
                        closedIcon: $('<span class="fa fa-plus-circle"></span>'),
                        openedIcon: $('<span class="fa fa-minus-circle"></span>'),
                        data: tree,
                        // First level open
                        autoOpen: 0,
                        selectable: true,
                        // Assign dept_id attribute to each tree <li>
                        onCreateLi: function (node, $li) {
                            $li.attr('dept_nid', node.dept_nid);
                            $li.attr('dept_id', node.dept_id);

                            if (standalone) {
                                $('#treediv').addClass('standalone');

                                $.each(standalone_ids, function (index, item) {
                                    if (item == node.dept_nid || node.dept_id == 'ASU') {
                                        $li.addClass('visible');
                                    }
                                });
                            }

                            if (!node.hasChildren()) {
                                $li.find('.jqtree-element').prepend('<span class="jqtree-folder-icon fa fa-bookmark"></span>');
                            }
                        }
                    });


                    if (config_target !== false && $(config_target).val() !== undefined) {
                        $target = $(config_target);
                        department = 'ASU';
                        $config = JSON.parse($(config_target).val());
                        $depts = $('#isearch_departments');

                        if ($config.length == 1) {
                            $depts.data.dept_id = $config[0].dept_id;
                            $depts.data.dept_nid = $config[0].dept_nid;
                            $depts.data.tree_nids = $config[0].tree_nids;
                        }

                        department = $depts.data.dept_id;

                        // If previous department was saved, open tree to that dept.
                        if (department != '') {
                            var $tree = $('#treediv');
                            var node = $tree.tree('getNodeById', department);
                            $tree.tree('selectNode', node, true);
                        }

                        asu_isearch_render_dept_list(tree, $config);


                        $('#treediv').bind('tree.click', function (event) {

                            if ($depts.data.dept_nid == event.node.dept_nid || event.node.dept_id == 'ASU' || !event.node.dept_nid) {
                                return false;
                            }

                            $depts.data.dept_nid = event.node.dept_nid;
                            deptnid = event.node.dept_nid;

                            // set and save to Dept. ID, so that we can save and recreate tree
                            $depts.data.dept_id = event.node.dept_id;
                            $depts.data.tree_nids = asu_isearch_dept_get_tree_ids(asu_isearch_dept_find_root(tree, deptnid));
                        });


                        $(document).on('change', config_target, function () {
                            asu_isearch_render_dept_list(tree, $config);
                        });

                        // Escape support, doesn't play nicely when viewing in pane edit screen
                        $(document).on('keyup', function (e) {
                            if (e.keyCode == 27) {
                                if ($('.asu-dept-picker').has('dialog-open')) {
                                    $('.asu-dept-picker').removeClass('dialog-open');
                                    e.preventDefault();
                                    return false;
                                }
                            }
                        });

                        // show dept picker
                        $(document).on('click', '#asu-isearch-dept-picker-trigger', function () {
                            $('.asu-dept-picker').addClass('dialog-open');
                        });

                        $(document).on('click', '#asu-isearch-dept-picker-cancel, .asu-dept-picker .close-dialog', function () {
                            $('.asu-dept-picker').removeClass('dialog-open');
                            return false;
                        });

                        $(document).on('click', '#asu-isearch-dept-picker-list li span.remove', function () {
                            if (dept_id = $(this).data('dept-id')) {
                                var dept_index = -1;
                                $.each($config.items, function (index, item) {
                                    if (item.dept_id == dept_id) {
                                        dept_index = index;
                                    }
                                });

                                if (dept_index != -1) {
                                    delete $config.options[dept_id];
                                    $config.items.splice(dept_index, 1);
                                    asu_isearch_set_config($config, $target);

                                    $('#asu-isearch-dept-picker-list li[data-key="' + dept_id + '"]').remove();
                                }
                            }

                            return false;
                        });

                        $(document).on('click', '#asu-isearch-dept-picker-select', function () {
                            var include_subdepts = ($('#asu-isearch-dept-include-subdept:checked').length != 0);

                            if (!$depts.data.dept_nid) {
                                return false;
                            }

                            var unique = true;
                            $.each($config.items, function (index, item) {
                                if (item.dept_nid == $depts.data.dept_nid) {
                                    unique = false;
                                    // update configuration
                                    $config.options[item.dept_id].subdepts = include_subdepts;
                                }
                            });

                            if (unique) {
                                $config.items.push({
                                    'dept_id': $depts.data.dept_id,
                                    'dept_nid': $depts.data.dept_nid,
                                    'tree_nids': $depts.data.tree_nids
                                });

                                $config.options[$depts.data.dept_id] = {
                                    subdepts: include_subdepts
                                };
                            }

                            asu_isearch_set_config($config, $target);

                            $('.asu-dept-picker').removeClass('dialog-open');

                            return false;
                        });
                    }
                }
                else {
                    $('#block-asu-dept-custom-info-asu-dept-custom-info-dept-hrc').find('.content').html('Error: Failed to load department data. If this error persists, please contact a site administrator.');
                }
            }
        }
    }
})(jQuery);

/**
 * Returns the node (and all children) where (node.tid == @param tid)
 * @param {Object} data
 *  Nested JSON object with department data
 * @param {integer} dept_id
 *  ID of the department that should be the root of the hierarchy
 */
function asu_isearch_dept_find_root(data, dept_id, lookup) {
    var success = null;

    if (arguments.length == 2) {
        lookup = 'dept_nid';
    }

    for (var i = 0; i < data.length; i++) {
        if (success == null && data[i] != null) {
            if (data[i][lookup] == dept_id) {
                return data[i];
            }
            else if (data[i].hasOwnProperty('children')) {
                success = asu_isearch_dept_find_root(data[i].children, dept_id, lookup);
            }
        }
        else {
            break;
        }
    }
    return success;
}


/**
 * Saves the ids of all departments under currently selected tree on #people's data object
 * @param {object}
 *  Nested JSON object with department data
 */
function asu_isearch_dept_get_tree_ids(tree, tree_ids) {

    if (arguments.length == 1) {
        tree_ids = [];
    }

    tree_ids.push(tree.dept_nid);

    for (var i = 0; i < tree.children.length; i++) {
        asu_isearch_dept_get_tree_ids(tree.children[i], tree_ids);
    }

    return tree_ids;
}

function asu_isearch_dept_get_tree_path_ids(tree, dept_nid, tree_path) {

    if (arguments.length == 2) {
        var tree_path = [];
    }

    if (item = asu_isearch_dept_find_root(tree, dept_nid, 'dept_nid')) {
        tree_path.push(item.dept_nid);
        if (item.parents.length) {
            var tree_item = asu_isearch_dept_find_root(tree, item.parents[0], 'tid');
            if (tree_item) {
                asu_isearch_dept_get_tree_path_ids(tree, tree_item.dept_nid, tree_path);
            }
        }
    }

    return tree_path;
}


function asu_isearch_dept_get_tree_path(tree, dept_tid) {
    var title = '';

    if (item = asu_isearch_dept_find_root(tree, dept_tid, 'tid')) {

        var className = 'fragment';

        if (item.parents[0] == '0') {
            // abbreviate Arizona State University
            item.name = 'ASU';
            className += ' first';
        }
        if (item.children.length == 0) {
            className += ' last';
        }

        title = '<span class="' + className + '">' + item.name + '</span>';
        if (item.parents.length) {
            return asu_isearch_dept_get_tree_path(tree, item.parents[0]) + title;
        }
    }

    return title;
}


function asu_isearch_render_dept_list(tree, config) {
    $ = jQuery;

    var list_html = [];

    $.each(config.items, function (index, item) {
        var tree_item = asu_isearch_dept_find_root(tree, item.dept_nid);
        var dept_path = asu_isearch_dept_get_tree_path(tree, tree_item.tid);
        if (dept_path != '') {
            var subdepts = '';

            if (config.options[item.dept_id].subdepts) {
                subdepts = '<span class="tag subdepts">+subdepts</span>';
            }

            list_html.push('<li data-key="' + item.dept_id + '">' + dept_path + subdepts
                + '<span class="tag remove" data-dept-id="' + item.dept_id + '"><span class="fa fa-close"></span></span></li>');
        }
    });

    if (list_html.length == 0) {
        list_html.push('<li><h4>Click browse to add a department</h4></li>');
    }

    $('#asu-isearch-dept-picker-list').html(list_html.join(''));
}

function asu_isearch_set_config($config, $target) {
    $target.val(JSON.stringify($config));
    $target.trigger('change');
}

function array_unique(data) {
    var result = [];
    for (var i = 0; i < data.length; i++) {
        if (result.indexOf(data[i]) == -1) {
            result.push(data[i]);
        }
    }
    return result;
}
