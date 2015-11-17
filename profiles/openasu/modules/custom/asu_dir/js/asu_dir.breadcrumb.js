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
            var crumb = settings.asu_dir.field_configs.breadcrumb;
            var admin = settings.asu_dir.admin;
            var crumb_element = $('.asu_directory_breadcrumb');
            var $people = $('#people');

            crumb_element.html(crumb);

            $('#treediv').bind(
                'tree.select',
                function (event) {
                    if (event.node) {

                        // Node that was selected.
                        var node = event.node;
                        var isearch_url = 'https://isearch.asu.edu/asu/dept/';

                        // Clear all of breadcrumb to reset on new node selection.
                        $('div.asu_directory_breadcrumb').empty();

                        // Recurse through parents to prepend() rest of breadcrumbs.
                        var current_node = node;
                        while ((current_node.name)) { // If current_node has a name, drop a breadcrumb.

                            if (current_node.name == node.name) { // Lowest level. No dividing character.
                                crumb_element.prepend('<a href="' + isearch_url + current_node.dept_id + '">' + current_node.name + '</a>');
                            } else {
                                if (!admin) {
                                    crumb_element.prepend('<a href="' + isearch_url + current_node.dept_id + '">' + current_node.name + '</a> <span class="breadcrumb-divider">/</span> ');
                                }
                            }

                            // Move next iteration up a level.
                            current_node = current_node.parent;
                        }


                        if (admin) {

                            var markup = crumb_element.html();
                            $people.data.field_configs.breadcrumb = markup;
                            asu_dir_set_field($people);
                        }
                    }
                }
            );
        }
    }
}(jQuery));