/**
 * Innovation theme JS
 */

(function ($, Drupal) {
  Drupal.behaviors.asu_standard = {
    attach: function (context, settings) {

      $("#asu_mobile_hdr").wrapInner("<div class='asu_mobile_hdr_wrapper'></div>");
      $("#asu_mobile_menu").wrapInner("<div class='asu_mobile_menu_wrapper'></div>");

      // Add header to Ctools Modal menu to improve UI
      $(".panels-add-content-modal .panels-categories-box").after("<h2 class=\"widget-list\">More Content Panes</h2>");

    }
  };
  // Add support for sticky menu
  var navOffset = 0;
  $(window).scroll(function () {
    if ($('#navbar-administration'.length > 0)) {
      navOffset = $('#navbar-bar').height() + $('#navbar-tray').height();
      if (typeof($('#navbar-tray').attr('data-offset-left')) !== typeof undefined) {
        navOffset = navOffset - $('#navbar-tray').height();
      }
    }
    navOffsetUnits = navOffset + "px";
    var navStyles = {"position": "sticky", "top": navOffsetUnits, "z-index": "1000", "width": "100%", "visibility": "visible"};
    $('#ASUNavMenu').addClass('sticky-menu').css(navStyles);
  });

  // Used to determine if RFI form is on the page.
  // Go to div if it is go to URL if it isn't #block-asu-rfi-asu-rfi-form-block
  $('#take-me-to-rfi').on('click', function (e) {
    e.preventDefault();
    if ($('#asu-rfi-form-data').length == 0) {
      location.href = 'https://students.asu.edu/typeofstudent';
    } else {
      location.href = '#asu-rfi-form-data';
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

  // WEBSPARK-897 - Stop conflict between Token module (and its jQuery calls) and Bootstrap's button() function
  // This was keeping Token dialog box's X button from rendering.
  $.fn.bootstrapBtn = $.fn.button.noConflict();

})(jQuery, Drupal);
