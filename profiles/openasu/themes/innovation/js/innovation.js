/**
 * Innovation theme JS
 */

(function ($, Drupal) {
  Drupal.behaviors.asu_standard = {
    attach: function (context, settings) { // Code to run on DOM ready, each AJAX request finish.

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
    if ($('#navbar-administration').length > 0) {
      navOffset = $('#navbar-bar').height() + $('#navbar-tray').height();
      if (typeof($('#navbar-tray').attr('data-offset-left')) !== typeof undefined) {
        navOffset = navOffset - $('#navbar-tray').height();
      }
    }
    // Admin Menu - Popular alternative
    else if ($('#admin-menu').length > 0) {
      navOffset = $('#admin-menu').height();
    }
    navOffsetUnits = navOffset + "px";
    var navOffsetTop = {"top": navOffsetUnits};
    if (($('#ASUNavMenu').offset().top - ($(window).scrollTop() + navOffset)) < 1 && $('.sticky-menu').length < 1) {
      $('#ASUNavMenu').addClass('sticky-menu').css(navOffsetTop);
    } else if (($('#ASUNavMenu').offset().top - ($(window).scrollTop() + navOffset)) >= 1) {
      $('#ASUNavMenu').removeClass('sticky-menu').removeAttr("style");
    }
  });

  // Fixes all anchor tags with hashes
  $('a').on('click', function (e) {
    var $this = $(this);
    var url = $this.attr('href');
    var cls = $this.attr('class');
    if (!$this.hasClass('accordion-toggle') && !$this.closest('ui-tabs').length == 0 && $this.closest('nav-tabs').length == 0) {
      if (url.slice(0, 1) == '#') {
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
    var hh = $('#header').height();
    var sp = $(document).scrollTop();
    var fx = $('#ASUNavMenu').height();
    if (sp < hh) {
      fx = fx * 2;
    }
    fx += 15;
    return fx;
  }

  // Hash smooth scrolling
  function smoothScroll(hash) {
    $('html,body').animate({scrollTop: $(hash).offset().top - offsetTop()}, 'slow');
    window.location.hash = hash;
  }

  // WEBSPARK-897 - Stop conflict between Token module (and its jQuery calls) and Bootstrap's button() function.
  $.fn.bootstrapBtn = $.fn.button.noConflict();

})(jQuery, Drupal);
