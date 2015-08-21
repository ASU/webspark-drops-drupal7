/**
 * ASU Directory module
 * People List JavaScript
 *
 * Provides AJAX behavior, pagination, modal, and sort for People block
 *
 * @author Colton Testamarck (ctestama@asu.edu)
 * @author Robert Jenkins ( rjenkins@eaglecrk.com )
 */
(function ($) {
    Drupal.behaviors.asu_dir_ppl_block = {
        attach: function (context, settings) {
            if (Drupal.settings && ( settings = Drupal.settings.asu_dir)) {
                if (( dept_nids = settings.dept_nids) && ( solr_server = settings.solr_server) && (field_configs = settings.field_configs) && (settings.admin !== undefined) && (top_level_ids = settings.top_level_ids)) {
                    $(window).bind('load', function () {
                        jQuery('#asu_directory_people_controls_bottom').hide();
                        var admin = settings.admin;
                        var query = null;

                        //this is the main people container
                        var $people = $('#people');

                        $people.data.field_items = dept_nids;
                        $people.data.top_level_ids = top_level_ids;
                        $people.data.field_configs = field_configs;

                        asu_dir_init_people($people);

                        if (field_configs.use_custom_q && field_configs.hasOwnProperty('custom_q')) {
                            query = field_configs.custom_q;
                        }

                        if (dept_nids[0] != top_level_ids.top_level_nid || field_configs.use_custom_q) {
                            asu_dir_build_table(query);
                        }

                        if (admin) {
                            asu_dir_activate_admin($people);
                        }

                        asu_dir_people_create_search(solr_server, settings.tree);

                        asu_dir_create_pagination();

                    })
                }
            }
        }
    };
})(jQuery);


/**
 * Assigns data to the people block to persist information for AJAX solr queries
 */
function asu_dir_init_people($people) {
    var $people = jQuery('#people');

    $people.data.sort = 'lastNameSort asc';
    $people.data.solr_server = solr_server;
    $people.data.manager_data = Object();

    $people.data.manager_data.department = 0;
    $people.data.manager_data.people = null;
    $people.data.manager_data.fq = '';
}

/**
 * Process configs and return a an object with solr query params
 *
 * @param $people
 * @param query
 * @returns {*}
 */
function asu_dir_build_query($people, query) {

    var field_configs = $people.data.field_configs;
    var field_items = [];
    var solr_data = {};
    var empl_types = $people.data.field_configs.employee_types;


    //if searching, search everything below the currently selected deparment
    //even if 'Show Sub-Departments' is not selected
    if ($people.data.search_mode && $people.data.hasOwnProperty('tree_nids')) {
        field_items = $people.data.tree_nids;
    } else {
        field_items = $people.data.field_items;
    }

    if ((field_configs.dept_id == $people.data.top_level_ids.top_level_psid || field_configs.dept_id == "" ) &&
        field_configs.use_custom_q === false) {
        return false;
    }

    if (!$people.data.page) {
        $people.data.page = 0;
    }

    //if custom query is selected, use that, otherwise get the global properties
    if ($people.data.field_configs.use_custom_q) {
        if (query) {
            solr_data = query;
        } else {
            var configs = $people.data.field_configs.custom_q;

            jQuery.each(configs, function (key, value) {
                solr_data[key] = value;
            });
        }
    } else {
        if ($people.data.hasOwnProperty('q')) {
            solr_data.q = $people.data.q;
        }
        else {
            solr_data.q = asu_dir_solr_search_string(field_items, 'deptids');
        }

        if ($people.data.hasOwnProperty('fq')) {
            solr_data.fq = $people.data.fq;
        } else {
            solr_data.fq = asu_dir_solr_search_string(empl_types, 'employeeTypes');
        }

        if ($people.data.hasOwnProperty('sort')) {
            solr_data.sort = $people.data.sort;

        } else {
            solr_data.sort = $people.data.sort = 'lastNameSort asc';
        }
    }

    var temp = solr_data.q;

    if ($people.data.search_mode == true) {
        solr_data.q = "(" + temp + ") AND " + $people.data.text;
    }

    //always return json format
    solr_data.wt = 'json';

    // Determine what page to display
    if (query && query.hasOwnProperty('offset')) {
        switch (query.offset) {
            case 'begin':
                $people.data.page = 0;
                break;
            case 'end':
                $people.data.page = $people.data.num_pages - 1;
                break;
            case 'previous':
                $people.data.page = $people.data.page - 1;
                break;
            case 'next':
                $people.data.page = $people.data.page + 1;
                break;
            default:
                $people.data.page = query.offset - 1;
        }
    }

    solr_data.start = ($people.data.page) * 10;

    return solr_data;
}

