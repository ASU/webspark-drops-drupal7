/**
* Provide the HTML to create the modal dialog.
*/
(function ($) {
Drupal.theme.prototype.other_dates_modal = function () {
  var html = ''
  html += '  <div id="ctools-modal">'
  html += '    <div class="ctools-modal-content">' // panels-modal-content
  html += '      <div class="modal-header">';
  html += '        <a class="close" href="#">';
  html +=            Drupal.CTools.Modal.currentSettings.closeImage;
  html += '        </a>';
  html += '        <span id="modal-title" class="modal-title">&nbsp;</span>';
  html += '      </div>';
  html += '      <div id="modal-content" class="modal-content">';
  html += '      </div>';
  html += '    </div>';
  html += '  </div>';

  return html;
}
})(jQuery);
