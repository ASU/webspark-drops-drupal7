<?php
/**
 * Created by IntelliJ IDEA.
 * User: bgronek
 * Date: 12/12/14
 * Time: 9:21 AM
 */

?>

<!-- Web Standards - Webspark FlexSlider -->
<div class="container">
    <div class="row row-padding-top row-padding-bottom">
        <div class="col-md-12">
            <div class="flexslider-ws">
                <ul class="slides">
                    <?php foreach($variables['items'] as $item ){?>
                        <?php
                        $thisItem = $item['item'];
                        $thumbnailUri = image_style_url('uto_carousel_thumbnail', $thisItem['uri']);
                        $carouselLink = $thisItem['link'];
                        ?>
                        <li>
                            <div class="col-sm-6 text-center">
                                <a href="<?php print $carouselLink ?>"><img src="<?php print $thumbnailUri ?>" class="img-responsive img-link"></a>
                            </div>
                            <div class="col-sm-6">
                                <h4><a href="<?php print $carouselLink ?>"><?php print $thisItem['title'] ?></a></h4>
                                <p><?php print $thisItem['description']?>
                                </p>
                            </div>
                        </li>
                    <?php } ?>
                    <!--<li>
                        <div class="col-sm-6">
                            <a href="#"><img src="http://placehold.it/600x300" class="img-responsive img-link"></a>
                        </div>
                        <div class="col-sm-6">
                            <h4><a href="#">Connected Treadmills</a></h4>
                            <p>Cupcake ipsum dolor sit amet toffee oat cake gingerbread cake. Hal&shy;vah halvah lollipop lollipop pudding lollipop cupcake biscuit. Apple pie cake chocolate cake marshmallow jelly-o.<br>
                                <a href="#">Continue Reading <i class="fa fa-long-arrow-right" aria-hidden="true"></i></a></p>
                        </div>
                    </li>
                    <li>
                        <div class="col-sm-6">
                            <a href="#"><img src="http://placehold.it/600x300" class="img-responsive img-link"></a>
                        </div>
                        <div class="col-sm-6">
                            <h4><a href="#">Success Story for Websites</a></h4>
                            <p>Cupcake ipsum dolor sit amet toffee oat cake gingerbread cake. Halvah halvah lollipop lollipop pudding lollipop cupcake biscuit. Apple pie cake chocolate cake marshmallow jelly-o.<br>
                                <a href="#">Continue Reading <i class="fa fa-long-arrow-right" aria-hidden="true"></i></a></p>
                        </div>
                    </li>-->
                </ul>
            </div>
        </div>
    </div>
</div>

<script type="text/javascript">
    (function($){
        $(document).ready(function(){
            $('.flexslider-ws').flexslider({
                animation: "slide",
                animationLoop: true,
                controlsContainer: jQuery('#flex-controls-ws'),
                controlNav: false,
                directionNav: true,
                slideshow: true,
                slideshowSpeed: 7000,
                randomize: true,
                startAt: 0 // Could add a random number here to start at
            });
        });
    })(jQuery);
</script>

<?php //dpm($variables) ?>

<?php
// print '<pre>';
//var_dump(get_defined_vars());
//print '</pre>';
?>