/**
 * Queries the solr server and for information about people in a given department
 * and constructs a table to display that information.
 *
 * @param {Object}
 *
 * information
 */
function asu_dir_build_table(query) {
    var $people = jQuery('#people');
    var solr_server = $people.data.solr_server;

    var show_managers = $people.data.field_configs.show_managers;
    var solr_data = {};

    if(!(solr_data = asu_dir_build_query($people, query))) {
        return false;
    }

    //if new custom query in admin display, clearout the people div before request
    if($people.data.page===0 && $people.data.field_configs.use_custom_q) {
        $people.html('');
        jQuery('#asu_directory_people_controls_bottom').hide();
    }

    //if the "Show Managers" Option is selected, and we are querying for the 1st page, run the management query
    if (show_managers && !$people.data.search_mode && !$people.data.field_configs.use_custom_q) {

        asu_dir_management_query(solr_server, solr_data);
        return false;
    }

    var html = '';

    jQuery.ajax({
        'url': solr_server,
        'cache': false,
        'data': solr_data,
        'dataType': 'jsonp',
        'jsonp': 'json.wrf',
        'success': function (data) {
            asu_dir_process_results($people, data);
        },
        // Handle timeout errors, since jsonp request will just hang if an error is thrown
        'timeout': 5000,
        'error': function (jqXHR, textStatus, errorThrown) {
            asu_dir_display_errors($people, textStatus);
        },
        'complete': function (jqXHR, textStatus) {
            asu_dir_after_query($people);
        }
    });
}

/**
 * Process results from main build_table function
 *
 */
function asu_dir_process_results($people, data) {

    var $controls_bottom = jQuery('#asu_directory_people_controls_bottom');

    if (!data.hasOwnProperty('responseHeader') || data.responseHeader.status != 0) {
        $people.html('<div>There was an error with this request.  Please try again later.</div>');
        return false;
    }

    // Show controls if they were hidden
    $controls_bottom.show();
    $people.data.num_pages = Math.ceil(data.response.numFound / 10);

    // Create markup to display received data
    html = asu_dir_build_table_markup(data.response.docs);
    jQuery('#people').html(html);
    // Fires asu_people_update event.
    jQuery('#people').trigger('asu_directory_people_update');

    asu_dir_set_page_buttons();

    //hide broken image containers
    jQuery('img').load(function () {
        jQuery(this).parent().removeClass('ppl_img');
    }).error(function () {
        jQuery(this).parent().addClass('ppl_img');
    });

    // If no employees in department, hide controls and display message
    if (data.response.numFound == 0) {
        $controls_bottom.hide();
        $people.html('<span>No employees found.</span>');
    }
}



/**
 *This is a function which will display managers at the top of the directory.  This operates differently since Solr cannot sort
 * by the managers field.   All solr data for the management will be queried and stored in the $people.data.manager, and
 * then pieced out by the asu_directory_build_ouput() function
 *
 * @param: {string} solr_server :  the url of the solr server
 * @param: {object} solr_data : the payload for the solr request
 */
