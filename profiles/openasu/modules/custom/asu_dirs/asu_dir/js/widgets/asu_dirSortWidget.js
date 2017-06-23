/**
 * Define the IS CurrentSearch Widget.
 */
(function ($, history) {

    AjaxSolr.asu_dirSortWidget = AjaxSolr.AbstractWidget.extend({
        start: 0,
        active_sort: null,
        direction: 'asc',

        /**
         * @param {Object} [attributes]
         * @param {Number} [attributes.start] This widget will by default set the
         *   offset parameter to 0 on each request.
         */
        constructor: function (attributes) {
            AjaxSolr.asu_dirTreeWidget.__super__.constructor.apply(this, arguments);
            AjaxSolr.extend(this, {
                sortItems: [],
                fieldConfigs: null,
                defaultSort: null,
                titleSortField: null,
                fieldId: null
            }, attributes);
        },

        init: function () {
            var self = this;
            var sort_items = self.sortItems;
            var fieldConfigs = self.fieldConfigs;
            var default_sort = self.defaultSort;
            var titlesort_field = self.titleSortField;
            //var tsort_placeholder = self.tsort_placeholder;
            var fieldId = self.fieldId;

            // set the default sort
            self.active_sort = default_sort;
            self.direction = 'asc';

            self.manager.store.remove('sort');

            if (self.active_sort != titlesort_field) {
                fieldConfigs.show_managers = false;
                self.manager.store.addByValue('sort', self.active_sort + ' ' + self.direction);
            } else {
                fieldConfigs.show_managers = true;
                self.manager.store.addByValue('sort', 'lastNameSort asc');
            }

            for (var i = 0; i < sort_items.length; i++) {

                var name = sort_items[i].field_name;

                if (fieldConfigs.show_managers || self.active_sort == titlesort_field) {

                    fieldConfigs.show_managers = true;

                    if (name == titlesort_field) {
                        $(sort_items[i].fieldId).addClass('dir-active-sort');
                    }
                } else if (name == self.active_sort) {
                    $(sort_items[i].fieldId).append('<i class="dir-sort-icon fa fa-sort-' + self.direction + '"></i>');
                    $(sort_items[i].fieldId).addClass('dir-active-sort');
                }

                $(sort_items[i].fieldId).click(function (field_name) {

                    // return a click handler, with the name copied to field_name, because we are
                    // in a loop
                    return function () {

                        //save prev sort before assigning new
                        var prev_sort = self.active_sort;

                        // if prevsort and new sort are title rank, return without doing anything.
                        // this is because we don't want to have reverse titlerank sort.
                        if (prev_sort == field_name && field_name == titlesort_field) {
                            return false;
                        }

                        self.active_sort = field_name;

                        //go back to first page if changing sort
                        self.manager.store.remove('start');

                        //if there was a previous sort, then do some logic to add active classes, etc.
                        //note:  there should always be a prev_sort, since we have a default

                        //SPECIAL CASE FOR THE TITLESORT FIELD
                        if (field_name == titlesort_field) {

                            ASUPeople[fieldId].fieldConfigs.show_managers = true;

                            // special case.  if we haven't changed placeholder yet,
                            // then return false after doing request, but don't change manager store sort
                            $(self.target).find('.dir-active-sort').removeClass('dir-active-sort');
                            $(this).addClass('dir-active-sort');
                            self.manager.store.remove('sort');
                            self.manager.store.addByValue('sort', 'lastNameSort asc');
                            self.manager.doRequest();
                            return false;

                        } else {
                            ASUPeople[fieldId].fieldConfigs.show_managers = false;
                        }

                        //special logic for ranksort, otherwise switch asc/desc
                        /*if (field_name == titleSortField) {

                         var target = $(self.target).find('.dir-active-sort');
                         target.removeClass('dir-active-sort');

                         $(this).addClass('dir-active-sort');
                         self.direction = 'asc';

                         } else*/

                        if (field_name == prev_sort) {

                            if (self.direction == 'asc') {
                                self.direction = 'desc';
                            } else {
                                self.direction = 'asc';
                            }
                        } else {
                            var t2 = $(self.target).find('.dir-active-sort');//.removeClass('dir-active-sort');
                            t2.removeClass('dir-active-sort');
                            $(this).addClass('dir-active-sort');
                            self.direction = 'asc';
                        }

                        var new_sort = self.active_sort + ' ' + self.direction;

                        if (self.active_sort == titlesort_field) {
                            new_sort += ',lastNameSort asc';
                        }

                        self.manager.store.remove('sort');
                        self.manager.store.addByValue('sort', new_sort);

                        self.manager.doRequest();

                        $(this).find('.fa').remove();

                        if (field_name != titlesort_field) {
                            $(this).append('<i class="dir-sort-icon fa fa-sort-' + self.direction + '"></i>');
                        }
                    }
                }(name));
            }
        }
    });

})(jQuery, window.History);