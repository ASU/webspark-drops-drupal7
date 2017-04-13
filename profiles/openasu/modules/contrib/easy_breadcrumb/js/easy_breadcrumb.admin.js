/**
 * @author Roger Padilla C.
 */

(function (window, $, Drupal) {
  'use strict';

  var document = window.document;

  Drupal.behaviors.easyBreadcrumbAdmin = {

    attach: function (context, settings) {

      var $includeTitleSegment = $('#edit-easy-breadcrumb-include-title-segment', context);

      var synchTitleSegmentRelatedFields = function () {
        if ($includeTitleSegment.is(':checked')) {
          $('#edit-easy-breadcrumb-title-from-page-when-available, #edit-easy-breadcrumb-title-segment-as-link', context).removeAttr('disabled');
        }
        else {
          $('#edit-easy-breadcrumb-title-from-page-when-available, #edit-easy-breadcrumb-title-segment-as-link', context).attr('disabled', 'disabled');
        }
      };

      synchTitleSegmentRelatedFields();

      $includeTitleSegment.change(function(evt) {
        synchTitleSegmentRelatedFields();
      });
    }
  };

})(window, jQuery, Drupal);
