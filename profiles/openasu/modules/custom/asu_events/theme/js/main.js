    jQuery(document).ready(function() {

        eventsGlobalSearch = new events_global_search();

        var idkOptionsBar = jQuery('#idk-options-bar');
        // Sticky IDK Filters ------------------------------------------------------------------------

        if (idkOptionsBar.length) {

            idkOptionsBar.affix({
                offset: {
                    top: idkOptionsBar.offset().top - 350
                }
            });

        }

        // IDK Search Options ------------------------------------------------------------------------------
        jQuery('[rel="idk-topic"]').click(function() {
            // Hide existing list
            jQuery('.event-list').fadeOut(100);
            // Add class to show filters are open
            jQuery('#idk-topic-list').addClass('open');
            // Update formatting of topic pill
            jQuery(this).toggleClass('selected').attr('aria-selected', 'true');
            if (jQuery(this).hasClass('selected')) {
                jQuery(this).attr('aria-selected', 'true');
            } else {
                jQuery(this).attr('aria-selected', 'false');
            }
            jQuery(this).find('i').toggleClass('fa-plus').toggleClass('fa-close');
            // Remove Empty Search Message
            jQuery('#empty-search-message').addClass('hide');
            // Scroll up to top of topics
            jQuery('html, body').animate({
                scrollTop: (jQuery("#idk-topic-list").offset().top - 93)
            }, 500);
            // If none are selected, hide list

            // If at least one is selected, get & show event list
            jQuery('#idk-event-list').removeClass('hide');
            jQuery('#idk-options-bar').removeClass('closed');
            jQuery('.event-list').removeClass('hide').fadeIn('slow');
        });
        // Event Detail Map --------------------------------------------------------------------------------
        if (jQuery('#event-map-canvas').length) {
            function map_recenter(latlng, offsetx, offsety) {
                var point1 = map.getProjection().fromLatLngToPoint(
                    (latlng instanceof google.maps.LatLng) ? latlng : map.getCenter()
                );
                var point2 = new google.maps.Point(
                    ((typeof(offsetx) === 'number' ? offsetx : 0) / Math.pow(2, map.getZoom())) || 0,
                    ((typeof(offsety) === 'number' ? offsety : 0) / Math.pow(2, map.getZoom())) || 0
                );
                map.setCenter(map.getProjection().fromPointToLatLng(new google.maps.Point(
                    point1.x - point2.x,
                    point1.y + point2.y
                )));
            }

            // Parking Modal ------------------------------------------------
            //jQuery('[rel="event-parking"]').click(function() {
            //  console.log('yup');
            //});

            // Google Map ---------------------------------------------------
            var targetLocation = new google.maps.LatLng(33.464080, -111.923186),
                locationName = 'ASU Skysong',
                mapCenter = targetLocation,
                mapStyles = [
                    //{"featureType":"all","elementType": "labels","stylers": [{"visibility": "off"}]},

                    {
                        "featureType": "landscape",
                        "stylers": [{
                            "hue": "#FFBB00"
                        }, {
                            "saturation": -43.400000000000006
                        }, {
                            "lightness": 37.599999999999994
                        }, {
                            "gamma": 1
                        }]
                    }, {
                        "featureType": "road.highway",
                        "stylers": [{
                            "hue": "#FFC200"
                        }, {
                            "saturation": -61.8
                        }, {
                            "lightness": 65.599999999999994
                        }, {
                            "gamma": 1
                        }]
                    }, {
                        "featureType": "road.arterial",
                        "stylers": [{
                            "hue": "#FF0300"
                        }, {
                            "saturation": -100
                        }, {
                            "lightness": 61.19999999999999
                        }, {
                            "gamma": 1
                        }]
                    }, {
                        "featureType": "road.local",
                        "stylers": [{
                            "hue": "#FF0300"
                        }, {
                            "saturation": -100
                        }, {
                            "lightness": 52
                        }, {
                            "gamma": 1
                        }]
                    }, {
                        "featureType": "water",
                        "stylers": [{
                            "hue": "#0078FF"
                        }, {
                            "saturation": -43.200000000000003
                        }, {
                            "lightness": 8.4000000000000057
                        }, {
                            "gamma": 1
                        }]
                    }, {
                        "featureType": "poi",
                        "stylers": [{
                            "hue": "#FFC200"
                        }, {
                            "saturation": -20.0989010989011234
                        }, {
                            "lightness": 61.200000000000017
                        }, {
                            "gamma": 1
                        }]
                    }
                ],
                mapOptions = {
                    // How zoomed in you want the map to start at (always required)
                    zoom: 15,
                    disableDefaultUI: true,
                    scrollwheel: false,
                    draggable: false,
                    panControl: false,

                    // The latitude and longitude to center the map (always required)
                    center: mapCenter,

                    // Map Styles
                    styles: mapStyles
                },
                mapMarkerIcon = {
                    url: '/img/now/asu-map-marker-selected.png',
                    size: new google.maps.Size(100, 100),
                    origin: new google.maps.Point(0, 0),
                    anchor: new google.maps.Point(20, 20),
                    scaledSize: new google.maps.Size(40, 40)
                };

            var map = new google.maps.Map(document.getElementById('event-map-canvas'), mapOptions);
            var marker = new google.maps.Marker({
                position: targetLocation,
                map: map,
                icon: mapMarkerIcon
            });
            google.maps.event.addListenerOnce(map, "projection_changed", function() {
                map_recenter(targetLocation, 230, 0);
            });

        } // end event detail map
        // event search filter
        /*jQuery('.event-search-filter').on('click',function(e){
            e.preventDefault();
            jQuery(this).remove();
        });*/

        // placeholder
        // jQuery('#search-keyword-field').placeholder();


    }); //end document ready



    // Event Global Search Bar.
    var events_global_search = function() {
        var $this = this;
        var searchBar; // grandparent.
        var searchBox; // parent.
        var searchOpt;
        var searchTextBox;
        var idkButton;
        var idkOptionsBar;
        var tooltip;
        var filterToggle;
        var filterCol;
        var filterBtn;
        this.has_bar;

        this.show_search_option = function() {
            searchOpt.removeClass('hide');
            jQuery('body').css('overflow-y', 'hidden');
            var currentWidth = $this.get_current_width();
            if (currentWidth < 768) {
                searchOpt.css({
                    'height': '245px',
                    'overflow-y': 'scroll',
                    'padding-top': '0',
                    'top': '55px'
                });
            }
        }
        this.hide_search_option = function() {
            jQuery('body').css('overflow-y', 'initial');
            searchOpt.removeAttr('style').addClass('hide');
        }
        this.show_tooltip = function() {
            if (searchBar.hasClass('affix')) {
                tooltip.addClass('bottom').animate({
                    'top': '60px',
                    'opacity': '1'
                }, {
                    duration: 300,
                    queue: false
                });
            }
            if (searchBar.hasClass('affix-top')) {
                var barOffset = searchBar.offset().top;
                var htmlTop = jQuery(document).scrollTop();

                if ((barOffset - htmlTop) < 110) {
                    tooltip.addClass('bottom').animate({
                        'top': '60px',
                        'opacity': '1'
                    }, {
                        duration: 300,
                        queue: false
                    });
                } else {
                    jQuery('#content').css({
                        'z-index': 1500
                    });
                    tooltip.addClass('top').animate({
                        'top': '-110px',
                        'opacity': '1'
                    }, {
                        duration: 300,
                        queue: false
                    });
                }
            }
        }
        this.hide_tooltip = function() {
            tooltip.animate({
                'top': '-25px',
                'opacity': '0'
            }, {
                duration: 300,
                queue: false,
                complete: function() {
                    jQuery('#content').css({
                        'z-index': 0
                    });
                    jQuery(this).removeClass('top bottom');
                }
            });
        }
        this.toggle_filter = function() {
            if (filterToggle.hasClass('open')) {
                filterToggle.find('span').text('Hide');
                filterCol.slideDown();
            } else {
                filterToggle.find('span').text('Show');
                filterCol.slideUp();
            }
            filterToggle.toggleClass('open');
            filterToggle.find('i').toggleClass('fa-caret-up').toggleClass('fa-caret-down');
        }
        this.toggle_filter_button = function(thisBtn) {

            thisBtn.toggleClass('selected');

            if (thisBtn.hasClass('selected')) {
                thisBtn.attr('aria-selected', 'true');
            } else {
                thisBtn.attr('aria-selected', 'false');
            }
            thisBtn.find('i').toggleClass('fa-plus').toggleClass('fa-close');

        }
        this.get_current_width = function() {
            return window.innerWidth || document.body.clientWidth || document.documentElement.clientWidth;
        }
        var init_affix = function() {
            searchBar.affix({
                offset: {
                    top: searchBar.offset().top
                }
            });
            searchBar.on('affix-top.bs.affix', function(e) {

                var currentWidth = $this.get_current_width();

                if (currentWidth < 768 && searchTextBox.is(':focus')) {
                    return false;
                }
            });
        }
        var init_search_option = function() {
            searchBox
                .on('click', function(e) {
                    e.stopPropagation();
                })
                .on('touchstart', function(e) {
                    e.stopPropagation();
                });

            searchTextBox
                .focusin(function(event) {
                    $this.show_search_option();
                })
                .focusout(function(event) {
                    jQuery('body').css('overflow-y', 'initial');
                    searchOpt.removeAttr('style');
                });

            jQuery(document).on('click', function(e) {
                $this.hide_search_option();
            });
            jQuery(document).on('touchstart', function(e) {
                $this.hide_search_option();
            });

        }
        var init_idk_button = function() {
            idkButton
                .on('mouseenter', function(e) {
                    $this.show_tooltip();
                })
                .on('mouseleave', function(e) {
                    $this.hide_tooltip();
                });
        }
        var init_filter_toggle = function() {
            filterToggle.click(function(event) {
                $this.toggle_filter();
            });
        }
        var init_filter_buttons = function() {
            filterBtn.on('click', function() {
                $this.toggle_filter_button(jQuery(this));
            });
        }
        var __const = function() {
            searchBar = jQuery('#events-global-search');
            $this.has_bar = searchBar.length > 0;
            if ($this.has_bar) {
                searchBox = jQuery('#events-global-search .search-box');
                searchOpt = jQuery('#events-search-options');
                searchTextBox = jQuery('#search-keyword-field');
                idkButton = jQuery('#events-global-search .idk-button button');
                idkOptionsBar = jQuery('#idk-options-bar');
                tooltip = jQuery('#idk-tooltip');
                filterToggle = jQuery('#filters-toggle');
                filterCol = jQuery('#events-search-options .column');
                filterBtn = jQuery('#events-search-options .column .btn');

                init_affix();
                init_search_option();
                init_idk_button();
                init_filter_toggle();
                init_filter_buttons();
            }
        }();
    }

    // jQuery(window).load(function() {
    //     // Event hero vertical.
    //     var eventHeroNav = jQuery('.event-hero-slider-nav');

    //     // vertical at 992px bug.
    //     eventHeroNav.slick({
    //             slidesToShow: 1,
    //             slidesToScroll: 1,
    //             dots: false,
    //             centerMode: false,
    //             focusOnSelect: true,
    //             arrows: false,
    //             variableWidth: true,
    //             vertical: false,
    //             infinite: true,
    //             mobileFirst: true,
    //             responsive: [{
    //                 breakpoint: 991,
    //                 settings: {
    //                     vertical: true,
    //                     centerMode: false,
    //                     variableWidth: false,
    //                     slidesToShow: 3,
    //                     slidesToScroll: 3,
    //                 }
    //             }, ]
    //         })
    //         .on('beforeChange', function(e, slick, current, next) {
    //             eventHeroNav.find('.slick-slide[data-slick-index="' + current + '"]').removeClass('selected');
    //             eventHeroNav.find('.slick-slide[data-slick-index="' + next + '"]').addClass('selected');
    //         });
    //     eventHeroNav.find('.slick-slide[data-slick-index="0"]').addClass('selected');

    // });