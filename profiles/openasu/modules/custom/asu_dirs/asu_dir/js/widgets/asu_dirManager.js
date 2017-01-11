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
                    field_configs: null,
                    sorted_people: {},
                    sorted_response: {},
                    override_fields: [],
                    field_id: null,
                    per_page: null,
                    local_people: null
                }, attributes);
            },

            executeRequest: function (servlet, string, handler, errorHandler) {
                var self = this,
                    options = {dataType: 'json'};
                var fq = self.store.get('fq');
                var q = self.store.get('q');
                var pag_results;
                var field_id = this.field_id;
                var field_configs = self.field_configs;
                var per_page = self.per_page;
                var override = this.checkOverrides();
                var locals = this.local_people;

                //add custom fq value if configured
                if (field_configs.use_custom_q) {
                    if (this.field_configs.custom_q.fq != null && this.field_configs.custom_q.fq != '') {
                        this.store.removeByValue('fq', field_configs.custom_q.fq);
                        this.store.addByValue('fq', field_configs.custom_q.fq);
                    }
                }

                if (field_configs.hasOwnProperty('filter_asurite')) {
                    var sstring = asu_dir_solr_search_string(field_configs.filter_asurite, 'asuriteId', true);
                    this.store.removeByValue('fq', sstring);
                    this.store.addByValue('fq', sstring);
                }

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
                if (field_configs.show_managers && !override) {

                    //get the start parameter, if it exists.  we need this for
                    //pagination of results
                    var start = 0;
                    if (self.store.params.start.value != undefined) {
                        start = parseInt(self.store.params.start.value);
                    }

                    // if we have not set sorted people for the current dept.
                    if (self.sorted_people[ASUPeople[field_id].dept_nid] == null) {
                        // grab all of the results and start from the beginning
                        // we'll need to sort all results as a group
                        options.url = options.url + "&rows=2000";

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
                            self.sorted_people[ASUPeople[field_id].dept_nid] = docs;

                            //substitute the proper page of the array
                            pag_results = self.sorted_people[ASUPeople[field_id].dept_nid].slice(start, start + self.per_page);

                            data.response.docs = pag_results;
                            self.sorted_response[ASUPeople[field_id].dept_nid] = data;

                            self.handleResponse(data);

                        }).fail(errorHandler);
                    } else {
                        var data = self.sorted_response[ASUPeople[field_id].dept_nid];
                        pag_results = self.sorted_people[ASUPeople[field_id].dept_nid].slice(start, start + self.per_page);
                        data.response.docs = pag_results;
                        //self.sorted_response[ASUPeople[field_id].dept_nid] = data;
                        self.handleResponse(data);
                    }

                } else {
                    jQuery.ajax(options).done(handler).fail(errorHandler);
                }
            },


            getEmployeeWeight: function (doc) {
                var locals = this.local_people;
                var field_configs = this.field_configs;
                var iweight = 999;
                var localweight = 999;
                var temp = doc;
                var field_id = this.field_id;
                var rank_mode = field_configs.default_rank_mode;
                var search = ASUPeople[field_id].dept_nid.toString();
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
                var override_fields = self.override_fields;
                var fq = self.store.get('fq');
                var q = self.store.get('q');
                var override = false;
                var field_configs = self.field_configs;
                var filters = field_configs.filters;

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