function asu_dir_management_query(solr_server, solr_data) {

    //var $controls_bottom = jQuery('#asu_directory_people_controls_bottom');
    var $people = jQuery('#people');
    var with_management = '(' + solr_data.fq + ') AND (managers:1)';
    var without_management = '(' + solr_data.fq + ')';
    var dept_id = $people.data.field_items[0].toString();
    var $controls_bottom = jQuery('#asu_directory_people_controls_bottom');
    var all_people;

    //Query for managers first
    var managers = Array();

    //sort alphabetically
    solr_data.sort = "lastNameSort asc";

    if ($people.data.field_items[0] != $people.data.manager_data.department || $people.data.manager_data.people == null || $people.data.manager_data.fq != solr_data.fq) {

        $people.data.manager_data.fq = solr_data.fq;

        $people.data.manager_data.department = $people.data.field_items[0];

        solr_data.rows = 2000;
        solr_data.fq = with_management;

        jQuery.ajax({
            'url': solr_server,
            'cache': false,
            'data': solr_data,
            'dataType': 'jsonp',
            'jsonp': 'json.wrf',
            'success': function (data) {

                if (!data.hasOwnProperty('responseHeader') || data.responseHeader.status != 0) {
                    $people.html('<div>There was an error with this request.  Please try again later.</div>');
                    return false;
                }

                var results = data.response.docs;

                for (var i = 0; i < results.length; i++) {
                    if (results[i].managers.indexOf(1) == results[i].deptids.indexOf(dept_id)) {
                        managers.push(results[i]);
                    }
                }

                //build the filter query string for excluding the managers
                if (managers.length > 0) {
                    var stop_or = managers.length - 1;
                    without_management += '-(';

                    for (var j in managers) {
                        without_management += 'asuriteId:' + managers[j].asuriteId;
                        if (j != stop_or) {
                            without_management += ' OR ';
                        }
                    }
                    without_management += ')';
                }

                //Query for non-managers second
                solr_data.fq = without_management;

                jQuery.ajax({
                    'url': solr_server,
                    'cache': false,
                    'data': solr_data,
                    'dataType': 'jsonp',
                    'jsonp': 'json.wrf',
                    'success': function (data) {
                        if (!data.hasOwnProperty('responseHeader') || data.responseHeader.status != 0) {
                            $people.html('<div>There was an error with this request.  Please try again later.</div>');
                            return false;
                        }

                        var results = data.response.docs;

                        if (managers.length > 0) {
                            for (var j in managers) {
                                results.unshift(managers[j]);
                            }
                        }

                        all_people = $people.data.manager_data.people = results;
                        asu_dir_build_output(all_people, solr_data);
                    },
                    // Handle timeout errors
                    'timeout': 5000,
                    'error': function (jqXHR, textStatus, errorThrown) {
                        asu_dir_display_errors($people, textStatus);
                    },
                    'complete': function (jqXHR, textStatus) {
                        asu_dir_after_query($people);
                    }
                });
            },
            // Handle timeout errors
            'timeout': 5000,
            'error': function (jqXHR, textStatus, errorThrown) {
                asu_dir_display_errors($people, textStatus);
            },
            'complete': function (jqXHR, textStatus) {
                asu_dir_after_query($people);
            }
        });

    } else {
        all_people = $people.data.manager_data.people;
        asu_dir_build_output(all_people, solr_data);
    }
}


/**
 * Function to build the common components of the people display
 *
 * @param people
 */
function asu_dir_build_output(all_people, solr_data) {

    var $people = jQuery('#people');
    var $controls_bottom = jQuery('#asu_directory_people_controls_bottom');

    // If no employees in department, hide controls and display message
    if (all_people.length == 0) {
        $controls_bottom.hide();
        $people.html('<span>No employees found.</span>');
    }

    if (all_people.length > 0) {

        var offset = solr_data.start;
        var sub_array = all_people.slice(offset, offset + 10);

        $people.data.num_pages = Math.ceil(all_people.length / 10);

        // Show controls if they were hidden
        $controls_bottom.show();
        // Assign data to the #people div for later use
        $people.data.num_pages = Math.ceil(all_people.length / 10);

        // Create markup to display received data
        html = asu_dir_build_table_markup(sub_array);
        $people.html(html);
        // Fires asu_people_update event.
        $people.trigger('asu_directory_people_update');

        asu_dir_set_page_buttons();

        // Replace missing/broken images with generic user icon
        //Most images coming from isearch-dev are broken right now, so removing broken images is done by jQuery
        jQuery('img').load(function () {
            jQuery(this).parent().removeClass('ppl_img');
        }).error(function () {
            jQuery(this).parent().addClass('ppl_img');
        });
    }
}

