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
            var tabs = null;
            var hasTabs = false;
            var tabContainId = '';
            var tabLinks = [];
            var tabsIDs = null;
            var universalCheck = $('.asu-dir-universal-filters').length > 0;

            // reset the ASUPeople global whenever reloading js, because it can cause weirdness with panels IPE
            ASUPeople = {};
            ASUPeople.man_array = [];
            ASUPeople.tab_list = {};

            // figure out if there are asu_dir tabbed panels
            if (Drupal.settings.websparkPanelsTabs != null) {
                tabsIDs = Drupal.settings.websparkPanelsTabs.tabsID;
            } else if (Drupal.settings.panelsTabs != null) {
                tabsIDs = Drupal.settings.panelsTabs.tabsID;
            }

            if (tabsIDs != null) {
                for (var key in tabsIDs) {
                    if ($('#' + tabsIDs[key] + ' .field-type-asu-directory').length > 0) {
                        hasTabs = true;
                        tabContainId = tabsIDs[key];
                        tabLinks = $('#' + tabContainId + ' .item-list a.ui-tabs-anchor');
                        tabs = $('#' + tabContainId + ' .field-type-asu-directory');
                        break;
                    }
                }
            }

            for (var i = 0; i < directories.length; i++) {

                var fieldId = directories[i].id;
                ASUPeople[fieldId] = {};
                ASUPeople[fieldId].dept_nid = 0;
                ASUPeople[fieldId].dept_id = '';
                var tab_pane = null;
                var tabPaneId = '';

                // todo: pass in the universal search box ID
                var universalSearchBoxId = '#asu-dir-ajax-solr-search-universal';

                // the real tab num is the index of the asu_dir tab in the tab nav set
                // the dirTabNum keeps track of where the current asu_dir is being placed in the
                // tab links array
                var realtabnum = 0;
                var dirTabNum = 0;


                // configure the tab properties of the directory tab pane, to allow
                // for keeping of state between directory panes
                if (hasTabs) {

                    for (var j = 0; j < tabLinks.length; j++) {

                        var tab = tabLinks.eq(j);
                        var theid = tab.attr('href');

                        var found = $(theid).find('#' + fieldId);

                        if (found.length > 0) {
                            realtabnum = j;
                        } else {
                            // look for view in pane, and add class if so
                            var is_view = $(theid).find('.view');
                            if (is_view.length > 0) {
                                if (!tabLinks.eq(j).hasClass('asu_isearch_view_tab')) {
                                    tabLinks.eq(j).addClass('asu_isearch_view_tab')
                                }
                            }
                        }
                    }

                    tabPaneId = tabLinks.eq(realtabnum).attr('href');


                    // save pane to global tab_list object
                    ASUPeople.tab_list[fieldId] = {};
                    ASUPeople.tab_list[fieldId].realTabNum = realtabnum;

                    // set dirTabnum to the real tab index within the jquery ui tab set
                    dirTabNum = realtabnum;
                }

                if (settings.hasOwnProperty(fieldId)) {
                    var isettings = settings[fieldId];

                    // get the configs passed in by Drupal
                    var topLevelIds = isettings.topLevelIds;
                    var fieldConfigs = isettings.fieldConfigs;
                    ASUPeople[fieldId].fieldConfigs = fieldConfigs;

                    console.log(fieldConfigs, 'THE FIELD CONFIGS');

                    // array of all saved dept nids
                    var savedDeptNids = isettings.deptNids;

                    // id of top level configured department
                    var savedDeptId = fieldConfigs.dept_id;

                    var solrServer = isettings.solrServer;
                    var pageAlias = isettings.pageAlias;

                    // this is the ASU Directory field id number from Drupa
                    var fidNum = fieldConfigs.pane_id;
                    var resPerPage = 10;
                    var localPeople = isettings.localPeople;
                    var iSearchUrl = isettings.iSearchUrl;
                    var filters = [];
                    var depts = fieldConfigs.depts.items;

                    // set the number of results per page, this will be added to the manager store as the
                    // 'rows' parameter.
                    if (fieldConfigs.pager_display == 'paged' && fieldConfigs.pager_items_per_page != 0) {
                        resPerPage = fieldConfigs.pager_items_per_page;

                    // if we want to show all results, then we set the 'rows' parameter to 200000,
                    // since that is the maximum request size we will want.
                    } else if (fieldConfigs.pager_display == 'all' || fieldConfigs.pager_items_per_page == 0) {
                        resPerPage = 200000;
                    }

                    // Build the pre-configured filter values, and store them in the fieldConfigs
                    // ADD FILTERING FOR TENURE OR NON-TENURE FACULTY TITLES, IF APPLICABLE
                    if (fieldConfigs.tenure_display && fieldConfigs.faculty_titles != null && fieldConfigs.tenure_display != 'Both') {
                        var facTitles = fieldConfigs.faculty_titles.titles;
                        var filtered = [];
                        var titleSearch = '';

                        if (fieldConfigs.tenure_display == 'Tenure') {
                            filtered = facTitles.filter(function (element, index, array) {
                                return (element.tenure === 1);
                            });
                        } else {
                            filtered = facTitles.filter(function (element, index, array) {
                                return (element.tenure === 0);
                            });
                        }

                        filtered = filtered.map(function (e) {
                            return e.name;
                        });

                        titleSearch += asu_dir_solr_search_string(filtered, 'facultyTitlesFacet', true);

                        fieldConfigs.ft_filter = titleSearch;
                        filters.push(titleSearch);
                    }


                    // Add the pre-configured filters to the fieldConfigs.  These are set in the field form,
                    // so we don't need to display these as facet fields or active filters.  They are handled behind
                    // the scenes.
                    fieldConfigs.filters = filters;

                    resPerPage = parseInt(resPerPage);

                    //create the dept. tree from the root dept
                    ASUPeople[fieldId].dept_nid = savedDeptNids[0];
                    var topNid = savedDeptNids[0];
                    var tree = [];

                    // Add widget instances for each facet.
                    //these are the fields which will be used for faceted search
                    //todo:  primary title facet?
                    var fields = ['expertiseAreasFacet', 'facultyTitlesFacet'];

                    //these are fields which will override the manager sort, and also the alpha filter widget
                    var overrideFields = ['lastName', 'primaryTitle', 'expertiseAreasFacet', 'facultyTitlesFacet'];

                    if (isettings.hasOwnProperty('tree') && isettings.tree.constructor != Array) {
                        tree = JSON.parse(isettings.tree);
                    } else {
                        tree = isettings.tree;
                    }

                    //stick with entire tree if top nid is not defined
                    if (topNid != null && tree) {

                        var ttree = [];

                        for (var k = 0; k < depts.length; k++) {
                            var tnid = depts[k].dept_nid;
                            ttree.push(asu_dir_ajax_solr_find_root(tree, tnid));
                        }

                        // Set the root of the tree to the point defined by id -> set by asu_directory.module
                        tree = ttree;
                    }

                    //Configure AjaxSolr
                    Manager = new AjaxSolr.asu_dirManager({
                        solrUrl: solrServer,
                        fieldConfigs: fieldConfigs,
                        overrideFields: overrideFields,
                        fieldId: fieldId,
                        perPage: resPerPage,
                        localPeople: localPeople
                    });

                    // Add in stock pager widget.
                    Manager.addWidget(new AjaxSolr.asu_dirPagerWidget({
                        id: 'pager',
                        target: '#asu-dir-ajax-solr-pager' + fidNum,
                        prevLabel: '<i class="fa fa-angle-double-left"></i><span class="asu-dir-hidden">Previous</span>',
                        nextLabel: '<i class="fa fa-angle-double-right"></i><span class="asu-dir-hidden">Next</span>',
                        innerWindow: 1,
                        renderHeader: function (perPage, offset, total) {
                            $('#pager-header').html($('<span></span>').text('displaying ' + Math.min(total, offset + 1) + ' to ' + Math.min(total, offset + perPage) + ' of ' + total));
                        },
                        per_page: resPerPage,
                        fieldConfigs: fieldConfigs
                    }));

                    //Add the Alpha bar widget
                    Manager.addWidget(new AjaxSolr.asuAlphaBarWidget({
                        id: 'asuAlphaBar',
                        target: '#ajax-solr-alpha-bar' + fidNum,
                        solrServer: solrServer,
                        fieldConfigs: fieldConfigs,
                        lastNameField: 'lastName',
                        fieldId: fieldId
                    }));

                    if (fieldConfigs.show_tree) {
                        // Add in a custom widget for managing the jqTree
                        Manager.addWidget(new AjaxSolr.asu_dirTreeWidget({
                            id: 'dirTree',
                            target: '#treediv' + fidNum,
                            tree: tree,
                            fieldConfigs: fieldConfigs,
                            topLevelIds: topLevelIds,
                            fieldId: fieldId,
                            fidNum: fidNum,
                            savedDeptId: savedDeptId
                        }));
                    }
                    //First Item in array will be the default Sort
                    var sort_items = [
                        {
                        'field_name': 'lastNameSort',
                        'fieldId': '#dir-lastNameSort' + fidNum
                        },
                        {//field doesn't actually exist in solr yet
                            'field_name': 'tsort',
                            'fieldId': '#dir-rankSort' + fidNum
                        },
                        {
                            'field_name': 'firstNameSort',
                            'fieldId': '#dir-firstNameSort' + fidNum
                        }
                    ];

                    var default_sort = fieldConfigs.default_sort_by;

                    //todo: remove this after removing usages
                    var titlesort_field = 'tsort';

                    // Add Sorting widget
                    // We add this even if the option to show_filters is not selected, because this handles the
                    // initial selected sorting and sorting for subsequent requests
                    Manager.addWidget(new AjaxSolr.asu_dirSortWidget({
                        id: 'asuDirSort',
                        target: '#asu-dir-ajax-solr-sort' + fidNum,
                        sortItems: sort_items,
                        fieldConfigs: fieldConfigs,
                        defaultSort: default_sort,
                        titleSortField: titlesort_field,
                        fieldId: fieldId
                    }));


                    // Add in Results widget. See our custom
                    // js/widgets/isPeopleResultWidget.js method extending AbstractWidget.
                    Manager.addWidget(new AjaxSolr.asu_dirResultWidget({
                        id: 'people',
                        target: '#asu-dir-ajax-solr-people' + fidNum,
                        solrServer: solrServer,
                        fieldConfigs: fieldConfigs,
                        overrideFields: overrideFields,
                        fieldId: fieldId,
                        perPage: resPerPage,
                        localPeople: localPeople,
                        iSearchUrl: iSearchUrl
                    }));

                    // only show these if the option is selected
                    if (fieldConfigs.show_filters) {

                        if (fieldConfigs.show_filter_faculty_titles) {
                            Manager.addWidget(new AjaxSolr.asu_dirFacetWidget({
                                id: 'facultyTitlesFacet' + fidNum,
                                target: '#facultyTitlesFacet' + fidNum,
                                field: 'facultyTitlesFacet'
                            }));
                        }

                        if (fieldConfigs.show_filter_expertise) {
                            Manager.addWidget(new AjaxSolr.asu_dirFacetWidget({
                                id: 'expertiseAreasFacet' + fidNum,
                                target: '#expertiseAreasFacet' + fidNum,
                                field: 'expertiseAreasFacet'
                            }));
                        }
                    }

                    // Manager.addWidget(new AjaxSolr.asu_dirFacetWidget({
                    // id: 'primaryTitleFacet'+fidNum,
                    // target: '#primaryTitleFacet'+fidNum,
                    // field: 'primaryTitlefacetf'
                    // }));

                    var selection_target = 'asu-dir-ajax-solr-selections';

                    // exclude these fields from the current search display, since they are pre-configured
                    // and either always in effect, or handled elsewhere
                    var excludes = ["deptids", "employeeTypes", "lastName", "expertiseAreas:", "titles", 'asuriteId'];
                    Array.prototype.push.apply(excludes, filters);

                    // CURRENT SEARCH 'BREADCRUMB' WIDGET
                    // Displays the current search or active filter next to 'People>', which allows toggling the filter off
                    // via a click to the 'x' near the active term.
                    // The universal filter form has a reset button and intuitive form filters,
                    // so there's no reason to have the current search breadcrumb showing
                    if (!universalCheck && fieldConfigs.show_filters) {
                        Manager.addWidget(new AjaxSolr.asu_dirCurrentSearchWidget({
                            id: 'currentSelections' + fidNum,
                            target: '#' + selection_target + fidNum,
                            fieldConfigs: fieldConfigs,
                            tree: tree,
                            fieldId: fieldId,
                            fidNum: fidNum,
                            current_search_exclude: excludes
                        }));
                    }

                    // SEARCH BOX WIDGET - only add the widget if we're configured to show it,
                    // or are using the universal filters
                    if (fieldConfigs.show_filter_omni || universalCheck) {

                        var theTarget = '#asu-dir-ajax-solr-search' + fidNum;

                        if (universalCheck) {
                            theTarget = universalSearchBoxId;
                        }

                        // Add in Text input/search widget. See our custom isTextWidget method
                        // extending AbstractWidget in js/widgets/isTextWidget.js.
                        Manager.addWidget(new AjaxSolr.asu_dirTextWidget({
                            id: 'text',
                            target: theTarget,
                            fieldConfigs: fieldConfigs,
                            tree: tree,
                            fieldId: fieldId
                        }));
                    }



                    // if this is the first manager created, make it the default.  this will allow us to
                    // keep track of which field the
                    var first = false;

                    if (dirTabNum == 0) {
                        first = true;
                    }

                    Manager.setStore(new AjaxSolr.asu_dirParameterHistoryStore({
                        pageAlias: pageAlias,
                        tree: tree,
                        fieldConfigs: fieldConfigs,
                        deptNids: savedDeptNids,
                        fieldId: fieldId,
                        isDefault: first,
                        fidNum: fidNum,
                        hasTabs: hasTabs,
                        tabContainId: tabContainId,
                        tabPaneId: tabPaneId,
                        tabNum: dirTabNum,
                        savedDeptNids: savedDeptNids
                    }));

                    Manager.store.exposed = ['fq', 'q', 'start', 'sort', 'rows'];


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

                    // if option to show breadcrumbs is enabled, then initialize with saved value
                    if (!fieldConfigs.show_tree && fieldConfigs.hasOwnProperty('breadcrumb')) {
                        var crumb_element = $('.asu-dir-breadcrumb' + fidNum);
                        crumb_element.html(fieldConfigs.breadcrumb);
                    }

                    ASUPeople.man_array.push(Manager);
                }
            }//end of for loop


            // once all widgets have been attached to each directory,
            // init and doRequest
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

