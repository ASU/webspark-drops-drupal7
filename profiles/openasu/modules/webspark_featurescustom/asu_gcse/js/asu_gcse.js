(function($) {
  Drupal.behaviors.asu_gcse_search = {
    attach: function (context, settings) {

      // Get URL path and set search variable
      var url_path_name = window.location.pathname;
      var url_search = '/search/';
      var node_search = 'search/node';
      var google_search = 'search/google';

      // If user is currently on a page with 'search' in the path
      if (url_path_name.indexOf(url_search) === 0) {

        var first_nav_pill_text_check = $('.nav-pills li:first-child a').text();

        // Move 'Content' aka 'This site' nav pill to first position if it's last (because it falls alphabetically behind 'All of ASU' either way)
        if (first_nav_pill_text_check != 'Content') {
          var $nav_pill_to_move = $('.nav-pills li:last-child');
          if ($nav_pill_to_move.not(':first-child')) {
            $nav_pill_to_move.prev().before($nav_pill_to_move);
          }
        }

        // Get nav pill data
        var first_nav_pill_url = $('.nav-pills li:first-child a').attr("href");
        var first_nav_pill_text = $('.nav-pills li:first-child a').text();
        var last_nav_pill_url = $('.nav-pills li:last-child a').attr("href");
        var last_nav_pill_text = $('.nav-pills li:last-child a').text();

        // Get the title set by the site
        var asu_site_title = $('.asu-site-title').text();

        // Forced a document title, because it doesn't reflect the h1 title (on both search pages)
        document.title = "Search Results | " + asu_site_title;

        // If the first nav pill URL matches the node_search form ('search/node') then proceed
        if (first_nav_pill_url && first_nav_pill_url.indexOf(node_search) != -1) {
          // Change 'Content' nav pill label to 'This site'
          $('.nav-pills li:first-child a').text("This site");

          // Hide 'Search results' h2 title (not the same as the #page-title added above) that is produced by node search
          if ($('.content h2').text() != '') {
            $('.content h2').hide();
          }
        }

        // If the last nav pill URL matches the node_search form ('search/google') then proceed
        if (last_nav_pill_url && last_nav_pill_url.indexOf(google_search) != -1) {
          // Google engine-specific JS here
        }

      }

    }
  };
})(jQuery);