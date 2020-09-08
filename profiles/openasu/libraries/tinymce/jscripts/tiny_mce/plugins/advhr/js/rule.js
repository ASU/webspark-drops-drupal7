var AdvHRDialog = {
	init : function(ed) {
		var dom = ed.dom, f = document.forms[0], n = ed.selection.getNode(), w;

		w = dom.getAttrib(n, 'width');
		f.width.value = w ? parseInt(w) : (dom.getStyle('width') || '');
    // Hardcoded 8px tall for WS2.0 (vs. '' empty string)
    f.size.value = dom.getAttrib(n, 'size') || parseInt(dom.getStyle('height')) || 8;
		selectByValue(f, 'width2', w.indexOf('%') != -1 ? '%' : 'px');
	},

	update : function() {
		var ed = tinyMCEPopup.editor, h, f = document.forms[0], st = '';

		h = '<hr class="ws2-hr ws2-hr-gold" ';

		if (f.size.value) {
      h += ' size="' + f.size.value + '"';
			st += ' height:' + f.size.value + 'px;';
		}
		if (f.width.value) {
			h += ' width="' + f.width.value + (f.width2.value == '%' ? '%' : '') + '"';
			st += ' width:' + f.width.value + (f.width2.value == '%' ? '%' : 'px') + ';';
		}
    if (f.align.value) {
      h += ' align="' + f.align.value + '"';
      if (f.align.value === "justify") {
        st += " text-align:" + f.align.value + "; text-justify: inter-word;";
      }
    }
    // WS2.0 styling
    st += " background-color: #ffc627; border: none;";

    if (ed.settings.inline_styles) {
      h += ' style="' + tinymce.trim(st) + '"';
    }

		h += ' />';

		ed.execCommand("mceInsertContent", false, h);
		tinyMCEPopup.close();
	}
};

tinyMCEPopup.requireLangPack();
tinyMCEPopup.onInit.add(AdvHRDialog.init, AdvHRDialog);
