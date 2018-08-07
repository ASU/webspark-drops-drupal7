(function ($) {
  Drupal.behaviors.asu_events_search = {
    attach: function (context, settings) {
      $('#btn-event-search').once('search-btn').bind('click', function (e) {
        e.preventDefault();
        var keyword = $('input[name=search-keyword-field]').val();
        var category = $.QueryString["category"];
        if ( category !== 'undefined') {
          window.location = window.location.origin + '/events-search-results?keywords=' + keyword + '&category=' + category;
        }
        else {
          window.location = window.location.origin + '/events-search-results?keywords=' + keyword;
        }
      });

      $('.event-category-filters a').once('category-filters').bind('click', function (e) {
        e.preventDefault();
        var filter = $(this).find('.category-name').html();
        var keyword = $.QueryString["keywords"];
        if ( keyword !== 'undefined') {
          window.location = window.location.origin + '/events-search-results?keywords=' + keyword + '&category=' + filter;
        }
        else {
          window.location = window.location.origin + '/events-search-results?category=' + filter;
        }

      });

    }
  };
})(jQuery);

(function($) {
    $.QueryString = (function(a) {
        if (a == "") return {};
        var b = {};
        for (var i = 0; i < a.length; ++i)
        {
            var p=a[i].split('=', 2);
            if (p.length != 2) continue;
            b[p[0]] = decodeURIComponent(p[1].replace(/\+/g, " "));
        }
        return b;
    })(window.location.search.substr(1).split('&'))
})(jQuery);
