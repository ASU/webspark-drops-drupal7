(function($) {
  Drupal.behaviors.webspark_megamenu_hidden = {
    attach: function(context, settings) {
      let tb_block = $(".tb-megamenu-block.tb-block.tb-megamenu-block");
      if (tb_block.length) {
        tb_block.closest(".tb-megamenu-row.row-fluid").addClass("hide-extra-padding");
        tb_block.closest(".tb-megamenu-block.tb-block.tb-megamenu-block").addClass("adding-padding");
      }
    }
  };
  Drupal.behaviors.webspark_resize_menu = {
    attach: function(context, settings) {

      var ASUNavMenu = $("#ASUNavMenu");
      if (ASUNavMenu.length) {
        $(window).on("resize load", function() {
          if (window.innerWidth > 991) {
            var a = ASUNavMenu.find("li.tb-megamenu-item.level-1.mega");
            var x = $("#ASUNavMenu .container .navbar-collapse").width();
            var count = 0;
            var t = 0;

            jQuery.each(a, function(a, b) {
              t += jQuery(b).width();
              count++;
            });
            var data = calcFits(t, x, count, a);
            ASUNavMenu.find("li.tb-megamenu-item.level-1.mega:not(.btn)").children("a").css({
              "font-size": data.fs,
              "padding": data.pds,
              "min-height": "3rem"
            });
          }
        });
      }

      $.fn.textWidth = function(text, font) {
        if (!$.fn.textWidth.fakeEl) $.fn.textWidth.fakeEl = $("<span>").hide().appendTo(document.body);
        $.fn.textWidth.fakeEl.text(text || this.val() || this.text()).css("font", font || this.css("font"));
        return $.fn.textWidth.fakeEl.width();
      };

      /**
       * Recalculates padding, font size, etc.??
       * @param t
       * @param x
       * @param count
       * @param a
       * @returns {{pd: number, fs: number, pds: string}}
       */
      function calcFits(t, x, count, a) {
        var data = [];
        var poss = [];
        var br = true;
        var objs = [{
          fs: 14,
          pd: 8,
          pds: "0.5rem 0.75rem"
        }, {
          fs: 15,
          pd: 8,
          pds: "0.5rem 0.75rem"
        }, {
          fs: 16,
          pd: 8,
          pds: "0.5rem 0.75rem"
        }];
        var megamenu = document.getElementsByClassName("tb-megamenu-nav")[0];
        var carets = 0;
        if (megamenu) {
          carets = megamenu.getElementsByClassName("caret").length * 10;
        }
        for (var i = 0; i < objs.length; ++i) {
          var hold = 0;
          for (var c = 0; c < a.length; ++c) {
            hold += $.fn.textWidth($(a[c]).find("a").eq(0).text(), objs[i].fs + "px sans-serif");
          }
          hold = hold + (count * objs[i].pd * 2);
          poss.push(hold);
        }

        // WS2.0 - Overrode
        if ((poss[2] + carets) < x) {
          if (typeof(Storage) !== "undefined") {
            localStorage.setItem("asuMegaFont", "16px");
            localStorage.setItem("asuMegaPadding", "0.5rem 0.75rem");
          }
          return objs[2];
        } else if ((poss[1] + carets) < x) {
          if (typeof(Storage) !== "undefined") {
            localStorage.setItem("asuMegaFont", "15px");
            localStorage.setItem("asuMegaPadding", "0.5rem 0.75rem");
          }
          return objs[1];
        } else {
          if (typeof(Storage) !== "undefined") {
            localStorage.setItem("asuMegaFont", "14px");
            localStorage.setItem("asuMegaPadding", "0.5rem 0.75rem");
          }
          return objs[0];
        }

      }

    }
  };
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
                if ($("#" + some[j].id).height() > bigheight) {
                  bigheight = $("#" + some[j].id).height();
                }
              }
              rows.css("display", "");
            }
            for (var j = 0; j < some.length; j++) {
              $("#" + some[j].id).css("height", bigheight + "px");
            }
          }
        }
      } catch (e) {}
    }
  };
  Drupal.behaviors.webspark_megamenu = {
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
  Drupal.behaviors.webspark_megamenu_accessible = {
    attach: function(context, settings) {
      $(".navmenu a").unbind().each(function() {
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
                if ($("#main-wrapper").find(":focusable").length !== 0) {
                  $("#main-wrapper").find(":focusable")[0].focus();
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
