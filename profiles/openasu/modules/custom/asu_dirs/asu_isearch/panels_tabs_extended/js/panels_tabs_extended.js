(function ($) {

    /**
     * JS related to the tabs in the Panels tabs.
     */
    Drupal.behaviors.panelsTabsExtended = {
        attach: function (context) {
            var tabsID = Drupal.settings.panelsTabsExtended.tabsID;

            for (var key in Drupal.settings.panelsTabsExtended.tabsID) {
                $('#' + tabsID[key] + ':not(.tabs-processed)', context)
                    .addClass('tabs-processed')
                    .tabs();
            }
        }
    };

})(jQuery);
