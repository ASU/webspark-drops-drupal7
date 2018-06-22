<?php
/**
 * Created by IntelliJ IDEA.
 * User: bgronek
 * Date: 11/15/15
 * Time: 8:46 AM
 */

// get each vocabulary term set and build the list of terms below.
// $entity = null;
// if ( isset($content['bean'])) {
//     $content = $content['bean'][array_keys($content['bean'])[0]];
//     $entity = $content['#entity'];
// }
$searchPath = "/event-search";
$idkPath = "/search-idk";
$searchMode = "event-search"; // possibilities include event-search, idk-search, sidebar-search, link-menu

// if ( isset($entity)) {
//     if (count($entity->field_search_page_path) > 0) {
//         $searchPath = $entity->field_search_page_path[LANGUAGE_NONE][0]['value'];
//     }
//
//     if (count($entity->field_asu_idk_page_path) > 0) {
//         $idkPath = $entity->field_asu_idk_page_path[LANGUAGE_NONE][0]['value'];
//     }
//
//     if (count($entity->field_asu_search_mode) > 0) {
//         $searchMode = $entity->field_asu_search_mode[LANGUAGE_NONE][0]['value'];
//     }
// }

// // get the topics tags.
// $topicVocab = taxonomy_vocabulary_machine_name_load("asu_event_topic");
// $topicTerms = taxonomy_get_tree($topicVocab->vid, 0, null, true);
//
// get the locations tags.
$locationVocab = taxonomy_vocabulary_machine_name_load("asu_news_locations");
$locationTerms = taxonomy_get_tree($locationVocab->vid, 0, null, true);
//
// get the cost tags
$priceVocab = taxonomy_vocabulary_machine_name_load("asu_events_event_price");
$priceTerms = taxonomy_get_tree($priceVocab->vid, 0, null, true);



