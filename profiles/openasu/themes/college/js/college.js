/**
 * College theme JS
 */

(function ($, Drupal) {
  // noinspection JSUnusedLocalSymbols
  Drupal.behaviors.asu_standard = {
    // Code to run on DOM ready, each AJAX request finish.
    attach: function (context, settings) {// jshint ignore:line
      $("#asu_mobile_hdr", context).wrapInner("<div class='asu_mobile_hdr_wrapper'></div>");
      $("#asu_mobile_menu", context).wrapInner("<div class='asu_mobile_menu_wrapper'></div>");
      // Add header to Ctools Modal menu to improve UI
      $(".panels-add-content-modal .panels-categories-box", context).after("<h2 class=\"widget-list\">More Content Panes</h2>");

      // College theme event listener
      $(window).resize(function () {
        adjustMobileHeight(context, settings);
      });
      $(window).load(function () {
        adjustMobileHeight(context, settings);
      });
      if ($("#navbar-bar").length) {
        $("#navbar-bar > .navbar-tab > a.navbar-tab," +
          "#navbar-tray .navbar-icon.navbar-icon-toggle-vertical," +
          "#navbar-tray .navbar-icon.navbar-icon-toggle-horizontal", context).on({
          mouseenter: function () {
            adjustMobileHeight(context, settings);
          },
          mouseout: function () {
            adjustMobileHeight(context, settings);
          }
        });
      }
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

  // College theme - header spacing fixes
  // @return int
  function returnHeight(elementStyle) {
    let menuHeight = "";
    for (prop in elementStyle) {
      if (prop.match(/^paddingTop/)) {
        menuHeight = elementStyle[prop].match(/\d+/)[0];
      }
    }
    return Number(menuHeight);
  }
  function adjustMobileHeight(context, settings) {
    // Checks if it is mobile view
    if ($(window).width() < 992) {
      // var druTopMenuProcess = settings.asu_standards.access;
      var druInitHt = settings.asu_standards.barbar;
      var totHeight = druInitHt;
      var druAdmMenuHt = 0;
      var asuMobMenu = $(".block-asu-brand div#headerContainer > header[class^=css-] > .navbar-component", context);
      var asuMobMenuHeight = asuMobMenu.outerHeight();
      if (!isNaN(asuMobMenuHeight)) {
        if (druInitHt === 39) { // Navbar (varied heights)
          const bodyTag = document.getElementsByTagName("body")[0];
          druAdmMenuHt = returnHeight(bodyTag.style);
          totHeight = Number(asuMobMenuHeight) - 4; // Remove 4px to account for #header height;
        } else if (druInitHt === 30) { // Admin menu
          druAdmMenuHt = druInitHt;
          totHeight = Number(asuMobMenuHeight) - 4; // Remove 4px to account for #header height;
        } else {
          // do nothing
          totHeight = druAdmMenuHt + Number(asuMobMenuHeight) - 4; // Remove 4px to account for #header height;
        }
      }
      // Body content - Padding top (combined heights)
      $("#page-wrapper #main-wrapper", context).css("paddingTop", totHeight + "px");
      // Mobile header - Top margin (only ASU admin menu height)
      if (druAdmMenuHt !== 0) {
        asuMobMenu.css({"margin-top": druAdmMenuHt});
      }
    } else {
      // console.log("No admin menu or navbar - SKIPPING");
      $("#page-wrapper #main-wrapper", context).css("paddingTop", 0);
    }
  }
})(jQuery, Drupal); // jshint ignore:line