/**
 * Function to attach click events to admin buttons
 *
 */
function asu_dir_activate_admin($people) {
    var showtree_element = jQuery('#asu_directory_show_tree');
    var manager_element = jQuery('#asu_directory_show_managers');
    var breadcrumb_toggle = jQuery('#asu_directory_show_breadcrumbs');
    var subtoggle_switch = jQuery('#asu_directory_show_subs');
    var type_buttons = jQuery('#asu_directory_employee_type_select').find('.asu_directory_type_select');
    var custom_group = jQuery('.asu_directory_custom_group');
    var custom_button = jQuery('#asu_directory_custom_query');
    var custom_save = jQuery('#asu_directory_custom_q_submit');

    if ($people.data.field_configs.sub_toggle == true) {
        subtoggle_switch.addClass('sub_activated');
        $people.data.field_configs.show_managers = false;
    }

    if ($people.data.field_configs.show_managers == true) {
        manager_element.addClass('active');
    }

    if ($people.data.field_configs.show_tree == true) {
        showtree_element.addClass('active');
    }

    if ($people.data.field_configs.show_breadcrumbs == true) {
        breadcrumb_toggle.addClass('active');
    }

    if ($people.data.field_configs.use_custom_q === true) {
        custom_button.addClass('active');
        custom_group.show();
        custom_save.addClass('asu_directory_custom_saved');
        custom_save.find('.custom-status').html('Saved');
        asu_dir_toggle_custom_query(true, $people, false);
    }

    var selected_types = $people.data.field_configs.employee_types;

    for (i = 0; i < selected_types.length; i++) {
        jQuery('#asu_directory_employee_type_select :button[value="' + selected_types[i] + '"]').addClass('active');
    }

    showtree_element.click(function (event) {
        event.preventDefault();
        $people.data.field_configs.show_tree = !$people.data.field_configs.show_tree;
        jQuery(this).toggleClass('active');
        asu_dir_set_field($people);
    });

    breadcrumb_toggle.click(function (event) {
        event.preventDefault();
        $people.data.field_configs.show_breadcrumbs = !$people.data.field_configs.show_breadcrumbs;
        jQuery(this).toggleClass('active');
        asu_dir_set_field($people);
    });


    manager_element.click(function (event) {
        event.preventDefault();

        //button should be disabled if sub_toggle is true, but in case it gets clicked
        $people.data.field_configs.show_managers = !$people.data.field_configs.show_managers;

        if ($people.data.field_configs.show_managers == true) {
            $people.data.field_configs.sub_toggle = false;
            subtoggle_switch.removeClass('sub_activated');
            var temp = $people.data.field_items[0];
            $people.data.field_items = [temp];
        }

        jQuery(this).toggleClass('active');
        $people.data.page = 0;
        asu_dir_set_field($people);
        asu_dir_build_table();
        asu_dir_cleanup($people);

    });

    type_buttons.mousedown(function (event) {
        event.preventDefault();

        jQuery(this).toggleClass('active');

        delete $people.data.field_configs.employee_types;

        var temp_array = Array();

        jQuery('#asu_directory_employee_type_select .active').each(function (index) {
            temp_array.push(jQuery(this).val());
            if (jQuery(this).val() == "Show All") {
                return false;
            }
        });

        //if array is empty, add "Show All" by default
        if (temp_array.length == 0) {
            temp_array.push("Show All");
        }

        $people.data.sort = 'lastNameSort asc';
        $people.data.field_configs.employee_types = temp_array;
        $people.data.page = 0;

        asu_dir_set_field($people);
        asu_dir_cleanup($people);
        asu_dir_build_table();

    });

    subtoggle_switch.mousedown(function (event) {

        var show_managers = jQuery('#asu_directory_show_managers');

        $people.data.page = 0;

        $people.data.field_configs.sub_toggle = !$people.data.field_configs.sub_toggle;

        //Store items and configs for our Drupal ASU_Directory field
        if ($people.data.field_configs.sub_toggle == true) {
            $people.data.field_items = $people.data.tree_nids;
            show_managers.removeClass('active');
            $people.data.field_configs.show_managers = false;

        } else {
            var temp = $people.data.field_items[0];
            $people.data.field_items = [temp];
        }

        subtoggle_switch.toggleClass('sub_activated');

        asu_dir_set_field($people);
        asu_dir_cleanup($people);
        asu_dir_build_table();

    });

    custom_button.click(function (event) {
        event.preventDefault();
        $people.data.field_configs.use_custom_q = !$people.data.field_configs.use_custom_q;
        jQuery(this).toggleClass('active');

        asu_dir_toggle_custom_query($people.data.field_configs.use_custom_q, $people, true);
        if ($people.data.field_configs.use_custom_q === false) {
            asu_dir_build_table();
            asu_dir_cleanup($people);
        }
    });

    custom_save.click(function (event) {
        //$people.data.page = 0;
        event.preventDefault();
        asu_dir_run_custom_query($people);
    });

    // Search event for input field
    custom_group.bind('keypress keyup change', function (event) {
        var keycode = (event.keyCode ? event.keyCode : event.which);
        if (keycode == '13') {
            event.preventDefault();
            asu_dir_run_custom_query($people);
        } else {
            custom_save.removeClass('asu_directory_custom_saved');
            custom_save.find('.custom-status').html('Save/Run');
        }

    });
}

