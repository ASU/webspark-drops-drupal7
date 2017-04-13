/**
 * Define the IS Text Widget (search input).
 */
(function ($) {

    AjaxSolr.asu_dirTextWidget = AjaxSolr.AbstractTextWidget.extend({

        constructor: function (attributes) {
            AjaxSolr.asu_dirTextWidget.__super__.constructor.apply(this, arguments);
            AjaxSolr.extend(this, {
                field_configs: null,
                tree: null
            }, attributes);
        },

        init: function () {
            var self = this;
            var field_configs = this.field_configs;
            var tree = this.tree;


            //behavior for the search box.  Bind to enter key, and
            // add q value when there is one present
            $(this.target).find('input').bind('keydown', function (e) {

                if (e.which == 13) {

                    var fq = self.manager.store.values('fq');

                    var value = $(this).val();

                    if (value) {
                        Manager.store.remove('q');
                        Manager.store.addByValue('q', value);
                        // If sub-departments toggle is not selected, then add sub-departments for search,
                        // and remove other fq values
                        if (!field_configs.sub_toggle && !field_configs.use_custom_q && field_configs.show_tree) {
                            //remove only the deptids fq parameter
                            for (var i = 0; i < fq.length; i++) {
                                if (fq[i] != null && fq[i].indexOf("deptids:") != -1) {
                                    Manager.store.removeByValue('fq', fq[i]);
                                }
                            }

                            var nid = ASUPeople.dept_nid;

                            var sub_tree = asu_dir_ajax_solr_find_root(tree, nid);
                            var tree_ids = asu_dir_get_tree_ids(sub_tree);
                            var search_string = asu_dir_solr_search_string(tree_ids, 'deptids');

                            Manager.store.addByValue('fq', search_string);
                        }

                        self.doRequest();
                    } else {
                        Manager.store.remove('q');
                        Manager.store.addByValue('q', '*:*');

                        //remove only the deptids parameter
                        if (!field_configs.sub_toggle) {
                            for (var i = 0; i < fq.length; i++) {
                                if (fq[i].indexOf("deptids:") != -1) {
                                    Manager.store.removeByValue('fq', fq[i]);
                                }
                            }
                            //Manager.store.remove('fq');
                            var nid = ASUPeople.dept_nid;
                            Manager.store.addByValue('fq', 'deptids:' + nid);
                        }
                        self.doRequest();
                    }
                }
            });
        },

        afterRequest: function () {


            // If the persisted input field value and current q value match,
            // leave input value alone. Otherwise, clear it.
            if (Manager.store.params.q.value == $(this.target).find('input').val()) {
                // Do nothing.
            }
            else {
                // Clear the value.
                $(this.target).find('input').val('');
            }
        } // end afterRequest

    });
})(jQuery);

