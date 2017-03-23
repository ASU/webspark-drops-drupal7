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

(function ($, history) {
    Drupal.behaviors.asu_dir_ajax_solr_field = {
        attach: function (context, settings) {

            var directories = $('.field-type-asu-directory');
            var tabs = $('.ui-tabs .field-type-asu-directory');
            var has_tabs = false;
            var tab_id = '';
            var tab_links = [];

            // reset the ASUPeople global, because it can cause weirdness with panels IPE
            ASUPeople = {};
            ASUPeople.man_array = [];

            if (tabs.length > 0) {
                has_tabs = true;
                //tab_id = tabs.get(0).closest(".ui-tabs");
                tab_id = tabs.eq(0).parents('.ui-tabs').eq(0);
                tab_id = tab_id.attr('id');
                tab_links = $('#' + tab_id + ' .ui-tabs-nav a');
            }

            for (var i = 0; i < directories.length; i++) {

                var field_id = directories[i].id;
                ASUPeople[field_id] = {};
                ASUPeople[field_id].dept_nid = 0;
                ASUPeople[field_id].dept_id = '';
                var tab_pane = null;
                var tab_pane_id = '';
                var tab_link = '';

                if (has_tabs) {
                    tab_pane = tabs.eq(i).closest('.ui-tabs-panel');
                    tab_pane_id = tab_pane.attr('id');
                    tab_link = tab_links.eq(i).attr('id');
                }

                if (settings.hasOwnProperty(field_id)) {
                    var isettings = settings[field_id];

                    //get the configs passed in by Drupal
                    var top_level_ids = isettings.top_level_ids;
                    var field_configs = isettings.field_configs;
                    ASUPeople[field_id].field_configs = field_configs;
                    var admin = isettings.admin;
                    var query = null;
                    var saved_dept_nids = isettings.dept_nids;
                    var saved_dept_id = field_configs.dept_id;
                    var solr_server = isettings.solr_server;
                    var page_alias = isettings.page_alias;
                    var isearch_mode = field_configs.isearch_flag;
                    var titlesort_field = isettings.titlesort_field;
                    var id_num = field_configs.pane_id;
                    var res_per_page = 10;
                    var local_people = isettings.local_people;
                    var isearch_url = isettings.isearch_url;
                    var filters = [];

                    // set the number of results per page, this will be added to the manager store as the
                    // 'rows' parameter.
                    if (field_configs.pager_display == 'paged' && field_configs.pager_items_per_page != 0) {
                        res_per_page = field_configs.pager_items_per_page;

                    // if we want to show all results, then we set the 'rows' parameter to 2000,
                    // since that is the maximum request size we will want.
                    } else if (field_configs.pager_display == 'all' || field_configs.pager_items_per_page == 0) {
                        res_per_page = 2000;
                    }


                    // Build the pre-configured filter values, and store them in the field_configs

                    // ADD FILTERING FOR TENURE OR NON-TENURE FACULTY TITLES, IF APPLICABLE
                    if (field_configs.tenure_display && field_configs.faculty_titles != null && field_configs.tenure_display != 'Both') {
                        var fac_titles = field_configs.faculty_titles.titles;
                        var filtered = [];
                        var title_search = '';

                        if (field_configs.tenure_display == 'Tenure') {
                            filtered = fac_titles.filter(function (element, index, array) {
                                return (element.tenure === 1);
                            });
                        } else {
                            filtered = fac_titles.filter(function (element, index, array) {
                                return (element.tenure === 0);
                            });
                        }

                        filtered = filtered.map(function (e) {
                            return e.name;
                        });

                        title_search += asu_dir_solr_search_string(filtered, 'facultyTitlesFacet', true);

                        field_configs.ft_filter = title_search;
                        filters.push(title_search);
                    }


                    // Add the pre-configured filters to the field_configs.  These are set in the field form,
                    // so we don't need to display these as facet fields or active filters.  They are handled behind
                    // the scenes.
                    field_configs.filters = filters;

                    res_per_page = parseInt(res_per_page);

                    //create the dept. tree from the root dept
                    ASUPeople[field_id].dept_nid = saved_dept_nids[0];
                    var top_nid = saved_dept_nids[0];
                    var tree = [];

                    // Add widget instances for each facet.
                    //these are the fields which will be used for faceted search
                    //todo:  primary title facet?
                    var fields = ['expertiseAreasFacet', 'facultyTitlesFacet'];

                    //these are fields which will override the manager sort, and also the alpha filter widget
                    var override_fields = ['lastName', 'primaryTitle', 'expertiseAreasFacet', 'facultyTitlesFacet'];

                    if (isettings.hasOwnProperty('tree') && isettings.tree.constructor != Array) {
                        tree = JSON.parse(isettings.tree);
                    } else {
                        tree = isettings.tree;
                    }

                    //stick with entire tree if top nid is not defined, or we are in iSearch mode
                    if (( top_nid != null) && (tree) && !isearch_mode) {
                        // Set the root of the tree to the point defined by id -> set by asu_directory.module
                        temp = [];
                        temp.push(asu_dir_ajax_solr_find_root(tree, top_nid));
                        tree = temp;
                    }

                    //Configure AjaxSolr
                    Manager = new AjaxSolr.asu_dirManager({
                        solrUrl: solr_server,
                        field_configs: field_configs,
                        override_fields: override_fields,
                        field_id: field_id,
                        per_page: res_per_page,
                        local_people: local_people
                    });

                    // Add in stock pager widget.
                    Manager.addWidget(new AjaxSolr.asu_dirPagerWidget({
                        id: 'pager',
                        target: '#asu-dir-ajax-solr-pager' + id_num,
                        prevLabel: '<i class="fa fa-angle-double-left"></i><span class="asu-dir-hidden">Previous</span>',
                        nextLabel: '<i class="fa fa-angle-double-right"></i><span class="asu-dir-hidden">Next</span>',
                        innerWindow: 1,
                        renderHeader: function (perPage, offset, total) {
                            $('#pager-header').html($('<span></span>').text('displaying ' + Math.min(total, offset + 1) + ' to ' + Math.min(total, offset + perPage) + ' of ' + total));
                        },
                        per_page: res_per_page,
                        field_configs: field_configs
                    }));
                    //Add the Alpha bar widget
                    Manager.addWidget(new AjaxSolr.asuAlphaBarWidget({
                        id: 'asuAlphaBar',
                        target: '#ajax-solr-alpha-bar' + id_num,
                        solr_server: solr_server,
                        field_configs: field_configs,
                        last_name_field: 'lastName',
                        field_id: field_id
                    }));

                    if (field_configs.show_tree) {
                        // Add in a custom widget for managing the jqTree
                        Manager.addWidget(new AjaxSolr.asu_dirTreeWidget({
                            id: 'dirTree',
                            target: '#treediv' + id_num,
                            tree: tree,
                            field_configs: field_configs,
                            top_level_ids: top_level_ids,
                            field_id: field_id,
                            id_num: id_num,
                            saved_dept_id: saved_dept_id
                        }));
                    }
                    //First Item in array will be the default Sort
                    var sort_items = [{
                        'field_name': 'lastNameSort',
                        'field_id': '#dir-lastNameSort' + id_num
                    },
                        {//field doesn't actually exist in solr yet
                            'field_name': 'tsort',
                            'field_id': '#dir-rankSort' + id_num
                        },
                        {//field doesn't actually exist in solr yet
                            'field_name': 'firstNameSort',
                            'field_id': '#dir-firstNameSort' + id_num
                        }
                    ];

                    var default_sort = field_configs.default_sort_by;

                    //todo: remove this after removing usages
                    var titlesort_field = 'tsort';

                    // Add Sorting widget
                    Manager.addWidget(new AjaxSolr.asu_dirSortWidget({
                        id: 'asuDirSort',
                        target: '#asu-dir-ajax-solr-sort' + id_num,
                        sort_items: sort_items,
                        field_configs: field_configs,
                        default_sort: default_sort,
                        titlesort_field: titlesort_field,
                        field_id: field_id
                    }));

                    // Add in Results widget. See our custom
                    // js/widgets/isPeopleResultWidget.js method extending AbstractWidget.
                    Manager.addWidget(new AjaxSolr.asu_dirResultWidget({
                        id: 'people',
                        target: '#asu-dir-ajax-solr-people' + id_num,
                        solr_server: solr_server,
                        field_configs: field_configs,
                        override_fields: override_fields,
                        field_id: field_id,
                        per_page: res_per_page,
                        local_people: local_people,
                        isearch_url: isearch_url
                    }));

                    Manager.addWidget(new AjaxSolr.asu_dirFacetWidget({
                        id: 'facultyTitlesFacet' + id_num,
                        target: '#facultyTitlesFacet' + id_num,
                        field: 'facultyTitlesFacet'
                    }));

                    Manager.addWidget(new AjaxSolr.asu_dirFacetWidget({
                        id: 'expertiseAreasFacet' + id_num,
                        target: '#expertiseAreasFacet' + id_num,
                        field: 'expertiseAreasFacet'
                    }));

                    /*
                     Manager.addWidget(new AjaxSolr.asu_dirFacetWidget({
                     id: 'primaryTitleFacet'+id_num,
                     target: '#primaryTitleFacet'+id_num,
                     field: 'primaryTitlefacetf'
                     }));
                     */

                    var selection_target = 'asu-dir-ajax-solr-selections';

                    // exclude these fields from the current search display, since they are pre-configured
                    // and either always in effect, or handled elsewhere
                    var excludes = ["deptids", "employeeTypes", "lastName", "expertiseAreas:", "titles", 'asuriteId'];
                    Array.prototype.push.apply(excludes, filters);


                    Manager.addWidget(new AjaxSolr.asu_dirCurrentSearchWidget({
                        id: 'currentSelections' + id_num,
                        target: '#' + selection_target + id_num,
                        field_configs: field_configs,
                        tree: tree,
                        field_id: field_id,
                        id_num: id_num,
                        current_search_exclude: excludes
                    }));

                    //If we're in iSearch mode, leave out the facet, current search , text (search), and history widgets
                    if (!isearch_mode) {
                        // Add in Text input/search widget. See our custom isTextWidget method
                        // extending AbstractWidget in js/widgets/isTextWidget.js.
                        Manager.addWidget(new AjaxSolr.asu_dirTextWidget({
                            id: 'text',
                            target: '#asu-dir-ajax-solr-search' + id_num,
                            field_configs: field_configs,
                            tree: tree,
                            field_id: field_id
                        }));

                        // if this is the first manager created, make it the default.  this will allow us to
                        // keep track of which field the
                        var first = false;

                        if (i == 0) {
                            first = true;
                        }

                        Manager.setStore(new AjaxSolr.asu_dirParameterHistoryStore({
                            page_alias: page_alias,
                            tree: tree,
                            field_configs: field_configs,
                            dept_nids: saved_dept_nids,
                            field_id: field_id,
                            is_default: first,
                            id_num: id_num,
                            has_tabs: has_tabs,
                            tab_id: tab_id,
                            tab_pane_id: tab_pane_id,
                            tab_link: tab_link,
                            tab_num: i,
                            saved_dept_nids: saved_dept_nids
                        }));
                        Manager.store.exposed = ['fq', 'q', 'start', 'sort', 'rows'];
                    }
                    //init was here


                    // Add Solr parameters for faceting.
                    var params = {
                        facet: true,
                        'facet.field': fields,
                        'facet.limit': -1,
                        'facet.mincount': 1,
                        'f.topics.facet.limit': 50,
                        'json.nl': 'map'
                    };

                    if (Manager.store.params.q !== undefined && Manager.store.params.q.value !== '*:*') {
                        $("#asu-dir-ajax-solr-search input").val(Manager.store.params.q.value);
                    }

                    Manager.asu_dirFacetDisplay = [];
                    Manager.asu_dirFacetDisplay.dropdownFacets = fields;

                    // Assign all the params to the Manager's store.
                    for (var name in params) {
                        Manager.store.addByValue(name, params[name]);

                    }

                    if (!field_configs.show_tree && field_configs.hasOwnProperty('breadcrumb')) {
                        var crumb_element = $('.asu-dir-breadcrumb' + id_num);
                        crumb_element.html(field_configs.breadcrumb);
                    }

                    ASUPeople.man_array.push(Manager);
                }
            }//end of for loop

            for (var x = 0; x < ASUPeople.man_array.length; x++) {
                ASUPeople.man_array[x].init();
                ASUPeople.man_array[x].doRequest();
            }


        }
    };
})(jQuery, window.History);


