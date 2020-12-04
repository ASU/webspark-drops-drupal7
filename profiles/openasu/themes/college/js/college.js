/**
 * College theme JS
 */

(function ($, Drupal) {
  // noinspection JSUnusedLocalSymbols
  Drupal.behaviors.asu_standard = {
    // Code to run on DOM ready, each AJAX request finish.
    attach: function (context, settings) {// jshint ignore:line
      $("#asu_mobile_hdr").wrapInner("<div class='asu_mobile_hdr_wrapper'></div>");
      $("#asu_mobile_menu").wrapInner("<div class='asu_mobile_menu_wrapper'></div>");
      // Add header to Ctools Modal menu to improve UI
      $(".panels-add-content-modal .panels-categories-box").after("<h2 class=\"widget-list\">More Content Panes</h2>");
    }
  };

  // Local functions that are globally available via Drupal.behaviors.asu_standard.
  // Add support for sticky menu
  var navOffset = 0;
  $(window).scroll(function () {
    // Mobile Friendly Navbar - Drupal default
    var asuNavMenu = $("#ASUNavMenu");
    if ($("#navbar-administration").length > 0) {
      var navTray = $("#navbar-tray");
      navOffset = $("#navbar-bar").height() + navTray.height();
      if (typeof(navTray.attr("data-offset-left")) !== typeof undefined) {
        navOffset = navOffset - navTray.height();
      }
    }
    // Admin Menu - Popular alternative
    else if ($("#admin-menu").length > 0) {
      navOffset = $("#admin-menu").height();
    }
    var navOffsetUnits = navOffset + "px";
    var navOffsetTop = {"top": navOffsetUnits};
    if ((navOffset + 1 - $(window).scrollTop()) >= 1) {
      // console.log("no sticky");
      asuNavMenu.removeClass("sticky-menu").removeAttr("style");
    } else if ((asuNavMenu.offset().top - ($(window).scrollTop() + navOffset)) < 1 && $(".sticky-menu").length < 1) {
      // console.log("sticky");
      asuNavMenu.addClass("sticky-menu").css(navOffsetTop);
    }
  });

  // Fixes all anchor tags with hashes
  $("a").on("click", function (e) {
    var $this = $(this);
    var url = $this.attr("href");
    // var cls = $this.attr("class");
    if (!$this.hasClass("accordion-toggle") && !$this.closest("ui-tabs").length === 0 && $this.closest("nav-tabs").length === 0) { // jshint ignore:line
      if (url.slice(0, 1) === "#") {
        e.preventDefault();
        smoothScroll(url);
      }
    }
  });

  // Fixes onload scroll to the hash that originates from page URL
  if (location.hash) {
    smoothScroll(location.hash);
  }

  // Function to calculate current offset with respect to scroll position
  function offsetTop() {
    var hh = $("#header").height();
    var sp = $(document).scrollTop();
    var fx = $("#ASUNavMenu").height();
    if (sp < hh) {
      fx = fx * 2;
    }
    fx += 15;
    return fx;
  }

  // Hash smooth scrolling
  function smoothScroll(hash) { // jshint ignore:line
    $("html,body").animate({scrollTop: $(hash).offset().top - offsetTop()}, "slow");
    window.location.hash = hash;
  }

  // WEBSPARK-897 - Stop conflict between Token module (and its jQuery calls) and Bootstrap's button() function.
  // $.fn.bootstrapBtn = $.fn.button.noConflict();
  // Removed for College theme

})(jQuery, Drupal); // jshint ignore:line