/***
 * Run and save custom query.
 *
 *
 */
function asu_dir_run_custom_query($people) {
    var q = jQuery('.asu_directory_q').val();
    var fq = jQuery('.asu_directory_fq').val();
    var sort = jQuery('.asu_directory_sort').val();
    var $button = jQuery('#asu_directory_custom_q_submit');

    //set other configs to false
    $people.data.field_configs.show_tree = false;
    $people.data.field_configs.show_breadcrumbs = false;
    $people.data.field_configs.show_managers = false;

    var query = {};

    if (q != '' && q != undefined) {
        query.q = q;
    } else {
        query.q = "*:*";
    }

    if (fq != '' && fq != undefined) {
        query.fq = fq;
    }

    if (sort != '' && sort != undefined) {
        query.sort = sort;
    } else {
        query.sort = "lastNameSort asc";
    }

    if (!$button.hasClass('asu_directory_custom_saved')) {
        $button.addClass('active');
        $button.find('.custom-status').html('Saved');
        $button.addClass('asu_directory_custom_saved');

        $people.data.field_configs.custom_q = query;
        asu_dir_set_field($people);

        asu_dir_cleanup($people);
        asu_dir_build_table(query);
    }
}


/**
 * Modify the form when toggling custom query
 * on and off.
 *
 */
function asu_dir_toggle_custom_query(custom, $people, reset) {
    if (reset === true) {
        asu_dir_reset_configs($people);
    }

    var custom_group = jQuery('.asu_directory_custom_group');

    var elements = [];
    elements.push(jQuery('.asu_directory_toggle_subdirectory'));
    elements.push(jQuery('#asu_directory_employee_type_select'));
    elements.push(jQuery('#asu_directory_show_tree'));
    elements.push(jQuery('#asu_directory_show_managers'));
    elements.push(jQuery('#asu_directory_show_breadcrumbs'));
    elements.push(jQuery('.asu-directory-tree-hierarchy'));

    if (custom) {
        custom_group.show();

        jQuery('#edit-title').val('Custom Query');
        jQuery('.asu_directory_breadcrumb').hide();
        var custom_q = $people.data.field_configs.custom_q;

        if (custom_q.hasOwnProperty('q')) {
            jQuery('.asu_directory_q').val(custom_q.q);
        }

        if (custom_q.hasOwnProperty('q')) {
            jQuery('.asu_directory_fq').val(custom_q.fq);
        }

        if (custom_q.hasOwnProperty('sort')) {
            jQuery('.asu_directory_sort').val(custom_q.sort);
        }

        jQuery('.asu_directory_show_subs').removeClass('sub_activated');

        jQuery.each(elements, function (index, value) {
            value.removeClass('active');
            value.hide();
        });
    } else {
        custom_group.hide();
        jQuery('.asu_directory_breadcrumb').show();
        jQuery.each(elements, function (index, value) {
            value.show();
        });
    }
}

