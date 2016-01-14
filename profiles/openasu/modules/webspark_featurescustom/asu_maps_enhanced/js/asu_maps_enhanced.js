/**
 * ASU Enhanced Maps
 *
 * ASU Enhanced Map JS
 * - Enables campus selection bar at the top of map
 *
 * @author Colton Testamarck ( colt@asu.edu )
 */
(function ($) {
    Drupal.behaviors.asu_maps_enhanced = {
        attach: function (context, settings) {
            //document.domain = 'asu.edu';
            var campus = 'TEMPE';

            if (settings.hasOwnProperty('asu_maps_enhanced')) {
                var map_settings = settings.asu_maps_enhanced;
                var campus = map_settings.campus;
            }

            $('.enhanced-map-nav .' + campus).addClass('cHover');


            $(document).on('click tap touch','.nav-left li',function() {
                var c = $(this).html();
                var mc = '?' + getMC(c);
                var mc_reg = /\?(mc.*)/;

                var currentSrc = $('#embed-iframe').attr('src');
                var newSrc = currentSrc.replace(mc_reg, mc);

                if (currentSrc != newSrc) {
                    $('#embed-iframe').attr('src', newSrc);
                }

                $('.nav-left>li.cHover').removeClass('cHover');
                $(this).addClass('cHover');


            });
        }
    }
}(jQuery));

function getMC(campus) {
    var ref = null;

    switch (campus) {
        case 'Polytechnic':
            ref = "mc/33.30463351165877,-111.67764695106507?z/16";
            break;
        case 'Downtown Phoenix':
            ref = "mc/33.4517422046421,-112.06978201586912?z/16";
            break;
        case 'West':
            ref = "mc/33.60560202626335,-112.16131285054018?z/16";
            break;
        case 'Research Park':
            ref = "mc/33.34149389022663,-111.89817340740967?z/16";
            break;
        case 'Skysong':
            ref = "mc/33.46387500000001,-111.92400399999997?z/17";
            break;
        case 'Lake Havasu':
            ref = "mc/34.472362999999994,-114.32183099999997?z/18";
            break;
        case 'Tempe':
        default:
            ref = "mc/33.42184849843031,-111.9283177883301?z/15";
            break;
    }

    return ref;
}

function feedback(){
    window.open('https://webapp4.asu.edu/feedback/feedback/map', '_blank').focus();
}