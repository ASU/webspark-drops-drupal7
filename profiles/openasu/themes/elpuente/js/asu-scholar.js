/**
 * Menu JS for adding Web Standard Assets & Styling to menus
 */

var asu_os_menu = (function asu_os_menu() {

  /**
   * Web Standard approved values
   * fontawesome: icons
   * wsApprovedSizing: Top level style values
   */
  var fontawesome = {
    caretDown: '<i class="fa fa-caret-down" aria-hidden="true"></i>',
    caretRight: '<i class="fa fa-caret-right" aria-hidden="true"></i>',
    homeIcon: '<i class="fa fa-home" aria-hidden="true"></i>',
  }

  var wsApprovedSizing = {
    large: 'font-size:16px; padding: 21px 25px;',
    medium: 'font-size:15px; padding: 21px 15px;',
    small: 'font-size:14px; padding: 21px 10px;',
  }

  /**
   * Init & Helper Functions for menu styling
   */
  return {
    initCaret: function setCaret(targets, topLevelClass) {
      if (targets && targets.length) {
        var haschildren = targets;

        for (var i = 0; i < haschildren.length; i++) {
          var item = haschildren[i];
          if (item.parentNode && item.parentNode.className && item.parentNode.className.includes(topLevelClass)) {
            item.firstChild.innerHTML = item.firstChild.innerHTML + fontawesome.caretDown;
          } else {
            item.firstChild.innerHTML = item.firstChild.innerHTML + fontawesome.caretRight;
          }
        }
      } else {
        console.log('Query Selector Failed to initCaret');
      }
    },
    initHome: function initHome(target) {
      if (target) {
        if (target.innerHTML == "Home" || target.innerHTML == "home") {
          target.innerHTML = fontawesome.homeIcon;
        }
      } else {
        console.log('Query Selector Failed to initHome');
      }
    },
    initSizing: function initSizing(maxStr, elemsStr) {
      if (localStorage.asumenusize) {
        this.size = localStorage.asumenusize;
      } else {
        this.size = 'large';
      }
      var max = document.getElementById(maxStr);
      var elems = document.querySelectorAll(elemsStr);

      try {
        this.resize(elems, this.size);

        this.width = this.countSize(elems);

        this.calibrate(max, elemsStr);

        var thisobj = this;
        window.addEventListener('resize', function () {
          thisobj.verifySize(max, elemsStr);
        });

      } catch (err) {
        console.log('Query Selector Failed to initSizing');
        console.log(err);
      }
    },
    countSize: function countSize(elems) {
      var counter = 0;
      for (var i = 0; i < elems.length; i++) {
        counter = counter += elems[i].clientWidth;
      }
      return counter;
    },
    resize: function sizeDown(elems, size) {
      for (var i = 0; i < elems.length; i++) {
        elems[i].firstChild.setAttribute('style', wsApprovedSizing[size]);
      }
    },
    calibrate: function calibrate(max, elemsStr) {
      this.ghosts = [];
      var keys = Object.keys(wsApprovedSizing);
      for (var i = 0; i < keys.length; i++) {
        var key = keys[i];
        var theUpsideDown = this.setShadow(max, key);
        var fakeElems = theUpsideDown.querySelectorAll(elemsStr);
        this.resize(fakeElems, key);
        var sizeof = this.countSize(fakeElems);
        this.ghosts[i] = {
          key: key,
          width: sizeof,
        };
      }
    },
    setShadow: function setShadow(max, key) {

      var clone = max.cloneNode(true);
      var theUpsideDown = document.createElement('span');
      theUpsideDown.id = "theUpsideDown-" + key;
      theUpsideDown.style.cssText = 'display: block; width: 100%; height: 0; overflow: hidden;';
      theUpsideDown.appendChild(clone);

      document.body.appendChild(theUpsideDown);

      return clone;
    },
    verifySize: function verifySize(max, elemsStr) {
      var maxWidth = max.clientWidth;
      var elems = max.querySelectorAll(elemsStr);
      var ok = [];

      for (var i = 0; i < this.ghosts.length; i++) {
        var obj = this.ghosts[i];

        if (obj.width < maxWidth) {
          ok.push(obj);
        }
      }

      ok.sort(function (a, b) {
        return b.width - a.width
      });

      if (ok.length == 0) {
        this.size = 'small';
      } else {
        this.size = ok[0].key;
      }

      localStorage.setItem('asumenusize', this.size);
      this.resize(elems, this.size);
    },
  }
})();

(function () {
  Drupal.behaviors.innovation = {
    attach: function (context, settings) {
      asu_os_menu.initCaret(document.querySelectorAll('#block-asu-primary-menu .menuparent'), "nice-menu");

      asu_os_menu.initHome(document.querySelector('#block-asu-primary-menu .nice-menu>.first>a'));

      asu_os_menu.initSizing('block-asu-primary-menu', '.nice-menu>li');
    }
  }
})();