/***
 * Reset ASU Directory configs on click event
 *
 */
function asu_dir_set_field($people) {
    // var $people = jQuery('#people');

    var configs = jQuery('#dhidden_config input');
    configs.val(JSON.stringify($people.data.field_configs));

    var items = jQuery('#dhidden_items input');
    items.val(JSON.stringify($people.data.field_items));
}


/**
 * Creates click for page buttons events to build ajax page requests
 */
function asu_dir_create_pagination() {
    var query = {};
    var $buttons = jQuery('#asu_directory_people_controls_bottom').find('.asu_directory_people_button');
    var $ellipses = jQuery('.asu_directory_people_ellipses');
    var $people = jQuery('#people');


    $buttons.mousedown(function (event) {

        // Only fire on left click if button is not inactive
        if (event.which == 1 && !jQuery(this).hasClass('disabled')) {

            if ($people.data.field_configs.use_custom_q && $people.data.field_configs.hasOwnProperty('custom_q')) {
                query = $people.data.field_configs.custom_q;
            }

            // Determine offest based on which button was pressed
            switch (jQuery(this).attr('id')) {
                case 'asu_directory_people_begin_btn':
                    query.offset = 'begin';
                    break;
                case 'asu_directory_people_prev_btn':
                    query.offset = 'previous';
                    break;
                case 'asu_directory_people_next_btn':
                    query.offset = 'next';
                    break;
                case 'asu_directory_people_end_btn':
                    query.offset = 'end';
                    break;
                default:
                    query.offset = jQuery(this).find('span').text();
            }

            // Rebuild table
            asu_dir_build_table(query);
        }
    });

    $ellipses.mousedown(function (event) {

        // Only fire on left click if button is not inactive
        if (event.which == 1 && !jQuery(this).hasClass('disabled')) {

            if ($people.data.field_configs.use_custom_q && $people.data.field_configs.hasOwnProperty('custom_q')) {
                query = $people.data.field_configs.custom_q;
            }

            // Determine offest based on which button was pressed
            query.offset = jQuery(this).find('span').text();

            // Rebuild table
            asu_dir_build_table(query);

        }
    });
}


/**
 * Controls display of pagination interface
 */
