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
          $('.tb-megamenu').each (function(){
            if ($(this).data('duration')) {
              mm_duration = $(this).data('duration');
            }
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
              });
              $(v).removeClass('open');
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
            }
            // If anchor's parent submenus are not open, open them
            var parents = $(this).parents('.tb-megamenu-item.dropdown-submenu');
            $.each(parents, function(i, v){
              if(!$(v).hasClass('open')){
                $(v).addClass('open');
              }
            });
          });
          var mm_timeout = mm_duration ? 100 + mm_duration : 500;
          $('.nav > li, li.mega').hover(function(event) {
            var $this = $(this);
            if ($this.hasClass ('mega')) {
              $this.addClass ('animating');
              clearTimeout ($this.data('animatingTimeout'));
              $this.data('animatingTimeout', setTimeout(function(){$this.removeClass ('animating')}, mm_timeout));
              clearTimeout ($this.data('hoverTimeout'));
              $this.data('hoverTimeout', setTimeout(function(){$this.addClass ('open')}, 100));  
            } else {
              clearTimeout ($this.data('hoverTimeout'));
              $this.data('hoverTimeout', 
              setTimeout(function(){$this.addClass ('open')}, 100));
            }
          },
          function(event) {
            var $this = $(this);
            if ($this.hasClass ('mega')) {
              $this.addClass ('animating');
              clearTimeout ($this.data('animatingTimeout'));
              $this.data('animatingTimeout', 
              setTimeout(function(){$this.removeClass ('animating')}, mm_timeout));
              clearTimeout ($this.data('hoverTimeout'));
              $this.data('hoverTimeout', setTimeout(function(){$this.removeClass ('open')}, 100));
            } else {
              clearTimeout ($this.data('hoverTimeout'));
              $this.data('hoverTimeout', 
              setTimeout(function(){$this.removeClass ('open')}, 100));
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

