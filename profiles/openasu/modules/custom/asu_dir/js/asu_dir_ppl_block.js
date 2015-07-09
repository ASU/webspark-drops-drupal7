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

                        var admin = settings.admin;

                        //this is the main people container
                        var $people = $('#people');

                        dept_nids = JSON.parse(dept_nids);

                        $people.data.field_items = dept_nids;

                        //employee types is still encoded so we'll decode here
                        field_configs.employee_types = JSON.parse(field_configs.employee_types);

                        $people.data.field_configs = field_configs;

                        asu_dir_init_people();

                        if (dept_nids[0] != top_level_ids.top_level_nid) {
                            asu_dir_build_table(null, true);
                        }

                        if (admin) {
                            asu_dir_activate_admin();
                        }

                        asu_dir_show_subdepts();

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
function asu_dir_init_people() {
    var $people = jQuery('#people');

    jQuery('#asu_directory_people_top_filter_aff').data.vert = 'asc';
    $people.data.sort = ('lastNameSort asc');
    //jQuery('#people').data.dept_nid = dept_nids[0];
    $people.data.solr_server = solr_server;
    $people.data.manager_data = Object();

    $people.data.manager_data.department = 0;
    $people.data.manager_data.people = null;
    $people.data.manager_data.fq = '';
}

/**
 * Queries the solr server and for information about people in a given department
 * and constructs a table to display that information.
 *
 * @param {String} dept_id : The ID of the department
 * @param {String} template : The mustache-ready template for display the
 * information
 * @param {String} solr_server: The base URL for the solr server with the
 * information
 */