function asu_dir_set_page_buttons() {
    var $people = jQuery('#people');
    var $buttons = jQuery('#asu_directory_people_controls_bottom').find('.asu_directory_people_button');
    var $ellipses = jQuery('.asu_directory_people_ellipses');
    $buttons.removeClass('disabled');
    // Remove page controls if there are not enough record to paginate
    if ($people.data.num_pages <= 1) {
        jQuery('#asu_directory_people_controls_bottom').hide();
    }
    // Deactivate [previous] button if we are on the first page
    else if ($people.data.page == 0) {
        jQuery('#asu_directory_people_controls_bottom').show();
        $buttons.eq(0).addClass('disabled');
    }
    // Deactivate [next] button if we are on the last page
    else if ($people.data.page >= $people.data.num_pages - 1) {
        jQuery('#asu_directory_people_controls_bottom').show();
        $buttons.eq(8).addClass('disabled');
    }
    // If fewer than three pages, hide the beginning / ending numerical buttons and
    // ellipses
    if ($people.data.num_pages <= 3) {
        $buttons.eq(1).hide();
        $buttons.eq(7).hide();
        $ellipses.hide();
    }
    else {

        // If on 3rd or lower page, hide beginning numerical button and ellipse
        if ($people.data.page > 2) {
            $buttons.eq(1).html('<span>1</span>').show();

            if ($people.data.page == 3) {
                $ellipses.eq(0).hide();
            } else if ($people.data.page == 4) {
                $ellipses.eq(0).html('<span>2</span>').removeClass('disabled').show();
            } else {
                $ellipses.eq(0).html('<span>...</span>').addClass('disabled').show();
            }
        }
        // Otherwise, show it
        else {
            $buttons.eq(1).hide();
            $ellipses.eq(0).hide();
        }
        // If on 3rd page from end or lower, hide ending numerical button and ellipse\\

        if ($people.data.page < $people.data.num_pages - 3) {
            $buttons.eq(7).html('<span>' + $people.data.num_pages + '</span>').show();

            if ($people.data.page == $people.data.num_pages - 4) {
                $ellipses.eq(1).hide();

            } else if ($people.data.page == $people.data.num_pages - 5) {
                $ellipses.eq(1).html('<span>' + ($people.data.num_pages - 1) + '</span>').removeClass('disabled').show();
            } else {
                $ellipses.eq(1).html('<span>...</span>').addClass('disabled').show();
            }

        }
        //Otherwise, show it
        else {
            $buttons.eq(7).hide();
            $ellipses.eq(1).hide();
        }
    }
    var page = $people.data.page;
    var num_pages = $people.data.num_pages;
    // Set text for center "current page" button
    $buttons.eq(4).html('<span>' + (page + 1) + '</span>');
    // Set behavior for remaining buttons
    if (page >= 2) {
        $buttons.eq(3).html('<span>' + page + '</span>').show();
        $buttons.eq(2).html('<span>' + (page - 1) + '</span>').show();
    }
    else if (page >= 1) {
        $buttons.eq(3).html('<span>' + page + '</span>').show();
        $buttons.eq(2).hide();
    }
    else if (page == 0) {
        $buttons.eq(3).hide();
        $buttons.eq(2).hide();
    }
    if (page <= num_pages - 3) {
        $buttons.eq(5).html('<span>' + (page + 2) + '</span>').show();
        $buttons.eq(6).html('<span>' + (page + 3 ) + '</span>').show();
    }
    else if (page <= num_pages - 2) {
        $buttons.eq(5).html('<span>' + (page + 2) + '</span>').show();
        $buttons.eq(6).hide();
    }
    else if (page == num_pages - 1) {
        $buttons.eq(5).hide();
        $buttons.eq(6).hide();
    }
}


/**
 * Creates HTML markup and injects information from AJAX Solr query into it
 * @param {JSON} data
 */
function asu_dir_build_table_markup(data) {

    var isearch_url = "https://isearch.asu.edu/profile/";
    var docs = data;
    var markup = '';
    var even = '';

    for (var i in docs) {

        even = '';

        if (i % 2 == 0) {
            even = 'asu_people_row_even';
        }
        //open row
        markup += '<div eid="' + docs[i].eid + '" class="row row-header asu_directory_people_row ' + even + '" >';

        var col_width = 'col-md-6';

        //PHOTO COLUMN
        if (docs[i].photoUrl != null && docs[i].photoUrl != '') {
            col_width = 'col-md-4';
            markup += '<div class="col-md-2 ppl_img"><img class="people_thumb img-responsive" src="' + docs[i].photoUrl + '" /></div>';
        }

        //concatenate string with all titles, and departments, followed by ; --limiting this to 3 titles/departments for display purposes
        var title_string = '';
        var titles = docs[i].titles;

        if (titles !== undefined) {
            for (var j = 0; j < titles.length && j < 3; j++) {
                title_string += titles[j] + ", " + docs[i].departments[j] + "; ";
            }
        }

        //NAME AND TITLE COLUMN
        markup += '<div class="' + col_width + '"><div class="row-profile-text row-field"><a href="' + isearch_url + docs[i].eid + '" class="displayName viewDetails" id="' + docs[i].eid + '">';
        markup += (docs[i].displayName != null ? docs[i].displayName : '') + '</a><br>';
        markup += '<div class="job-title">' + title_string + '</div></div></div>';

        //CONTACT INFO COLUMN
        markup += '<div class="col-md-3"><div class="row-profile-contact"><div class="row-profile-email row-field"><a class="emailAddress"';
        markup += 'href="mailto:' + docs[i].emailAddress + '">' + docs[i].emailAddress + '</a><br>';

        if (docs[i].hasOwnProperty('phone') && docs[i].phone != '') {
            markup += '<span class="phone_number">' + docs[i].phone + '</span>';
        }

        markup += '</div></div></div>';

        //close row
        markup += '</div>';

    }
    return markup;
}

/**
 * Search behavior for the People block
 */
