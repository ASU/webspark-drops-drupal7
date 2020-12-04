/*
 * College theme JS
 */

(function ($, Drupal) {
  Drupal.behaviors.innovationAdmin = {
    attach: function (context, settings) {
      /* Adds color coding to watchdog cells */
      $(".view-better-watchdog-ui-view table td.views-field-severity").each(function () {
        var test = $(this).text().trim();
        if (test === "emergency") {
          $(this).css({"background-color" : "#f79bff"});
        }
        if (test === "alert") {
          $(this).css({"background-color" : "#ff9b9b"});
        }
        if (test === "critical") {
          $(this).css({"background-color" : "#ff9b9b"});
        }
        if (test === "error") {
          $(this).css({"background-color" : "#ffab9b"});
        }
        if (test === "warning") {
          $(this).css({"background-color" : "#ffd39b"});
        }
        if (test === "notice") {
          $(this).css({"background-color" : "#e9ff9b"});
        }
        if (test === "info") {
          $(this).css({"background-color" : "#b3ff9b"});
        }
        if (test === "debug") {
          $(this).css({"background-color" : "#9bffeb"});
        }
      });
    }
  };
})(jQuery, Drupal);
