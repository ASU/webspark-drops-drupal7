/**
 * Define the IS Text Widget (search input).
 */
(function ($) {

    AjaxSolr.asu_dirTextWidget = AjaxSolr.AbstractTextWidget.extend({

        constructor: function (attributes) {
            AjaxSolr.asu_dirTextWidget.__super__.constructor.apply(this, arguments);
            AjaxSolr.extend(this, {
                fieldConfigs: null,
                tree: null,
                fieldId: null
            }, attributes);
        },

        init: function () {
            var self = this;
            var fieldConfigs = this.fieldConfigs;
            var tree = this.tree;
            var fieldId = this.fieldId;


            //behavior for the search box.  Bind to enter key, and
            // add q value when there is one present
            $(this.target).find('input').bind('keydown', function (e) {

                if (e.which == 13) {

                    var fq = self.manager.store.values('fq');

                    var value = $(this).val();

                    if (value) {
                        self.manager.store.remove('q');
                        self.manager.store.addByValue('q', value);
                        self.doRequest();
                    } else {
                        self.manager.store.remove('q');
                        self.manager.store.addByValue('q', '*:*');
                        self.doRequest();
                    }
                }
            });
        },

        afterRequest: function () {
            var self = this;

            // If the persisted input field value and current q value match,
            // leave input value alone. Otherwise, clear it.
            if (self.manager.store.params.q.value == $(this.target).find('input').val()) {
                // Do nothing.
            }
            else {
                // Clear the value.
                $(this.target).find('input').val('');
            }
        } // end afterRequest

    });
})(jQuery);

