(function ($) {

/**
 * JS related to the tabs in the Panels tabs.
 */
Drupal.behaviors.panelsTabs = {
  attach: function (context) {
    var tabsID = Drupal.settings.websparkPanelsTabs.tabsID;

    for (var key in Drupal.settings.websparkPanelsTabs.tabsID) {
      $('#' + tabsID[key] +':not(.tabs-processed)', context)
        .addClass('tabs-processed')
        .tabs().tabgroups({
          target: '#' + tabsID[key]
        });
    }
  }
};

})(jQuery);
