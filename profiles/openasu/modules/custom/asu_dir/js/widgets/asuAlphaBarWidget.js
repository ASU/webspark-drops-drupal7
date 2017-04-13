/**
 * Define the ASU AlphaBar Widget.
 */
(function ($, history) {

    AjaxSolr.asuAlphaBarWidget = AjaxSolr.AbstractWidget.extend({

        /**
         * @param {Object} [attributes]
         *
         */
        constructor: function (attributes) {
            AjaxSolr.asuAlphaBarWidget.__super__.constructor.apply(this, arguments);
            AjaxSolr.extend(this, {
                field_configs: null,
                last_name_field: null

            }, attributes);
        },

        /*
         In Init, we bind to the Alpha bar, and add the value as a Filter Query
         */
        init: function () {
            var self = this;
            var state = history.getState();
            var lnamefield = self.last_name_field;

            // if lastname parameter is passed in URL, highlight the proper alpha bar item
            var url = state.cleanUrl;
            url = decodeURIComponent(url);
            var index = url.indexOf(lnamefield);

            if (index != -1) {
                index = index + lnamefield.length + 1;
                var passed_letter = url.substr(index, 1);
                var selected_letter = $(self.target).find('li').filter(':contains("' + passed_letter + '")');
                selected_letter.addClass('active-letter');
            }

            // select all letters in the alpha bar, and bind a click event
            // to run the proper query when selected
            var alphabar = $(self.target + ' ul li');

            alphabar.click(function (event) {
                var fq = self.manager.store.get('fq');
                var letter = event.target.innerHTML;

                //handle case of 'un-clicking' the active alpha filter
                if ($(this).hasClass('active-letter')) {
                    $(this).removeClass('active-letter');
                    self.manager.store.removeByValue('fq', lnamefield + ":" + letter + "*");

                    //otherwise, remove any active and add filter
                } else {
                    alphabar.removeClass('active-letter');
                    //if we already have a lastName filter, get rid of it;
                    for (var i = 0; i < fq.length; i++) {
                        if (fq[i] != null && fq[i].value != null && fq[i].value.indexOf(lnamefield) != -1) {
                            self.manager.store.removeByValue('fq', fq[i].value);
                        }
                    }

                    $(this).addClass('active-letter');
                    self.manager.store.addByValue('fq', lnamefield + ":" + letter + "*");
                }

                // remove paging parameter, and do the request
                self.manager.store.remove('start');
                self.manager.doRequest();

            });
        }
    });

})(jQuery, History);