?>
<div id="<?php print $searchMode?>">
    <?php if ( $searchMode == "event-search" || $searchMode == "event-search-page"){ ?>
        <!-- ASU Events Search -->
        <div class="events-global-search-ctr">
            <div class="events-global-search " id="events-global-search">
                <div class="container">
                    <div class="row">
                        <!-- search box -->
                        <div class="search-box">
                            <div class="search-icon"><i class="fa fa-search"></i></div>
                            <div class="col-md-10 col-sm-12">
                                <!-- search-keyword -->
                                <div class="row search-keyword">
                                    <div class="col-md-10 col-sm-12">
                                        <div class="form-group large-input">
                                            <label for="search-keyword-field">Search Keyword</label>
                                            <input type="text" class="form-control js-search-keyword-field" placeholder="Search events"
                                                   id="search-keyword-field" name="search-keyword-field"/>
                                        </div>
                                    </div>
                                    <div class="col-md-2 hidden-sm hidden-xs">
                                        <button id="btn-event-search" class="btn btn-primary btn-lg btn-block js-btn-event-search">Search</button>
                                    </div>
                                </div>
                                <!-- search options -->
                                <div id="events-search-options" class="js-events-search-options events-search-options clearfix hide">
                                    <div class="hidden-sm hidden-xs">
                                        <div class="column col-md-12 col-sm-12">
                                            <p class="small">Type in keywords or select a few options below to find events around ASU</p>

                                            <div class="column-wide">
                                                <h5>Date</h5>
                                                <a href="#" class="btn btn-secondary btn-block" data-vocabulary="date_range" data-term="today" data-text="Today">Today <i class="fa fa-plus"></i></a>
                                                <a href="#" class="btn btn-secondary btn-block" data-vocabulary="date_range" data-term="tomorrow" data-text="Tomorrow">Tomorrow <i class="fa fa-plus"></i></a>
                                                <a href="#" class="btn btn-secondary btn-block" data-vocabulary="date_range" data-term="this_weekend" data-text="This Weekend">This Weekend <i class="fa fa-plus"></i></a>
                                                <a href="#" class="btn btn-secondary btn-block" data-vocabulary="date_range" data-term="this_week" data-text="This Week">This Week <i class="fa fa-plus"></i></a>
                                                <a href="#" class="btn btn-secondary btn-block" data-vocabulary="date_range" data-term="this_month" data-text="This Month">This Month <i class="fa fa-plus"></i></a>
                                                <a href="#" class="btn btn-secondary btn-block" data-vocabulary="date_range" data-term="all_events" data-text="All Events">All Events <i class="fa fa-plus"></i></a>
                                            </div>
                                            <div class="column-wide">
                                                <h5>Location</h5>
                                                <?php
                                                $locationTermCount = 0;
                                                foreach($locationTerms as $locationTerm){
                                                    if ( ++$locationTermCount > 12 ){
                                                        break;
                                                    }?>
                                                    <a href="#" class="btn btn-secondary btn-block" data-vocabulary="location" data-term="<?php print $locationTerm->machine_name?>" data-text="<?php print $locationTerm->name?>"><?php print $locationTerm->name?> <i class="fa fa-plus"></i></a>
                                                <?php }?>
                                            </div>
                                            <div class="column-wide">
                                                <h5>Cost</h5>
                                                <?php foreach($priceTerms as $priceTerm){?>
                                                    <a href="#" class="btn btn-secondary btn-block" data-vocabulary="asu_events_event_price" data-term="<?php print $priceTerm->machine_name?>" data-text="<?php print $priceTerm->name?>"><?php print $priceTerm->name?> <i class="fa fa-plus"></i></a>
                                                <?php }?>
                                            </div>
                                            <div class="column-wide">
                                              <h5><?php print $vars['topics_title']; ?></h5>
                                                <?php
                                                $topicCount = count($vars['topics']);
                                                for ( $i = 0; $i < ($topicCount < 10 ? $topicCount : 10); $i++ ){{
                                                    $topicTerm = $vars['topics'][$i];
                                                }?>
                                                    <a href="#" class="btn btn-secondary btn-block" data-vocabulary="asu_event_topic" data-term="<?php print $topicTerm->machine_name?>" data-text="<?php print $topicTerm->name?>"><?php print $topicTerm->name?> <i class="fa fa-plus"></i></a>
                                                <?php }?>
                                            </div>
                                            <div class="column-wide">
                                                <h5>&nbsp;</h5>
                                                <?php if ( $topicCount > 10 ){
                                                    for ( $i = 10; $i < $topicCount; $i++ ) {
                                                        $topicTerm = $vars['topics'][$i];
                                                        ?>
                                                        <a href="#" class="btn btn-secondary btn-block" data-vocabulary="asu_event_topic" data-term="<?php print $topicTerm->machine_name?>" data-text="<?php print $topicTerm->name?>"><?php print $topicTerm->name?> <i class="fa fa-plus"></i></a>
                                                        <?php
                                                    }
                                                }?>
                                            </div>
                                        </div>
                                        <button id="filters-toggle" class="btn btn-block filters-toggle"><span>Hide</span> Additional Filters <i
                                                class="fa fa-caret-up"></i></button>
                                    </div>
                                    <!-- mobile -->
                                    <div class="visible-xs-block visible-sm-block">
                                        <div class="col-sm-12">
                                            <div class="event-dropdowns mobile clearfix">

                                                <div class="select-style">
                                                    <i class="fa fa-calendar" aria-hidden="true"></i>
                                                    <select name="date-list" class="js-date-list js-tag-dd dropdown dropdown-alt dropdown-dark">
                                                        <option value="">Date</option>
                                                        <option value="">All Dates</option>
                                                        <option value="today">Today</option>
                                                        <option value="tomorrow">Tomorrow</option>
                                                        <option value="this_weekend">This Weekend</option>
                                                        <option value="this_week">This Week</option>
                                                        <option value="this_month">This Month</option>
                                                        <option value="all_events">All Events</option>
                                                    </select>
                                                    <i class="fa fa-caret-down" aria-hidden="true"></i>
                                                </div>

                                                <div class="select-style">
                                                    <i class="fa fa-map-marker" aria-hidden="true"></i>
                                                    <select name="location-list" class="js-location-list js-tag-dd dropdown dropdown-alt dropdown-dark">
                                                        <option value="">Location</option>
                                                        <option value="">All Locations</option>
                                                        <?php foreach($locationTerms as $locationTerm){?>
                                                            <option value="<?php print $locationTerm->machine_name?>"><?php print $locationTerm->name?></option>
                                                        <?php }?>
                                                    </select>
                                                    <i class="fa fa-caret-down" aria-hidden="true"></i>
                                                </div>

                                                <div class="select-style">
                                                    <i class="fa fa-money" aria-hidden="true"></i>
                                                    <select name="price-list" class="js-price-list js-tag-dd dropdown dropdown-alt dropdown-dark">
                                                        <option value="">Cost</option>
                                                        <option value="">All Costs</option>
                                                        <?php foreach($priceTerms as $priceTerm){?>
                                                            <option value="<?php print $priceTerm->machine_name?>"><?php print $priceTerm->name?></option>
                                                        <?php }?>
                                                    </select>
                                                    <i class="fa fa-caret-down" aria-hidden="true"></i>
                                                </div>
                                            </div>
                                            <hr>
                                            <a href="#" class="btn btn-primary btn-block js-btn-event-search">Explore Events</a>
                                            <a href="#" class="btn btn-primary btn-block js-btn-event-idk">"But IDK!" Get Suggested Events</a>

                                        </div>
                                    </div>
                                    <!-- / mobile -->
                                </div>
                                <!-- /.search-options -->

                            </div>
                        </div>
                        <!-- /.search-box -->
                        <div class="col-md-2 hidden-sm hidden-xs">
                            <div class="idk-button">
                                <button id="btn-event-idk" class="btn btn-primary btn-lg btn-block js-btn-event-idk" aria-labelledby="idk-tooltip">IDK</button>
                                <!--<span class="sr-only">Not sure what you want to do? Let us make some suggestions.</span>-->
                                <div id="idk-tooltip" class="idk-tooltip">
                                    <strong>But I Don't Know!</strong>

                                    <p>Not sure what you want to do? Let us make some suggestions.</p>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <?php if ( $searchMode == "event-search-page"){ ?>
            <div class="container events-search-results space-top-xl space-bot-xl">
                <div class="row clearfix space-bot-lg">
                    <div class="col-xs-12 col-sm-8 space-top-sm">
                        <span class="events-search-filter-pretext"><span class="js-event-count"></span> Events<span class="js-events-for" style="display:none;"> for</span>:</span>
                        <div id="asu-search-term-chicklets" class="js-search-term-chicklets">

                        </div>
                    </div>
                    <div class="col-sm-4 text-right">
                        <div class="view-toggle-text">
                            <span>View</span>
                        </div>

                        <div class="view-toggle-switch">
                            <div class="button-wrap">
                                <div class="button-bg">
                                    <div class="view-list"><i class="fa fa-list-ul"></i></div>
                                    <div class="view-flip"><i class="fa fa-th-large"></i></div>
                                    <div class="button-switch"></div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        <?php } ?>
    <?php } else if ($searchMode == "idk-search"){ ?>
        <div class="idk-options" id="idk-topic-list">
            <div class="hidden-xs">
                <div class="event-topic-list idk-topics clearfix">
                    <ul class="js-events-search-options">
                        <?php foreach ($topicTerms as $topicTerm){
                            $termImg = "";
                            $termAlt = "";
                            if ( count($topicTerm->field_asu_event_topic_image) > 0 && count($topicTerm->field_asu_event_featured_topic) > 0 &&
                                $topicTerm->field_asu_event_featured_topic[LANGUAGE_NONE][0]['value'] == "1" ){
                                $termImgObj = $topicTerm->field_asu_event_topic_image[LANGUAGE_NONE][0];
                                $termImg = image_style_url('asu_events_topic_square', $termImgObj['uri']);
                                if ( count($termImgObj['field_file_image_alt_text']) > 0 ){
                                    $termAlt = $termImgObj['field_file_image_alt_text'][LANGUAGE_NONE][0]['safe_value'];
                                }
                            }else{
                                continue;
                            }
                            ?>
                            <li>
                                <a href="#" class="js-event-idk-term-btn" data-vocabulary="asu_event_topic" data-term="<?php print $topicTerm->machine_name?>" data-text="<?php print $topicTerm->name?>" rel="idk-topic">
                              <span class="image" style="background-image: url('<?php print $termImg?>');"><img
                                      class="img-sr-only" alt="<?php print $termAlt?>" src="<?php print $termImg?>"/></span>
                                    <span class="title"><?php print $topicTerm->name?></span>
                                    <i class="fa fa-plus"></i>
                                </a>
                            </li>
                        <?php } ?>
                    </ul>
                </div>
            </div>
            <div id="idk-search-dropdowns">
                <div class="event-dropdowns idk-search-dropdowns clearfix">

                    <div class="select-style hidden-sm hidden-md hidden-lg">
                        <i class="fa fa-book" aria-hidden="true"></i>
                        <select name="topic-list" class="js-topic-list js-tag-dd dropdown dropdown-alt dropdown-dark">
                            <option value="">All Topics</option>
                            <?php foreach($topicTerms as $topicTerm){?>
                                <option value="<?php print $topicTerm->machine_name?>"><?php print $topicTerm->name?></option>
                            <?php }?>
                        </select>
                        <i class="fa fa-caret-down" aria-hidden="true"></i>
                    </div>

                    <div class="select-style">
                        <i class="fa fa-calendar" aria-hidden="true"></i>
                        <select name="date-list" data-vocabulary="date_range" class="js-date-list js-tag-dd dropdown dropdown-alt dropdown-dark">
                            <option value="-1">Date</option>
                            <option value="All Dates">All Dates</option>
                            <option value="today">Today</option>
                            <option value="tomorrow">Tomorrow</option>
                            <option value="this_weekend">This Weekend</option>
                            <option value="this_week">This Week</option>
                            <option value="this_month">This Month</option>
                            <option value="all_events">All Events</option>
                        </select>
                        <i class="fa fa-caret-down" aria-hidden="true"></i>
                    </div>

                    <div class="select-style">
                        <i class="fa fa-map-marker" aria-hidden="true"></i>
                        <select name="location-list" data-vocabulary="location" class="js-location-list js-tag-dd dropdown dropdown-alt dropdown-dark">
                            <option value="">Location</option>
                            <option value="">All Locations</option>
                            <?php foreach($locationTerms as $locationTerm){?>
                                <option value="<?php print $locationTerm->machine_name?>"><?php print $locationTerm->name?></option>
                            <?php }?>
                        </select>
                        <i class="fa fa-caret-down" aria-hidden="true"></i>
                    </div>

                    <div class="select-style">
                        <i class="fa fa-money" aria-hidden="true"></i>
                        <select name="price-list" data-vocabulary="asu_events_event_price" class="js-price-list js-tag-dd dropdown dropdown-alt dropdown-dark">
                            <option value="">Cost</option>
                            <option value="">All Costs</option>
                            <?php foreach($priceTerms as $priceTerm){?>
                                <option value="<?php print $priceTerm->machine_name?>"><?php print $priceTerm->name?></option>
                            <?php }?>
                        </select>
                        <i class="fa fa-caret-down" aria-hidden="true"></i>
                    </div>
                </div>
            </div>
            <h3 id="empty-search-message" class="empty-search space-bot-lg space-top-xl">Choose options to populate your
                feed</h3>
        </div>

    <?php } else if ( $searchMode == "sidebar-search"){ ?>
        <div class="space-bot-sm">
            <div class="event-dropdowns  clearfix">

                <div class="select-style">
                    <i class="fa fa-calendar" aria-hidden="true"></i>
                    <select name="date-list" data-vocabulary="date_range" class="js-date-list js-tag-dd dropdown dropdown-alt dropdown-dark">
                        <option value="-1">Date</option>
                        <option value="All Dates">All Dates</option>
                        <option value="today">Today</option>
                        <option value="tomorrow">Tomorrow</option>
                        <option value="this_weekend">This Weekend</option>
                        <option value="this_week">This Week</option>
                        <option value="this_month">This Month</option>
                        <option value="all_events">All Events</option>
                    </select>
                    <i class="fa fa-caret-down" aria-hidden="true"></i>
                </div>

                <div class="select-style">
                    <i class="fa fa-map-marker" aria-hidden="true"></i>
                    <select name="location-list" data-vocabulary="location" class="js-location-list js-tag-dd dropdown dropdown-alt dropdown-dark">
                        <option value="">Location</option>
                        <option value="">All Locations</option>
                        <?php foreach($locationTerms as $locationTerm){?>
                            <option value="<?php print $locationTerm->machine_name?>"><?php print $locationTerm->name?></option>
                        <?php }?>
                    </select>
                    <i class="fa fa-caret-down" aria-hidden="true"></i>
                </div>

                <div class="select-style">
                    <i class="fa fa-money" aria-hidden="true"></i>
                    <select name="price-list" data-vocabulary="asu_events_event_price" class="js-price-list js-tag-dd dropdown dropdown-alt dropdown-dark">
                        <option value="">Cost</option>
                        <option value="">All Costs</option>
                        <?php foreach($priceTerms as $priceTerm){?>
                            <option value="<?php print $priceTerm->machine_name?>"><?php print $priceTerm->name?></option>
                        <?php }?>
                    </select>
                    <i class="fa fa-caret-down" aria-hidden="true"></i>
                </div>
            </div>
        </div>
        <div class="event-topic-list home-sidebar clearfix">
            <ul class="js-events-search-options">
                <?php foreach ($topicTerms as $topicTerm){
                    $termImg = "";
                    $termAlt = "";
                    if ( count($topicTerm->field_asu_event_topic_image) > 0 && count($topicTerm->field_asu_event_featured_topic) > 0 &&
                        $topicTerm->field_asu_event_featured_topic[LANGUAGE_NONE][0]['value'] == "1" ){
                        $termImgObj = $topicTerm->field_asu_event_topic_image[LANGUAGE_NONE][0];
                        $termImg = image_style_url('asu_events_topic_square', $termImgObj['uri']);
                        if ( count($termImgObj['field_file_image_alt_text']) > 0 ){
                            $termAlt = $termImgObj['field_file_image_alt_text'][LANGUAGE_NONE][0]['safe_value'];
                        }
                    }else{
                        continue;
                    }
                    ?>
                    <li>
                        <a class="js-event-idk-term-btn" data-vocabulary="asu_event_topic" data-term="<?php print $topicTerm->machine_name?>" data-text="<?php print $topicTerm->name?>" href="#">
                        <span class="image" style="background-image: url('<?php print $termImg?>');"><img
                                class="img-sr-only" alt="<?php print $termAlt?>" src="<?php print $termImg?>"/></span>
                            <span class="title"><?php print $topicTerm->name?></span>
                            <i class="fa fa-plus"></i>
                        </a>
                    </li>
                <?php } ?>


            </ul>
        </div>
    <?php }else if ( $searchMode == "link-list"){ ?>
        <div class="browse-events hidden-xs hidden-sm">
            <div class="container">
                <div class="row js-events-search-options">
                    <ul class="browse-events-list col-md-15">
                        <li class="event-title"><h2><i class="fa fa-calendar"></i>Date</h2></li>
                        <li><a href="#" class="js-event-idk-term-btn" data-vocabulary="date_range" data-term="today" data-text="Today">Today</a></li>
                        <li><a href="#" class="js-event-idk-term-btn" data-vocabulary="date_range" data-term="tomorrow" data-text="Tomorrow">Tomorrow</a></li>
                        <li><a href="#" class="js-event-idk-term-btn" data-vocabulary="date_range" data-term="this_weekend" data-text="This Weekend">This Weekend</a></li>
                        <li><a href="#" class="js-event-idk-term-btn" data-vocabulary="date_range" data-term="this_week" data-text="This Week">This Week</a></li>
                        <li><a href="#" class="js-event-idk-term-btn" data-vocabulary="date_range" data-term="this_month" data-text="This Month">This Month</a></li>
                        <li><a href="#" class="js-event-idk-term-btn" data-vocabulary="date_range" data-term="all_events" data-text="All Events">All Events</a></li>
                    </ul>
                    <ul class="browse-events-list col-md-15">
                        <li class="event-title"><h2><i class="fa fa-map-marker"></i>Location</h2></li>
                        <?php
                        $locationTermCount = 0;
                        foreach($locationTerms as $locationTerm){
                            if ( ++$locationTermCount > 12 ){
                                break;
                            }?>
                            <li><a href="#" class="js-event-idk-term-btn" data-vocabulary="location" data-term="<?php print $locationTerm->machine_name?>" data-text="<?php print $locationTerm->name?>"><?php print $locationTerm->name?></a></li>
                        <?php }?>
                        <!--<li><a href="#">ASU Tempe</a></li>
                        <li><a href="#">ASU Downtown</a></li>
                        <li><a href="#">ASU West</a></li>
                        <li><a href="#">ASU Polytechnic</a></li>
                        <li><a href="#">ASU Skysong</a></li>-->
                    </ul>
                    <ul class="browse-events-list col-md-15">
                        <li class="event-title"><h2><i class="fa fa-money"></i>Cost</h2></li>
                        <?php foreach($priceTerms as $priceTerm){?>
                            <li><a href="#" class="js-event-idk-term-btn" data-vocabulary="asu_events_event_price" data-term="<?php print $priceTerm->machine_name?>" data-text="<?php print $priceTerm->name?>"><?php print $priceTerm->name?></a></li>
                        <?php }?>
                        <!--<li><a href="#">Free</a></li>
                        <li><a href="#">Under &#36;10</a></li>
                        <li><a href="#">Under &#36;25</a></li>
                        <li><a href="#">&#36;25 and More</a></li>-->
                    </ul>
                    <ul class="browse-events-list col-md-15">
                        <li class="event-title"><h2><i class="fa fa-book"></i>Topic</h2></li>
                        <?php
                        $topicCount = count($topicTerms);
                        for ( $i = 0; $i < ($topicCount < 10 ? $topicCount : 10); $i++ ){{
                            $topicTerm = $topicTerms[$i];
                        }?>
                            <li><a class="js-event-idk-term-btn" data-vocabulary="asu_event_topic" data-term="<?php print $topicTerm->machine_name?>"
                                   data-text="<?php print $topicTerm->name?>" href="#"><?php print $topicTerm->name?></a></li>
                        <?php }?>
                    </ul>
                    <?php if ( $topicCount > 10 ){?>
                        <ul class="browse-events-list col-md-15">
                            <li class="event-title"><h2>&nbsp;</h2></li>

                            <?php for ( $i = 10; $i < $topicCount; $i++ ) {
                                $topicTerm = $topicTerms[$i];
                                ?>
                                <li><a class="js-event-idk-term-btn" data-vocabulary="asu_event_topic" data-term="<?php print $topicTerm->machine_name?>"
                                       data-text="<?php print $topicTerm->name?>" href="#"><?php print $topicTerm->name?></a></li>
                                <?php
                            }?>
                        </ul>
                    <?php }?>
                </div>
            </div>
        </div>

    <?php } ?>

</div>

<script>
    if (typeof(EventSearchBarInit) == 'undefined') {
        window["EventSearchBarInit"] = [{
            id: "<?php print $searchMode?>",
            searchPath: "<?php print $searchPath?>",
            searchMode: "<?php print $searchMode?>",
            idkPath: "<?php print $idkPath?>"
        }];
    } else {
        EventSearchBarInit.push({
            id: "<?php print $searchMode?>",
            searchPath: "<?php print $searchPath?>",
            searchMode: "<?php print $searchMode?>",
            idkPath: "<?php print $idkPath?>"
        });
    }
</script>