function asu_dir_people_create_search() {
    var $input = jQuery('#asu_directory_people_search_box');
    var $button = jQuery('#asu_directory_people_search_btn');
    var $form = jQuery('#asu_directory_people_search_group');
    var $people = jQuery('#people');
    var list = [];

    // Search event for button
    $button.bind('click', function (event) {
        event.preventDefault();
        if ($people.data.field_items.length > 2000) {
            alert('There are too many departments to search through. Please narrow your search by selecting a sub-department from the Department Hierarchy and try again.');
        }
        else {
            asu_dir_people_search($people, $input);
        }
    });
    // Search event for input field
    $input.bind('keypress', function (event) {

        var keycode = (event.keyCode ? event.keyCode : event.which);
        if (keycode == '13') {
            event.preventDefault();

            if ($people.data.field_items.length > 2000) {
                alert('There are too many departments to search through. Please narrow your search by selecting a sub-department from the Department Hierarchy and try again.');
            }
            else {
                asu_dir_people_search($people, $input);
            }
        }
    });
}

/**
 * Parses through the department tree and returns a subtree
 * @param {object} data : The department tree
 * @param {String} data : The department ID on which the subtree should be based
 */
function asu_dir_people_find_root(data, dept_id) {
    var success = null;
    for (var i = 0; i < data.length; i++) {
        if (success == null) {
            if (data[i].dept_nid == dept_id) {
                return data[i];
            }
            else if (data[i].hasOwnProperty('children')) {
                success = asu_dir_people_find_root(data[i].children, dept_id);
            }
        }
        else {
            break;
        }
    }
    return success;
}

/**
 * Creates a solr query and calls the method to rebuild the table
 * @param {object} $input : The jQuery object that holds the input field
 * @param {object} $people : The jQuery object that holds the people mock-table
 */
function asu_dir_people_search($people, $input) {
    var text = $input.val();

    if (text != "" && text != undefined) {
        var text = text.split(' ');
        var query = {};
        var $people = jQuery('#people');

        for (var i in text) {
            text[i] = "*" + text[i] + "*";
        }
        $people.data.search_mode = true;
        $people.data.text = text;
        $people.data.page = 0;
        asu_dir_build_table();

    } else {

        asu_dir_cleanup($people);
        asu_dir_build_table();
    }

}

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


/**
 * Function to cleanup query variables after switching options
 *
 *
 */
function asu_dir_cleanup($people) {
    $people.data.page = 0;
    $people.data.search_mode = false;
    delete $people.data.text;
    delete $people.data.fq;
    delete $people.data.q;
    delete $people.data.sort;
    jQuery('.asu_directory_people_search_group input').val('');
}

/**
 * Reset all of the configs to the most basic configuration.
 *
 *
 * @param $people
 */
function asu_dir_reset_configs($people) {

    var custom_query_selected = $people.data.field_configs.use_custom_q;
    var query = $people.data.field_configs.custom_q;
    var field_configs = $people.data.field_configs;

    field_configs.show_breadcrumbs = false;
    field_configs.show_managers = false;
    field_configs.show_tree = false;
    field_configs.employee_types = ["Show All"];

    jQuery('#asu_directory_people_controls_bottom').hide();

    asu_dir_set_field($people);

    jQuery('#asu_directory_employee_type_select button').removeClass('active');
    jQuery("[value='Show All']").addClass('active');

    $people.html('');
}

/**
 * Clean up after a an ajax query request is run
 *
 * @param $people
 */
function asu_dir_after_query($people) {
    if ($people.data.field_configs.use_custom_q === true) {
        jQuery('#asu_directory_custom_q_submit').removeClass('active');
    }
}

/**
 * Display errors after an ajax query request
 *
 * @param $people
 * @param error_text
 */
function asu_dir_display_errors($people, error_text) {
    var $controls_top = jQuery('#asu_directory_people_controls_top');
    var $controls_bottom = jQuery('#asu_directory_people_controls_bottom');

    $controls_top.hide();
    $controls_bottom.hide();
    $people.text('Error: ' + error_text + '. This might be a bad request. Please contact a site administrator if the problem persists.');
}
