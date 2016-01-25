/**
 * ASU Directory module
 * Department Hierarchy Block JavaScript
 *
 * Provides AJAX behavior, pagination, modal, and sort for Department block
 *
 * @author Colton Testamarck (colt@asu.edu)
 * @author Robert Jenkins ( rjenkins@eaglecrk.com )
 * @author Michael Samuelson ( mlsamuel@asu.edu / mlsamuelson@gmail.com )
 */

(function ($) {
    Drupal.behaviors.asu_dir_hierarchy_block = {
        attach: function (context, settings) {
            if (settings.hasOwnProperty('asu_dir')) {

                settings = settings.asu_dir;
                var $people = jQuery('#people');
                var $title = jQuery('#edit-title');
                var top_nid = null;
                var department = 'ASU';
                var whole_tree = false;
                var top_level_ids = settings.top_level_ids;
                var dept_nids = [top_level_ids.top_level_nid];
                var standalone = false;

                if (settings.hasOwnProperty('dept_nids')) {
                    dept_nids = settings.dept_nids;
                }

                if (settings.hasOwnProperty('standalone')) {
                    standalone = settings.standalone;
                }

                if (settings.hasOwnProperty('field_configs') && settings.field_configs.hasOwnProperty('dept_id')) {
                    department = settings.field_configs.dept_id;
                } else {
                    department = settings.top_level_psid;
                }

                //Show the entire tree if whole_tree is set to true
                if (settings.whole_tree !== undefined) {
                    whole_tree = settings.whole_tree;
                }

                //if we want the whole tree, use the top level (ASU),
                //else, the stored root department will be used
                if (whole_tree) {
                    top_nid = top_level_ids.top_level_nid;
                } else {
                    top_nid = dept_nids[0];
                }

                var $people = $('#people');

                var tree = [];

                if (( top_nid != null) && ( tree = JSON.parse(settings.tree))) {

                    // Set the root of the tree to the point defined by id -> set by asu_directory.module
                    temp = [];
                    temp.push(asu_dir_hrc_find_root(tree, top_nid));
                    tree = temp;

                    $people.data.tree_nids = asu_dir_get_tree_ids(asu_dir_hrc_find_root(tree, dept_nids[0]));
                }

                if (tree != null && tree.length > 0) {

                    // Build Department Hierarchy tree list for display in block
                    jQuery('#treediv').tree({
                        closedIcon: $('<span class="glyphicon glyphicon-plus-sign"></span>'),
                        openedIcon: $('<span class="glyphicon glyphicon-minus-sign"></span>'),
                        data: tree,
                        // First level open
                        autoOpen: 0,
                        selectable: true,
                        // Assign dept_id attribute to each tree <li>
                        onCreateLi: function (node, $li) {
                            $li.attr('dept_nid', node.dept_nid);
                            $li.attr('dept_id', node.dept_id);

                            if (!node.hasChildren()) {
                                $li.find('.jqtree-element').prepend('<span class="jqtree-folder-icon fa fa-bookmark"></span>');
                            }
                        }
                    });


                    //if tree is standing alone, bind click function to refresh the people table
                    if (!standalone) {
                        jQuery('#treediv').bind('tree.click', function (event) {

                            if ($people.data.field_configs.dept_id == event.node.dept_id || event.node.dept_id == top_level_ids.top_level_psid) {
                                return false;
                            }

                            $people.data.dept_nid = event.node.dept_nid;

                            deptnid = event.node.dept_nid;

                            $title.val(event.node.name);

                            //set and save to Dept. ID, so that we can save and recreate tree
                            $people.data.field_configs.dept_id = event.node.dept_id;

                            $people.data.page = 0;

                            $people.data.tree_nids = asu_dir_get_tree_ids(asu_dir_hrc_find_root(tree, deptnid));

                            if (field_configs.sub_toggle === true) {
                                $people.data.field_items = $people.data.tree_nids;
                            } else {
                                $people.data.field_items = [deptnid];
                            }

                            asu_dir_cleanup($people);

                            asu_dir_set_field($people);
                            //rebuild the table
                            asu_dir_build_table();

                        });

                        //If previous department was saved, open tree to that dept.
                        if (department != '' && department != 'ASU') {
                            var $tree = jQuery('#treediv');
                            var node = $tree.tree('getNodeById', department);
                            $tree.tree('selectNode', node, true);
                        }
                    }
                }
                else {
                    jQuery('#block-asu-dept-custom-info-asu-dept-custom-info-dept-hrc').find('.content').html('Error: Failed to load department data. If this error persists, please contact a site administrator.');
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
function asu_dir_hrc_find_root(data, dept_id) {
    var success = null;
    for (var i = 0; i < data.length; i++) {
        if (success == null) {
            if (data[i].dept_nid == dept_id) {
                return data[i];
            }
            else if (data[i].hasOwnProperty('children')) {
                success = asu_dir_hrc_find_root(data[i].children, dept_id);
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
function asu_dir_get_tree_ids(tree, tree_ids) {

    if (arguments.length == 1) {
        tree_ids = [];
    }

    tree_ids.push(tree.dept_nid);

    for (var i = 0; i < tree.children.length; i++) {
        asu_dir_get_tree_ids(tree.children[i], tree_ids);
    }

    return tree_ids;

}



