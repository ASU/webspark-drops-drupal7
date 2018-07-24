(function ($) {
  Drupal.behaviors.asu_solr_events_load_more = {
    attach: function (context, settings) {
      // Make sure that autopager plugin is loaded
      var eventsView = false;
      $('.nodes-date-wrapper').once('load-more-dates').each(function( key, value ) {
        var nodes = $(value).find('.node');
        if (nodes.length > 2) {
          count = 0;
          $.each( nodes, function( i, node ) {
            if (i > 1) {
              console.log(node);
              height = $(node).show().height();
              $(node).addClass('nodeHide');
              if ($(window).width() > 1215)
                $(node).hide().css({height: 0});
              else
                $(node).hide();
              // $(node).css('border', '1px solid transparent');
              // $(node).hide();
            }
          });
        }
      });
      $('.view-more-btn-date').once('view-more').bind('click', function(e) {
        e.preventDefault();
        var hidden_nodes = $(this).parent().find('.nodeHide');
        var nodeEvent = $(this);
        if ($(hidden_nodes).is(":visible"))
        {
          if ($(window).width() > 1215) {
            $(hidden_nodes).animate({height: 0}, {
              complete: function () {
                $(hidden_nodes).hide();
                $(nodeEvent).text("view more events");
              }
            });
          }
          else
          {
            $(hidden_nodes).slideUp(function () {
              $(nodeEvent).text("view more events");
            });
          }
          eventsView = true;
        }
        else
        {
          if ($(window).width() > 1215) {
            $(hidden_nodes).show().animate({height: height}, {
              complete: function () {
                $(nodeEvent).text("view fewer events");
              }
            });
          }
          else
          {
            $(hidden_nodes).slideDown(function() {
                $(nodeEvent).text("view fewer events");
              }
            );
          }
            eventsView = false;
        }
        console.log(hidden_nodes);
      });
      // $(window).resize(function()
      // {
      //   height = $('.node-asu-event').height();
      //   if (height < 300)
      //   {
      //     height = 300;
      //     alert("height is " + height);
      //   }
      // });
      if($.autopager) {
        // define autopager parameters
        var solr_content_selector = '.solr-items-wrapper';
        var solr_items_selector = solr_content_selector + ' nodes-date-wrapper';
        var solr_next_selector = '.solr-events-pager-next a';
        var solr_pager_selector = '.solr-events-pager';



        $(solr_pager_selector).hide();

        console.log(Drupal.settings);
        if (typeof Drupal.settings.asu_events !== 'undefined') {
          var pager_total = Drupal.settings.asu_events.pager_total;
          var current_page = 0;
          var throb_solr_events = Throbber({
              size: 20, // this will also be applied to the gif
              padding: 10
          });


          // if (Drupal.settings.asu_events.view_mode != 'calendar') {

          // if ( throb_solr_events !== 'undefined' && $('.asu-solor-events-load-more-btn').length > 0 ) {
          //   try {
          //     throb_solr_events.appendTo($('.asu-solor-events-load-more-btn')[0]);
          //   }
          //   catch (e) {
          //     console.log($('.asu-solor-events-load-more-btn')[0]);
          //   }
          //
          // }

            // $('.asu-solor-events-load-more-btn canvas').css('margin-left', '7px');
            if(pager_total == 1) {
              $('.asu-solor-events-load-more-btn').hide();
            }
            $('.asu-solor-events-load-more-btn').once('solr-events-load-more', function() {
              // height += $('.node-asu-event').height()/6;
              $(this).bind('click', function(e) {
                var current_nids = [];
                $('.pane-asu-events-exhibits-search-listing article').each(function (i){
                  current_nids.push($(this).attr('id').replace('node-',''));
                });
                current_nids = JSON.stringify(current_nids);
                console.log(current_nids);
                current_page += 1;
                var url = updateQueryStringParameter($(location).attr('href') , 'current_search_page', current_page);
                e.preventDefault();
                $.ajax({
                  url: url,
                  method: 'POST',
                  type: 'POST',
                  data: {'current_nids' : current_nids},
                  beforeSend: function( xhr ) {
                    throb_solr_events.start();
                    // $('.asu-solor-events-load-more-btn canvas').css('display', 'inline');
                  },
                  success: function (data) {
                    $('.solr-items-wrapper').append($(data).find('.nodes-date-wrapper'));
                  },
                  dataType: 'html'
                }).done(function( msg ) {
                  throb_solr_events.stop();
                  Drupal.attachBehaviors();
                });

              });
            });
          // }
        }
      }
    }
  };

  function updateQueryStringParameter(uri, key, value) {
    var re = new RegExp("([?&])" + key + "=.*?(&|#|$)", "i");
    if( value === undefined ) {
      if (uri.match(re)) {
          return uri.replace(re, '$1$2');
      } else {
          return uri;
      }
    } else {
      if (uri.match(re)) {
          return uri.replace(re, '$1' + key + "=" + value + '$2');
      } else {
      var hash =  '';
      if( uri.indexOf('#') !== -1 ){
          hash = uri.replace(/.*#/, '#');
          uri = uri.replace(/#.*/, '');
      }
      var separator = uri.indexOf('?') !== -1 ? "&" : "?";
      return uri + separator + key + "=" + value + hash;
    }
    }
  }

})(jQuery);
