(function () {
  if (typeof (Storage) !== "undefined") {
    if (localStorage.asuMegaFont && localStorage.asuMegaPadding) {
      buildStyle(localStorage.asuMegaFont, localStorage.asuMegaPadding);
    }
  }
  
  function buildStyle(fontSize, padding){
    var styleItem = document.createElement('style');
    styleItem.type = 'text/css';
    styleItem.id = 'asu-preselected-megamenu-style';
    styleItem.textContent = 'body #block-tb-megamenu-main-menu .tb-megamenu-nav>.tb-megamenu-item>a.dropdown-toggle,body #block-tb-megamenu-main-menu .tb-megamenu-nav>.tb-megamenu-item>a{font-size:'+fontSize+';padding:'+padding+';}';
    document.head.appendChild(styleItem);
  }
})()