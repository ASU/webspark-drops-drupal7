(function ($) {
  Drupal.behaviors.asu_feeds = {
    attach: function (context, settings) {

      /**
       * If selection is colleges, show college options, hide campus options;
       * if selection is campuses, hide college options, show campus options.
       */
      if ($("#edit-feeds-asueadvisorfeedfetcher-service").val() == 'eAdvisorDSFind.findDegreeByCollegeAndProgram') {
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(1)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(2)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(3)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(4)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(5)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(6)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(7)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(8)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(9)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(10)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(11)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(12)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(13)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(14)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(15)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(16)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(17)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(18)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(19)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(20)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(21)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(22)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(23)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(24)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(25)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(26)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(27)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(28)').hide();
      } else if ($("#edit-feeds-asueadvisorfeedfetcher-service").val() == 'eAdvisorDSFind.findDegreeByCampusMapArray') {
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(1)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(2)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(3)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(4)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(5)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(6)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(7)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(8)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(9)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(10)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(11)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(12)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(13)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(14)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(15)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(16)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(17)').hide();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(18)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(19)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(20)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(21)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(22)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(23)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(24)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(25)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(26)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(27)').show();
        $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(28)').show();
      }

      $("#edit-feeds-asueadvisorfeedfetcher-service").change(function() {
        var service_val = jQuery(this).val();
        if (service_val == 'eAdvisorDSFind.findDegreeByCollegeAndProgram') {
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(1)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(2)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(3)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(4)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(5)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(6)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(7)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(8)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(9)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(10)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(11)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(12)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(13)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(14)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(15)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(16)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(17)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(18)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(19)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(20)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(21)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(22)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(23)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(24)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(25)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(26)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(27)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(28)').hide();
        } else if (service_val == 'eAdvisorDSFind.findDegreeByCampusMapArray') {
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(1)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(2)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(3)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(4)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(5)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(6)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(7)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(8)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(9)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(10)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(11)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(12)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(13)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(14)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(15)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(16)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(17)').hide();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(18)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(19)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(20)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(21)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(22)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(23)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(24)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(25)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(26)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(27)').show();
          $('#asu-ap-feed-node-form #edit-feeds-asueadvisorfeedfetcher-unit-identifier option:nth-child(28)').show();
        }
      });

    }
  };
})(jQuery);
