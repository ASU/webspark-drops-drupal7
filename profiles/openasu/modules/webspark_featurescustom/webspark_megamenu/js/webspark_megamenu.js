(function ($) {
    Drupal.behaviors.webspark_megamenu_hidden = {
        attach : function(context, settings) {

            if ($('.tb-megamenu-block.tb-block.tb-megamenu-block').length) {
                $('.tb-megamenu-block.tb-block.tb-megamenu-block').closest('.tb-megamenu-row.row-fluid').addClass('hide-extra-padding');
                $('.tb-megamenu-block.tb-block.tb-megamenu-block').closest('.tb-megamenu-block.tb-block.tb-megamenu-block').addClass('adding-padding');
            }

        }
    }
    Drupal.behaviors.webspark_resize_menu = {
    attach: function (context, settings) {

      $(window).on('resize load', function () {
        if (window.innerWidth > 930) {
          var a = jQuery('#ASUNavMenu').find('li.tb-megamenu-item.level-1.mega');
          var x = $('#ASUNavMenu .container .navbar-collapse').width();
          var count = 0;
          var t = 0;

          jQuery.each(a, function (a, b) {
            t += jQuery(b).width();
            count++;
          });
          var data = calcFits(t, x, count, a);
          jQuery('#ASUNavMenu').find('li.tb-megamenu-item.level-1.mega').children("a").css({
            'font-size': data.fs,
            'padding': data.pds,
            'min-height': '57px'
          });
        }
      });

      $.fn.textWidth = function (text, font) {
        if (!$.fn.textWidth.fakeEl) $.fn.textWidth.fakeEl = $('<span>').hide().appendTo(document.body);
        $.fn.textWidth.fakeEl.text(text || this.val() || this.text()).css('font', font || this.css('font'));
        return $.fn.textWidth.fakeEl.width();
      };

      function calcFits(t, x, count, a) {
        var data = [];
        var poss = [];
        var br = true;
        var objs = [{fs: 14,pd: 10,pds: "21px 10px 20px 10px"},{fs: 15,pd: 15,pds: '21px 15px'},{fs: 16, pd: 25,pds: '22px 25px 21px 25px'}];

        for (var i = 0; i < objs.length; ++i) {
          var hold = 0;
          for (var c = 0; c < a.length; ++c) {
            hold += $.fn.textWidth($(a[c]).find('a').eq(0).text(), objs[i].fs + 'px sans-serif');
          }
          hold = hold + (count * objs[i].pd * 2)
          poss.push(hold);
        }
        if (poss[2] < x) {
          return objs[2];
        } else if (poss[1] < x) {
          return objs[1];
        } else {
          return objs[0];
        }

      }

    }
  }
}(jQuery));