/**
 * Define the IS CurrentSearch Widget.
 */
(function ($) {

    AjaxSolr.asu_dirCurrentSearchWidget = AjaxSolr.AbstractWidget.extend({
        start: 0,

        /**
         * @param {Object} [attributes]
         *
         */
        constructor: function (attributes) {
            AjaxSolr.asu_dirCurrentSearchWidget.__super__.constructor.apply(this, arguments);
            AjaxSolr.extend(this, {
                breadcrumb_target: null,
                field_configs: null,
                tree: null,
                field_id: null,
                id_num: null,
                current_search_exclude: []
            }, attributes);
        },


        init: function () {

        },

        afterRequest: function () {
            var self = this;
            var field_configs = this.field_configs;
            var tree = this.tree;
            var links = [];
            var field_id = this.field_id;
            var custom_q = field_configs.use_custom_q;
            var excludes = this.current_search_exclude;
            var custom_fq = null;

            if (field_configs.custom_q != null && field_configs.custom_q.fq != null) {
                custom_fq = field_configs.custom_q.fq;
            }

            var q = this.manager.store.get('q').val();
            if (q != '*:*') {
                links.push($('<a href="#"></a>').text('"' + q + '"').append(' <i class="fa fa-close"></i> ').click(function () {
                    self.manager.store.get('q').val('*:*');
                    /*TODO: get rid of if not needed
                     if (!field_configs.sub_toggle && !field_configs.use_custom_q) {
                     self.manager.store.remove('fq');
                     self.manager.store.addByValue('fq', 'deptids:' + ASUPeople[field_id].dept_nid);
                     }*/

                    self.doRequest();
                    return false;
                }));
            }

            var fq = this.manager.store.values('fq');
            var filters = field_configs.filters;

            for (var i = 0, l = fq.length; i < l; i++) {
                var skip = false;
                // Match only the value. Not the label.
                if (fq[i] != null && typeof fq[i] !== 'undefined') {

                    for (var x = 0; x < excludes.length; x++) {
                        if (fq[i].indexOf(excludes[x]) != -1 || fq[i] == custom_fq) {
                            skip = true;
                        }
                    }

                    //don't push the deptids fq, or the employee types fq
                    if (!skip) {
                        var match = fq[i].match(/:(.*)/);

                        if (match !== null) {
                            links.push($('<a href="#"></a>').text(match[1]).append(' <i class="fa fa-close"></i> ').click(self.removeFacet(fq[i])));
                        }
                    }
                }
            }

            if (links.length) {
                var $target = $(this.target);
                $target.empty();

                for (var i = 0, l = links.length; i < l; i++) {
                    $target.append(' &gt; ').append(links[i]); //.append(' &gt; ');
                }
            } else {
                $(this.target).html(' &gt; '); // Default when no search search params provided.
            }
        },

        removeFacet: function (facet) {
            var self = this;
            return function () {
                if (self.manager.store.removeByValue('fq', facet)) {
                    self.doRequest();
                }
                return false;
            };
        }
    });

})(jQuery);



