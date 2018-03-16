/**
 * Define the IS CurrentSearch Widget.
 */
(function ($, history) {

    AjaxSolr.asu_dirTreeWidget = AjaxSolr.AbstractWidget.extend({
        start: 0,

        /**
         * @param {Object} [attributes]
         * @param {Number} [attributes.start] This widget will by default set the
         *   offset parameter to 0 on each request.
         */
        constructor: function (attributes) {
            AjaxSolr.asu_dirTreeWidget.__super__.constructor.apply(this, arguments);
            AjaxSolr.extend(this, {
                target: null,
                tree: null,
                fieldConfigs: null,
                topLevelIds: null,
                fieldId: null,
                fidNum: null,
                savedDeptId: null
            }, attributes);
        },

        init: function () {
            var self = this;
            var treediv = $(this.target);
            var tree = this.tree;
            var fieldConfigs = this.fieldConfigs;
            var dept_nids = [];
            var fieldId = this.fieldId;
            var fidNum = this.fidNum;
            var savedDeptId = this.savedDeptId;
            var topLevelIds = this.topLevelIds;

            // Build Department Hierarchy tree list for display in block
            treediv.tree({
                closedIcon: $('<span tabindex="0" class="glyphicon glyphicon-plus-sign"></span>'),
                openedIcon: $('<span tabindex="0" class="glyphicon glyphicon-minus-sign"></span>'),
                data: tree,
                // First level open
                autoOpen: 0,
                selectable: true,
                keyboardSupport: false,
                // Assign dept_id attribute to each tree <li>
                onCreateLi: function (node, $li) {
                    $li.attr('dept_nid', node.dept_nid);
                    $li.attr('dept_id', node.dept_id);
                    $li.find('.glyphicon').attr('name', node.name);

                    if (!node.hasChildren()) {
                        $li.find('.jqtree-element').prepend('<span tabindex="0" class="jqtree-folder-icon fa fa-circle" name="' + node.name + '"></span>');
                    }
                }
            });

            treediv.bind('tree.click', function (event) {

                //if the tree node is already highlighted, or is the very top dept, don't do anything
                if (event.node.dept_id == topLevelIds.top_level_psid || event.node.dept_nid == ASUPeople[fieldId].dept_nid) {
                    return false;
                }

                //set global dept nid to the tree node's nid
                ASUPeople[fieldId].dept_nid = event.node.dept_nid;
                ASUPeople[fieldId].dept_id = event.node.dept_id;

                /*
                 //if showing people in sub-departments, get sub-departments and do request
                 if (fieldConfigs.sub_toggle === true) {
                 dept_nids = asu_dir_get_tree_ids(asu_dir_ajax_solr_find_root(tree, ASUPeople[fieldId].dept_nid));
                 } else {
                 dept_nids = [event.node.dept_nid];
                 }

                 //remove other values and alphabar active class


                 self.manager.store.remove('q');
                 self.manager.store.addByValue('q', '*:*');
                 self.manager.store.remove('start');
                 self.manager.store.remove('fq');
                 self.manager.store.addByValue('fq', asu_dir_solr_search_string(dept_nids, 'deptids'));*/
                self.manager.doRequest();
            });


            //set up breadcrumb functionality, if configured
            if (fieldConfigs.show_breadcrumbs) {

                var crumb_element = $('.asu-dir-breadcrumb' + fidNum);

                treediv.bind(
                    'tree.select',
                    function (event) {

                        if (event.node) {

                            // Node that was selected.
                            var node = event.node;

                            // Clear all of breadcrumb to reset on new node selection.
                            crumb_element.empty();

                            // Recurse through parents to prepend() rest of breadcrumbs.
                            asu_dir_traverse_crumbs(node, crumb_element);
                        }
                    }
                );
            }

            //Accessibility Settings
            var accessLinks = $(this.target + ' .jqtree_common');

            var pluses = treediv.find('.glyphicon-plus-sign');
            var mp = treediv.find('.fa-circle');

            pluses.on('focus', function (event) {
                var parents = $(this).parents().eq(1);
                var pnode = $(this).parents().eq(2).attr('dept_id');
                var $tree = $(this.target);
                var node = $tree.tree('getNodeById', pnode);
                $tree.tree('openNode', node);
                parents.find("span.glyphicon-minus-sign").focus();
            });

            accessLinks.on('keydown', function (event) {
                if (event.which == 13) {
                    var parent = $(this).parents().eq(0);
                    parent.click();
                }
            });

            mp.on('keydown', function (event) {
                if (event.which == 13) {
                    var parent = $(this).parents().eq(0);
                    parent.click();
                }
            });

            //check the history state for a dept Id
            var state = history.getState();
            // If initial load, load the state from the URL.
            var url = state.cleanUrl, index = url.indexOf("?");// ASU edit.

            if (index != -1 && ASUPeople.active == fieldId) {
                //get the query string from URL
                var query_string = url.substr(index + 1);
                var re = /query=/gi;
                query_string = query_string.replace(re, 'q=');

                asu_dir_selectNode(tree, query_string, fidNum);
            } else {
                //If previous department was saved, open tree to that dept.
                if (savedDeptId != '' && savedDeptId != topLevelIds.top_level_psid && fieldConfigs.show_tree) {
                    var node = treediv.tree('getNodeById', savedDeptId);
                    treediv.tree('selectNode', node, true);
                }
            }
        }
    });

})(jQuery, window.History);

/**
 * Global Utility Function to select a tree node in the jqtree, without a click event
 * @param tree
 * @param hash
 */
function asu_dir_selectNode(tree, hash, id) {
    var nid = asu_dir_get_nid_from_hash(hash);
    var dept_id = asu_dir_get_id_from_nid(tree, nid);
    var $tree = jQuery('#treediv' + id);
    //var selected = $tree.tree('getSelectedNode');
    var node = $tree.tree('getNodeById', dept_id);

    $tree.tree('selectNode', node, true);
    ASUPeople['asu_dir' + id].dept_nid = nid;
}

// Utility function to traverse nodes from the current node of the jqtree, and append breadcrumbs to the
// crumb element
function asu_dir_traverse_crumbs(current_node, crumb_element) {

    var node = current_node;

    while ((current_node.name)) { // If current_node has a name, drop a breadcrumb.

        if (current_node.name == node.name) { // Lowest level. No dividing character.
            crumb_element.prepend('<a onclick=asu_dirGoDept(' + current_node.dept_nid + ')>' + current_node.name + '</a>');
        } else {
            crumb_element.prepend('<a onclick=asu_dirGoDept(' + current_node.dept_nid + ')>' + current_node.name + '</a> <span class="breadcrumb-divider">/</span> ');
        }

        // Move next iteration up a level.
        current_node = current_node.parent;
    }
}


/***
 * Fires a click event on the selected Department nid
 * @param nid
 */
function asu_dirGoDept(nid) {
    var dept_nid_string = "[dept_nid=" + nid + "]";
    var dept = jQuery(dept_nid_string + ">div");

    //Create a new jQuery.Event object without the "new" operator.
    dept.click();
}