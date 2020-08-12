(function ($, Drupal) {
    Drupal.behaviors.webspark_mega_footer = {
        attach: function (context, settings) {

            if ($(window).innerWidth() >= 992) {
                $('.big-foot-nav').not('.in').addClass('in');
                $('.big-foot-head').removeAttr("data-toggle");
            } else {
                $('.big-foot-nav').removeClass('in');
            }

            $(window).resize(function () {
                if ($(window).innerWidth() >= 992) {
                    $('.big-foot-nav').not('.in').addClass('in');
                    $('.big-foot-head').removeAttr("data-toggle");
                } else {
                    $('.big-foot-nav').removeClass('in');
                    $('.big-foot-head').attr("data-toggle", "collapse");
                }

            });
        }
    };
})(jQuery, Drupal);


// We define a function that takes one parameter named $.
(function ($) {
    // On window load. This waits until images have loaded which is essential
    $(window).load(function(){
        var gray = [], white = [];

        // Fade in images so there isn't a color "pop" document load and then on window load
        $(".gray img").fadeIn(500);

        // clone image
        $(".gray img").each(function(i){
            var el = $(this);
            el.css({"position":"absolute"}).wrap("<div class='img_wrapper' style='display: inline-block'>").clone().addClass('img_grayscale').css({"position":"absolute","z-index":"998","opacity":"0","top":7}).insertBefore(el).queue(function(){
                var el = $(this);
                el.parent().css({"min-width":38,"height":38,"padding":0});
                el.dequeue();
            });
            gray.push(grayscale(this.src));
            white.push(whiten(this.src));

            this.src = gray[gray.length-1];
        });

        // Fade image
        $(".gray img").mouseover(function(){
            this.src = white[$(".gray img").index(this)/2];
            $(this).parent().find('img:first').stop().animate({opacity:1},0);
        });
        $(".gray img").mouseout(function(){
            $(this).parent().find('img:first').stop().animate({opacity:0},0);
        });
    });

    // Grayscale w canvas method
    function grayscale(src){
        var canvas = document.createElement('canvas');
        var ctx = canvas.getContext('2d');
        var imgObj = new Image();
        imgObj.src = src;
        canvas.width = imgObj.width;
        canvas.height = imgObj.height;
        ctx.drawImage(imgObj, 0, 0);
        var imgPixels = ctx.getImageData(0, 0, canvas.width, canvas.height);
        for(var y = 0; y < imgPixels.height; y++){
            for(var x = 0; x < imgPixels.width; x++){
                var i = (y * 4) * imgPixels.width + x * 4;
                var avg = (imgPixels.data[i] + imgPixels.data[i + 1] + imgPixels.data[i + 2]) / 3;
                imgPixels.data[i] = avg + 50;
                imgPixels.data[i + 1] = avg + 50;
                imgPixels.data[i + 2] = avg + 50;
            }
        }
        ctx.putImageData(imgPixels, 0, 0, 0, 0, imgPixels.width, imgPixels.height);
        return canvas.toDataURL();
    }

    // Grayscale w canvas method
    function whiten(src){
        var canvas = document.createElement('canvas');
        var ctx = canvas.getContext('2d');
        var imgObj = new Image();
        imgObj.src = src;
        canvas.width = imgObj.width;
        canvas.height = imgObj.height;
        ctx.drawImage(imgObj, 0, 0);
        var imgPixels = ctx.getImageData(0, 0, canvas.width, canvas.height);
        for(var y = 0; y < imgPixels.height; y++){
            for(var x = 0; x < imgPixels.width; x++){
                var i = (y * 4) * imgPixels.width + x * 4;
                imgPixels.data[i] = imgPixels.data[i] + (255-imgPixels.data[i]);
                imgPixels.data[i + 1] = imgPixels.data[i + 1] + (255-imgPixels.data[i + 1]);
                imgPixels.data[i + 2] = imgPixels.data[i + 2] + (255-imgPixels.data[i + 2]);
            }
        }
        ctx.putImageData(imgPixels, 0, 0, 0, 0, imgPixels.width, imgPixels.height);
        return canvas.toDataURL();
    }}
(jQuery));

