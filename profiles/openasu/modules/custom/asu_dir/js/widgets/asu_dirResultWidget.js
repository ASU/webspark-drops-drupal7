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
                override_fields: []
            }, attributes);
        },

        beforeRequest: function () {

            var self = this;
            var field_configs = self.field_configs;
            var solr_url = self.solr_server;
            var managers = [];
            var start = self.manager.store.get('start').val();
            var q = self.manager.store.get('q').val();
            var fq = self.manager.store.get('fq');
            var manager_fq = '';
            var override_fields = self.override_fields;
            var override = false;

            //empty the people listing, and scroll to top of page
            $(this.target).empty();
            window.scrollTo(0, 0);

            //If employee types other than "Show All" are selected, add those as a filter query
            var show_all = field_configs.employee_types.indexOf("Show All");

            if (show_all == -1 && !field_configs.use_custom_q) {
                var types = field_configs.employee_types;
                var search_string = asu_dir_solr_search_string(types, 'employeeTypes');

                //need to add this to the manager query also
                manager_fq += '&fq=' + search_string;
                self.manager.store.addByValue('fq', search_string);
            }


            //if an override field is found as an fq, override the manager query
            for (var i = 0; i < fq.length; i++) {
                for (var j = 0; j < override_fields.length; j++) {

                    if (fq[i] != null && fq[i].value != null && fq[i].value.indexOf(override_fields[j]) != -1) {
                        override = true;
                    }
                }
            }

            var active_letter = false;

            //get rid of styling for active letter if it is not ther
            for (var i = 0; i < fq.length; i++) {
                if (fq[i] != null && fq[i].value != null && fq[i].value.indexOf('lastName') != -1) {
                    active_letter = true;
                }
            }

            if (!active_letter) {
                $('.alphabet .active-letter').removeClass('active-letter');
            }


            // To display managers at the beginning of the list is not possible since the managers field is
            // multi-valued in Solr, so this workaround does a separate request and prepends the managers to the
            // front page in alphabetical order
            // If the show_managers options is selected, no facets are selected,
            // and we are on the front page, prepend the managers to the front of the people listing
            // Note:  we need to check the ASUPeople global field configs in this case, because selection the 'rank'
            //      for sorting will need to switch the manager sort on
            if (!override && q == "*:*" && ASUPeople.field_configs.show_managers && (start == 0 || start == null)) {

                //if we don't have managers saved for current department, do separate AJAX request and prepend them
                if (this.saved_deptnid != ASUPeople.dept_nid) {

                    $.ajax({
                        'url': solr_url + 'select?fq=deptids:' + ASUPeople.dept_nid + manager_fq + '&fq=managers:1&q=*:*&sort=lastNameSort asc&wt=json',
                        'cache': false,
                        'dataType': 'jsonp',
                        'jsonp': 'json.wrf',
                        'success': function (data) {
                            if (data.response.docs.length > 0) {

                                //array to store indexes of managers to remove
                                var to_remove = [];

                                managers = data.response.docs;

                                // Remove any managers who are not managers for this dept,
                                // since managers field is multi-valued
                                for (var i = 0; i < managers.length; i++) {
                                    var temp = managers[i];
                                    var search = ASUPeople.dept_nid.toString();
                                    var position = temp.deptids.indexOf(search);

                                    if (position >= 0) {
                                        //if person is not a manager of given department, add index to the to_remove array for later removal
                                        if (temp.managers[position] != 1) {
                                            to_remove.push(i);
                                        }
                                    }
                                }

                                // Traverse the array of indexes backwards, to avoid splicing
                                // the wrong elements in subsequent iterations
                                if (to_remove.length >= 1) {

                                    for (var i = to_remove.length - 1; i >= 0; i--) {
                                        managers.splice(to_remove[i], 1);
                                    }
                                }

                                self.managers = managers;
                                self.saved_deptnid = ASUPeople.dept_nid;

                                //insert managers at the beginning of the list, in alphabetical order
                                self.renderPeople(managers, true);
                            }
                        },
                        // Handle timeout errors, since jsonp request will just hang if an error is thrown
                        'timeout': 5000,
                        'error': function (jqXHR, textStatus, errorThrown) {

                        },
                        'complete': function (jqXHR, textStatus) {

                        }
                    });

                    //if managers for a department are already saved, use this.managers
                } else if (this.managers.length > 0) {
                    managers = this.managers;
                    self.renderPeople(managers, true);
                }
            }
            /*
            if (!field_configs.use_custom_q) {
                //For now, always sort by last name alphabetically
                self.manager.store.addByValue('sort', 'lastNameSort asc');
            }*/
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
            var override_fields = self.override_fields;
            var override = false;

            if (results.length == 0) { // Display no results message.
                $('#asu-dir-ajax-solr-people').html('<div class="row-profile-text row-field row">No results found.</div>');
                return false;
            }

            //if an override field is found as an fq, override the stripping of managers
            for (var i = 0; i < fq.length; i++) {
                for (var j = 0; j < override_fields.length; j++) {
                    if (fq[i] != null && fq[i].value != null && fq[i].value.indexOf(override_fields[j]) != -1) {
                        override = true;
                    }
                }
            }


            // since we appended managers to the front of the listing, we
            // remove them from the rest of the results, to avoid double-listings
            if (q == "*:*" && !override && results.length > 0 && field_configs.show_managers) {

                //an array of indexes of managers, which we later remove
                var to_remove = [];

                for (var i = 0; i < results.length; i++) {
                    var temp = results[i];

                    var search = ASUPeople.dept_nid.toString();
                    var position = temp.deptids.indexOf(search);

                    if (position >= 0) {
                        //if person is not a manager of given department, add index to the to_remove array for later removal
                        if (temp.managers[position] == 1) {
                            to_remove.push(i);
                        }
                    }
                }

                if (to_remove.length >= 1) {
                    //traverse in reverse order, since we are removing elements
                    for (var i = to_remove.length - 1; i >= 0; i--) {
                        results.splice(to_remove[i], 1);
                    }
                }
            }

            this.renderPeople(results, false);

            if (Drupal.settings.asu_dept_info) {
               var info_nid = $('.jqtree-selected').attr('dept_nid');

               asu_dept_info_process_directory_admins(info_nid);
            }

        },

        template: function (doc) {

            var markup = '';
            var getUrl = window.location;
            var host = getUrl.host;
            var isearch_env = 'isearch.asu.edu';

            if (host == 'isearch-dev.asu.edu' || host == 'isearch-qa.asu.edu') {
                isearch_env = host;
            }

            //open row
            markup += '<div eid="' + doc.eid + '" asurite="' + doc.asuriteId + '" class="row row-header asu_directory_people_row " >';

            var col_width = 'col-md-6';

            markup += '<div class="col-md-2 peopleImg">';

            //PHOTO COLUMN
            if (doc.photoPreference != 'none' && doc.photoUrl != null && doc.photoUrl != '') {
                markup += '<div class="row-profile-image row-field"><img src="' + doc.photoUrl + '?size=medium"></div>';
            }

            markup += '</div>';

            //concatenate string with all titles, and departments, followed by ; --limiting this to 3 titles/departments for display purposes
            var title_string = '';
            var titles = doc.titles;

            if (titles !== undefined) {
                for (var j = 0; j < titles.length && j < 3; j++) {
                    title_string += titles[j] + ", " + doc.departments[j] + "; ";
                }
            }

            //NAME AND TITLE COLUMN
            markup += '<div class="' + col_width + '"><div class="row-profile-text row-field"><a href="//' + isearch_env + '/profile/' + doc.eid + '" target="_blank" class="displayName viewDetails" id="'
                + doc.eid + '" class="displayName viewDetails">';
            markup += (doc.displayName != null ? doc.displayName : '') + '</a><br>';
            markup += '<div class="job-title">' + title_string + '</div></div></div>';

            //CONTACT INFO COLUMN
            markup += '<div class="col-md-4 asu-dir-contact-col"><div class="row-profile-contact"><div class="row-profile-email row-field"><a class="emailAddress"';
            markup += 'href="mailto:' + doc.emailAddress + '">' + doc.emailAddress + '</a>&nbsp; <span class="asu-dir-admin"></span><br>';

            if (doc.hasOwnProperty('phone') && doc.phone != '') {
                markup += '<div class="phone_number">' + doc.phone + '</div>';
            }
            markup += '</div></div></div>';

            //markup += '<div class="col-md-3"><div id="expertise_links_' + doc.eid + '" class="row-profile-expertise-area row-field"></div></div>';

            //close row
            markup += '</div>';

            return markup;

        },

        // Parameters are an array of solr docs, and a flag on whether to prepend to the beginning of target div.
        // This allows us to run the manager and non-manager query at the same time.
        renderPeople: function (docs, prepend) {

            if (docs.length > 0) {

                if (prepend) {

                    //prepend backwards for alphabetical order
                    for (var i = docs.length - 1; i >= 0; i--) {
                        var doc = docs[i];
                        $(this.target).prepend(this.template(doc));
                        /*
                         // For display in results.
                         var items = [];
                         items = items.concat(this.facetLinks('expertiseAreasFacet', doc.expertiseAreasFacet));

                         var $links = $('#expertise_links_' + doc.eid);
                         $links.empty();
                         for (var j = 0, m = items.length; j < m; j++) {
                         $links.append($('<li></li>').append(items[j]));
                         }*/
                    }
                } else {
                    for (var i = 0, l = docs.length; i < l; i++) {

                        var doc = docs[i];

                        $(this.target).append(this.template(doc));

                        // For display in results.
                        /*
                         var items = [];
                         items = items.concat(this.facetLinks('expertiseAreasFacet', doc.expertiseAreasFacet));

                         var $links = $('#expertise_links_' + doc.eid);
                         $links.empty();
                         for (var j = 0, m = items.length; j < m; j++) {
                         $links.append($('<li></li>').append(items[j]));
                         }*/
                    }
                }
            }
        }

    });

})(jQuery);