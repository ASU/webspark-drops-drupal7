Drupal.TBMegaMenu = Drupal.TBMegaMenu || {};

(function ($) {
  Drupal.TBMegaMenu.oldWindowWidth = 0;
  Drupal.TBMegaMenu.displayedMenuMobile = false;
  Drupal.TBMegaMenu.supportedScreens = [980];
  Drupal.TBMegaMenu.menuResponsive = function () {
    var windowWidth = window.innerWidth ? window.innerWidth : $(window).width();
    var navCollapse = $('.tb-megamenu').children('.nav-collapse');
    if (windowWidth < Drupal.TBMegaMenu.supportedScreens[0]) {
      navCollapse.addClass('collapse');
      if (Drupal.TBMegaMenu.displayedMenuMobile) {
        navCollapse.css({height: 'auto', overflow: 'visible'});
      } else {
        navCollapse.css({height: 0, overflow: 'hidden'});
      }
    } else {
      // If width of window is greater than 980 (supported screen).
      navCollapse.removeClass('collapse');
      if (navCollapse.height() <= 0) {
        navCollapse.css({height: 'auto', overflow: 'visible'});
      }
    }
  };
  
  Drupal.behaviors.tbMegaMenuAction = {
    attach: function(context) {
      var ariaCheck = function() {
        $("li.tb-megamenu-item").each(function () {
          if ($(this).is('.mega-group')) {
            // Mega menu item has mega class (it's a true mega menu)
            if(!$(this).parents().is('.open')) {
              // Mega menu item has mega class and its ancestor is closed, so apply appropriate ARIA attributes
              $(this).children().attr('aria-expanded', 'false');
            } else if ($(this).parents().is('.open')) {
              // Mega menu item has mega class and its ancestor is open, so apply appropriate ARIA attributes
              $(this).children().attr('aria-expanded', 'true');
            }
          } else if ($(this).is('.dropdown') || $(this).is('.dropdown-submenu')) {
            // Mega menu item has dropdown (it's a flyout menu)
            if (!$(this).is('.open')) {
              // Mega menu item has dropdown class and is closed, so apply appropriate ARIA attributes
              $(this).children().attr('aria-expanded', 'false');
            } else if ($(this).is('.open')) {
              // Mega menu item has dropdown class and is open, so apply appropriate ARIA attributes
              $(this).children().attr('aria-expanded', 'true');
            }
          } else {
            // Mega menu item is neither a mega or dropdown class, so remove ARIA attributes (it doesn't have children)
            $(this).children().removeAttr('aria-expanded');
          }
        });
      };
      var showMenu = function ($menuItem, mm_timeout) {
        console.log("showMenu");
        if ($menuItem.hasClass ('mega')) {
          $menuItem.addClass ('animating');
          clearTimeout ($menuItem.data('animatingTimeout'));
          $menuItem.data('animatingTimeout', setTimeout(function(){$menuItem.removeClass ('animating')}, mm_timeout));
          clearTimeout ($menuItem.data('hoverTimeout'));
          $menuItem.data('hoverTimeout', setTimeout(function(){
            $menuItem.addClass ('open');
            ariaCheck();
          }, 100));
        } else {
          clearTimeout ($menuItem.data('hoverTimeout'));
          $menuItem.data('hoverTimeout',
              setTimeout(function() {
                $menuItem.addClass ('open');
                ariaCheck();
              }, 100));
        }
      };
      var hideMenu = function ($menuItem, mm_timeout) {
        console.log("hideMenu");
        $menuItem.children('.dropdown-toggle').attr('aria-expanded', 'false');
        if ($menuItem.hasClass ('mega')) {
          $menuItem.addClass ('animating');
          clearTimeout ($menuItem.data('animatingTimeout'));
          $menuItem.data('animatingTimeout',
              setTimeout(function(){$menuItem.removeClass ('animating')}, mm_timeout));
          clearTimeout ($menuItem.data('hoverTimeout'));
          $menuItem.data('hoverTimeout', setTimeout(function() {
            $menuItem.removeClass ('open');
            ariaCheck();
          }, 100));
        } else {
          clearTimeout ($menuItem.data('hoverTimeout'));
          $menuItem.data('hoverTimeout',
              setTimeout(function() {
                $menuItem.removeClass ('open');
                ariaCheck();
              }, 100));
        }
      };
      $('.tb-megamenu-button', context).once('menuIstance', function () {
        var This = this;
        $(This).click(function() {
          if(parseInt($(this).parent().children('.nav-collapse').height())) {
            $(this).parent().children('.nav-collapse').css({height: 0, overflow: 'hidden'});
            Drupal.TBMegaMenu.displayedMenuMobile = false;
          }
          else {
            $(this).parent().children('.nav-collapse').css({height: 'auto', overflow: 'visible'});
            Drupal.TBMegaMenu.displayedMenuMobile = true;
          }
        });
      });

      var isTouch = 'ontouchstart' in window && !(/hp-tablet/gi).test(navigator.appVersion);
      if(!isTouch){
        $(document).ready(function($){
          var mm_duration = 0;
          $('.tb-megamenu', context).each (function(){
            if ($(this).data('duration')) {
              mm_duration = $(this).data('duration');
            }
          });

          var mm_timeout = mm_duration ? 100 + mm_duration : 500;
          $('.nav > li, li.mega', context).bind('mouseenter', function(event) {
            showMenu($(this), mm_timeout);
          });
          $('.nav > li > .dropdown-toggle, li.mega > .dropdown-toggle', context).bind('focus', function(event) {
            var $this = $(this);
            var $subMenu = $this.closest('li');
            console.log("showMenu call");
            showMenu($subMenu, mm_timeout);
            // If the focus moves outside of the subMenu, close it.
            $(document).bind('focusin', function(event) {
              if ($subMenu.has(event.target).length) {
                return;
              }
              $(document).unbind(event);
              console.log("hideMenu call");
              hideMenu($subMenu, mm_timeout);
            });
          });
          $('.nav > li, li.mega', context).bind('mouseleave', function(event) {
            hideMenu($(this), mm_timeout);
          });
        });

        /**
         * Allow tabbing by appending the open class.
         * Works in tandem with CSS changes that utilize opacity rather than display none
         */
        // If the selected anchor is not in the TB Megamenu, remove all "open" class occurrences
        $('a').focus(function(event){
          if(!$(this).parent().hasClass('tb-megamenu-item')) {
            $('.tb-megamenu .open').removeClass('open');
            $('.tb-megamenu-item.dropdown-submenu.open').removeClass('open');
            ariaCheck();
          }
        });

        $('.nav > li > a, li.mega > a').focus(function(event) {

          // Remove all occurrences of "open" from other menu trees
          var siblings = $(this).parents('.tb-megamenu-item').siblings();
          // var siblings = $(this).closest('.tb-megamenu-item.level-1').siblings();
          $.each(siblings, function(i, v){
            var cousins = $(v).find('.open');
            $.each(cousins, function(index, value){
              $(value).removeClass('open');
              ariaCheck($(this));
            });
            $(v).removeClass('open');
            ariaCheck();
          });
          // Open the submenu if the selected item has one
          if($(this).next(".tb-megamenu-submenu").length > 0){
            if(!$(this).parent().hasClass("open")){
              $(this).parent().addClass("open");
            }
          }
          // If the anchor's top-level parent is not open, open it
          if(!$(this).closest('.tb-megamenu-item.dropdown').hasClass('open') && $(this).closest('.tb-megamenu-item.dropdown').find('.tb-megamenu-submenu').length > 0){
            $(this).closest('.tb-megamenu-item.dropdown').addClass('open');
            ariaCheck();
          }
          // If anchor's parent submenus are not open, open them
          var parents = $(this).parents('.tb-megamenu-item.dropdown-submenu');
          $.each(parents, function(i, v){
            if(!$(v).hasClass('open')){
              $(v).addClass('open');
              ariaCheck();
            }
          });
        });
      }
      
      $(window).resize(function() {
        var windowWidth = window.innerWidth ? window.innerWidth : $(window).width();
        if(windowWidth != Drupal.TBMegaMenu.oldWindowWidth){
          Drupal.TBMegaMenu.oldWindowWidth = windowWidth;
          Drupal.TBMegaMenu.menuResponsive();
        }
      });
    },
  }
})(jQuery);