function asu_dir_build_table(query, reset) {
    var $people = jQuery('#people');
    var $controls_top = jQuery('#asu_directory_people_controls_top');
    var $controls_bottom = jQuery('#asu_directory_people_controls_bottom');
    var solr_server = $people.data.solr_server;
    var field_items = $people.data.field_items;
    var empl_types = $people.data.field_configs.employee_types;
    var show_managers = $people.data.field_configs.show_managers;

    if (!$people.data.page) {
        $people.data.page = 0;
    }

    var solr_data = {
        'wt': 'json'
    };

    // Parse query data, if any, and assign any missing pieces
    if (query) {
        // Search text
        if (query.hasOwnProperty('q') && !$people.data.hasOwnProperty('text')) {
            solr_data.q = query.q;
        }
        else
        // Query
        if ($people.data.hasOwnProperty('q')) {
            solr_data.q = $people.data.q;
        }
        else {
            solr_data.q = asu_dir_solr_search_string(field_items, 'deptids');
        }

        // Filter Query
        if (query.hasOwnProperty('fq')) {
            solr_data.fq = query.fq;
        }
        else if ($people.data.hasOwnProperty('fq')) {
            solr_data.fq = $people.data.fq;
        }
        else {
            solr_data.fq = asu_dir_solr_search_string(empl_types, 'employeeTypes');
        }
        // Apply chosen sort method to AJAX query
        if (query.hasOwnProperty('sort') && query.hasOwnProperty('vert')) {
            solr_data.sort = query.sort + ' ' + query.vert;
        }
        else if ($people.data.hasOwnProperty('sort')) {
            solr_data.sort = $people.data.sort;
        }
        else {
            solr_data.sort = $people.data.sort = 'lastNameSort asc';
        }
        // Determine what page to display
        if (query.hasOwnProperty('offset')) {
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
    }
    // If no query, use some default values
    else {

        //main query on deptids (actually maps to department nids at isearch.asu.edu)
        //filter query is on employee types, such as University Staff, Faculty, etc.
        solr_data.sort = 'lastNameSort asc';//($people.data.sort != null) ? $people.data.sort : 'lastName asc';
        solr_data.q = asu_dir_solr_search_string(field_items, 'deptids');
        solr_data.fq = asu_dir_solr_search_string(empl_types, 'employeeTypes');
        solr_data.start = 0;
    }

    //if the "Show Managers" Option is selected, and we are querying for the 1st page, run the management query
    if (show_managers == true && !$people.data.hasOwnProperty('q')) {

        asu_dir_management_query(solr_server, solr_data);
        return false;
    }

    var html = '';
    jQuery.ajax({
        'url': solr_server + '/solr/directory/select/',
        'cache': false,
        'data': solr_data,
        'dataType': 'jsonp',
        'jsonp': 'json.wrf',
        'success': function (data) {

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
        },
        // Handle timeout errors
        'timeout': 3000000,
        error: function (jqXHR, textStatus, errorThrown) {
            $controls_top.hide();
            $controls_bottom.hide();
            $people.text('Error: ' + textStatus.charAt(0).toUpperCase() + textStatus.slice(1) + '. Please contact a site administrator if the problem persists.');
        }
    });
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

    if ($people.data.field_items[0] != $people.data.manager_data.department || $people.data.manager_data.people == null || $people.data.manager_data.fq != solr_data.fq) {

        $people.data.manager_data.fq = solr_data.fq;

        $people.data.manager_data.department = $people.data.field_items[0];

        solr_data.rows = 2000;
        solr_data.fq = with_management;

        jQuery.ajax({
            'url': solr_server + '/solr/directory/select/',
            'cache': false,
            'data': solr_data,
            'dataType': 'jsonp',
            'jsonp': 'json.wrf',
            'success': function (data) {

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
                    'url': solr_server + '/solr/directory/select/',
                    'cache': false,
                    'data': solr_data,
                    'dataType': 'jsonp',
                    'jsonp': 'json.wrf',
                    'success': function (data) {

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
                    'timeout': 3000000,
                    error: function (jqXHR, textStatus, errorThrown) {
                        $controls_top.hide();
                        $controls_bottom.hide();
                        $people.text('Error: ' + textStatus.charAt(0).toUpperCase() + textStatus.slice(1) + '. Please contact a site administrator if the problem persists.');
                    }
                });
            },
            // Handle timeout errors
            'timeout': 3000000,
            error: function (jqXHR, textStatus, errorThrown) {
                $controls_top.hide();
                $controls_bottom.hide();
                $people.text('Error: ' + textStatus.charAt(0).toUpperCase() + textStatus.slice(1) + '. Please contact a site administrator if the problem persists.');
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
 * Creates click event for showing the subdirectories and takes care of adding active class if option
 * was selected before
 */
function asu_dir_show_subdepts() {
    var $people = jQuery('#people');
    var subtoggle_switch = jQuery('#asu_directory_show_subs');

    if ($people.data.field_configs.sub_toggle == true) {
        jQuery('#asu_directory_show_subs').addClass('sub_activated');
    }

    subtoggle_switch.mousedown(function (event) {

        $people.data.page = 0;

        $people.data.field_configs.sub_toggle = !$people.data.field_configs.sub_toggle;

        //Store items and configs for our Drupal ASU_Directory field
        if ($people.data.field_configs.sub_toggle == true) {
            $people.data.field_items = $people.data.tree_nids;
        } else {
            var temp = $people.data.field_items[0];
            $people.data.field_items = [temp];
        }

        subtoggle_switch.toggleClass('sub_activated');

        var show_managers = jQuery('#asu_directory_show_managers');

        //"Show sub-departments" and "Show Managers" Options cannot be selected at the same time
        if (subtoggle_switch.hasClass('sub_activated')) {
            show_managers.removeClass('active');
            show_managers.addClass('disabled');
            $people.data.field_configs.show_managers = false;

        } else if (show_managers.hasClass('disabled')) {
            show_managers.removeClass('disabled');
        }

        asu_dir_set_field();
        asu_dir_build_table();
        asu_dir_cleanup($people);
    })
}

/**
 * Function to attach click events to admin buttons
 *
 */
function asu_dir_activate_admin() {
    var showtree_element = jQuery('#asu_directory_show_tree');
    var manager_element = jQuery('#asu_directory_show_managers');
    var $people = jQuery('#people');


    if ($people.data.field_configs.sub_toggle == true) {
        manager_element.addClass('disabled');
        $people.data.field_configs.show_managers = false;
    } else if ($people.data.field_configs.show_managers == true) {
        manager_element.addClass('active');
    }

    if ($people.data.field_configs.show_tree == true) {
        showtree_element.addClass('active');
    }

    var selected_types = $people.data.field_configs.employee_types;

    for (i = 0; i < selected_types.length; i++) {
        jQuery('#asu_directory_employee_type_select :button[value="' + selected_types[i] + '"]').addClass('active');
    }

    showtree_element.click(function (event) {
        event.preventDefault();
        $people.data.field_configs.show_tree = !$people.data.field_configs.show_tree;
        jQuery(this).toggleClass('active');
        asu_dir_set_field();
    });

    manager_element.click(function (event) {
        event.preventDefault();

        //button should be disabled if sub_toggle is true, but in case it gets clicked
        if ($people.data.field_configs.sub_toggle == true) {
            jQuery(this).removeClass('active').addClass('disabled');
            $people.data.field_configs.show_managers = false;
        } else {
            $people.data.field_configs.show_managers = !$people.data.field_configs.show_managers;
            jQuery(this).toggleClass('active');
            $people.data.page = 0;
            asu_dir_set_field();
            asu_dir_build_table();
            asu_dir_cleanup($people);
        }
    });

    var $type_buttons = jQuery('#asu_directory_employee_type_select').find('.asu_directory_type_select');


    $type_buttons.mousedown(function (event) {
        event.preventDefault();

        var $people = jQuery('#people');
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

        asu_dir_set_field();
        asu_dir_cleanup($people);
        asu_dir_build_table();

    })
}

/***
 * Function to reset ASU Directory configs on click event
 *
 */
function asu_dir_set_field() {
    var $people = jQuery('#people');

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

    $buttons.mousedown(function (event) {
        // Only fire on left click if button is not inactive
        if (event.which == 1 && !jQuery(this).hasClass('disabled')) {
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

            if($people.data.page == 3) {
                $ellipses.eq(0).hide();
            } else if ( $people.data.page == 4 ) {
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

            if($people.data.page == $people.data.num_pages - 4) {
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
    //we'll set the width of the main name/title column to  col-md-6 if there is no photo

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
                asu_dir_people_search($people, jQuery(this));
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
    var query = {};
    var text = $input.val().split(' ');
    var items = $people.data.tree_nids;

    //if displaying without tree, go with the field items
    if (items === undefined) {
        items = $people.data.field_items;
    }

    var empl_types = $people.data.field_configs.employee_types;

    for (var i in text) {
        text[i] = "*" + text[i] + "*";
    }
    text = text.join('');

    var dept_q = asu_dir_solr_search_string(items, 'deptids');
    var etypes = asu_dir_solr_search_string(empl_types, 'employeeTypes');

    query.q = $people.data.q = text;
    query.fq = $people.data.fq = "(" + dept_q + ") AND (" + etypes + ")";
    query.sort = 'score';
    query.vert = 'desc';
    query.offset = 'begin';
    $people.data.sort = 'score desc';
    asu_dir_build_table(query);
    $people.data.text = text;
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
    delete $people.data.text;
    delete $people.data.fq;
    delete $people.data.q;
    delete $people.data.sort;
    jQuery('.asu_directory_people_search_group input').val('');
}