/***
 * Function  to create concatenated deptids search string with OR operator
 *
 * @param field:  string value of the field to be queried in solr
 * @param items
 * @param quotes: boolean,  wrap each value in quotes or not
 * @returns {string}
 */
function asu_dir_solr_search_string(items, field, quotes) {
    field = field || 'deptids';
    quotes = quotes != null ? quotes : false;

    if (items.indexOf("Show All") > -1 || items.length == 0 || items == null) {
        return "employeeTypes:*";
    }

    var wrap = '';

    if (quotes) {
        wrap = '"';
    }

    var temp = field + ':(';
    var last = items.length - 1;

    for (var i = 0; i < items.length; i++) {

        temp += wrap + items[i] + wrap;
        if (i != last) {
            temp += ' OR ';
        }
    }

    temp += ')';

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

    if (tree === null) {
        return false;
    }


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

    check = decoded_uri.indexOf(dstring);

    var start = decoded_uri.indexOf(dstring) + dstring.length;
    var stop = start + 8;
    var nid = 0;

    //get the NID from the string
    nid = decoded_uri.slice(start, stop);
    nid = nid.replace(/\D/g, '');
    nid = parseInt(nid);
    return nid;
}

/**
 * Utility function to get the field id from the hash
 * @param hash
 */
function asu_dir_get_field_id_from_hash(hash) {

    var decoded_uri = decodeURIComponent(hash);
    var dstring = "id=";
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

