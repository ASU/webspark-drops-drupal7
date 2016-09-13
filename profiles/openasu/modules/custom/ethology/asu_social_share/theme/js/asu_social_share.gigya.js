(function ($) {
  function ASUGigyaShare(){

  }

  Drupal.behaviors.asu_social_share_gigya = {
    attach: function (context, settings) {
      ASUGigyaShare.Share = function(event, thisObj){
        event.preventDefault();
        event.stopPropagation();

        try {
            var thisObj = $(thisObj),
                provider = thisObj.attr("data-ua-provider"),
                imageUrl = thisObj.attr("data-ua-image"),
                description = decodeURIComponent(thisObj.attr("data-ua-description")),
                linkback = thisObj.attr("data-ua-linkback"),
                title = decodeURIComponent(thisObj.attr("data-ua-title")),
                context = thisObj.attr("data-ua-context");
            var image = null;
            if (imageUrl && imageUrl != null && imageUrl != "") {
                image = {
                    type: 'image',
                    src: imageUrl,
                    href: linkback
                };
            }
            var ua = new gigya.socialize.UserAction();
            ua.setLinkBack(linkback);
            ua.setTitle(title);
            ua.setDescription(description);
            if (image != null) {
                ua.addMediaItem(image);
            }

            var params = {
                provider: provider,
                url: linkback,
                userAction: ua,
                cid: context,
                shortURLs: 'always'
            };
console.log(params);
            gigya.socialize.postBookmark(params);
        }catch(err){
            console.log("Gigya Posting Error: " + err);
        }
      };


      $('.js-gigya').once('gigya').bind('click', function(event){
          ASUGigyaShare.Share(event, this);
      });
    }
  };

})(jQuery);
