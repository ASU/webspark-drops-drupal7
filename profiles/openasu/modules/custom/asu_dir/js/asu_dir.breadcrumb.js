/**
 * ASU Dept Manager module
 *
 * Department Widget Breadcrumb JavaScript
 *
 * @author Michael Samuelson ( mlsamuel@asu.edu / mlsamuelson@gmail.com )
 * @author Colton Testamarck ( colt@asu.edu )
 */
(function ($) {
    Drupal.behaviors.asu_dir_breadcrumb = {
        attach: function (context, settings) {

            // On select of a treenode clear and then (re)calc and write the trail.
            var field_configs = settings.asu_dir.field_configs;

            var admin = settings.asu_dir.admin;
            var isearch_url = 'https://isearch.asu.edu/asu/dept/';
            var crumb_element = $('.asu_directory_breadcrumb');


            //if option to show tree is selected, then traverse to set starting crumbs, and also
            // bind to the tree select event to amend breadcrumbs
            if (field_configs.show_tree) {

                // check for ASUPeople global, which indicates we are on the frontend user interface
                // rather than the ASU Directory node form
                if (typeof ASUPeople !== undefined) {

                    var $tree = $('#treediv');
                    var current_node = $tree.tree('getSelectedNode');

                    if (current_node) {
                        asu_dir_traverse_crumbs(current_node, crumb_element);
                    }
                }

                $('#treediv').bind(
                    'tree.select',
                    function (event) {
                        if (event.node) {

                            // Node that was selected.
                            var node = event.node;

                            // Clear all of breadcrumb to reset on new node selection.
                            $('div.asu_directory_breadcrumb').empty();

                            // Recurse through parents to prepend() rest of breadcrumbs.
                            if (node && !admin) {
                                asu_dir_traverse_crumbs(node, crumb_element);
                            }

                            if (admin) {
                                var markup = '<a onclick=asu_dirGoDept(' + node.dept_id + ')>' + node.name + '</a>';
                                ASUPeople.field_configs.breadcrumb = markup;
                                asu_dir_set_field();
                            }

                        }
                    }
                );
            } else if (field_configs.hasOwnProperty('breadcrumb')) {
                crumb_element.html(field_configs.breadcrumb);
            }
        }
    }
}(jQuery));



// Utility function to traverse nodes from the current node of the jqtree, and append breadcrumbs to the
// crumb element
function asu_dir_traverse_crumbs(current_node, crumb_element) {

    var node = current_node;
    var isearch_url = 'https://isearch.asu.edu/asu/dept/';

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

function asu_dirGoDept(nid) {
    var dept_nid_string = "[dept_nid=" + nid + "]";
    var dept = jQuery(dept_nid_string + ">div");

    //Create a new jQuery.Event object without the "new" operator.
    dept.click();
}