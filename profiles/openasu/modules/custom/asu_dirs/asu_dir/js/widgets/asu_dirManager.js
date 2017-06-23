/**
 * Created by ctestama on 4/21/16.
 */


/**
 * The Manager acts as the controller in a Model-View-Controller framework. All
 * public calls should be performed on the manager object.
 *
 * @param properties A map of fields to set. Refer to the list of public fields.
 * @class AbstractManager
 */
(function (callback) {
    if (typeof define === 'function' && define.amd) {
        define(['core/AbstractManager'], callback);
    }
    else {
        callback();
    }
}(function () {


    /**
     * @see http://wiki.apache.org/solr/SolJSON#JSON_specific_parameters
     * @class Manager
     * @augments AjaxSolr.AbstractManager
     */
    AjaxSolr.asu_dirManager = AjaxSolr.AbstractManager.extend(
        /** @lends AjaxSolr.Manager.prototype */
        {
            /**
             * @param {Object} [attributes]
             * @param {Number} [attributes.start] This widget will by default set the
             *   offset parameter to 0 on each request.
             */
            constructor: function (attributes) {
                AjaxSolr.asu_dirManager.__super__.constructor.apply(this, arguments);
                AjaxSolr.extend(this, {
                    fieldConfigs: null,
                    sortedPeople: {},
                    sortedResponse: {},
                    overrideFields: [],
                    fieldId: null,
                    perPage: null,
                    localPeople: null
                }, attributes);
            },

            // overriden to add the preconfigured filters.
            init: function () {
                this.initialized = true;
                if (this.store === null) {
                    this.setStore(new AjaxSolr.ParameterStore());
                }
                this.store.load(false);
                for (var widgetId in this.widgets) {
                    this.widgets[widgetId].init();
                }
                this.store.init();

                // add the preconfigured filter values
                this.addPreFilters();
            },

            executeRequest: function (servlet, string, handler, errorHandler) {
                var self = this,
                    options = {dataType: 'json'};
                var fq = self.store.get('fq');
                var q = self.store.get('q');
                var pag_results;
                var fieldId = this.fieldId;
                var fieldConfigs = self.fieldConfigs;
                var override = this.checkOverrides();

                string = string || this.store.string();
                handler = handler || function (data) {
                        self.handleResponse(data);
                    };
                errorHandler = errorHandler || function (jqXHR, textStatus, errorThrown) {
                        self.handleError(textStatus + ', ' + errorThrown);
                    };
                if (this.proxyUrl) {
                    options.url = this.proxyUrl;
                    options.data = {query: string};
                    options.type = 'POST';
                }
                else {
                    options.url = this.solrUrl + servlet + '?' + string + '&wt=json&json.wrf=?';
                }

                // If we are using our custom manager sort, then we need to check if we already have a sorted array,
                // or need to grab and sort from Solr
                if (fieldConfigs.show_managers && !override) {

                    //get the start parameter, if it exists.  we need this for
                    //pagination of results
                    var start = 0;
                    if (self.store.params.start.value != undefined) {
                        start = parseInt(self.store.params.start.value);
                    }

                    // if we have not set sorted people for the current dept.
                    if (self.sortedPeople[ASUPeople[fieldId].dept_nid] == null) {
                        // grab all of the results and start from the beginning
                        // we'll need to sort all results as a group
                        // todo:  remove if not needed
                        //options.url = options.url + "&rows=200000";

                        var rep = /(start=).*?(&)/gi;

                        options.url = options.url.replace(rep, "start=0&");

                        jQuery.ajax(options).done(function (data) {

                            //array to store managers
                            var docs = data.response.docs;

                            //manipulate the docs in order to facilitate rank sorting
                            for (var i = 0; i < docs.length; i++) {
                                var temp = docs[i];
                                docs[i].mappedWeight = self.getEmployeeWeight(docs[i]);
                            }

                            // function to sort by rankweight
                            docs.sort(function (a, b) {

                                //sort by manager status first
                                /* deprecated
                                 if (a.manmap > b.manmap) {
                                 return -1;
                                 }
                                 if (a.manmap < b.manmap) {
                                 return 1;
                                 }*/

                                //sort by weight if possible.
                                if (a.mappedWeight < b.mappedWeight) {
                                    return -1;
                                }
                                if (a.mappedWeight > b.mappedWeight) {
                                    return 1;
                                }

                                //if mapped weights are equal, sort by last name
                                if (a.lastName < b.lastName) {
                                    return -1;
                                }
                                if (a.lastName > b.lastName) {
                                    return 1;
                                }

                                //if the weights and last names are equal, return 0
                                return 0;
                            });

                            //maintain a complete array of sorted results for the dept.
                            self.sortedPeople[ASUPeople[fieldId].dept_nid] = docs;

                            //substitute the proper page of the array
                            pag_results = self.sortedPeople[ASUPeople[fieldId].dept_nid].slice(start, start + self.perPage);

                            data.response.docs = pag_results;
                            self.sortedResponse[ASUPeople[fieldId].dept_nid] = data;

                            self.handleResponse(data);

                        }).fail(errorHandler);
                    } else {
                        var data = self.sortedResponse[ASUPeople[fieldId].dept_nid];
                        pag_results = self.sortedPeople[ASUPeople[fieldId].dept_nid].slice(start, start + self.perPage);
                        data.response.docs = pag_results;
                        //self.sortedResponse[ASUPeople[fieldId].dept_nid] = data;
                        self.handleResponse(data);
                    }

                } else {
                    jQuery.ajax(options).done(handler).fail(errorHandler);
                }
            },

            // adds preconfigured filters to the manager
            addPreFilters: function() {

                var self = this;
                var fieldConfigs = self.fieldConfigs;
                var start = self.store.get('start').val();
                var q = self.store.get('q').val();
                var fq = self.store.get('fq');
                var etypes = fieldConfigs.employee_types;

                // ADD EMPLOYEE TYPES FILTER TO QUERY
                if (etypes != null && etypes.length > 0) {
                    //If employee types other than "Show All" are selected, add those as a filter query
                    var show_all = fieldConfigs.employee_types.indexOf("All");
                    var legacy = fieldConfigs.employee_types.indexOf("Show All");

                    if (fieldConfigs.employee_types.length > 0 && show_all == -1 && legacy == -1) {
                        var types = fieldConfigs.employee_types;
                        var search_string = asu_dir_solr_search_string(types, 'employeeTypes', true);

                        //need to add this to the manager query also
                        self.manager.store.addByValue('fq', search_string);
                    }
                }

                // add the faculty titles filter if it is configured - tenure/non-tenure relies on this
                if (fieldConfigs.hasOwnProperty('ft_filter')) {
                    self.store.addByValue('fq', fieldConfigs.ft_filter);
                }

                // ADD FILTERING FOR EXPERTISE AREAS
                if (fieldConfigs.expertise_areas != null && fieldConfigs.expertise_areas != '') {
                    var exp_string = asu_dir_solr_search_string(fieldConfigs.expertise_areas, 'expertiseAreas', true);
                    self.store.addByValue('fq', exp_string);
                }

                // ADD FILTERING FOR TITLES
                if (fieldConfigs.filter_title != null && fieldConfigs.filter_title != '') {
                    self.store.addByValue('fq', 'titles:(' + fieldConfigs.filter_title + ')');
                }

                //add custom fq value if configured
                if (fieldConfigs.use_custom_q) {
                    if (this.fieldConfigs.custom_q.fq != null && this.fieldConfigs.custom_q.fq != '') {
                        //self.store.removeByValue('fq', fieldConfigs.custom_q.fq);
                        self.store.addByValue('fq', fieldConfigs.custom_q.fq);
                    }
                }

                // add preconfigured asurite filters - Right now this works through the use of the local tag taxonomy
                // system--where terms can be added to the isearch_local_tags taxonomy, and then attached to
                // local isearch_profile nodes.
                if (fieldConfigs.hasOwnProperty('filter_asurite')) {
                    var sstring = asu_dir_solr_search_string(fieldConfigs.filter_asurite, 'asuriteId', true);
                    //self.store.removeByValue('fq', sstring);
                    self.store.addByValue('fq', sstring);
                }
            },


            getEmployeeWeight: function (doc) {
                var locals = this.localPeople;
                var fieldConfigs = this.fieldConfigs;
                var iweight = 999;
                var localweight = 999;
                var temp = doc;
                var fieldId = this.fieldId;

                var rank_mode = fieldConfigs.default_rank_mode;
                var search = ASUPeople[fieldId].dept_nid.toString();
                var asurite = doc.asuriteId;

                // find the iSearch weight
                var position = temp.deptids.indexOf(search);

                if (position >= 0) {
                    //get the person's employee weight for this department
                    if (temp.hasOwnProperty('employeeWeight') && jQuery.trim(temp.employeeWeight[position]) != "") {
                        iweight = parseInt(temp.employeeWeight[position]);
                    }
                }

                //find the localweight if it exists
                if (asurite != null) {

                    if (locals[asurite] != null && locals[asurite].rankweight != null) {
                        localweight = parseInt(locals[asurite].rankweight);
                    }
                }

                if (rank_mode == 'local') {
                    return (localweight < 999) ? localweight : 999;
                } else if (rank_mode == 'isearch') {
                    return (iweight < 999) ? iweight : 999;
                } else {
                    return (iweight < localweight) ? iweight : localweight;
                }
            },


            // if the fq value is listed as an override field (exposed facet, or search), then it overrides rank sorting
            checkOverrides: function () {
                var self = this;
                var override_fields = self.overrideFields;
                var fq = self.store.get('fq');
                var q = self.store.get('q');
                var override = false;
                var fieldConfigs = self.fieldConfigs;
                var filters = fieldConfigs.filters;

                if (q != null && q.value != "*:*") {
                    return true;
                }

                //if an override field is found as an fq, override the manager query
                for (var i = 0; i < fq.length; i++) {
                    if (jQuery.inArray(fq[i].value, filters) == -1) {
                        for (var j = 0; j < override_fields.length; j++) {
                            if (fq[i] != null && fq[i].value != null && fq[i].value.indexOf(override_fields[j]) != -1) {
                                override = true;
                            }
                        }
                    }
                }

                return override;
            }
        });

}));