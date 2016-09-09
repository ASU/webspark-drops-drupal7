/**
 * @file
 * Gigya functions from Drupal
 */

(function ($) {

    /**
     * @todo Undocumented Code!
     */
    $.extend({
        getUrlVars: function () {
          var vars = [], hash;
          var hashes = window.location.href.slice(window.location.href.indexOf('?') + 1).split('&');
          for (var i = 0; i < hashes.length; i++) {
            hash = hashes[i].split('=');
            vars.push(hash[0]);
            vars[hash[0]] = hash[1];
          }
          return vars;
        },
        getUrlVar: function (name) {
          return $.getUrlVars()[name];
        }
    });

    Drupal.gigya = Drupal.gigya || {};

    Drupal.gigya.hideLogin = function () {
      $('#user-login').hide();
    }

    /**
     * @todo Undocumented Code!
     */
    Drupal.gigya.logoutResponse = function (response) {
      if (response['status'] == 'OK') {
        document.getElementById('logoutMessage').innerHTML = "Successfully logged out, redirecting";
        window.location = Drupal.settings.gigya.logoutLocation;
      }
    };

    Drupal.gigya.addEmail = function (email) {
      if (typeof Drupal.gigya.toPost !== 'undefined') {
        Drupal.gigya.toPost.user.email = email;
        Drupal.gigya.login(Drupal.gigya.toPost);
      }
    }

    Drupal.gigya.login = function (post) {
      if (typeof post.context !== 'undefined') {
        var base = post.context.id
      }
      else {
        var base = $('.gigya-social-login').eq(0).attr('id');
      }
      var element_settings = {};
      element_settings.url = Drupal.settings.basePath + 'socialize-login';
      element_settings.event = 'gigyaLogin';
      var ajax = new Drupal.ajax(base, $('#' + base), element_settings);
      ajax.options.data = post;
      $(ajax.element).trigger('gigyaLogin');
    }



  /**
   * @todo Undocumented Code!
   */
  Drupal.gigya.loginCallback = function (response) {
    Drupal.gigya.toPost = response;
    if ((response.user.email.length === 0) && (response.user.isSiteUID !== true)) {
      var html = '<div class="form-item form-type-textfield form-item-email"><div class="description">Additional information is required in order to complete your registeration. Please fill-in the following info:</div><label for="email" style="float: none;">Email <span class="form-required" title="This field is required.">*</span></label><input type="text" id="email" name="email" value="" size="20" maxlength="60" class="form-text required"><button type="button" class="button" onClick="Drupal.gigya.addEmail(jQuery(this).prev().val())">' + Drupal.t('Submit') + '</button></div>';
      Drupal.CTools.Modal.show();
      $('#modal-title').html('Please fill-in missing details');
      $('#modal-content').html(html);
      $('#modalContent .close').click(function() {
        gigya.socialize.logout();
      });
      return false;
    }
    if(response.provider === 'site' ) {
      return false;
    }
    Drupal.gigya.login(response);
  };

    // Send the account object that is returned in the onLogin event to Drupal.
    Drupal.gigya.raasRegLogin = function (data) {
      var base = Drupal.settings.gigya.raas.linkId || $('.gigya-raas-login').attr('id');
      var element_settings = {};
      element_settings.url = Drupal.settings.basePath + 'raas-login';
      element_settings.event = 'gigyaLogin';
      var ajax = new Drupal.ajax(base, $('#' + base), element_settings);
      ajax.options.data = data;
      $(ajax.element).trigger('gigyaLogin');
    }

    Drupal.gigya.profileUpdated = function (data) {
      console.log(data);
      var base = 'gigyaRequestForms',
          element_settings = {};
      element_settings.url = Drupal.settings.basePath + 'raas-profile-update';
      element_settings.event = 'gigyaProfileUp';
      var ajax = new Drupal.ajax(base, $('#' + base), element_settings);
      ajax.options.data = data.profile;
      $(ajax.element).trigger('gigyaProfileUp');
    }



    /**
     * Callback for the getUserInfo function.
     *
     * Takes the getUserInfo object and renders the HTML to display an array
     * of the user object
     *
     * TODO: probably should be removed in production, since its just for dumping
     * user output.
     */
    Drupal.gigya.getUserInfoCallback = function (response) {
      if (response.status == 'OK') {
        var user = response['user'];
        // Variable which will hold property values.
        var str="<pre>";
        for (prop in user) {
          if (prop == 'birthYear' && user[prop] == 2009) {
            user[prop] = '';
          }
          if (prop == 'identities') {
            for (ident in user[prop]) {
              for (provide in user[prop][ident]) {
                str+=provide + " SUBvalue :"+ user[prop][ident][provide]+"\n";
              }
            }
          }
          // Concate prop and its value from object.
          str+=prop + " value :"+ user[prop]+"\n";
        }
        str+="</pre>";

        document.getElementById('userinfo').innerHTML = str;
      }
    };

    /**
     * @todo Undocumented Code!
     */
    Drupal.gigya.showAddConnectionsUI = function (connectUIParams) {
      gigya.services.socialize.showAddConnectionsUI(connectUIParams);
    };

    /**
     * @todo Undocumented Code!
     */
    Drupal.gigya.notifyLoginCallback = function (response) {
      if (response['status'] == 'OK') {
        setTimeout("$.get(Drupal.settings.basePath + 'socialize-ajax/notify-login')", 1000);
      }
    };


    /**
     * @todo Undocumented Code!
     */
    Drupal.gigya.initResponse = function (response) {
      if (null != response.user) {
        if (response.user.UID != Drupal.settings.gigya.notifyLoginParams.siteUID || !response.user.isLoggedIn) {
          gigya.services.socialize.notifyLogin(Drupal.settings.gigya.notifyLoginParams);
        }
      }
    }
    /**
     * this function checks if the user is looged in at gigya if so it renders the Gamification Plugin
     */
    Drupal.gigya.gmInit = function (response) {
      if (response.errorCode === 0) {
        if (typeof response.UID !== 'undefined') {
          Drupal.gigya.gmRender();
        }
      }
      return false;
    };

    /**
     * function that renders the Gamification Plugin
     */
    Drupal.gigya.gmRender = function () {
      $.each(Drupal.settings.gigyaGM, function(key, block) {
        $.each(block, function(name, params) {
          switch(name) {
          case 'challengeStatusParams':
            gigya.gm.showChallengeStatusUI(params);
            break;
          case 'userStatusParams':
            gigya.gm.showUserStatusUI(params);
            break;
          case 'achievementsParams':
            gigya.gm.showAchievementsUI(params);
            break;
          case 'leaderboardParams':
            gigya.gm.showLeaderboardUI(params);
            break;
          }
        });
      });
    }
    /**
     * this function checks if the user is looged in at gigya if so it renders the Gamification notification Plugin
     */
    Drupal.gigya.gmNotiInit = function (response) {
      if (response.errorCode === 0) {
        if (typeof response.UID !== 'undefined') {
          var params = Drupal.settings.gigyaGMnotification;
          delete params.enable;
          gigya.gm.showNotifications(params);
        }
      }
      return false;
    };
    Drupal.gigya.logoutCallback = function (res){
        if (typeof res.context.id !== 'undefined') {
          document.location = Drupal.settings.basePath + 'user/logout';
        }
    }


})(jQuery);

