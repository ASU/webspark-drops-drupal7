(function($) {

/**
 * Attach this editor to a target element.
 */
Drupal.wysiwyg.editor.attach.yui = function(context, params, settings) {
  // Apply theme.
  $('#' + params.field).parent().addClass('yui-skin-' + settings.theme);
  // Attach editor.
  var editor = new YAHOO.widget.Editor(params.field, settings);
  editor.render();
};

/**
 * Detach a single or all editors.
 *
 * See Drupal.wysiwyg.editor.detach.none() for a full desciption of this hook.
 */
Drupal.wysiwyg.editor.detach.yui = function (context, params, trigger) {
  var method = (trigger && trigger == 'serialize') ? 'saveHTML' : 'destroy';
  if (typeof params != 'undefined') {
    var instance = YAHOO.widget.EditorInfo.getEditorById(params.field);
    if (instance) {
      instance[method]();
    }
  }
  else {
    for (var e in YAHOO.widget.EditorInfo._instances) {
      // Save contents of all editors back into textareas.
      var instance = YAHOO.widget.EditorInfo._instances[e];
      instance[method]();
    }
  }
};

Drupal.wysiwyg.editor.instance.yui = {
  insert: function (content) {
    YAHOO.widget.EditorInfo.getEditorById(this.field).cmd_inserthtml(content);
  },

  setContent: function (content) {
    YAHOO.widget.EditorInfo.getEditorById(this.field).setEditorHTML(content);
  },

  getContent: function () {
    var instance = YAHOO.widget.EditorInfo.getEditorById(this.field);
    return instance.cleanHTML(instance.getEditorHTML(content));
  }
};

})(jQuery);
