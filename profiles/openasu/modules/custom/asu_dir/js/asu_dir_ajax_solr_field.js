/**
 * ASU Directory module
 * Directory field display javascript
 *
 * Provides AJAX behavior, pagination, modal, and sort for People block
 *
 * @author Colton Testamarck (ctestama@asu.edu)
 */


var Manager;

//define the ASUPeople global variable, for keeping track of currently selected dept between widgets.
var ASUPeople = {};
ASUPeople.dept_nid = 0;
ASUPeople.dept_id = '';

(function ($, history) {
    Drupal.behaviors.asu_dir_ajax_solr_field = {
        attach: function (context, settings) {
            if (settings.hasOwnProperty('asu_dir')) {

                settings = settings.asu_dir;

                //get the configs passed in by Drupal
                var top_level_ids = settings.top_level_ids;
                var field_configs = settings.field_configs;
                var admin = settings.admin;
                var query = null;
                var saved_dept_nids = settings.dept_nids;
                var saved_dept_id = field_configs.dept_id;
                var solr_server = settings.solr_server;
                var page_alias = settings.page_alias;
                var isearch_mode = field_configs.isearch_flag;

                //create the dept. tree from the root dept
                var top_nid = saved_dept_nids[0];
                var tree = [];

                // Add widget instances for each facet.

                //these are the fields which will be used for faceted search
                var fields = [/*'primaryTitle', */'expertiseAreasFacet'];

                //these are fields which will override the manager sort, and also the alpha filter widget
                var override_fields = ['expertiseAreasFacet', 'lastName'];

                //stick with entire tree if top nid is not defined, or we are in iSearch mode
                if (( top_nid != null) && ( tree = JSON.parse(settings.tree)) && !isearch_mode) {
                    // Set the root of the tree to the point defined by id -> set by asu_directory.module
                    temp = [];
                    temp.push(asu_dir_ajax_solr_find_root(tree, top_nid));
                    tree = temp;
                }

                //Configure AjaxSolr
                Manager = new AjaxSolr.Manager({
                    solrUrl: solr_server
                });

                // Add in Results widget. See our custom
                // js/widgets/isPeopleResultWidget.js method extending AbstractWidget.
                Manager.addWidget(new AjaxSolr.asu_dirResultWidget({
                    id: 'people',
                    target: '#asu-dir-ajax-solr-people',
                    solr_server: solr_server,
                    field_configs: field_configs,
                    override_fields: override_fields
                }));

                // Add in stock pager widget.
                Manager.addWidget(new AjaxSolr.PagerWidget({
                    id: 'pager',
                    target: '#asu-dir-ajax-solr-pager',
                    prevLabel: '<i class="fa fa-angle-double-left"></i>',
                    nextLabel: '<i class="fa fa-angle-double-right"></i>',
                    innerWindow: 1,
                    renderHeader: function (perPage, offset, total) {
                        $('#pager-header').html($('<span></span>').text('displaying ' + Math.min(total, offset + 1) + ' to ' + Math.min(total, offset + perPage) + ' of ' + total));
                    }
                }));

                //Add the Alpha bar widget
                Manager.addWidget(new AjaxSolr.asuAlphaBarWidget({
                    id: 'asuAlphaBar',
                    target: '#ajax-solr-alpha-bar',
                    solr_server: solr_server,
                    field_configs: field_configs,
                    last_name_field: 'lastName'
                }));

                /* Manager.addWidget(new AjaxSolr.asu_dirFacetWidget({
                 id: 'primaryTitle',
                 target: '#primaryTitleFacet',
                 field: 'primaryTitle'
                 }));*/

                if (field_configs.show_tree) {
                    // Add in a custom widget for managing the jqTree
                    Manager.addWidget(new AjaxSolr.asu_dirTreeWidget({
                        id: 'dirTree',
                        target: '#treediv',
                        tree: tree,
                        field_configs: field_configs,
                        top_level_ids: top_level_ids
                    }));
                }


                //If we're in iSearch mode, leave out the facet, current search , text (search), and history widgets
                if (!isearch_mode) {

                    Manager.addWidget(new AjaxSolr.asu_dirCurrentSearchWidget({
                        id: 'currentSelections',
                        target: '#asu-dir-ajax-solr-selections',
                        field_configs: field_configs,
                        tree: tree
                    }));


                    Manager.addWidget(new AjaxSolr.asu_dirFacetWidget({
                        id: 'expertiseAreasFacet',
                        target: '#expertiseAreasFacet',
                        field: 'expertiseAreasFacet'
                    }));

                    // Add in Text input/search widget. See our custom isTextWidget method
                    // extending AbstractWidget in js/widgets/isTextWidget.js.
                    Manager.addWidget(new AjaxSolr.asu_dirTextWidget({
                        id: 'text',
                        target: '#asu-dir-ajax-solr-search',
                        field_configs: field_configs,
                        tree: tree
                    }));


                    Manager.setStore(new AjaxSolr.asu_dirParameterHistoryStore({
                        page_alias: page_alias,
                        tree: tree,
                        field_configs: field_configs,
                        dept_nids: saved_dept_nids
                    }));

                    Manager.store.exposed = ['fq', 'q', 'start', 'sort', 'rows'];
                }


                Manager.init();

                // Add Solr parameters for faceting.
                var params = {
                    facet: true,
                    'facet.field': [/*'primaryTitle',*/ 'expertiseAreasFacet'],
                    'facet.limit': -1,
                    'facet.mincount': 1,
                    'f.topics.facet.limit': 50,
                    'json.nl': 'map'
                };

                if (Manager.store.params.q !== undefined && Manager.store.params.q.value !== '*:*') {
                    $("#asu-dir-ajax-solr-search input").val(Manager.store.params.q.value);
                }

                Manager.asu_dirFacetDisplay = [];
                Manager.asu_dirFacetDisplay.dropdownFacets = ['primaryTitle', 'expertiseAreasFacet'];

                // Assign all the params to the Manager's store.
                for (var name in params) {
                    Manager.store.addByValue(name, params[name]);
                }

                // Initial request on load
                if (Manager.store.params.q === undefined) {

                    if (!field_configs.use_custom_q) {
                        //Set the global if no params are set
                        ASUPeople.dept_nid = saved_dept_nids[0];

                        Manager.store.addByValue('q', '*:*');

                        //Create the query string for depts
                        Manager.store.addByValue('fq', asu_dir_solr_search_string(saved_dept_nids, 'deptids'));

                        //Default to alphabetical sort if no params defined
                        //Manager.store.addByValue('sort', 'lastNameSort asc');

                        //handle custom query
                        if (field_configs.use_custom_q && field_configs.hasOwnProperty('custom_q')) {
                            query = field_configs.custom_q;
                        }

                        //If previous department was saved, open tree to that dept.
                        if (saved_dept_id != '' && saved_dept_id != top_level_ids.top_level_psid && field_configs.show_tree) {
                            var $tree = jQuery('#treediv');
                            var node = $tree.tree('getNodeById', saved_dept_id);
                            $tree.tree('selectNode', node, true);
                        }

                        //CUSTOM QUERY HANDLING HERE
                    } else {

                        if (field_configs.hasOwnProperty('custom_q')) {

                            if (field_configs.custom_q.hasOwnProperty('q')) {
                                Manager.store.addByValue('q', field_configs.custom_q.q);
                            } else {
                                Manager.store.addByValue('q', '*:*');
                            }

                            if (field_configs.custom_q.hasOwnProperty('fq')) {
                                Manager.store.addByValue('fq', field_configs.custom_q.fq);
                            }

                            if (field_configs.custom_q.hasOwnProperty('sort')) {
                                Manager.store.addByValue('sort', field_configs.custom_q.sort);
                            } else {
                                Manager.store.addByValue('sort', 'lastNameSort asc');
                            }
                        }
                    }
                }

                //deMorgan's law applied to !( isearch_mode && top_nid == top_level_ids.top_level_nid )
                if (!isearch_mode || top_nid != top_level_ids.top_level_nid) {
                    Manager.doRequest();
                }
            }
        }
    };
})(jQuery, window.History);


