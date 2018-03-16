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
                    pageAlias: null,
                    tree: null,
                    fieldConfigs: null,
                    fieldId: null,
                    isDefault: null,
                    fidNum: null,
                    hasTabs: null,
                    tabContainId: null,
                    tabPaneId: null,
                    tabNum: null,
                }, attributes);
            },

            init: function () {
                var self = this;
                var state = history.getState();
                var url = state.cleanUrl, index = url.indexOf("?");

                if (this.exposed.length) {
                    if (!history) {
                        throw 'ParameterHistoryStore requires History.js';
                    }
                    $(window).unbind('statechange.' + self.fieldId);
                    history.Adapter.bind(window, 'statechange.' + self.fieldId, this.stateChangeFunction(this));
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

            /**
             * Stores the values of the exposed parameters in both the local hash and History.js
             * No other code should be made to change these two values.
             */
            save: function () {

                var state = history.getState();
                this.hash = decodeURIComponent(this.exposedString());
                var url = state.cleanUrl;
                var fieldConfigs = this.fieldConfigs;
                var fieldId = this.fieldId;

                // if this is the active tab, then save the param info into the history state object
                if (ASUPeople.active == fieldId) {

                    var url_hash = this.getPrettyQString();

                    // Only save the new state if it's different from the current state. On initial load, replace the page
                    // state
                    if (state.data.params === undefined) {
                        history.replaceState({params: this.hash}, document.title, '/' + this.pageAlias + '?' + url_hash);
                    } else if (state.data.params != this.hash && this.hash) {
                        history.pushState({params: this.hash}, document.title, '/' + this.pageAlias + '?' + url_hash);
                    }
                }
            },

            /***
             * Clean up the URL string before saving
             * @param hash
             */
            getPrettyQString: function () {
                //  Drupal doesn't like the q param, so we'll replace it in the saved uri with 'query'
                //  Also remove parameters for configs which were set in the in the
                var fieldId = this.fieldId;
                var fidNum = this.fidNum;
                var converted = {};

                converted.dept = ASUPeople[fieldId].dept_nid;
                converted.id = fidNum;

                var qparam = decodeURIComponent(this.params.q.value);

                if (qparam != "*:*") {
                    converted.query = qparam;
                }

                if (this.params.start && this.params.start.value) {
                    converted.start = this.params.start.value;
                }

                return $.param(converted);

            },

            /**
             * @see ParameterStore#storedString()
             */
            storedString: function () {

                var state = history.getState();
                var self = this;
                var url = state.cleanUrl, index = url.indexOf("?");
                var id;
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
                    id = this.getIdFromString(url);

                    if (id == this.fidNum) {
                        ASUPeople.active = this.fieldId;
                    }
                } else if (this.isDefault) {
                    ASUPeople.active = this.fieldId;
                }

                // If this field's not active, return empty string
                if (ASUPeople.active != this.fieldId) {
                    return '';
                }

                // Set the active tab if applicable
                if (this.hasTabs) {
                    var activetab = $('.ui-tabs-nav .ui-state-active a');

                    // if an asu_isearch pane is active, don't click it
                    if (!activetab.hasClass('asu_isearch_view_tab')) {
                        $('#' + this.tabContainId).tabs("option", "active", self.tabNum);
                    }
                }

                // Load the state from the History object.
                if (state.data && state.data.params) {
                    //index = url.indexOf(this.pageAlias);
                    return state.data.params;
                }

                // If initial load, load the state from the URL.
                if (index != -1) {

                    // get current prettified query string, convert it to Solr-compatible string, then return it
                    var query_string = location.search.substring(1);
                    query_string = this.processExposedQuery(query_string);

                    return query_string;
                }

                return '';
            },


            /**
             * Return the current active field ID from the cleanURL
             * @param url
             */
            getIdFromString: function (url) {
                var idString = /id=(\d*)/gi;
                var id = url.match(idString);

                if (id != null && id.length > 0) {
                    id = parseInt(id[0].match(/(\d+)$/)[0], 10);
                }

                return id;
            },

            /**
             * Return current query params as an object
             * @param qstring - the query string
             */
            getQueryObject: function (qstring) {

                // Convert query string to object
                // https://stackoverflow.com/questions/8648892/convert-url-parameters-to-a-javascript-object
                return qstring ? JSON.parse('{"' + qstring.replace(/&/g, '","').replace(/=/g, '":"') + '"}',
                    function (key, value) {
                        return key === "" ? value : decodeURIComponent(value)
                    }) : {};
            },

            /**
             * The cleanUrl we're storing and presenting to the user is not a Solr compatible query. We need to
             * process and convert this to a proper Solr query to be compatible with the current state management.
             */
            processExposedQuery: function (qstring) {

                // get the params as an object to make this easier
                var qObj = this.getQueryObject(qstring);
                var fieldConfigs = this.fieldConfigs;
                var tree = this.tree;
                var fieldId = this.fieldId;
                var nid;

                // Get the active nid if it was passed
                if (qObj.hasOwnProperty('dept')) {
                    nid = qObj.dept;
                    delete qObj.dept;
                }

                if (qObj.hasOwnProperty('query')) {
                    qObj.q = qObj.query;
                    delete qObj.query;
                }

                if (qObj.hasOwnProperty('id')) {
                    delete qObj.id;
                }

                // Set the active global department
                if (nid != null) {
                    ASUPeople[fieldId].dept_nid = nid;
                }

                // return string of parameters
                return $.param(qObj);
            },


            /**
             * Called when History.js detects a state change. Checks if state is different to previous state,
             * and if so, sends a request to Solr. This needs to check if the state has changed since it also
             * gets called when we call above.
             */
            stateChangeFunction: function (self) {

                return function () {

                    var hash = self.storedString();
                    var fieldId = self.fieldId;
                    var fidNum = self.fidNum;

                    hash = decodeURIComponent(hash);
                    self.hash = decodeURIComponent(self.hash);

                    // if this field is active
                    if (ASUPeople.active == fieldId && self.hash != hash) {

                        self.load();
                        var nid = asu_dir_get_nid_from_hash(hash);
                        ASUPeople[fieldId].dept_nid = nid;

                        self.manager.doRequest();

                        //if the tree and widget are loaded
                        if (self.fieldConfigs.show_tree) {
                            //select department tree node from the
                            asu_dir_selectNode(self.tree, self.hash, fidNum);
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
                    } else {
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

