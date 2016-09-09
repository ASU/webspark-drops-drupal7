/**
 * @file
 * Drupal behaviors for gigya.
 */

(function ($) {

  'use strict';
  /**
   * @todo Undocumented Code!
   */
  Drupal.behaviors.gigyaNotifyFriends = {
    attach: function (context, settings) {
      if (typeof gigya !== 'undefined') {
        $('.friends-ui:not(.gigyaNotifyFriends-processed)', context).addClass('gigyaNotifyFriends-processed').each(
          function () {
            gigya.services.socialize.getUserInfo({callback: Drupal.gigya.notifyFriendsCallback});
            gigya.services.socialize.addEventHandlers({
              onConnect: Drupal.gigya.notifyFriendsCallback,
              onDisconnect: Drupal.gigya.notifyFriendsCallback
            });
          }
        );
      }
    }
  };

  /**
   * @todo Undocumented Code!
   */
  Drupal.behaviors.gigyaInit = {
    attach: function (context, settings) {
      if (typeof gigya !== 'undefined') {
        if (typeof Drupal.settings.gigya.notifyLoginParams !== 'undefined') {
          Drupal.settings.gigya.notifyLoginParams.callback = Drupal.gigya.notifyLoginCallback;
          gigya.services.socialize.getUserInfo({callback: Drupal.gigya.initResponse});
        }

        // Attach event handlers.
        if (typeof  Drupal.settings.gigya.regEvents === 'undefined') {
          // If we are in RaaS mode register the RaaS login function.
          if (Drupal.settings.gigya.loginMode === 'raas') {
            gigya.accounts.addEventHandlers({
              onLogin: Drupal.gigya.raasRegLogin,
              onLogout: Drupal.gigya.logoutCallback
            });
          }
          // If we are in socialize mode register the socialize login function.
          else {
            gigya.socialize.addEventHandlers({
              onLogin: Drupal.gigya.loginCallback,
              onLogout: Drupal.gigya.logoutCallback
            });
          }
          Drupal.settings.gigya.regEvents = true;
        }

        // Display LoginUI if necessary.
        if (typeof Drupal.settings.gigya.loginUIParams !== 'undefined') {
          $.each(Drupal.settings.gigya.loginUIParams, function (index, value) {
            value.context = {id: value.containerID};
            gigya.services.socialize.showLoginUI(value);
          });
        }

        // Display ConnectUI if necessary.
        if (typeof Drupal.settings.gigya.connectUIParams !== 'undefined') {
          gigya.services.socialize.showAddConnectionsUI(Drupal.settings.gigya.connectUIParams);
        }

        // Call ShareUI if it exists.
        if (typeof Drupal.settings.gigya.shareUIParams !== 'undefined') {
          //build a media object
          var mediaObj = {type: 'image', href: Drupal.settings.gigya.shareUIParams.linkBack};
          if ((Drupal.settings.gigya.shareUIParams.imageBhev === 'url') && (Drupal.settings.gigya.shareUIParams.imageUrl !== '')) {
            mediaObj.src = Drupal.settings.gigya.shareUIParams.imageUrl;
          }
          else if (Drupal.settings.gigya.shareUIParams.imageBhev === 'default') {
            if ($('meta[property="og:image"]').length > 0) {
              mediaObj.src = $('meta[property="og:image"]').attr('content');
            }
            else {
              mediaObj.src = $('#block-system-main img').eq(0).attr('src') || $('img').eq(0).attr('src');
            }
          }
          else {
            mediaObj.src = $('#block-system-main img').eq(0).attr('src') || $('img').eq(0).attr('src');
          }
          // Step 1: Construct a UserAction object and fill it with data.
          var ua = new gigya.services.socialize.UserAction();
          if (typeof Drupal.settings.gigya.shareUIParams.linkBack !== 'undefined') {
            ua.setLinkBack(Drupal.settings.gigya.shareUIParams.linkBack);
          }
          if (typeof Drupal.settings.gigya.shareUIParams.title !== 'undefined') {
            ua.setTitle(Drupal.settings.gigya.shareUIParams.title);
          }
          if (typeof Drupal.settings.gigya.shareUIParams.description !== 'undefined') {
            ua.setDescription(Drupal.settings.gigya.shareUIParams.description);
          }
          ua.addMediaItem(mediaObj);
          var params = {};
          if (typeof Drupal.settings.gigya.shareUIParams.extraParams !== 'undefined') {
            params = Drupal.settings.gigya.shareUIParams.extraParams;
          }
          params.userAction = ua;
          gigya.services.socialize.showShareUI(params);
        }
      }
    }
  };

  /**
   * @todo Undocumented Code!
   */
  Drupal.behaviors.gigyaLogut = {
    attach: function (context, settings) {
      if (typeof gigya !== 'undefined') {
        if ($.cookie('Drupal.visitor.gigya') == 'gigyaLogOut') {
          if (Drupal.settings.gigya.loginMode === 'raas') {
            gigya.accounts.logout();
          }
          else {
            gigya.services.socialize.logout();
          }
          $.cookie('Drupal.visitor.gigya', null);
        }
      }
    }
  };
  /**
   * initiate Gamification
   */

  Drupal.behaviors.gamification = {
    attach: function (context, settings) {
      if (typeof gigya !== 'undefined') {
        if (typeof Drupal.settings.gigyaGM !== 'undefined') {
          gigya.services.socialize.getUserInfo({callback: Drupal.gigya.gmInit});
        }
      }
    }
  };
  Drupal.behaviors.GMnotifications = {
    attach: function (context, settings) {
      if (typeof gigya !== 'undefined') {
        if (typeof Drupal.settings.gigyaGMnotification !== 'undefined') {
          gigya.services.socialize.getUserInfo({callback: Drupal.gigya.gmNotiInit});
        }
      }
    }
  };
  /**
   * initiate Activity Feed
   */
  Drupal.behaviors.gigyaActivityFeed = {
    attach: function (context, settings) {
      if (typeof gigya !== 'undefined') {
        if (typeof Drupal.settings.gigyaActivityFeed !== 'undefined') {
          gigya.socialize.showFeedUI(Drupal.settings.gigyaActivityFeed);
        }
      }
    }
  };
  Drupal.behaviors.addGigyaUidToForm = {
    attach: function (context, settings) {
      if (typeof gigya !== 'undefined') {
        if ($('#gigya-link-accounts-form .gigyaUid').length > 0) {
          $('#gigya-link-accounts-form .gigyaUid').val(Drupal.gigya.toPost.user.UID);
        }
        if ($('#modal-content form .gigyaUid').length > 0) {
          $('#modal-content form .gigyaUid').val(Drupal.gigya.toPost.user.UID);
        }
        $('#modal-content form .close-modal').once().click(function (e) {
          e.preventDefault();
          Drupal.CTools.Modal.dismiss();
        });
      }
    }
  };
  Drupal.behaviors.gigyaFillRegForm = {
    attach: function (context, settings) {
      if (typeof gigya !== 'undefined') {
        if ($('.modal-content #user-register-form').length > 0) {
          $('.modal-content #user-register-form input:[name=mail]').val(Drupal.gigya.toPost.user.email);
          $('.modal-content #user-register-form input:[name=name]').val(Drupal.gigya.toPost.user.email);
          jQuery('#gigya-link-accounts-form').parent().prev().find('.close').click(function () {
            gigya.socialize.logout();
          });
        }
      }
    }
  };

  Drupal.behaviors.gigyaCheckLoginStatus = {
    attach: function (context, settings) {
      if (typeof gigya !== 'undefined') {
        try {
          if (Drupal.settings.gigyaExtra.sessionMode == 'gigya') {
            var getAccountInfoResponse = function (response) {
              if (!response) {
                return;
              }
              if (response.errorCode != 0) {
                if (Drupal.settings.gigyaExtra.isLogin == true) {
                  //Login in drupal but not in Gigya.
                  if (!Drupal.settings.gigyaExtra.bypassRaas == true) {
                    //No bypass raas perm.
                    //Log out the user.
                    document.location = Drupal.settings.basePath + 'user/logout';
                  }
                }
              }
              else {
                if (Drupal.settings.gigyaExtra.isLogin == false) {
                  Drupal.gigya.raasRegLogin(response);
                }
              }
            }
            gigya.accounts.getAccountInfo({callback: getAccountInfoResponse});
          }
        } catch (e) {
        } finally {
        }
      }
    }
  };


  Drupal.behaviors.gigyaRaas = {
    attach: function (context, settings) {
      if (typeof gigya !== 'undefined') {
        if (Drupal.settings.gigya.loginMode == 'raas') {
          $('.gigya-raas-login').once('gigya-raas').click(function (e) {
            e.preventDefault();
            gigya.accounts.showScreenSet(Drupal.settings.gigya.raas.login);
            Drupal.settings.gigya.raas.linkId = $(this).attr('id');
          });
          $('.gigya-raas-reg').once('gigya-raas').click(function (e) {
            e.preventDefault();
            gigya.accounts.showScreenSet(Drupal.settings.gigya.raas.register);
            Drupal.settings.gigya.raas.linkId = $(this).attr('id');
          });
          $('.gigya-raas-prof, a[href="/user"]').once('gigya-raas').click(function (e) {
            e.preventDefault();
            Drupal.settings.gigya.raas.profile.onAfterSubmit = Drupal.gigya.profileUpdated;
            gigya.accounts.showScreenSet(Drupal.settings.gigya.raas.profile);
          });
          var loginDiv = $('#gigya-raas-login-div');
          if (loginDiv.size() > 0 && (typeof Drupal.settings.gigya.raas.login !== 'undefined')) {
            var id = loginDiv.eq(0).attr('id');
            Drupal.settings.gigya.raas.login.containerID = id;
            Drupal.settings.gigya.raas.linkId = id;
            gigya.accounts.showScreenSet(Drupal.settings.gigya.raas.login);
          }
          var regDiv = $('#gigya-raas-register-div');
          if (regDiv.size() > 0 && (typeof Drupal.settings.gigya.raas.register !== 'undefined')) {
            var id = regDiv.eq(0).attr('id');
            Drupal.settings.gigya.raas.register.containerID = id;
            Drupal.settings.gigya.raas.linkId = id;
            gigya.accounts.showScreenSet(Drupal.settings.gigya.raas.register);
          }
          var profDiv = $('#gigya-raas-profile-div');
          if ((profDiv.size() > 0) && (typeof Drupal.settings.gigya.raas.profile !== 'undefined')) {
            Drupal.settings.gigya.raas.profile.containerID = profDiv.eq(0).attr('id');
            Drupal.settings.gigya.raas.profile.onAfterSubmit = Drupal.gigya.profileUpdated;
            gigya.accounts.showScreenSet(Drupal.settings.gigya.raas.profile);
          }
        }
      }
    }
  };
})(jQuery);

