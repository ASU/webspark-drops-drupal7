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
                solrServer: null,
                fieldConfigs: null,
                managers: [],
                savedDeptNid: 0,
                overrideFields: [],
                perPage: null,
                localPeople: null,
                iSearchUrl: null
            }, attributes);
        },

        beforeRequest: function () {


            //self.manager.store.addByValue('rows', self.perPage);
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
            var fieldConfigs = this.fieldConfigs;
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
            var fieldConfigs = this.fieldConfigs;
            var expertise = doc.expertiseAreas;
            var shortbio = doc.shortBio;
            var col_widths = this.getColWidths(fieldConfigs);

            //open row
            markup += '<div eid="' + eid + '" asurite="' + doc.asuriteId + '" class="row row-header asu_directory_people_row " >';

            markup += '<div class="col-md-2 peopleImg">';

            //PHOTO COLUMN
            if (doc.photoPreference != 'none' && doc.photoUrl != null && doc.photoUrl != '' && fieldConfigs.display_photo) {
                markup += '<div class="row-profile-image row-field"><img alt="' + doc.displayName + '" src="' + doc.photoUrl + '?size=medium"></div>';
            } else if (fieldConfigs.default_photo.display && fieldConfigs.default_photo.url != null) {
                markup += '<div class="row-profile-image row-field"><img alt="Default photo" src="' + fieldConfigs.default_photo.url + '"></div>';
            }

            markup += '</div>';

            //NAME AND TITLE COLUMN
            markup += '<div class="' + col_widths.name_col + '"><div class="row-profile-text row-field"><a href="' + url + '"';

            //open in new tab?
            if (fieldConfigs.new_tab) {
                markup += 'target="_blank"';
            }

            markup += 'class="displayName viewDetails" id="'
                + doc.eid + '" class="displayName viewDetails">';
            markup += (doc.displayName != null ? doc.displayName : '') + '</a><br>';


            markup += title_string;


            // close the title div
            markup += '</div>';

            if (fieldConfigs.display_short_bio && shortbio != null) {
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

            markup += this.contactDiv(doc, fieldConfigs, wrappers);

            //close row
            markup += '</div>';

            return markup;

        },

        contactDiv: function (doc, fieldConfigs, classes) {
            var markup = '';
            var addLine2 = doc.addressLine2;
            var addLine1 = doc.addressLine1;
            var addLine3 = doc.addressLine3;
            var cols = classes.join(' ');
            var address = '';

            //CONTACT INFO COLUMN
            markup += '<div class="' + cols + '"><div class="row-profile-contact"><div class="row-profile-email row-field"><a class="emailAddress"';
            markup += 'href="mailto:' + doc.emailAddress + '">' + doc.emailAddress + '</a>&nbsp; <span class="asu-dir-admin"></span><br>';


            if (doc.phone != null && doc.phone != '') {
                doc.phone = doc.phone.replace(/\//g, "-");
                markup += '<div class="phone_number">' + doc.phone + '</div>';
            }

            if (fieldConfigs.display_building && addLine1 != null) {
                markup += '<div class="isearch-address building">' + addLine1 + '</div>';

                if (addLine2 != null) {
                    markup += '<div class="isearch-address room">&nbsp;' + addLine2 + '</div>';
                }

                if (addLine3 != null) {
                    markup += '<div class="isearch-address line3">&nbsp;' + addLine3 + '</div>';
                }


            }

            //end contact info
            markup += '</div></div></div>';

            return markup;
        },

        getColWidths: function (fieldConfigs) {
            var cols = {};
            cols.name_col = 'col-md-6';
            cols.con_col = 'col-md-4';

            if (fieldConfigs.display_expertise) {
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
            var fieldConfigs = this.fieldConfigs;
            var expertise = doc.expertiseAreas;
            var shortbio = doc.shortBio;

            var markup = '<div class="asu-dir-grid-col gridborder col-1 col-md-3 "> <div class="grid-item"><div class="peopleImg row-profile-image">';

            if (fieldConfigs.new_tab) {
                target = 'target="_blank"';
            }

            if (doc.photoPreference != 'none' && doc.photoUrl != null && doc.photoUrl != '' && fieldConfigs.display_photo) {
                markup += '<a class="row-profile-image row-field" ' + target + ' href="' + url + '" title="'
                    + doc.displayName + '"><img alt="' + doc.displayName + '" class = "asu-dir-grid-image " src="' + doc.photoUrl + '"></a>';
            } else if (fieldConfigs.default_photo.display && fieldConfigs.default_photo.url != null) {
                markup += '<a class="row-profile-image row-field" ' + target + ' href="' + url + '" title="'
                    + doc.displayName + '"><img alt="Default photo" class = "asu-dir-grid-image" src="' + fieldConfigs.default_photo.url + '"></a>';
            }

            markup += '</div><div class="fs-title"><a ' + target + '" href="' + url + '" title="' + doc.displayName + '">' + doc.displayName + '</a></div>';
            markup += '<div class="job-title">' + title_string + '</div>';


            var wrappers = ["asu-dir-contact-col"];
            markup += this.contactDiv(doc, fieldConfigs, wrappers);

            if (fieldConfigs.display_short_bio && shortbio != null) {
                markup += '<div class="short-bio"><span class="short-title">Short Bio: </span>' + shortbio + '</div>';
            }

            if (fieldConfigs.display_expertise) {

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
            var configs = this.fieldConfigs;
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
            var dept_names = doc.departments;
            var title_string = '';
            var is_tree = this.fieldConfigs.show_tree;
            var fieldConfigs = this.fieldConfigs;
            var confob = 'asu_dir' + fieldConfigs.pane_id;
            var department;

            // Get current dept id from the ASUPeople global, which is defined in the asu_dir module JS
            var dept_nid = ASUPeople[confob].dept_nid;
            var index = -1;

            // Get the index of the current department in the deptids array,
            // so that we can map the proper title and employee class.
            // edit - we only do this if a department tree is shown
            if (depts != null && is_tree) {
                for (var i = 0; i < depts.length; i++) {
                    if (depts[i] == dept_nid) {
                        index = i;
                    }
                }
            }

            // if no current dept index was set, set to the primary title
            if (index == -1) {
                index = $.inArray(doc.primaryiSearchDepartmentAffiliation, doc.departments);
            }

            // if we failed to get a primary or current dept title, fallback to the first one found
            if (index == -1) {
                index = 0;
            }

            department = dept_names[index];

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
            if (title != null && (titleSource == 'titles' || workingTitle == null)) { // Determine if using custom title field.
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
            title_string = '<div class="job-title">' + title_string.trim();

            if (fieldConfigs.display_department && department != null) {
                title_string += '<br>' + department;
            }

            title_string += '</div>';

            return title_string;
        },

        getprofileURL: function (doc) {
            var locals = this.localPeople;
            var url = this.iSearchUrl + '/profile/' + doc.eid;

            if (doc.asuriteId) {
                if (locals[doc.asuriteId] != null) {
                    if (locals[doc.asuriteId].alias != null) {
                        url = '/' + locals[doc.asuriteId].alias;
                    } else if (locals[doc.asuriteId].nid != null) {
                        url = '/node/' + locals[doc.asuriteId].nid;
                    }
                }
            }

            return url;
        }

    });


})(jQuery);