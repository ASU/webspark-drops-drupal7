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
                tree: null,
                field_configs: null,
                top_level_ids: null
            }, attributes);
        },

        init: function () {
            var self = this;
            var treediv = $(this.target);
            var tree = this.tree;
            var field_configs = this.field_configs;
            var hash = this.hash;
            var dept_nids = [];
            var top_ids = this.top_level_ids;

            var tree_open = "glyphicon-minus-sign";
            var tree_close = "glyphicon-plus-sign";
            var tree_marker = "fa-bookmark";

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
                        $li.find('.jqtree-element').prepend('<span tabindex="0" class="jqtree-folder-icon fa fa-bookmark" name="' + node.name + '"></span>');
                    }
                }
            });

            treediv.bind('tree.click', function (event) {

                //if the tree node is already highlighted, or is the very top dept, don't do anything
                if (event.node.dept_id == top_ids.top_level_psid || event.node.dept_nid == ASUPeople.dept_nid) {
                    return false;
                }

                //set global dept nid to the tree node's nid
                ASUPeople.dept_nid = event.node.dept_nid;
                ASUPeople.dept_id = event.node.dept_id;

                //if showing people in sub-departments, get sub-departments and do request
                if (field_configs.sub_toggle === true) {
                    dept_nids = asu_dir_get_tree_ids(asu_dir_ajax_solr_find_root(tree, ASUPeople.dept_nid));
                } else {
                    dept_nids = [event.node.dept_nid];
                }

                //remove other values and alphabar active class
                var alphabar = $('#ajax-solr-alpha-bar ul li');
                alphabar.removeClass('active-letter');

                self.manager.store.remove('q');
                self.manager.store.addByValue('q', '*:*');
                self.manager.store.remove('start');
                self.manager.store.remove('fq');
                self.manager.store.addByValue('fq', asu_dir_solr_search_string(dept_nids, 'deptids'));
                self.manager.doRequest();
            });

            var access_links = $('#treediv .jqtree_common');

            var pluses = $('#treediv .glyphicon-plus-sign');
            var mp = $('#treediv .fa-bookmark');

            pluses.on('focus', function(event) {
                var parents = $(this).parents().eq(1);
                var pnode = $(this).parents().eq(2).attr('dept_id');
                var $tree = $('#treediv');
                var node = $tree.tree('getNodeById', pnode);
                $tree.tree('openNode', node);
                parents.find("span.glyphicon-minus-sign").focus();
            });

            access_links.on('keydown', function(event) {
                if(event.which == 13) {
                    var parent = $(this).parents().eq(0);
                    parent.click();
                }
            });

            mp.on('keydown', function(event) {
                if(event.which == 13) {
                    var parent = $(this).parents().eq(0);
                    parent.click();
                }
            });

            var state = history.getState();
            // If initial load, load the state from the URL.
            var url = state.cleanUrl, index = url.indexOf("?");// ASU edit.

            if (index != -1) {
                //get the query string from URL
                var query_string = url.substr(index + 1);
                var re = /query=/gi;
                query_string = query_string.replace(re, 'q=');
                asu_dir_selectNode(tree, query_string);
            }
        }
    });

})(jQuery, window.History);


/**
 * Global Utility Function to select a tree node in the jqtree, without a click event
 * @param tree
 * @param hash
 */
function asu_dir_selectNode(tree, hash) {
    var nid = asu_dir_get_nid_from_hash(hash);
    dept_id = asu_dir_get_id_from_nid(tree, nid);

    var $tree = jQuery('#treediv');
    //var selected = $tree.tree('getSelectedNode');
    var node = $tree.tree('getNodeById', dept_id);

    $tree.tree('selectNode', node, true);
    ASUPeople.dept_nid = nid;
}