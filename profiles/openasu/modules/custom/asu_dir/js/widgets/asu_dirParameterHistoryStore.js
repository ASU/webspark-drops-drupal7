;
(function (history) {
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

            init: function () {

                if (this.exposed.length) {
                    if (!history) {
                        throw 'ParameterHistoryStore requires History.js';
                    }

                    history.Adapter.bind(window, 'statechange', this.stateChangeFunction(this));
                }
            },

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
                    dept_nids: []
                }, attributes);
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

                this.hash = this.exposedString();

                var url_hash = this.hash;
                var state = history.getState();
                var field_configs = this.field_configs;

                //Drupal doesn't like the q param, so we'll replace it in the saved uri with 'query'
                var re = /(fq=deptids:).*?(&)/gi;
                var eq = /(fq=employeeTypes:).*?(&)/gi;
                var sort = /(&sort=lastNameSort).*?(asc)/gi;

                var qparam = /q=/gi;


                //clean up the URL if not using the custom query
                if (!field_configs.use_custom_q) {
                    url_hash = decodeURIComponent(url_hash);

                    //remove the sort and employee type parameters from the
                    url_hash = url_hash.replace(eq, "");
                    url_hash = url_hash.replace(sort, "");
                    url_hash = url_hash.replace(re, 'dept=' + ASUPeople.dept_nid + '&');
                }

                url_hash = url_hash.replace(qparam, 'query=');

                //only save the new state if it's different from the current state
                if (state.data.params != this.hash) {
                    history.pushState({params: this.hash}, null, '/' + this.page_alias + '?' + url_hash);
                }
            },

            /**
             * @see ParameterStore#storedString()
             */
            storedString: function () {
                var state = history.getState();
                var tree = this.tree;
                var self = this;
                var field_configs = this.field_configs;
                var dept_nids = this.dept_nids;

                // Load the state from the History object.
                if (state.data && state.data.params) {
                    //index = url.indexOf(this.page_alias);
                    return state.data.params;
                }

                // If initial load, load the state from the URL.
                var url = state.cleanUrl, index = url.indexOf("?");

                if (index == -1) {
                    return '';
                } else {
                    //get the query string from URL
                    var query_string = url.substr(index + 1);

                    // Check if the query value is the default *:*, otherwise
                    // append all sub-departments to deptids: fq, to search all sub-departments
                    var search_re = /query=\*:\*/gi;
                    var search_string = query_string.match(search_re);

                    if (!field_configs.use_custom_q) {
                        query_string = decodeURIComponent(query_string);

                        var q_dept = /dept=/gi;
                        query_string = query_string.replace(q_dept, 'fq=deptids:');
                        var nid = asu_dir_get_nid_from_hash(query_string);

                        // Append the sub-departments to the query string if that option is selected
                        if (field_configs.sub_toggle || search_string == null) {
                            var sub_tree = asu_dir_ajax_solr_find_root(tree, nid);
                            var tree_ids = asu_dir_get_tree_ids(sub_tree);
                            var new_string = asu_dir_solr_search_string(tree_ids, 'deptids');
                            var old_string = query_string.match(/fq=deptids:.*?&/gi);

                            query_string = query_string.replace(old_string, 'fq=' + new_string + '&');
                        }

                        ASUPeople.dept_nid = nid;
                    }

                    var re = /query=/gi;
                    query_string = query_string.replace(re, 'q=');

                    return query_string;
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

                    hash = decodeURIComponent(hash);
                    self.hash = decodeURIComponent(self.hash);

                    if (self.hash != hash) {
                        self.load();
                        var nid = asu_dir_get_nid_from_hash(hash);
                        ASUPeople.dept_nid = nid;

                        self.manager.doRequest();

                        //if the tree and widget are loaded
                        if (self.field_configs.show_tree) {
                            //select department tree node from the
                            asu_dir_selectNode(self.tree, self.hash);
                        }
                    }
                }
            }

        });
})(window.History);

