(function (RLD, $) {

  function mapKeyToChar(isShifted, keyCode) {
    if (keyCode === 27
      || keyCode === 8
      || keyCode === 9
      || keyCode === 20
      || keyCode === 16
      || keyCode === 17
      || keyCode === 91
      || keyCode === 13
      || keyCode === 92
      || keyCode === 18) {
      return false;
    }
    if (typeof isShifted != "boolean" || typeof keyCode != "number") {
      return false;
    }
    var charMap = [];
    charMap[192] = "~";
    charMap[49] = "!";
    charMap[50] = "@";
    charMap[51] = "#";
    charMap[52] = "$";
    charMap[53] = "%";
    charMap[54] = "^";
    charMap[55] = "&";
    charMap[56] = "*";
    charMap[57] = "(";
    charMap[48] = ")";
    charMap[109] = "_";
    charMap[107] = "+";
    charMap[219] = "{";
    charMap[221] = "}";
    charMap[220] = "|";
    charMap[59] = ":";
    charMap[222] = "\"";
    charMap[188] = "<";
    charMap[190] = ">";
    charMap[191] = "?";
    charMap[32] = " ";
    var character = "";
    if (isShifted) {
      if (keyCode >= 65 && keyCode <= 90) {
        character = String.fromCharCode(keyCode);
      }
      else {
        character = charMap[keyCode];
      }
    }
    else {
      if (keyCode >= 65 && keyCode <= 90) {
        character = String.fromCharCode(keyCode).toLowerCase();
      }
      else {
        character = String.fromCharCode(keyCode);
      }
    }
    return character;
  }

  RLD['Utils'] = {};
  /**
   * Keymanager
   */
  RLD['Utils'].keyManager = function (event) {
    var pattern = event.data.pattern;
    var callback = event.data.callback;
      // Get the key.
    var key = mapKeyToChar(event.shiftKey, event.keyCode);
    if (key && typeof pattern === 'object' && 'exec' in pattern && typeof callback === 'function') {
      // Invoke callback if the key is allowed or the delete key is pressed.
      if (pattern.exec(key) || $.inArray(key, [8]) > -1) {
        event.key = key;
        callback.apply(this, arguments);
      }
      else {
        console.log(event.keyCode);
        // The key(s) are illegal, do nothing.
        event.preventDefault();
      } 
    }
  };
}(ResponsiveLayoutDesigner, jQuery));