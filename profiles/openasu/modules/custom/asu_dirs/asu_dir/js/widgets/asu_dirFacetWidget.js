/**
 * Define the isFacet Widget.
 */
(function ($) {
    AjaxSolr.asu_dirFacetWidget = AjaxSolr.AbstractFacetWidget.extend({

        init: function () {
            this.initStore();
        },


        /**
         * @param {String} value The value.
         * @returns {Function} Sends a request to Solr if it successfully adds a
         *   filter query with the given value.
         */
        clickHandler: function (value) {
            var self = this, meth = this.multivalue ? 'add' : 'set';

            return function () {

                if (self[meth].call(self, value)) {
                    self.doRequest();
                }
                return false;
            }
        },

        selectClickHandler: function () {

            var self = this, meth = this.multivalue ? 'add' : 'set';

            return function () {
                var value = $(self.target).val();

                if (value != 0) {
                    if (self[meth].call(self, value)) {
                        self.doRequest();
                    }
                }

                return false;
            }
        },


        /**
         * @param {String} value The value.
         * @returns {Function} Sends a request to Solr if it successfully removes a
         *   filter query with the given value.
         */
        unclickHandler: function (value) {
            var self = this;
            return function () {

                if (value != 0) {
                    if (self.remove(value)) {
                        self.doRequest();
                    }
                }

                return false;
            }
        },


        afterRequest: function () {
            if (this.manager.response.facet_counts.facet_fields[this.field] === undefined) {
                $(this.target).html('no items found in current selection');
                return;
            }

            var maxCount = 0;
            var objectedItems = [];
            for (var facet in this.manager.response.facet_counts.facet_fields[this.field]) {
                var count = parseInt(this.manager.response.facet_counts.facet_fields[this.field][facet]);
                if (count > maxCount) {
                    maxCount = count;
                }

                if (facet != '' && facet != ' ') {
                    objectedItems.push({facet: facet, count: count});
                }
            }

            objectedItems.sort(function (a, b) {
                return a.facet < b.facet ? -1 : 1;
            });

            // For non-dropdown facets, clear out the results each time.
            if ($.inArray(this.field, this.manager.asu_dirFacetDisplay.dropdownFacets) < 0) {
                $(this.target).empty();
            } else { // Remove all but first option in select list.
                $(this.target).find("option:gt(0)").remove();
            }

            for (var i = 0, l = objectedItems.length; i < l; i++) {
                var facet = objectedItems[i].facet;
                var count = objectedItems[i].count;

                // If is affiliation type facet. Output <li> tags.
                if ($.inArray(this.field, this.manager.asu_dirFacetDisplay.affiliationFacets) >= 0) {
                    $(this.target).append(
                        $('<li><a href="#" class="facet_item">' + facet + '</a></li>')
                        //.addClass('tagcloud_size_' + parseInt(objectedItems[i].count / maxCount * 10))
                            .click(this.clickHandler(facet))
                            .append(' <span class="badge count">' + count + '</span>')
                    );

                }
                // If is dropdown type facet. Output <option> tags.
                else if ($.inArray(this.field, this.manager.asu_dirFacetDisplay.dropdownFacets) >= 0) {

                    $(this.target).append(
                        $('<option class="facet_item" value=""></option>')
                            .text(facet + ' (' + count + ')').attr('value', facet)
                        //.addClass('tagcloud_size_' + parseInt(objectedItems[i].count / maxCount * 10))
                    );


                    //only bind once
                    if (i == 0) {
                        $(this.target).unbind('change').change(this.selectClickHandler());
                    }

                }
                // Fall through to just outputting facet as links.
                else {

                    $(this.target).append(
                        $('<a href="#" class="facet_item"></a><br />')
                            .text(facet + '(' + count + ')')
                            //.addClass('tagcloud_size_' + parseInt(objectedItems[i].count / maxCount * 10))
                            .click(this.clickHandler(facet))
                    );

                }


            }

            // If we only have the default option in a dropdown facet, hide.
            $('.facet-widget').each(function () {
                // In toggle() TRUE == show, FALSE == hide
                // We use 2 as display threshold because of label option, and
                // if we've had a selection, we'll have 2. Also, if we only
                // have one actual option, no need to allow select.
                //$(this).toggle($(this).find('option').size() > 1);
                if ($(this).find('option').size() > 1) {
                    $(this).show();
                } else {
                    $(this).hide();
                }


            });


        }

    });
})(jQuery);

