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
                field_configs: null,
                tree: null
            }, attributes);
        },

        afterRequest: function () {
            var self = this;
            var field_configs = this.field_configs;
            var tree = this.tree;
            var links = [];

            var q = this.manager.store.get('q').val();
            if (q != '*:*') {
                links.push($('<a href="#"></a>').text('"' + q + '"').append(' <i class="fa fa-close"></i> ').click(function () {
                    self.manager.store.get('q').val('*:*');

                    if (!field_configs.sub_toggle && !field_configs.use_custom_q) {
                        self.manager.store.remove('fq');
                        self.manager.store.addByValue('fq', 'deptids:' + ASUPeople.dept_nid);
                    }

                    self.doRequest();
                    return false;
                }));
            }

            var fq = this.manager.store.values('fq');

            for (var i = 0, l = fq.length; i < l; i++) {
                // Match only the value. Not the label.
                if (fq[i] !== null) {
                    var index_nids = fq[i].indexOf("deptids:");
                    var empl_types = fq[i].indexOf("employeeTypes");
                    var last_names = fq[i].indexOf("lastName");

                    //don't push the deptids fq, or the employee types fq
                    if (index_nids == -1 && empl_types == -1 && last_names == -1) {
                        var match = fq[i].match(/:(.*)/);

                        links.push($('<a href="#"></a>').text(match[1]).append(' <i class="fa fa-close"></i> ').click(self.removeFacet(fq[i])));
                    }
                }
            }

            if (links.length) {
                var $target = $(this.target);
                $target.empty();
                /*
                 if (links.length > 0) {
                 $target.append('<span class="breadcrumb"> People </span>');
                 }*/

                for (var i = 0, l = links.length; i < l; i++) {
                    if (i > 0) {
                        $target.append(' &gt; ').append(links[i]);
                    } else {
                        $target.append(links[i]);
                    }
                }
            }
            else {
                $(this.target).html(''); // Default when no search search params provided.
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

