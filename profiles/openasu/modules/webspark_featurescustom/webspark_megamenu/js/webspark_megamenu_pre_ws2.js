(function () {
  function buildStyle(fontSize, padding, fontSizeSubT){
    var styleItem = document.createElement("style");
    styleItem.type = "text/css";
    styleItem.id = "asu-preselected-megamenu-style";
    styleItem.textContent = "#ASUNavMenu .tb-megamenu-nav>.tb-megamenu-item>a.dropdown-toggle," +
      "#ASUNavMenu .tb-megamenu-nav > .tb-megamenu-item > a," +
      ".ghostSlider .tb-megamenu-nav > .tb-megamenu-item > a.dropdown-toggle," +
      ".ghostSlider .tb-megamenu-nav > .tb-megamenu-item > a {font-size:"+fontSize+";padding:"+padding+
      ";}" +
      "#ASUNavMenu .tb-megamenu-nav li.tb-megamenu-item.mega a:not(.mega-group-title)," +
      "#ASUNavMenu .tb-megamenu-nav li.tb-megamenu-item.level-1.mega.btn a:not(.mega-group-title)" +
      "{ font-size:" + fontSize + ";}" +
      "#ASUNavMenu .tb-megamenu .dropdown-menu .mega-group > a.mega-group-title," +
      "#ASUNavMenu .tb-megamenu .dropdown-menu .mega-nav .mega-group > .mega-group-title," +
      "#ASUNavMenu .tb-megamenu .dropdown-menu .active .mega-nav .mega-group > .mega-group-title" +
      "{ font-size:" + fontSizeSubT + ";}";
    document.head.appendChild(styleItem);
  }
  if (typeof (Storage) !== "undefined") {
    if (localStorage.asuMegaFont && localStorage.asuMegaPadding && localStorage.asuMegaSubTFont) {
      buildStyle(localStorage.asuMegaFont, localStorage.asuMegaPadding, localStorage.asuMegaSubTFont);
    }
  }
})();
