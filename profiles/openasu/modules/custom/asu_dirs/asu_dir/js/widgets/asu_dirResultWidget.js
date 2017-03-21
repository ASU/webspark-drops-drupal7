/**
 * Define the IS People Result widget.  This part handles the output of the people listing after the Solr request.
 * The logic and functions to append managers to the front of the list is also here, since that functionality needs to
 * act on the template during/after the request.
 *
 */
(function ($) {

    AjaxSolr.asu_dirResultWidget = AjaxSolr.AbstractWidget.extend({
        start: 0,

        /**
         * @param {Object} [attributes]
         *
         */
        constructor: function (attributes) {
            AjaxSolr.asu_dirResultWidget.__super__.constructor.apply(this, arguments);
            AjaxSolr.extend(this, {
                solr_server: null,
                field_configs: null,
                managers: [],
                saved_deptnid: 0,
                override_fields: [],
                per_page: null,
                local_people: null,
                isearch_url: null
            }, attributes);
        },

        beforeRequest: function () {
            //TODO: consolidate the preconfigured filters into the manager widget
            var self = this;
            var field_configs = self.field_configs;
            var start = self.manager.store.get('start').val();
            var q = self.manager.store.get('q').val();
            var fq = self.manager.store.get('fq');
            var etypes = field_configs.employee_types;

            // ADD EMPLOYEE TYPES FILTER TO QUERY
            if (etypes != null && etypes.length > 0) {
                //If employee types other than "Show All" are selected, add those as a filter query
                var show_all = field_configs.employee_types.indexOf("All");
                var legacy = field_configs.employee_types.indexOf("Show All");

                if (field_configs.employee_types.length > 0 && show_all == -1 && legacy == -1) {
                    var types = field_configs.employee_types;
                    var search_string = asu_dir_solr_search_string(types, 'employeeTypes', true);

                    //need to add this to the manager query also
                    self.manager.store.addByValue('fq', search_string);
                }
            }


            // add the faculty titles filter if it is configured
            if (field_configs.hasOwnProperty('ft_filter')) {
                self.manager.store.addByValue('fq', field_configs.ft_filter);
            }

            // ADD FILTERING FOR EXPERTISE AREAS
            // TODO:  need to wrap field params with parentheses
            if (field_configs.expertise_areas != null && field_configs.expertise_areas != '') {
                var exp_string = asu_dir_solr_search_string(field_configs.expertise_areas, 'expertiseAreas', true);
                self.manager.store.addByValue('fq', exp_string);
            }

            // ADD FILTERING FOR TITLES
            if (field_configs.filter_title != null && field_configs.filter_title != '') {
                self.manager.store.addByValue('fq', 'titles:(' + field_configs.filter_title + ')');
            }

            //self.manager.store.addByValue('rows', self.per_page);
        },

        facetLinks: function (facet_field, facet_values) {
            var links = [];
            if (facet_values) {
                for (var i = 0, l = facet_values.length; i < l; i++) {
                    if (facet_values[i] !== undefined) {
                        links.push(
                            $('<a href="#"></a>')
                                .text(facet_values[i])
                                .click(this.facetHandler(facet_field, facet_values[i]))
                        );
                    }
                    else {
                        links.push('no items found in current selection');
                    }
                }
            }
            return links;
        },

        facetHandler: function (facet_field, facet_value) {
            var self = this;
            return function () {
                self.manager.store.remove('fq');
                self.manager.store.addByValue('fq', facet_field + ':' + AjaxSolr.Parameter.escapeValue(facet_value));
                self.doRequest(0);
                return false;
            };
        },

        afterRequest: function () {

            var results = this.manager.response.response.docs;
            var self = this;
            var field_configs = this.field_configs;
            var q = self.manager.store.get('q').val();
            var fq = self.manager.store.get('fq');

            //empty the people listing
            $(this.target).empty();

            if (!results.length) { // Display no results message.
                $(this.target).html('<div class="row-profile-text row-field row">No results found.</div>');
                return false;
            }

            this.renderPeople(results);

            if (Drupal.settings.asu_dept_info) {
                var info_nid = $('.jqtree-selected').attr('dept_nid');
                asu_dept_info_process_directory_admins(info_nid);
            }

        },

        template: function (doc) {

            var markup = '';
            var getUrl = window.location;
            var eid = doc.eid;
            var title_string = this.getTitle(doc);
            var url = this.getprofileURL(doc);
            var field_configs = this.field_configs;
            var expertise = doc.expertiseAreas;
            var shortbio = doc.shortBio;
            var col_widths = this.getColWidths(field_configs);

            //open row
            markup += '<div eid="' + eid + '" asurite="' + doc.asuriteId + '" class="row row-header asu_directory_people_row " >';

            markup += '<div class="col-md-2 peopleImg">';

            //PHOTO COLUMN
            if (doc.photoPreference != 'none' && doc.photoUrl != null && doc.photoUrl != '' && field_configs.display_photo) {
                markup += '<div class="row-profile-image row-field"><img alt="' + doc.displayName + '" src="' + doc.photoUrl + '?size=medium"></div>';
            }

            markup += '</div>';

            //NAME AND TITLE COLUMN
            markup += '<div class="' + col_widths.name_col + '"><div class="row-profile-text row-field"><a href="' + url + '"';

            //open in new tab?
            if (field_configs.new_tab) {
                markup += 'target="_blank"';
            }

            markup += 'class="displayName viewDetails" id="'
                + doc.eid + '" class="displayName viewDetails">';
            markup += (doc.displayName != null ? doc.displayName : '') + '</a><br>';
            markup += '<div class="job-title">' + title_string + '</div></div>'

            if (field_configs.display_short_bio && shortbio != null) {
                markup += '<div class="short-bio">' + shortbio + '</div>';
            }

            markup += '</div>';

            //EXPERTISE AREAS COLUMN
            if (col_widths.exp_col != null) {
                markup += '<div class="' + col_widths.exp_col + '">';

                if (expertise != null) {
                    for (var i = 0; i < expertise.length; i++) {
                        markup += '<div class="asu-dir-exp-item">' + expertise[i] + '</div>';
                    }
                }

                markup += '</div>';
            }

            var wrappers = [col_widths.con_col, "asu-dir-contact-col"];

            markup += this.contactDiv(doc, field_configs, wrappers);

            //close row
            markup += '</div>';

            return markup;

        },

        contactDiv: function (doc, field_configs, classes) {
            var markup = '';
            var addLine2 = doc.addressLine2;
            var addLine1 = doc.addressLine1;
            var cols = classes.join(' ');

            //CONTACT INFO COLUMN
            markup += '<div class="' + cols + '"><div class="row-profile-contact"><div class="row-profile-email row-field"><a class="emailAddress"';
            markup += 'href="mailto:' + doc.emailAddress + '">' + doc.emailAddress + '</a>&nbsp; <span class="asu-dir-admin"></span><br>';


            if (doc.phone != null && doc.phone != '') {
                doc.phone = doc.phone.replace(/\//g, "-");
                markup += '<div class="phone_number">' + doc.phone + '</div>';
            }

            if (field_configs.display_building && addLine1 != null) {
                markup += '<div class="building">' + addLine1 + '</div>';

                if (addLine2 != null) {
                    markup += '<div class="room">' + addLine2 + '</div>';
                }
            }

            //end contact info
            markup += '</div></div></div>';

            return markup;
        },

        getColWidths: function (field_configs) {
            var cols = {};
            cols.name_col = 'col-md-6';
            cols.con_col = 'col-md-4';

            if (field_configs.display_expertise) {
                cols.name_col = 'col-md-4';
                cols.exp_col = 'col-md-3';
                cols.con_col = 'col-md-3';
            }

            return cols;
        },

        gridTemplate: function (doc) {

            var getUrl = window.location;
            var title_string = this.getTitle(doc);
            var url = this.getprofileURL(doc);
            var target = '';
            var field_configs = this.field_configs;
            var expertise = doc.expertiseAreas;
            var shortbio = doc.shortBio;

            var markup = '<div class="asu-dir-grid-col gridborder col-1 col-md-3 "> <div class="grid-item"><div class="peopleImg row-profile-image">';

            if (field_configs.new_tab) {
                target = 'target="_blank"';
            }

            if (doc.photoPreference != 'none' && doc.photoUrl != null && doc.photoUrl != '' && field_configs.display_photo) {
                markup += '<a class="row-profile-image row-field" ' + target + ' href="' + url + '" title="'
                    + doc.displayName + '"><img alt="' + doc.displayName + '" class = "asu-dir-grid-image " src="' + doc.photoUrl + '"></a>';
            }

            markup += '</div><div class="fs-title"><a ' + target + '" href="' + url + '" title="' + doc.displayName + '">' + doc.displayName + '</a></div>';
            markup += '<div class="job-title">' + title_string + '</div>';


            var wrappers = ["asu-dir-contact-col"];
            markup += this.contactDiv(doc, field_configs, wrappers);

            if (field_configs.display_short_bio && shortbio != null) {
                markup += '<div class="short-bio"><span class="short-title">Short Bio: </span>' + shortbio + '</div>';
            }

            if (field_configs.display_expertise) {

                markup += '<div class="asu-dir-expertise">';

                if (expertise != null) {
                    markup += '<span class="asu-dir-expertise-title">Expertise: </span>';

                    markup += expertise.join(', ');
                }

                markup += '</div>';
            }

            markup += '</div></div>';

            return markup;

        },

        // Parameters are an array of solr docs, and a flag on whether to prepend to the beginning of target div.
        // This allows us to run the manager and non-manager query at the same time.
        renderPeople: function (docs) {
            var configs = this.field_configs;
            var dtype = 'list';

            if (configs.hasOwnProperty('display_type')) {
                dtype = configs.display_type;
            }

            if (docs.length > 0) {

                var open = false;

                if (dtype == 'list') {
                    for (var i = 1, l = docs.length; i <= l; i++) {
                        var doc = docs[i - 1];
                        $(this.target).append(this.template(doc));
                    }
                } else {

                    var markup = '';

                    for (var i = 1, l = docs.length; i <= l; i++) {
                        var doc = docs[i - 1];

                        if (i % 4 == 1) {
                            markup += "<div class='row asu-dir-grid-row asu_directory_people_row'>";
                            open = true;
                        }

                        markup += this.gridTemplate(doc);

                        if (i % 4 == 0) {
                            markup += "</div>";
                            open = false;
                        }
                    }

                    if (open) {
                        markup += "</div>";
                    }

                    $(this.target).append(markup);
                }

            }
        },

        getTitle: function (doc) {

            // Logic to get title string
            var titles = doc.titles;
            var depts = doc.deptids;
            var title_string = '';

            // Get current dept id from the ASUPeople global, which is defined in the asu_dir module JS
            var dept_nid = ASUPeople.dept_nid;

            var index = 0;

            // Get the index of the current department in the deptids array,
            // so that we can map the proper title and employee class.

            if (depts != null) {
                for (var i = 0; i < depts.length; i++) {
                    if (depts[i] == dept_nid) {
                        index = i;
                    }
                }
            }


            if (doc.titleSource != null) {
                var titleSource = doc.titleSource[index];
            }
            if (doc.titles != null) {
                var title = doc.titles[index];
            }
            if (doc.workingTitle != null) {
                var workingTitle = doc.workingTitle;
            }
            if (doc.primaryTitle != null) {
                var primaryTitle = doc.primaryTitle;
            }

            if (doc.emplClasses != null) {
                var displayEmplClass = doc.emplClasses[index];
            }


            // Title to output.
            if (titleSource == 'titles') { // Determine if using custom title field.
                title_string = title;
            }
            else if (workingTitle != null) {
                title_string = workingTitle;
            }
            else if (primaryTitle != null) {
                title_string = primaryTitle;
            }
            else {
                title_string = '';
            }

            // If title_string is still empty, fall back to emplClass as a last
            // option.
            if (title_string == '' && displayEmplClass !== '' && displayEmplClass != null) {
                title_string = displayEmplClass;
            }

            // Trim the title, since it might show up as a blank space, like " "
            title_string = title_string.trim();

            return title_string;
        },

        getprofileURL: function (doc) {
            var locals = this.local_people;
            var url = this.isearch_url + '/profile/' + doc.eid;

            if (doc.asuriteId) {
                if (locals[doc.asuriteId] != null) {
                    url = '/' + locals[doc.asuriteId].alias;
                }
            }

            return url;
        }

    });


})(jQuery);