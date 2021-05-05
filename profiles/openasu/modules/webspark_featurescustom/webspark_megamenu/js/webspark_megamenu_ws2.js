(function($) {
  /**
   * Move padding from row-fluid to .tb-megamenu-block??
   * @type {{attach: Drupal.behaviors.webspark_megamenu_hidden.attach}}
   */
  Drupal.behaviors.webspark_megamenu_hidden = { // jshint ignore:line
    attach: function(context, settings) { // jshint ignore:line
      var tb_block = $(".tb-megamenu-block.tb-block.tb-megamenu-block", context);
      if (tb_block.length) {
        tb_block.closest(".tb-megamenu-row.row-fluid").addClass("hide-extra-padding");
        tb_block.closest(".tb-megamenu-block.tb-block.tb-megamenu-block").addClass("adding-padding");
      }
    }
  };

  /**
   * Resize the main menu's font size and padding.
   * @type {{attach: Drupal.behaviors.webspark_resize_menu.attach}}
   */
  Drupal.behaviors.webspark_resize_menu = { // jshint ignore:line
    attach: function(context, settings) { // jshint ignore:line

      /**
       * Recalculates padding, font size, etc.??
       * @param t - (int) sum of pixel widths of all items in the navbar
       * @param x - (int) pixel width of $("#ASUNavMenu .container .navbar-collapse")
       * @param count - (int) number of elements in a (jQuery collection below)
       * @param a - (obj) jQuery collection of menu items
       * @returns {{mrg: number, fs: number, pds: string, subfs: string}}
       */
      function calcFits(t, x, count, a) {
        var possTextWidths = [];
        var objs = [{
          fs: 14,
          mrg: 8,
          pds: "0.5rem 0.5rem",
          subfs: "1.25rem"
        }, {
          fs: 15,
          mrg: 8,
          pds: "0.5rem 0.5rem",
          subfs: "1.25rem"
        }, {
          fs: 16,
          mrg: 8,
          pds: "0.5rem 0.75rem",
          subfs: "1.5rem"
        }];

        var megamenu = document.getElementsByClassName("tb-megamenu-nav")[0].children;
        var chevron = document.getElementsByClassName("fa fa-chevron-down");
        var chevronPadd = 8; // Manually set padding width
        var chevronTotal = 0;
        if (chevron.length > 0) {
          var chevronWidth = chevron[0].clientWidth;
          // Calculate Chevrons net width
          var chevronPadTotal = chevronWidth + chevronPadd; //DEFAULT 12px width + 0.5rem padding
          if (megamenu.length > 0) {
            chevronTotal = chevron.length * chevronPadTotal;
          }
        }

        // Sum Top-level menu item text lengths (in px), based on the 3 different font sizes
        for (var i = 0; i < objs.length; ++i) {
          var hold = 0;
          for (var c = 0; c < a.length; ++c) {
            hold += $.fn.textWidth($(a[c]).find("a").eq(0).text(), objs[i].fs + "px sans-serif");
          }
          hold += (count * objs[i].mrg);
          hold += (count * (chevronPadd * 2));
          possTextWidths.push(hold);
        }

        // Take the ASU WS2.0 logo width into account
        var ws2_logo = document.getElementsByClassName("ws2-global-header-logo")[0].offsetWidth;
        // Calculate Total menu width - Logo width - menu elem padding
        var ws2_menu_width = Number(x) - Number(ws2_logo);

        if ((possTextWidths[2] + chevronTotal) < ws2_menu_width) {
          if (typeof(Storage) !== "undefined") {
            localStorage.setItem("asuMegaFont", "16px");
            localStorage.setItem("asuMegaPadding", "0 0.5rem");
            localStorage.setItem("asuMegaSubTFont", "1.5rem");
          }
          return objs[2];
        } else if ((possTextWidths[1] + chevronTotal) < ws2_menu_width) {
          if (typeof(Storage) !== "undefined") {
            localStorage.setItem("asuMegaFont", "15px");
            localStorage.setItem("asuMegaPadding", "0 0.5rem");
            localStorage.setItem("asuMegaSubTFont", "1.25rem");
          }
          return objs[1];
        } else {
          if (typeof(Storage) !== "undefined") {
            localStorage.setItem("asuMegaFont", "14px");
            localStorage.setItem("asuMegaPadding", "0 0.5rem");
            localStorage.setItem("asuMegaSubTFont", "1.25rem");
          }
          return objs[0];
        }
      }

      /**
       * Calculate the total text width
       * @param text
       * @param font
       * @returns {*}
       */
      $.fn.textWidth = function(text, font) {
        if (!$.fn.textWidth.fakeEl) {
          $.fn.textWidth.fakeEl = $("<span>").hide().appendTo(document.body);
        }
        $.fn.textWidth.fakeEl.text(text || this.val() || this.text()).css("font", font || this.css("font"));
        return $.fn.textWidth.fakeEl.width();
      };

      // Calculates the proper font size and padding to top-level links and buttons.
      var ASUNavMenu = $("#ASUNavMenu", context);
      if (ASUNavMenu.length) {
        $(window).on("resize load", function() {
          if (window.innerWidth > 991) {
            var a = ASUNavMenu.find("li.tb-megamenu-item.level-1.mega");
            var x = $("#ASUNavMenu .container .navbar-collapse").width();
            var count = 0;
            var t = 0;
            // Get element widths
            jQuery.each(a, function(a, b) {
              t += jQuery(b).width();
              count++;
            });

            // Apply styling on background if necessary
            var check = $("#ASUNavMenu li.tb-megamenu-item.level-1.mega.mega-align-justify.dropdown")
              .children(".tb-megamenu-submenu");
            if (check.length > 0) {
              for (var cnt = 0; cnt < check.length; cnt++) {
                var tbShell = document.getElementById("tb-megamenu-ws2-shell").offsetWidth; // 1140px max-width
                var LHSpacing = (window.innerWidth - tbShell) / 2;
                var subMenu = check[cnt].firstElementChild;
                // subMenu.style.backgroundColor = "blue";
                var subMenuWidth = subMenu.offsetWidth;
                var RHSpacing = window.innerWidth - LHSpacing - subMenuWidth;
                /*
                1 - left margin = innerWidth - tbShell
                2 - RH margin = innerWidth - left Margin - submenuwidth
                 */
                // check[cnt].style.backgroundColor = "aqua";
                check[cnt].style.marginLeft = ((-1 * LHSpacing - 6) + "px"); // Mystery 6px????
                check[cnt].style.paddingLeft = LHSpacing + "px";
                check[cnt].style.paddingRight = RHSpacing + "px";
              }
            }

            var data = calcFits(t, x, count, a);
            // Restyle top-level non-button menu items
            ASUNavMenu.find("li.tb-megamenu-item.level-1.mega:not(.btn)").children("a").css({
              "font-size" : data.fs,
              "padding" : data.pds,
              "min-height" : "3rem"
            });
            // Resize top-level buttons, submenu links
            ASUNavMenu.find("li.tb-megamenu-item.mega, li.tb-megamenu-item.level-1.mega.btn").children("a:not(.mega-group-title)").css({
              "font-size" : data.fs,
            });
            ASUNavMenu.find("li.tb-megamenu-item.mega").children("a.mega-group-title").css({
              "font-size" : data.subfs,
            });
          }
        });
      }
    }
  };

  // noinspection JSUnusedLocalSymbols,JSHint
  /**
   * purpose - unknown. Perhaps to make all columns in a menu row the same height as the tallest?
   * @type {{attach: Drupal.behaviors.webspark_megamenu_driveify.attach}}
   */
  Drupal.behaviors.webspark_megamenu_driveify = {
    attach: function(context, settings) {
      var rows = $(".tb-megamenu-row");
      try {
        for (var i = 0; i < rows.length; i++) {
          if (rows[i].children.length > 1) {
            var some = rows[i].children;
            var bigheight = 0;
            for (var j = 0; j < some.length; j++) {
              rows.css("display", "block");
              if (some[j].className.indexOf("tb-megamenu-column") >= 0) {
                var elemHeight = $("#" + some[j].id).height();
                if (elemHeight > bigheight) {
                  bigheight = elemHeight;
                }
              }
              rows.css("display", "");
            }
            for (var k = 0; k < some.length; k++) {
              $("#" + some[k].id).css("height", bigheight + "px");
            }
          }
        }
      } catch (e) {}
    }
  };
  /**
   * Swaps out Home link with FontAwesome home icon
   */
  Drupal.behaviors.webspark_megamenu = { // jshint ignore:line
    attach: function() {
      var firstNavItem = $(".tb-megamenu-nav > li:first-child > a");
      try {
        if (firstNavItem.text().trim() === "Home") {
          var a = "<span class=\"fa fa-home icon-white\"><span class=\"sr-only\">Home</span></span>";
          $(".tb-megamenu-nav>li:first-child>a").empty().append(a);
        }
      } catch (e) {}
    }
  };

  /**
   * Added Accessibility capability
   * @type {{attach: Drupal.behaviors.webspark_megamenu_accessible.attach}}
   */
  Drupal.behaviors.webspark_megamenu_accessible = { // jshint ignore:line
    attach: function(context, settings) { // jshint ignore:line
      $(".navmenu a", context).unbind().each(function() {
        $(this).unbind().on("keydown", function(e) {
          // On keydown tab (no shift)
          if (e.keyCode === 9 && !e.shiftKey) {
            // Clear arrow focus classes
            $(".last-tb-focus").removeClass("last-tb-focus");
            // Anchor tag's parent is the top level
            if ($(this).parent().hasClass("tb-megamenu-item level-1")) {
              // Anchor tag's parent is the last element of top level elements
              if ($(this).parent().is(":last-child")) {
                e.preventDefault();
                var mainWrapper = $("#main-wrapper").find(":focusable");
                if (mainWrapper.length !== 0) {
                  mainWrapper[0].focus();
                } else {
                  $("#page-footer").find(":focusable")[0].focus();
                }
                // Anchor tag's parent is not the last element of top level elements
              } else {
                e.preventDefault();
                $(this).parent().addClass("open");
                $(this).parent().next().children("a").focus();
              }
            }
          }
          // On keydown shift+tab
          if (e.shiftKey && e.keyCode === 9) {
            // Anchor tag's parent is the top level
            if ($(this).parent().hasClass("tb-megamenu-item level-1")) {
              // Anchor tag's parent is the first element of top level elements
              if ($(this).parent().is(":first-child")) {
                $(this).parent().removeClass("open");
                $("#asu_universal_nav").find("li:last-child").children("a").focus();
                // Anchor tag's parent is not the first element of top level elements
              } else {
                e.preventDefault();
                $(this).parent().addClass("open");
                $(this).parent().removeClass("open").prev().addClass("open").children("a").focus();
              }
            }
          }
          // On keydown right arrow
          if (e.keyCode === 39) {
            e.preventDefault();
            // If this is the last column
            if ($(this).parents(".tb-megamenu-subnav.level-1").parents(".tb-megamenu-column").is(":last-child")) {
              // If the parent is the last child
              if ($(this).parents(".tb-megamenu-item.level-2").length && $(this).parents(".tb-megamenu-item.level-2").is(":last-child")) {
                // If the parent is the last child of child menu
                if ($(this).parent(".level-3").length && $(this).parent(".level-3").is(":last-child")) {
                  $(this).addClass("last-tb-focus").closest(".tb-megamenu-item.level-1").find(".tb-megamenu-block .menu-link-button").focus();
                  // Prevent tabbing
                  return;
                  // Else if there is no level 3 then return (there are no level 3 children)
                } else if ($(this).parent(".level-3").length === 0 && $(this).parents(".tb-megamenu-item.level-2").find(".level-3").length === 0) {
                  return;
                }
              }
            }
            if ($(this).parent().hasClass("tb-megamenu-item level-1")) {
              $(this).parent().addClass("open");
              $(this).parent().next().children("a").focus();
              return;
            }
            $(this).emulateTab(1);
          }
          // On keydown down arrow
          if (e.keyCode === 40) {
            e.preventDefault();
            // If this is the last column
            if ($(this).parents(".tb-megamenu-subnav.level-1").parents(".tb-megamenu-column").is(":last-child")) {
              // If the parent is the last child
              if ($(this).parents(".tb-megamenu-item.level-2").length && $(this).parents(".tb-megamenu-item.level-2").is(":last-child")) {
                // If the parent is the last child of child menu
                if ($(this).parent(".level-3").length && $(this).parent(".level-3").is(":last-child")) {
                  $(this).addClass("last-tb-focus").closest(".tb-megamenu-item.level-1").find(".tb-megamenu-block .menu-link-button").focus();
                  // Prevent tabbing
                  return;
                  // Else if there is no level 3 then return (there are no level 3 children)
                } else if ($(this).parent(".level-3").length === 0 && $(this).parents(".tb-megamenu-item.level-2").find(".level-3").length === 0) {
                  return;
                }
              }
            }
            $(this).emulateTab(1);
          }
          // On keydown left arrow
          if (e.keyCode === 37) {
            // Anchor tag's parent is the top level
            if ($(this).parent().hasClass("tb-megamenu-item level-1")) {
              // Anchor tag's parent is the first element of top level elements
              if ($(this).parent().is(":first-child")) {
                $(this).parent().removeClass("open");
                $("#asu_universal_nav").find("li:last-child").children("a").focus();
                // Anchor tag's parent is not the first element of top level elements
              } else {
                e.preventDefault();
                $(this).parent().addClass("open");
                $(this).parent().removeClass("open").prev().addClass("open").children("a").focus();
              }
            } else {
              e.preventDefault();
              $(this).emulateTab(-1);
            }
          }
          // On keydown up arrow
          if (e.keyCode === 38) {
            e.preventDefault();
            $(this).emulateTab(-1);
          }
        });
      });
    }
  };
}(jQuery));
