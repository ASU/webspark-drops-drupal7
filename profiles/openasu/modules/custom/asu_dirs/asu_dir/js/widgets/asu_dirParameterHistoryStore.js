;
(function (history, $) {
    /**
     * A parameter store that stores the values of exposed parameters in the URL via History.js
     * to maintain the application's state. This uses the HTML5 History API for newer browsers, and
     * falls back to using the hash in older browsers. Don't forget to add the following (or similar)
     * inside your <tt>head</tt> tag:
     *
     * <pre>
     * <script src="history.js/scripts/bundled/html4+html5/jquery.history.js"></script>
     * </pre>
     *
     * Configure the manager with:
     *
     * <pre>
     * Manager.setStore(new AjaxSolr.ParameterHistoryStore());
     * </pre>
     *
     * @class ParameterHistoryStore
     * @augments AjaxSolr.ParameterStore
     * @see https://github.com/browserstate/history.js
     * @see http://www.whatwg.org/specs/web-apps/current-work/multipage/history.html
     */
    AjaxSolr.asu_dirParameterHistoryStore = AjaxSolr.ParameterHistoryStore.extend( // ASU edit - extend ParameterHistoryStore.
        /** @lends AjaxSolr.ParameterHistoryStore.prototype */
        {
            /**
             * @param {Object} [attributes]
             *
             */
            constructor: function (attributes) {
                AjaxSolr.asu_dirParameterHistoryStore.__super__.constructor.apply(this, arguments);
                AjaxSolr.extend(this, {
                    page_alias: null,
                    tree: null,
                    field_configs: null,
                    dept_nids: [],
                    field_id: null,
                    is_default: null,
                    id_num: null,
                    has_tabs: null,
                    tab_id: null,
                    tab_pane_id: null,
                    tab_link: null,
                    tab_num: null,
                    saved_dept_nids: null
                }, attributes);
            },

            init: function () {
                var self = this;
                var state = history.getState();
                var url = state.cleanUrl, index = url.indexOf("?");
                var saved_dept_nids = this.saved_dept_nids;
                var field_id = this.field_id;

                // Initial request on load
                if (self.manager.store.params.q == null) {

                    //Set the global if no params are set
                    ASUPeople[field_id].dept_nid = saved_dept_nids[0];
                    self.manager.store.addByValue('q', '*:*');
                    //Create the query string for depts
                    self.manager.store.addByValue('fq', asu_dir_solr_search_string(saved_dept_nids, 'deptids'));
                }

                if (index != -1) {
                    var id_string = /id=(\d*)/gi;
                    var id = url.match(id_string);

                    if (id != null && id.length > 0) {
                        id = parseInt(id[0].match(/(\d+)$/)[0], 10);
                    }

                    if (id == this.id_num) {
                        ASUPeople.active = this.field_id;
                    }
                } else if (this.is_default) {
                    ASUPeople.active = this.field_id;
                }

                if (this.exposed.length) {
                    if (!history) {
                        throw 'ParameterHistoryStore requires History.js';
                    }

                    history.Adapter.bind(window, 'statechange', this.stateChangeFunction(this));
                }

                if (this.has_tabs) {
                    var tab_num = this.tab_num;

                    $("#" + this.tab_id).on("tabsactivate", function (event, ui) {

                        var index = ui.newTab.index();

                        if (index == tab_num) {
                            ASUPeople.active = field_id;
                            self.save();
                        }

                    });
                }
            },


            /**
             * Some Solr parameters may be specified multiple times. It is easiest to
             * hard-code a list of such parameters. You may change the list by passing
             * <code>{ multiple: /pattern/ }</code> as an argument to the constructor of
             * this class or one of its children, e.g.:
             *
             * <p><code>new ParameterStore({ multiple: /pattern/ })</code>
             *
             * @param {String} name The name of the parameter.
             * @returns {Boolean} Whether the parameter may be specified multiple times.
             * @see http://lucene.apache.org/solr/api/org/apache/solr/handler/DisMaxRequestHandler.html
             */
            isMultiple: function (name) {
                // We need a null check. Perhaps due to not displaying results when no
                // search string is in, by default.
                if (name != null) {
                    return name.match(/^(?:bf|bq|facet\.date|facet\.date\.other|facet\.date\.include|facet\.field|facet\.pivot|facet\.range|facet\.range\.other|facet\.range\.include|facet\.query|fq|group\.field|group\.func|group\.query|pf|qf)$/);
                }
            },

            // Only need to replace these two methods. ?q= arg won't fly with Drupal,
            // as it collides with Drupal's mod_rewrite to ?q=. So we use the search
            // path + q= instead. And that seems to work alright.

            /**
             * Stores the values of the exposed parameters in both the local hash and History.js
             * No other code should be made to change these two values.
             */
            save: function () {

                var state = history.getState();
                this.hash = this.exposedString();
                var url = state.cleanUrl, index = url.indexOf("?");

                this.hash = decodeURIComponent(this.hash);
                var url_hash = this.hash;
                var field_configs = this.field_configs;
                var field_id = this.field_id;

                //todo: only replace the q=
                // so something like /(\/|&)q=/gi but with positive lookbehind-like behavior


                if (ASUPeople.active == field_id) {

                    url_hash = this.cleanCustomString(url_hash, field_configs);

                    //only save the new state if it's different from the current state
                    if (state.data.params === undefined) {
                        history.replaceState({params: this.hash}, null, '/' + this.page_alias + '?' + url_hash);
                    } else if (state.data.params != this.hash && this.hash) {
                        history.pushState({params: this.hash}, null, '/' + this.page_alias + '?' + url_hash);
                    }
                }
            },

            /***
             * Clean up the URL string before saving
             * @param hash
             * @param field_configs
             */
            cleanCustomString: function (url_hash, field_configs) {
                //  Drupal doesn't like the q param, so we'll replace it in the saved uri with 'query'
                //  Also remove parameters for configs which were set in the in the
                var re = /(fq=deptids:).*?(&|$)/gi;
                var eq = /(fq=employeeTypes:).*?(&)/gi;
                var sort = /(&sort=.*?)(?=&|$)/gi;
                var rows = /(&rows=.*?)(?=&|$)/gi;
                var field_id = this.field_id;
                var qparam = /q=/gi;
                var id_num = this.id_num;

                //var ft = /(fq=facultyTitles:).*?(&)/gi;
                // if we have the facultytitles config active, then remove it from URL
                if (field_configs.hasOwnProperty('ft_filter')) {

                    var escaped = field_configs.ft_filter.replace(/[\-\[\]\/\{\}\(\)\*\+\?\.\\\^\$\|]/g, "\\$&");

                    var ft_string = '(fq=' + escaped + '&?)';
                    var ft = new RegExp(ft_string, 'gi');

                    url_hash = url_hash.replace(ft, "");

                }

                // remove the custom fq value
                if (field_configs.use_custom_q) {
                    if (this.field_configs.custom_q.fq != null && this.field_configs.custom_q.fq != '') {

                        var custom_fq = field_configs.custom_q.fq.replace(/[\-\[\]\/\{\}\(\)\*\+\?\.\\\^\$\|]/g, "\\$&");
                        var fq_string = '(fq=' + custom_fq + '&?)';
                        var fq_regex = new RegExp(fq_string, 'gi');

                        url_hash = url_hash.replace(fq_regex, "");
                    }
                }

                //clean up the URL for display.  this means removing all pre-configured filter values
                url_hash = decodeURIComponent(url_hash);

                //remove the sort and employee type parameters from the hash
                url_hash = url_hash.replace(eq, "");
                url_hash = url_hash.replace(sort, "");
                url_hash = url_hash.replace(rows, "");
                url_hash = url_hash.replace(re, 'dept=' + ASUPeople[field_id].dept_nid + '&');


                this.hash = this.hash.replace(sort, "");
                this.hash = this.hash.replace(rows, "");

                url_hash = url_hash.replace(qparam, 'query=');
                url_hash = url_hash + '&id=' + id_num;

                return url_hash;

            },

            /**
             * @see ParameterStore#storedString()
             */
            storedString: function () {
                var state = history.getState();
                var tree = this.tree;
                var self = this;
                var field_configs = this.field_configs;
                var field_id = this.field_id;
                var id_num = this.id_num;
                var url = state.cleanUrl, index = url.indexOf("?");
                var id_string = /id=(\d*)/gi;
                var id = null;
                var currentState = window.history.state;

                // manage state after saving in ipe. that logic found in asu_dir_config.js
                if (currentState != null && currentState.hasOwnProperty('reset') &&
                    currentState.reset === true) {
                    return '';
                }

                // Very important:  Each time a statechange is detected, this storedString function is the first to run.
                // Find the ID in the cleanurl if it exists, and set the 'active' parameter on the ASUPeople global.
                // We only want to do a request on the current exposed/active directory, so all functions which do requests
                // will key on this value
                if (index != -1) {
                    id = url.match(id_string);

                    if (id != null && id.length > 0) {
                        id = parseInt(id[0].match(/(\d+)$/)[0], 10);
                    }

                    ASUPeople.active = 'asu_dir' + id;
                }


                // Load the state from the History object.
                if (state.data && state.data.params) {

                    if (id == id_num) {
                        $('#' + this.tab_link).click();
                        //index = url.indexOf(this.page_alias);
                        return state.data.params;
                    } else {
                        return '';
                    }
                }

                // If initial load, load the state from the URL.
                if (index == -1) {
                    return '';
                } else if (id == id_num) {

                    //get the query string from URL
                    var query_string = url.substr(index + 1);

                    // Check if the query value is the default *:*, otherwise
                    // append all sub-departments to deptids: fq, to search all sub-departments
                    var search_re = /query=\*:\*/gi;

                    var replace_search = /query=/gi;
                    var search_string = query_string.match(search_re);

                    if (search_string != -1) {
                        query_string = query_string.replace(replace_search, 'q=');
                    }

                    query_string = decodeURIComponent(query_string);

                    id_string = /&id=(\d*)/gi;
                    var q_dept = /dept=/gi;
                    var nid = asu_dir_get_nid_from_hash(query_string);

                    //change back to the deptids:
                    query_string = query_string.replace(q_dept, 'fq=deptids:');

                    //remove the id parameter, since it does not exist in SolR
                    query_string = query_string.replace(id_string, '');

                    // Append the sub-departments to the query string if that option is selected
                    if (field_configs.sub_toggle || search_string == null) {

                        var sub_tree = asu_dir_ajax_solr_find_root(tree, nid);
                        var tree_ids = asu_dir_get_tree_ids(sub_tree);
                        var new_string = asu_dir_solr_search_string(tree_ids, 'deptids');
                        var old_string = query_string.match(/fq=deptids:.*?&/gi);

                        query_string = query_string.replace(old_string, 'fq=' + new_string + '&');
                    }

                    //set the active department, and tab
                    ASUPeople[field_id].dept_nid = nid;


                    ASUPeople.active = field_id;
                    $('#' + this.tab_link).click();


                    return query_string;
                } else {
                    return '';
                }
            },


            /**
             * Called when History.js detects a state change. Checks if state is different to previous state,
             * and if so, sends a request to Solr. This needs to check if the state has changed since it also
             * gets called when we call pushttp://dmod.dev/content/university-technology-office?fquery=deptids%3A1565&query=*%3A*&sort=lastNameSort%20aschState above.
             */
            stateChangeFunction: function (self) {

                return function () {

                    var hash = self.storedString();
                    var field_id = self.field_id;
                    var id_num = self.id_num;

                    hash = decodeURIComponent(hash);
                    self.hash = decodeURIComponent(self.hash);

                    if (ASUPeople.active == field_id) {
                        if (self.hash != hash) {

                            self.load();
                            var nid = asu_dir_get_nid_from_hash(hash);
                            ASUPeople[field_id].dept_nid = nid;

                            self.manager.doRequest();

                            //if the tree and widget are loaded
                            if (self.field_configs.show_tree) {
                                //select department tree node from the
                                asu_dir_selectNode(self.tree, self.hash, id_num);
                            }
                        }
                    }
                }
            },

            /**
             * If the parameter may be specified multiple times, creates a parameter using
             * the given name and value, and adds it to the list of identically-named
             * parameters, unless one already exists with the same value. If it may be
             * specified only once, replaces the parameter.
             *
             * @param {String} name The name of the parameter.
             * @param {String|Number|String[]|Number[]} value The value.
             * @param {Object} [locals] The parameter's local parameters.
             * @returns {AjaxSolr.Parameter|Boolean} The parameter, or false.
             */
            addByValue: function (name, value, locals) {

                if (locals === undefined) {
                    locals = {};
                }
                if (this.isMultiple(name) && AjaxSolr.isArray(value)) {
                    var ret = [];
                    for (var i = 0, l = value.length; i < l; i++) {
                        ret.push(this.add(name, new AjaxSolr.Parameter({name: name, value: value[i], locals: locals})));
                    }
                    return ret;
                }
                else {
                    return this.add(name, new AjaxSolr.Parameter({name: name, value: value, locals: locals}));
                }
            },

            /**
             * If the parameter may be specified multiple times, adds the given parameter
             * to the list of identically-named parameters, unless one already exists with
             * the same value. If it may be specified only once, replaces the parameter.
             *
             * @param {String} name The name of the parameter.
             * @param {AjaxSolr.Parameter} [param] The parameter.
             * @returns {AjaxSolr.Parameter|Boolean} The parameter, or false.
             */
            add: function (name, param) {
                if (param === undefined) {
                    param = new AjaxSolr.Parameter({name: name});
                }
                if (this.isMultiple(name)) {

                    // for some reason, the facultyTitles fq query string is getting split into 2 arrays,
                    // along the Instructor, ABD comma split.
                    // TODO:  pre-emptively stop the behavior
                    param.value = param.value.toString();

                    if (this.params[name] === undefined) {
                        this.params[name] = [param];
                    }
                    else {
                        if (AjaxSolr.inArray(param.val(), this.values(name)) == -1) {
                            this.params[name].push(param);
                        }
                        else {
                            return false;
                        }
                    }
                }
                else {
                    this.params[name] = param;
                }
                return param;
            }

        });
})(window.History, jQuery);

