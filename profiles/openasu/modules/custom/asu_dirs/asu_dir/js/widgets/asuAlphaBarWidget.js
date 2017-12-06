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
                fieldConfigs: null,
                lastNameField: null,
                fieldId: null

            }, attributes);
        },

        /*
         In Init, we bind to the Alpha bar, and add the value as a Filter Query
         */
        init: function () {
            var self = this;
            var state = history.getState();
            var lnamefield = self.lastNameField;
            var fieldId = this.fieldId;

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

                    if (letter != 'ALL') {
                        $(this).addClass('active-letter');
                        self.manager.store.addByValue('fq', lnamefield + ":" + letter + "*");
                    }
                }

                // remove paging parameter, and do the request
                self.manager.store.remove('start');
                self.manager.doRequest();

            });
        },

        // before the request, check if the lastname alphabar facet is active, then add or
        // remove the active-class if applicable
        beforeRequest: function () {

            var self = this;
            var start = self.manager.store.get('start').val();
            var q = self.manager.store.get('q').val();
            var fq = self.manager.store.get('fq');
            var active_letter = false;
            var lastNameField = this.lastNameField;
            var passed_letter = '';

            //get rid of styling for active letter if it is not there
            for (var i = 0; i < fq.length; i++) {
                if (fq[i] != null && fq[i].value != null && fq[i].value.indexOf('lastName') != -1) {

                    var index = fq[i].value.indexOf(lastNameField);
                    index = index + lastNameField.length + 1;
                    passed_letter = fq[i].value.substr(index, 1);
                    active_letter = true;
                }
            }

            if (!active_letter) {
                $(this.target + ' .alphabet .active-letter').removeClass('active-letter');

                /*var all = $(self.target).find('li').filter(function() {
                 return $(this).text() == 'ALL';
                 });*/

            } else {

                $(this.target + ' .alphabet .active-letter').removeClass('active-letter');

                //get the letter li by an exact match
                var selected_letter = $(self.target).find('li').filter(function () {
                    return $(this).text() == passed_letter;
                });

                if (!selected_letter.hasClass('active-letter')) {
                    selected_letter.addClass('active-letter');
                }
            }
        }
    });

})(jQuery, History);