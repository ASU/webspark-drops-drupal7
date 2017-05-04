(function ($) {

    $.widget("custom.tabgroups", {

        // Default options.
        options: {
            target: null
        },
        navPrev: null,
        navNext: null,
        groups: [],
        curgrp: 0,
        _create: function () {
            var self = this;
            var options = self.options;

            var nav = self.element.find(".ui-tabs-nav");
            var thetabs = nav.find("li");
            var contain = self.element.find(".item-list");

            var navPrev = $('<i class="fa fa-chevron-left fa-lg tabnav tabnav-left" aria-hidden="true"></i>').prependTo(nav);//.hide();
            var navNext = $('<i class="fa fa-chevron-right fa-lg tabnav tabnav-right" aria-hidden="true"></i>').appendTo(nav);//.hide();

            self.navPrev = navPrev;
            self.navNext = navNext;

            self.initializeGroups();
            self.activateGroup();

            // show the proper group whenever a tab is activated programmatically (
            self.element.on("tabsactivate", function (event, ui) {

                // find the index of the current active tab
                for (var i = 0; i < thetabs.length; i++) {
                    var ttab = thetabs.eq(i);

                    if (ttab.is(ui.newTab)) {

                        // find which group the tab is in
                        var counter = 0;

                        for (var j = 0; j < self.groups.length; j++) {
                            counter += self.groups[j].length;

                            if (i < counter) {

                                if (self.curgrp != j) {
                                    self.curgrp = j;
                                    self.activateGroup();
                                }

                                return;
                            }
                        }
                    }
                }
            });

            navNext.click(function (event) {
                self.curgrp += 1;
                self.activateGroup();
            });

            navPrev.click(function (event) {
                self.curgrp -= 1;
                self.activateGroup();
            });

        },
        initializeGroups: function () {
            var self = this;
            var containWidth = this.element.outerWidth(true);
            var options = self.options;

            self.element.addClass("ui-tabs-scrollable");
            // var scrollContainer = $('<div class="ui-tabs-scroll-container"></div>').prependTo(this.element);
            //self.header = $('<div class="ui-tabs-nav-scrollable ui-widget-header ui-corner-all"></div>').prependTo(scrollContainer);
            var nav = $(".ui-tabs-nav");
            var thetabs = nav.find('li');

            // array to hold groups of tabs
            // and an int to denote the current active group
            var groups = [];
            var activegroup = 0;
            var gwidth = 0;
            var curgrp = 0;

            for (var i = 0; i < thetabs.length; i++) {
                var ttab = thetabs.eq(i);
                var twidth = ttab.outerWidth(true);
                var link = ttab.find('a');

                var lwidth = link.outerWidth(true);

                // if first tab, create 1st group and add tab to it
                if (i == 0) {
                    groups[0] = [];
                    groups[0].push(ttab);
                    gwidth = twidth;

                    // else if the tab won't fit in current group, create new group and add to it
                } else if ((twidth + gwidth) > containWidth) {
                    curgrp++;
                    gwidth = 0;
                    groups[curgrp] = [];
                    groups[curgrp].push(ttab);
                    gwidth = twidth;

                    // else add it to active group, add it
                } else {
                    gwidth += twidth;
                    groups[curgrp].push(ttab);
                }

                // set the activegroup based on which has active state
                if (ttab.hasClass('ui-state-active')) {
                    activegroup = curgrp;
                }
            }

            self.groups = groups;
            self.curgrp = activegroup;
        },
        activateGroup: function () {
            var self = this;
            var curgrp = self.curgrp;
            var numgrps = self.groups.length;
            var nav = this.element.find(".ui-tabs-nav");
            var next = self.navNext;
            var prev = self.navPrev;

            for (var j = 0; j < numgrps; j++) {
                var cgroup = self.groups[j];

                for (var i = 0; i < cgroup.length; i++) {

                    if (curgrp == j) {
                        cgroup[i].show();
                    } else {
                        cgroup[i].hide();
                    }
                }
            }

            next.hide();
            prev.hide();

            if (numgrps > 1 && (curgrp == 0 || curgrp != (numgrps - 1))) {
                next.show();
            } else if (curgrp > 0) {
                prev.show();
            }
        }
    });
})(jQuery);