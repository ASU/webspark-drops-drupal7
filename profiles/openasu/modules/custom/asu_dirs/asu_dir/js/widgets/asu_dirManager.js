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
                    localPeople: null,
                    savedDeptNids: null,
                    prevDeptNid: null,
                    tree: []
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

            /**
             * Stores the Solr parameters to be sent to Solr and sends a request to Solr.
             *
             * @param {Boolean} [start] The Solr start offset parameter.
             * @param {String} [servlet] The Solr servlet to send the request to.
             */
            doRequest: function (start, servlet) {
                if (this.initialized === false) {
                    this.init();
                }
                // Allow non-pagination widgets to reset the offset parameter.
                if (start !== undefined) {
                    this.store.get('start').val(start);
                }
                if (servlet === undefined) {
                    servlet = this.servlet;
                }

                // add a q value if there is none
                if (!this.store.params.q.value) {
                    this.store.addByValue('q', '*:*');
                }

                // add the department filter first thing
                this.addDeptFilter();

                this.store.save();

                for (var widgetId in this.widgets) {
                    this.widgets[widgetId].beforeRequest();
                }

                this.executeRequest(servlet);
            },

            executeRequest: function (servlet, string, handler, errorHandler) {

                var self = this,
                    options = {dataType: 'json'};
                var fq = self.store.get('fq');
                var q = self.store.get('q');
                var pag_results;
                var fieldId = this.fieldId;
                var fieldConfigs = self.fieldConfigs;
                //var override = this.checkOverrides();

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

                // The employeeWeights field in Solr is a multivalued field. If we are using rank
                // sort, then we need to pull all results, map the employee
                // rank weights according to backend configs, and slice the array to get
                // the paginated results.
                if (fieldConfigs.show_managers) {

                    //get the start parameter, if it exists.  we need this for
                    //pagination of results
                    var start = 0;
                    if (self.store.params.start.value != undefined) {
                        start = parseInt(self.store.params.start.value);
                    }

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

                        var sorted = docs;

                        //substitute the proper page of the array
                        pag_results = sorted.slice(start, start + self.perPage);
                        data.response.docs = pag_results;

                        self.handleResponse(data);

                    }).fail(errorHandler);

                } else {
                    jQuery.ajax(options).done(handler).fail(errorHandler);
                }
            },

            addDeptFilter: function () {
                // load the nids from the tree dynamically if possible
                var dynamic_nids = [];
                var self = this;
                var fieldConfigs = this.fieldConfigs;
                var savedDeptNids = this.savedDeptNids;
                var fieldId = this.fieldId;
                var prevDeptNid = this.prevDeptNid;
                var fq = this.store.values('fq');

                // Initial request on load
                if (!ASUPeople[fieldId].dept_nid) {
                    //Set the global if no params are set
                    ASUPeople[fieldId].dept_nid = savedDeptNids[0];
                }

                // If nid state hasn't changed, don't add any filters
                if (prevDeptNid == ASUPeople[fieldId].dept_nid) {
                    return false;
                }

                this.prevDeptNid = ASUPeople[fieldId].dept_nid;

                // Remove previous dept nid params
                for (var x = 0; x < fq.length; x++) {
                    if (fq[x] != null && fq[x].indexOf("deptids:") != -1) {
                        self.store.removeByValue('fq', fq[x]);
                    }
                }

                // If we're showing the directory tree, build the department down from the active
                // department
                if (fieldConfigs.show_tree) {

                    dynamic_nids = this.addDepts(ASUPeople[fieldId].dept_nid, fieldConfigs.sub_toggle, dynamic_nids);

                    // If not showing tree, build a query of all configured departments
                } else {
                    if (fieldConfigs.depts != null && fieldConfigs.depts.items != null) {

                        var depts = fieldConfigs.depts.items;

                        for (var i = 0; i < depts.length; i++) {
                            dynamic_nids = this.addDepts(depts[i].dept_nid, depts[i].options.subdepts, dynamic_nids)
                        }
                    }
                }

                //Create the query string for depts
                if (dynamic_nids.length > 0) {
                    self.store.addByValue('fq', asu_dir_solr_search_string(dynamic_nids, 'deptids'));
                }
            },

            /**
             * Add departments to an array given a dept nid to build from.
             * @param deptNid - Dept node id to build from
             * @param subdepts (bool) - Add subdepartments under deptNid
             * @param nidArray - array to add to
             *
             **/
            addDepts: function (deptNid, subdepts, nidArray) {
                var tree = this.tree;
                var stree;
                var sarray;
                var tar;
                nidArray = nidArray ? nidArray : [];

                if (subdepts) {
                    stree = asu_dir_ajax_solr_find_root(tree, deptNid);
                    sarray = asu_dir_get_tree_ids(stree);
                    nidArray = nidArray.concat(sarray);
                } else {
                    tar = [deptNid];
                    nidArray = nidArray.concat(tar);
                }

                return nidArray;
            },

            /**
             *
             * adds preconfigured filters to the manager
             */
            addPreFilters: function () {

                var self = this;
                var fieldConfigs = self.fieldConfigs;
                var start = self.store.get('start').val();
                var q = self.store.get('q').val();
                var fq = self.store.get('fq');
                var etypes = fieldConfigs.employee_types;

                // ADD EMPLOYEE TYPES FILTER TO QUERY
                if (etypes && etypes.length > 0) {
                    //If employee types other than "Show All" are selected, add those as a filter query
                    var show_all = fieldConfigs.employee_types.indexOf("All");
                    var legacy = fieldConfigs.employee_types.indexOf("Show All");

                    if (fieldConfigs.employee_types.length > 0 && show_all == -1 && legacy == -1) {
                        var types = fieldConfigs.employee_types;
                        var search_string = asu_dir_solr_search_string(types, 'employeeTypes', true);

                        //need to add this to the manager query also
                        self.store.addByValue('fq', search_string);
                    }
                }

                // add the faculty titles filter if it is configured - tenure/non-tenure relies on this
                if (fieldConfigs.hasOwnProperty('ft_filter') && fieldConfigs.ft_filter) {
                    self.store.addByValue('fq', fieldConfigs.ft_filter);
                }

                // ADD FILTERING FOR EXPERTISE AREAS
                if (fieldConfigs.expertise_areas) {
                    var exp_string = asu_dir_solr_search_string(fieldConfigs.expertise_areas, 'expertiseAreas', true);
                    self.store.addByValue('fq', exp_string);
                }

                // ADD FILTERING FOR TITLES
                if (fieldConfigs.filter_title) {
                    self.store.addByValue('fq', 'titles:(' + fieldConfigs.filter_title + ')');
                }

                //add custom fq value if configured
                if (fieldConfigs.use_custom_q && fieldConfigs.custom_q.fq) {
                    //self.store.removeByValue('fq', fieldConfigs.custom_q.fq);
                    self.store.addByValue('fq', fieldConfigs.custom_q.fq);
                }

                // add preconfigured asurite filters - Right now this works through the use of the local tag taxonomy
                // system--where terms can be added to the isearch_local_tags taxonomy, and then attached to
                // local isearch_profile nodes.
                if (fieldConfigs.filter_asurite) {
                    var sstring = asu_dir_solr_search_string(fieldConfigs.filter_asurite, 'asuriteId', true);
                    //self.store.removeByValue('fq', sstring);
                    self.store.addByValue('fq', sstring);
                }
            },

            /**
             * Get the mapped employee weight for a given Solr doc
             * @param doc
             * @returns {number}
             */
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
            }
            // if the fq value is listed as an override field (exposed facet, or search), then it overrides rank sorting
            /*checkOverrides: function () {
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
             }*/
        });

}));