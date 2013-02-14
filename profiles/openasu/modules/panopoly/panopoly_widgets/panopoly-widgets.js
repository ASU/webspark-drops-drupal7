Drupal.settings.spotlight_settings = Drupal.settings.spotlight_settings || {};

(function ($) {
 /**
  * Form behavior for Spotlight
  */
 Drupal.behaviors.panopolySpotlight = {
   attach: function (context, settings) {
     if ($('.field-name-field-basic-spotlight-items').length) {
     	var rotation_time = Drupal.settings.spotlight_settings.rotation_time;
       $('.field-name-field-basic-spotlight-items').tabs().tabs("rotate", rotation_time, true);
       // $('.field-name-field-basic-spotlight-items').css('height', $('.field-name-field-basic-spotlight-items').height());
       // $('.field-name-field-basic-spotlight-items').css('overflow', 'hidden');
     }
   }
 }

 /**
  * Automagically set te height of the Video Widget
  */
 Drupal.behaviors.panopolyWidgetVideo = {
   attach: function (context, settings) {

     $('.pane-bundle-video .media-vimeo-outer-wrapper').each(function() {
       var width = $(this).width();
       var height = width / 16 * 9;
       console.log(width);
       $(this).css('height', height);
       $(this).css('width', width);
       $(this).find('.media-vimeo-preview-wrapper').css('height', height);
       $(this).find('.media-vimeo-preview-wrapper').css('width', width);
       $(this).find('iframe.vimeo-player').css('height', height);
       $(this).find('iframe.vimeo-player').css('width', width);
       $(window).unbind('resize', Drupal.media_vimeo.resizeEmbeds);
     }); 

     $('.pane-bundle-video .media-youtube-outer-wrapper').each(function() {
       var width = $(this).width();
       var height = width / 16 * 9;
       console.log(width);
       $(this).css('height', height);
       $(this).css('width', width);
       $(this).find('.media-youtube-preview-wrapper').css('width', width);
       $(this).find('.media-youtube-preview-wrapper').css('height', height);
       $(this).find('iframe.youtube-player').css('width', width);
       $(this).find('iframe.youtube-player').css('height', height);
       $(window).unbind('resize', Drupal.media_youtube.resizeEmbeds);
     });

   }
 }

 /**
  * Create responsive magic for Table Widget
  */
 Drupal.behaviors.panopolyWidgetTables = {
   attach: function (context, settings) {

     $('table.tablefield', context).each(function() {
       var table = $(this); // cache table object.
       var head = table.find('thead th');
       var rows = table.find('tbody tr').clone(); // appending afterwards does not break original table.

       // create new table
       var newtable = $(
         '<table class="mobile-table">' +
         '  <tbody>' +
         '  </tbody>' +
         '</table>'
       );

       // cache tbody where we'll be adding data.
       var newtable_tbody = newtable.find('tbody');

       rows.each(function(i) {
         var cols = $(this).find('td');
         var classname = i % 2 ? 'even' : 'odd';
         cols.each(function(k) {
           var new_tr = $('<tr class="' + classname + '"></tr>').appendTo(newtable_tbody);
           new_tr.append(head.clone().get(k));
           new_tr.append($(this));
         });
       });

       $(this).after(newtable);
     });

   }
 }
})(jQuery);
