(function (callback) {
    if (typeof define === 'function' && define.amd) {
        define(['core/AbstractWidget'], callback);
    }
    else {
        callback();
    }
}(function () {

    (function ($) {

        /**
         * A pager widget for jQuery.
         *
         * <p>Heavily inspired by the Ruby on Rails will_paginate gem.</p>
         *
         * @expects this.target to be a list.
         * @class PagerWidget
         * @augments AjaxSolr.AbstractWidget
         * @todo Don't use the manager to send the request. Request only the results,
         * not the facets. Update only itself and the results widget.
         */
        AjaxSolr.asu_dirPagerWidget = AjaxSolr.PagerWidget.extend(
            /** @lends AjaxSolr.PagerWidget.prototype */
            {

                /**
                 * @param {Object} [attributes]
                 * @param {Number} [attributes.innerWindow] How many links are shown around
                 *   the current page. Defaults to 4.
                 * @param {Number} [attributes.outerWindow] How many links are around the
                 *   first and the last page. Defaults to 1.
                 * @param {String} [attributes.prevLabel] The previous page link label.
                 *   Defaults to "&laquo; Previous".
                 * @param {String} [attributes.nextLabel] The next page link label. Defaults
                 *   to "Next &raquo;".
                 * @param {String} [attributes.separator] Separator between pagination links.
                 *   Defaults to " ".
                 */
                constructor: function (attributes) {
                    AjaxSolr.asu_dirPagerWidget.__super__.constructor.apply(this, arguments);
                    AjaxSolr.extend(this, {
                        per_page: null,
                        field_configs: null
                    }, attributes);
                },

                /**
                 * @returns {Number} The number of results to display per page.
                 */
                perPage: function () {
                    return this.per_page;
                },

                /**
                 * @returns {Number} The Solr offset parameter's value.
                 */

                getOffset: function () {
                    return parseInt(this.manager.response.responseHeader && this.manager.response.responseHeader.params && this.manager.response.responseHeader.params.start || this.manager.store.get('start').val() || 0);
                },

                /**
                 * @returns {Number} The Solr offset parameter's value.
                 */
                /*
                 getOffset: function () {
                 return parseInt(this.manager.response.responseHeader && this.manager.response.responseHeader.params && this.manager.response.responseHeader.params.start || this.manager.store.get('start').val() || 0);
                 },*/


                /**
                 *  We override this function to add a scroll to the top of the page after a page click
                 *
                 * @param {Number} page A page number.
                 * @returns {Function} The click handler for the page link.
                 */
                clickHandler: function (page) {
                    var self = this;
                    return function () {
                        self.manager.store.get('start').val((page - 1) * self.per_page);
                        self.doRequest();
                        window.scrollTo(0, 0);
                        return false;
                    }
                },

                afterRequest: function () {
                    var perPage = this.perPage();
                    var offset = this.getOffset();
                    var total = parseInt(this.manager.response.response.numFound);
                    offset = offset - offset % perPage;

                    this.currentPage = Math.ceil((offset + 1) / perPage);
                    this.totalPages = Math.ceil(total / perPage);

                    if (this.totalPages === 1) {
                        $(this.target).css('visibility', 'hidden');
                    } else {
                        $(this.target).css('visibility', 'inherit');
                    }

                    $(this.target).empty();

                    this.renderLinks(this.windowedLinks());
                    this.renderHeader(perPage, offset, total);
                },

                /****
                 * Need to switch between the manager query, and other filters/facets
                 *
                 */
                beforeRequest: function () {
                    var self = this;
                    var field_configs = this.field_configs;
                    var override = this.manager.checkOverrides();
                    var per_page = this.per_page;

                    //if we are showing managers, we need to grab all results and reorder array
                    if (field_configs.show_managers && !override) {
                        self.manager.store.remove('rows');
                        self.manager.store.addByValue('rows', 200000);

                        //otherwise, set the number of row to per_page variable
                    } else {
                        self.manager.store.remove('rows');
                        self.manager.store.addByValue('rows', per_page);
                    }
                }
            });

    })(jQuery);

}));
