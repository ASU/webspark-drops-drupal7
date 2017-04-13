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
                sort_tems: [],
                field_configs: null,
                default_sort: null,
                titlesort_field: null,
                tsort_placeholder: null
            }, attributes);
        },

        init: function () {
            var self = this;
            var sort_items = self.sort_items;
            var field_configs = self.field_configs;
            var default_sort  = 'lastNameSort asc';
            var titlesort_field = self.titlesort_field;
            var tsort_placeholder = self.tsort_placeholder;

            // if we are no longer using the ranksort placeholder, grab the sort value from
            // the saved state if possible
            if (titlesort_field != tsort_placeholder) {

                var man_sort = self.manager.store.get('sort').val();

                if (Array.isArray(man_sort)) {
                    man_sort = man_sort[0];
                }

                if (man_sort != null) {
                    default_sort  = man_sort.split(' ');
                } else {
                    default_sort  = self.default_sort.split(' ');
                }

                if (default_sort[0] != titlesort_field) {
                    field_configs.show_managers = false;
                }

            } else {
                default_sort  = self.default_sort.split(' ');
            }

            self.active_sort = default_sort[0];
            self.direction = default_sort[1];

            if (titlesort_field != tsort_placeholder) {
                var starting_sort = self.active_sort + ' ' + self.direction;
                self.manager.store.remove('sort');

                if (self.active_sort == titlesort_field) {
                    starting_sort += ',lastNameSort asc';
                    self.manager.store.addByValue('sort', starting_sort);
                }

            } else {
                self.manager.store.remove('sort');
                self.manager.store.addByValue('sort', 'lastNameSort asc');
            }


            for (var i = 0; i < sort_items.length; i++) {

                var name = sort_items[i].field_name;

                if (field_configs.show_managers || self.active_sort == titlesort_field) {

                    field_configs.show_managers = true;

                    if (name == titlesort_field) {
                        $(sort_items[i].field_id).addClass('dir-active-sort');
                    }
                } else if (name == self.active_sort) {
                    $(sort_items[i].field_id).append('<i class="dir-sort-icon fa fa-sort-' + self.direction + '"></i>');
                    $(sort_items[i].field_id).addClass('dir-active-sort');
                }

                $(sort_items[i].field_id).click('click', function(field_name) {

                    // return a click handler, with the name copied to field_name, because we are
                    // in a loop
                    return function() {

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
                        //note:  there should always be a prev_sort, since we always have a default

                        //SPECIAL CASE FOR THE TITLESORT FIELD
                        if (field_name == titlesort_field) {

                            ASUPeople.field_configs.show_managers = true;

                            // special case.  if we haven't changed placeholder yet,
                            // then return false after doing request, but don't change manager store sort
                            if (titlesort_field == tsort_placeholder) {
                                $(self.target).find('.dir-active-sort').removeClass('dir-active-sort');
                                $(this).addClass('dir-active-sort');
                                self.manager.store.remove('sort');
                                self.manager.store.addByValue('sort', 'lastNameSort asc');
                                self.manager.doRequest();
                                return false;
                            }
                        } else {
                            ASUPeople.field_configs.show_managers = false;
                        }

                        //special logic for ranksort, otherwise switch asc/desc
                        if (field_name == titlesort_field) {
                            $(self.target).find('.dir-active-sort').removeClass('dir-active-sort');
                            $(this).addClass('dir-active-sort');
                            self.direction = 'asc';

                        } else if (field_name == prev_sort) {

                            if (self.direction == 'asc') {
                                self.direction = 'desc';
                            } else {
                                self.direction = 'asc';
                            }
                        } else {
                            $(self.target).find('.dir-active-sort').removeClass('dir-active-sort');
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
                        $(self.target).find('.fa').remove();

                        if (field_name != titlesort_field) {
                            $(this).append('<i class="dir-sort-icon fa fa-sort-' + self.direction + '"></i>');
                        }
                    }
                } (name) );
            }
        },
        beforeRequest: function () {
            var self = this;
        }



    });

})(jQuery, window.History);