/***
 * Function  to create concatenated deptids search string with OR operator
 *
 * @param field:  string value of the field to be queried in solr
 * @param items
 * @returns {string}
 */
function asu_dir_solr_search_string(items, field) {
    field = field || 'deptids';
    var wrap = '';

    if (field == "employeeTypes") {
        wrap = '"';
    }

    if (items.indexOf("Show All") > -1) {
        return "employeeTypes:*";
    }

    var temp = '';
    var last = items.length - 1;

    for (var i = 0; i < items.length; i++) {
        temp += field + ':' + wrap + items[i] + wrap;
        if (i != last) {
            temp += ' OR ';
        }
    }

    return temp;
}

// Department tree utility functions

/**
 * Returns the node (and all children) where (node.tid == @param tid)
 * @param {Object} data
 *  Nested JSON object with department data
 * @param {integer} dept_id
 *  ID of the department that should be the root of the hierarchy
 */
function asu_dir_ajax_solr_find_root(data, dept_id) {
    var success = null;
    for (var i = 0; i < data.length; i++) {
        if (success == null) {
            if (data[i].dept_nid == dept_id) {
                return data[i];
            } else if (data[i].hasOwnProperty('children')) {
                success = asu_dir_ajax_solr_find_root(data[i].children, dept_id);
            }
        }
        else {
            break;
        }
    }
    return success;
}


/**
 * Returns an array of
 * @param {array} The dept. tree
 * @param {array} tree_ids. Optional.  Dept ids will be pushed onto this array.
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


/**
 * Gets the dept id given a dept nid
 * @param tree
 * @param dept_nid
 */
function asu_dir_get_id_from_nid(tree, dept_nid) {

    var id = null;
    for (var i = 0; i < tree.length; i++) {
        if (id == null) {
            if (tree[i].dept_nid == dept_nid) {
                return tree[i].id;
            }
            else if (tree[i].hasOwnProperty('children')) {
                id = asu_dir_get_id_from_nid(tree[i].children, dept_nid);
            }
        }
        else {
            break;
        }
    }

    return id;
}

/**
 * Utility function to parse the NID from the query string for asu_dirParameterHistoryStore
 * @param hash
 * @returns {number}
 */
function asu_dir_get_nid_from_hash(hash) {
    var decoded_uri = decodeURIComponent(hash);
    var dstring = "fq=deptids:";
    var check = decoded_uri.indexOf(dstring);

    if (check == -1) {
        dstring = "dept=";
    }

    var start = decoded_uri.indexOf(dstring) + dstring.length;
    var stop = start + 8;
    var nid = 0;

    //get the NID from the string
    nid = decoded_uri.slice(start, stop);
    nid = nid.replace(/\D/g, '');
    nid = parseInt(nid);
    return nid;
}

