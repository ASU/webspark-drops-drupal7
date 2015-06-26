<?php

/**
 * @file
 * Bartik's theme implementation to display a single Drupal page.
 *
 * The doctype, html, head, and body tags are not in this template. Instead
 * they can be found in the html.tpl.php template normally located in the
 * core/modules/system directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 * - $
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 * - $hide_site_name: TRUE if the site name has been toggled off on the theme
 *   settings page. If hidden, the "element-invisible" class is added to make
 *   the site name visually hidden, but still accessible.
 * - $hide_site_slogan: TRUE if the site slogan has been toggled off on the
 *   theme settings page. If hidden, the "element-invisible" class is added to
 *   make the site slogan visually hidden, but still accessible.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $main_menu_expanded (array): An array containing 2 depths of the Main menu links
 *   for the site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on
 *   the menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node entity, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['content']: The main content of the current page.
 *
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see template_process()
 * @see bartik_process_page()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */

// Set node array in one place:
if (is_numeric(arg(1))) {
  $node_info = $variables['page']['content']['system_main']['nodes'][arg(1)];
}
else {
  $node_info = array();
}

//dpm(get_defined_vars());
?>

<div id="page-wrapper">
  <div id="page">

    <!-- Page Header -->
    <header id="header">
      <div class="container">
        <div class="row">
          <div class="column col-md-12">
            <?php print render($page['header']); ?>
            <?php if ($site_name): ?>
              <h1 class="header__sitename<?php if ($hide_site_name) { print ' element-invisible'; } ?>">
                <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span><?php print $site_name; ?></span></a>
              </h1>
            <?php endif; ?>
          </div>
        </div>
      </div>
    </header>
    <!-- /.header -->


    <!-- Nav Bar -->
    <div id="ASUNavMenu" class="navmenu">
      <div class="container">
        <!--Commented to work with mega menu-->
        <nav class="navbar-collapse collapse">
          <?php print render($page['menu']); ?>
        </nav>
        <!-- /#navbar -->
      </div>
      <!-- /.container -->
    </div>
    <!-- /.navmenu -->


    <!-- PROGRAM DECIDER - UNDERGRADUATE or GRADUATE -->
    <?php if (isset($node_info['field_asu_degree_program']['#items'][0]['value'])): ?>
	     <?php $program_decider_value = ($node_info['field_asu_degree_program']['#items'][0]['value']); ?>
	      <?php if ($program_decider_value == 'undergrad'): ?>
		        <!-- undergraduate formatting -->

            <!-- Page Main Undergraduate -->
            <div id="main-wrapper" class="clearfix">
              <div id="main" class="clearfix">
                <a id="main-content"></a>

                <div class="asu-degree-banner-image"
                     style="background-image:url(/sites/default/files/<?php echo $node_info['field_asu_banner_image']['#items'][0]['filename']; ?>)">
                  <div class="container">
                    <div class="row">
                      <div class="col-md-12">
                        <?php if (($no_panels || $always_show_page_title) && $title): ?>
                          <h1 id="page-title" class="title">
                            <?php print $title; ?>
                            <?php if (isset($node_info['field_asu_degree']['#items'][0]['value'])): ?>
                              (<?php print render($node_info['field_asu_degree']['#items'][0]['value']); ?>)
                            <?php endif; ?>
                            <!-- Displaying 'Accelerated Degree' field if true, displaying nothing if false -->
                            <?php if (isset($node_info['field_asu_degree_acc_program']['#items'][0]['value'])): ?>
                              <?php $accelerated_degree_value = ($node_info['field_asu_degree_acc_program']['#items'][0]['value']); ?>
                              <?php if ($accelerated_degree_value == '1'): ?>
                                <br>
                                <i class="fa fa-location-arrow"></i>
                                <span class="asu-degrees-program-flag">Accelerated Program</span>
                              <?php else: ?>
                                <!-- do nothing, it's not an accelerated degree -->
                              <?php endif; ?>
                            <?php endif; ?>
                            <!-- Displaying 'Concurrent Degree' field if true, displaying nothing if false -->
                            <?php if (isset($node_info['field_asu_degree_conc_program']['#items'][0]['value'])): ?>
                              <?php $concurrent_degree_value = ($node_info['field_asu_degree_conc_program']['#items'][0]['value']); ?>
                              <?php if ($concurrent_degree_value == '1'): ?>
                                <?php if ($accelerated_degree_value == '1'): ?>
                                  <i class="fa fa-star"></i>
                                  <span class="asu-degrees-program-flag">Concurrent Program</span>
                                <?php else: ?>
                                  <br>
                                  <i class="fa fa-star"></i>
                                  <span class="asu-degrees-program-flag">Concurrent Program</span>
                                <?php endif; ?>
                              <?php else: ?>
                                <!-- do nothing, it's not a concurrent degree -->
                              <?php endif; ?>
                            <?php endif; ?>
                            <!-- Displaying 'New Degree' field if true, displaying nothing if false -->
                            <?php if (isset($node_info['field_asu_degree_new_program']['#items'][0]['value'])): ?>
                              <?php $new_degree_value = ($node_info['field_asu_degree_new_program']['#items'][0]['value']); ?>
                              <?php if ($new_degree_value == '1'): ?>
                                <?php if (($accelerated_degree_value || $concurrent_degree_value) == '1'): ?>
                                  <i class="fa fa-retweet"></i>
                                  <span class="asu-degrees-program-flag">New Program</span>
                                <?php else: ?>
                                  <br>
                                  <i class="fa fa-retweet"></i>
                                  <span class="asu-degrees-program-flag">New Program</span>
                                <?php endif; ?>
                              <?php else: ?>
                                <!-- do nothing, it's not a new degree -->
                              <?php endif; ?>
                            <?php endif; ?>
                          </h1>
                        <?php endif; ?>
                      </div>
                    </div>
                  </div>
                </div>
              </div>
              <div id="top-content" class="column container">

                <?php if ($messages): ?>
                  <div id="messages">
                    <?php print $messages; ?>
                  </div>
                <?php endif; ?>

                <?php if ($tabs): ?>
                  <div id="tabs">
                    <?php print render($tabs); ?>
                  </div>
                <?php endif; ?>

                <?php if ($action_links): ?>
                  <div id="action-links">
                    <?php print render($action_links); ?>
                  </div>
                <?php endif; ?>
              </div>
              <!-- /#top-content -->

              <!--Start degree content-->
              <?php print theme('breadcrumb', array('breadcrumb' => drupal_get_breadcrumb())); ?>
              <div class="container">
                <?php if (isset($node_info['field_asu_degree_short_desc']['#items'][0]['safe_value'])): ?>
                  <div class="asu-degree-short-description">
                    <?php print render($node_info['field_asu_degree_short_desc']['#items'][0]['safe_value']); ?>
                    <div class="asu-degree-read-more">
                      <a href="#degree-collapse" data-toggle="collapse" aria-expanded="false">Read More</a>
                    </div>
                    <div id="degree-collapse" class="collapse">
                      <?php if (isset($node_info['body'])): ?>
                        <?php print render($node_info['body']); ?>
                      <?php endif; ?>
                    </div>
                  </div>

                <?php elseif (isset($node_info['body'])): ?>
                  <?php print render($node_info['body']); ?>
                <?php endif; ?>
                  <div class="row space-bot-lg">
                    <div class="col-sm-6 col-md-4 space-bot-md">
                      <a href="#asu-rfi-form-data" id="take-me-to-rfi" class="btn btn-gold btn-block btn-lg">Request information</a>
                    </div>
                    <div class="col-sm-6 col-md-4 space-bot-md">
                      <a href="https://visit.asu.edu/"
                         class="btn btn-gold btn-block btn-lg">Schedule a visit</a>
                    </div>
                    <div class="col-sm-6 col-md-4 space-bot-md">
                      <a href="http://www.asu.edu/enroll/apply"
                         class="btn btn-gold btn-block btn-lg">How and when to apply</a>
                    </div>
                  </div>
              </div>
              <div class="asu-degree-grey-section">
                <div class="container">
                  <div class="row">
                    <div class="col-sm-6 col-md-4">
                      <h2>Degree Offered</h2>

                      <div class="asu-degree-page-degree-offered">
                        <p>
                          <?php if (isset($node_info['field_asu_degree_awarded']['#items'][0]['value'])): ?>
                            <?php print render($node_info['field_asu_degree_awarded']['#items'][0]['value']); ?>
                          <?php endif; ?>
                          <?php if (isset($node_info['field_asu_degree']['#items'][0]['value'])): ?>
                            (<?php print render($node_info['field_asu_degree']['#items'][0]['value']); ?>)
                          <?php endif; ?><br>

                          <?php if (isset($node_info['field_asu_college']['#items'][0]['value'])): ?>
                            <?php if (isset($node_info['field_asu_college_url']['#items'][0]['url'])): ?>
                              <a href="<?php echo $node_info['field_asu_college_url']['#items'][0]['url']; ?>" target="_blank">
                            <?php endif; ?>
                            <?php print render($node_info['field_asu_college']['#items'][0]['value']); ?>
                            <?php if (isset($node_info['field_asu_college_url']['#items'][0]['url'])): ?>
                              </a>
                            <?php endif; ?>
                          <?php endif; ?>
                        </p>
                      </div>
                      <p>
                        <b>Location</b><br>
                        <?php
                          if (isset($node_info['field_asu_degree_campus']['#items'][0]['value'])) {
                            $c = count($node_info['field_asu_degree_campus']['#items']) - 1;
                            $i = 0;
                            foreach ($node_info['field_asu_degree_campus']['#items'] as $campus) {
                              $a = true;
                              switch ($campus['value']) {
                                case 'Tempe':
                                  echo '<a href="//www.asu.edu/tour/tempe/index.html">'.$campus['value'].'</a>';
                                  break;
                                case 'Polytechnic':
                                  echo '<a href="//www.asu.edu/tour/polytechnic/index.html">'.$campus['value'].'</a>';
                                  break;
                                case 'Downtown':
                                  echo '<a href="//www.asu.edu/tour/downtown/index.html">'.$campus['value'].'</a>';
                                  break;
                                case 'West':
                                  echo '<a href="//www.asu.edu/tour/west/index.html">'.$campus['value'].'</a>';
                                  break;
                                case 'Lake Havasu':
                                  echo '<a href="//havasu.asu.edu/">'.$campus['value'].'</a>';
                                  break;
                                case 'Eastern Arizona College':
                                  echo '<a href="//transfer.asu.edu/eac">'.$campus['value'].'</a>';
                                  break;
                                case 'Online':
                                  echo '<a href="//asuonline.asu.edu/">'.$campus['value'].'</a>';
                                  break;
                                //Check ASU Feeds Parser.  The campus being used doesn't exist.
                                default:
                                  echo 'Campus Not Found';
                                  //$a = false;
                                  echo '<!--'.$campus['value'].'-->';
                                  break;
                              }
                              if($i < $c && $a) {
                                echo ', ';
                              }
                              ++$i;
                            }
                          }
                        ?>
                      </p>

                      <h2>What is a Major Map?</h2>

                      <p>A major map outlines a major’s critical requirements, elective
                        and required courses, and optimal course sequencing to help
                        students stay on the right track to graduation.</p>
                      <?php if (isset($node_info['field_asu_degree_major_map_url'])): ?>
                        <p><a
                            href="<?php echo $node_info['field_asu_degree_major_map_url']['#items'][0]['url']; ?>"
                            target="_blank">View Major Map</a></p>
                      <?php endif ?>

                      <div class="asu-degree-subplans">
                      <?php if (isset($node_info['field_asu_degree_subplan_url']['#items'])): ?>
                        <div class='asu-degree-sublplans'><p><b>Subplans</b><br/></div>
                          <?php foreach ($node_info['field_asu_degree_subplan_url']['#items'] as $sp) {
                            if ($sp['title'] != $sp['url']) {
                              echo '<a href="'.$sp['url'].'">'.$sp['title'].'</a><br/>';
                            }
                            else {
                              echo '<a href="'.$sp['url'].'">Online</a><br/>';
                            }
                          }
                        echo '</p>';
                      endif ?>
                      </div>
                    </div>
                    <div class="col-sm-6 col-md-4">
                      <h2>Application Requirements</h2>

                      <p>
                        All students are required to meet general university admission
                        requirements.<br>
                        <a href="https://students.asu.edu/freshman">Freshman</a><br>
                        <a href="https://transfer.asu.edu/">Transfer</a><br>
                        <a
                          href="https://students.asu.edu/international">International</a><br>
                        <a href="https://students.asu.edu/readmission">Readmission</a><br>
                        <?php if (isset($node_info['field_asu_degree_additional_req']['#items'][0]['url'])): ?>
                          <a href="<?php echo $node_info['field_asu_degree_additional_req']['#items'][0]['url']; ?>">Additional Requirements</a>
                        <?php endif ?>
                      </p>
                    </div>
                    <div class="col-sm-6 col-md-4">
                      <h2>Affording College</h2>

                      <p>
                        <?php if (isset($node_info['field_scholarship_link']['#items'][0]['url'])): ?>
                          <a href="<?php echo $node_info['field_scholarship_link']['#items'][0]['url'] ?>">Scholarships</a><br>
                        <?php else: ?>
                          <a href="<?php echo 'https://scholarships.asu.edu/colleges' ?>">Scholarships</a><br>
                        <?php endif ?>
                        Find and apply for relevant scholarships.
                      </p>

                      <?php if (isset($node_info['field_asu_degree_wue_available']['#items'][0]['value']) && $node_info['field_asu_degree_wue_available']['#items'][0]['value'] == 1): ?>
                        <p>
                          <?php if (isset($node_info['field_asu_degree_wue_link']['#items'][0]['url'])): ?>
                            <a href="<?php echo $node_info['field_asu_degree_wue_link']['#items'][0]['url'] ?>">WUE eligible program</a><br>
                          <?php else: ?>
                            <a href="<?php echo 'https://students.asu.edu/admission/wue' ?>">WUE eligible program</a><br>
                          <?php endif ?>
                          Undergraduate students from western states who enroll in this
                          program are eligible for a discounted tuition rate.
                        </p>
                      <?php endif ?>

                      <p>
                        <?php if (isset($node_info['field_financial_aid_link']['#items'][0]['url'])): ?>
                          <a href="<?php echo $node_info['field_financial_aid_link']['#items'][0]['url'] ?>">Financial Aid</a><br>
                        <?php else: ?>
                          <a href="<?php echo 'https://students.asu.edu/financialaid' ?>">Financial Aid</a><br>
                        <?php endif ?>
                        ASU has many financial aid options. Almost everyone, regardless
                        of income, can qualify for some form of financial aid. In fact,
                        more than 70 percent of all ASU students receive some form of
                        financial assistance every year.
                      </p>
                    </div>
                  </div>
                </div>
              </div>

              <div class="container">
                <?php print render($page['asu_degree_marketing']); ?>
              </div>

              <div class="container space-top-xl space-bot-xl">
                <div class="col-md-8">
                  <?php if (isset($node_info['field_asu_degree_career_opps'])): ?>
                    <h2>Career Outlook</h2>
                    <?php print render($node_info['field_asu_degree_career_opps']); ?>
                  <?php endif; ?>
                  <?php if (isset($node_info['field_asu_degree_example_careers'])): ?>
                    <h2>Example Careers</h2>
                    <?php print render($node_info['field_asu_degree_example_careers']); ?>
                  <?php endif; ?>
                </div>
                <?php if (isset($node_info['field_asu_degree_relatedprograms'])): ?>
                  <div class="col-md-4">
                    <div class="pane-menu-tree">
                      <h4>Related Programs</h4>
                      <?php for ($it = 0; $it < 1000; $it++) {
                        if (isset($node_info['field_asu_degree_relatedprograms'][$it]['#markup'])) {
                          $rp_result = $node_info['field_asu_degree_relatedprograms'][$it]['#markup'];
                        }
                        if (!empty($rp_result)) {
                          print $rp_result;
                          unset($rp_result);
                        } else {
                          break 1;
                        }
                      ?>
                      <br>
                      <?php } ?>
                    </div>
                  </div>
                <?php endif; ?>

                  <div class="col-md-4">
                    <?php print render($page['asu_degree_sidebar']); ?>
                  </div>
                </div>

                <div class="container">
                  <?php print render($page['prefooter']); ?>
                </div>

              </div>
            </div>
            <!-- /#main, /#main-wrapper -->

        <?php elseif ($program_decider_value == 'graduate'): ?>
		        <!-- graduate formatting -->

            <!-- Page Main Graduate -->
            <div id="main-wrapper" class="clearfix">
              <div id="main" class="clearfix">
                <a id="main-content"></a>

                <div class="asu-degree-banner-image"
                     style="background-image:url(/sites/default/files/<?php echo $node_info['field_asu_banner_image']['#items'][0]['filename']; ?>)">
                  <div class="container">
                    <div class="row">
                      <div class="col-md-12">
                        <?php if (($no_panels || $always_show_page_title) && $title): ?>
                          <h1 id="page-title" class="title">
                            <?php print $title; ?>
                            <!-- Displaying 'Accelerated Degree' field if true, displaying nothing if false -->
                            <?php if (isset($node_info['field_asu_degree_acc_program']['#items'][0]['value'])): ?>
                              <?php $accelerated_degree_value = ($node_info['field_asu_degree_acc_program']['#items'][0]['value']); ?>
                              <?php if ($accelerated_degree_value == '1'): ?>
                                <br>
                                <i class="fa fa-location-arrow"></i>
                                <span class="asu-degrees-program-flag">Accelerated Program</span>
                              <?php else: ?>
                                <!-- do nothing, it's not an accelerated degree -->
                              <?php endif; ?>
                            <?php endif; ?>
                            <!-- Displaying 'Concurrent Degree' field if true, displaying nothing if false -->
                            <?php if (isset($node_info['field_asu_degree_conc_program']['#items'][0]['value'])): ?>
                              <?php $concurrent_degree_value = ($node_info['field_asu_degree_conc_program']['#items'][0]['value']); ?>
                              <?php if ($concurrent_degree_value == '1'): ?>
                                <?php if ($accelerated_degree_value == '1'): ?>
                                  <i class="fa fa-star"></i>
                                  <span class="asu-degrees-program-flag">Concurrent Program</span>
                                <?php else: ?>
                                  <br>
                                  <i class="fa fa-star"></i>
                                  <span class="asu-degrees-program-flag">Concurrent Program</span>
                                <?php endif; ?>
                              <?php else: ?>
                                <!-- do nothing, it's not a concurrent degree -->
                              <?php endif; ?>
                            <?php endif; ?>
                            <!-- Displaying 'New Degree' field if true, displaying nothing if false -->
                            <?php if (isset($node_info['field_asu_degree_new_program']['#items'][0]['value'])): ?>
                              <?php $new_degree_value = ($node_info['field_asu_degree_new_program']['#items'][0]['value']); ?>
                              <?php if ($new_degree_value == '1'): ?>
                                <?php if (($accelerated_degree_value || $concurrent_degree_value) == '1'): ?>
                                  <i class="fa fa-retweet"></i>
                                  <span class="asu-degrees-program-flag">New Program</span>
                                <?php else: ?>
                                  <br>
                                  <i class="fa fa-retweet"></i>
                                  <span class="asu-degrees-program-flag">New Program</span>
                                <?php endif; ?>
                              <?php else: ?>
                                <!-- do nothing, it's not a new degree -->
                              <?php endif; ?>
                            <?php endif; ?>
                          </h1>
                        <?php endif; ?>
                      </div>
                    </div>
                  </div>
                </div>
              </div>
              <div id="top-content" class="column container">

                <?php if ($messages): ?>
                  <div id="messages">
                    <?php print $messages; ?>
                  </div>
                <?php endif; ?>

                <?php if ($tabs): ?>
                  <div id="tabs">
                    <?php print render($tabs); ?>
                  </div>
                <?php endif; ?>

                <?php if ($action_links): ?>
                  <div id="action-links">
                    <?php print render($action_links); ?>
                  </div>
                <?php endif; ?>
              </div>
              <!-- /#top-content -->

              <!--Start degree content-->
              <?php print theme('breadcrumb', array('breadcrumb' => drupal_get_breadcrumb())); ?>
              <div class="container">

                <!-- Start optional description video display -->
                <?php if (isset($node_info['field_asu_degree_grad_desc_video']['#items'][0]['safe_value'])): ?>

                  <!-- IF VIDEO IS PRESENT -->
                  <div class="row">
                      <div class="col-md-8">
                        <?php if (isset($node_info['field_asu_degree_short_desc']['#items'][0]['safe_value'])): ?>
                          <div class="asu-degree-short-description">
                            <?php print render($node_info['field_asu_degree_short_desc']['#items'][0]['safe_value']); ?>
                            <div class="asu-degree-read-more">
                              <a href="#degree-collapse" data-toggle="collapse" aria-expanded="false">Read More</a>
                            </div>
                            <div id="degree-collapse" class="collapse">
                              <?php if (isset($node_info['body'])): ?>
                                <?php print render($node_info['body']); ?>
                              <?php endif; ?>
                            </div>
                          </div>
                        <?php elseif (isset($node_info['body'])): ?>
                          <?php print render($node_info['body']); ?>
                        <?php endif; ?>
                      </div>
                      <div class="col-md-4">
                        <?php echo $node_info['field_asu_degree_grad_desc_video']['#items'][0]['safe_value']; ?>
                      </div>
                  </div>

                <?php else: ?>

                  <!-- IF VIDEO IS NOT PRESENT -->
                  <?php if (isset($node_info['field_asu_degree_short_desc']['#items'][0]['safe_value'])): ?>
                    <div class="asu-degree-short-description">
                      <?php print render($node_info['field_asu_degree_short_desc']['#items'][0]['safe_value']); ?>
                      <div class="asu-degree-read-more">
                        <a href="#degree-collapse" data-toggle="collapse" aria-expanded="false">Read More</a>
                      </div>
                      <div id="degree-collapse" class="collapse">
                        <?php if (isset($node_info['body'])): ?>
                          <?php print render($node_info['body']); ?>
                        <?php endif; ?>
                      </div>
                    </div>
                  <?php elseif (isset($node_info['body'])): ?>
                    <?php print render($node_info['body']); ?>
                  <?php endif; ?>

                <?php endif; ?>
                <!-- End optional description video display -->

                  <div class="row space-bot-lg">
                    <div class="col-sm-6 col-md-4 space-bot-md">
                      <a href="#asu-rfi-form-data" id="take-me-to-rfi" class="btn btn-gold btn-block btn-lg">Request information</a>
                    </div>
                    <div class="col-sm-6 col-md-4 space-bot-md">
                      <a href="https://visit.asu.edu/"
                         class="btn btn-gold btn-block btn-lg">Schedule a visit</a>
                    </div>
                    <div class="col-sm-6 col-md-4 space-bot-md">
                      <a href="http://www.asu.edu/enroll/apply"
                         class="btn btn-gold btn-block btn-lg">How and when to apply</a>
                    </div>
                  </div>
              </div>
              <div class="asu-degree-grey-section">
                <div class="container">
                  <div class="row">
                    <div class="col-sm-6 col-md-4">
                      <h2>Degree Offered</h2>

                      <div class="asu-degree-page-degree-offered">
                        <p>
                          <?php if (isset($node_info['field_asu_degree_awarded']['#items'][0]['value'])): ?>
                            <?php print render($node_info['field_asu_degree_awarded']['#items'][0]['value']); ?>
                          <?php endif; ?><br>

                          <?php if (isset($node_info['field_asu_college']['#items'][0]['value'])): ?>
                            <?php if (isset($node_info['field_asu_college_url']['#items'][0]['url'])): ?>
                              <a href="<?php echo $node_info['field_asu_college_url']['#items'][0]['url']; ?>" target="_blank">
                            <?php endif; ?>
                            <?php print render($node_info['field_asu_college']['#items'][0]['value']); ?>
                            <?php if (isset($node_info['field_asu_college_url']['#items'][0]['url'])): ?>
                              </a>
                            <?php endif; ?>
                          <?php endif; ?>
                        </p>
                      </div>
                      <p>
                        <b>Location</b><br>
                        <?php
                          if (isset($node_info['field_asu_degree_campus']['#items'][0]['value'])) {
                            $c = count($node_info['field_asu_degree_campus']['#items']) - 1;
                            $i = 0;
                            foreach ($node_info['field_asu_degree_campus']['#items'] as $campus) {
                              $a = true;
                              switch ($campus['value']) {
                                case 'Tempe':
                                  echo '<a href="//www.asu.edu/tour/tempe/index.html">'.$campus['value'].'</a>';
                                  break;
                                case 'Polytechnic':
                                  echo '<a href="//www.asu.edu/tour/polytechnic/index.html">'.$campus['value'].'</a>';
                                  break;
                                case 'Downtown':
                                  echo '<a href="//www.asu.edu/tour/downtown/index.html">'.$campus['value'].'</a>';
                                  break;
                                case 'West':
                                  echo '<a href="//www.asu.edu/tour/west/index.html">'.$campus['value'].'</a>';
                                  break;
                                case 'Lake Havasu':
                                  echo '<a href="//havasu.asu.edu/">'.$campus['value'].'</a>';
                                  break;
                                case 'Eastern Arizona College':
                                  echo '<a href="//transfer.asu.edu/eac">'.$campus['value'].'</a>';
                                  break;
                                case 'Online':
                                  echo '<a href="//asuonline.asu.edu/">'.$campus['value'].'</a>';
                                  break;
                                //Check ASU Feeds Parser.  The campus being used doesn't exist.
                                default:
                                  echo 'Campus Not Found';
                                  //$a = false;
                                  echo '<!--'.$campus['value'].'-->';
                                  break;
                              }
                              if($i < $c && $a) {
                                echo ', ';
                              }
                              ++$i;
                            }
                          }
                        ?>
                      </p>

                      <h2>Plan of Study</h2>

                      <p>The Plan of Study is the required cirriculum to complete the program.</p>
                      <?php if (isset($node_info['field_asu_degree_asuds_url'])): ?>
                        <p><a
                            href="<?php echo $node_info['field_asu_degree_asuds_url']['#items'][0]['url']; ?>"
                            target="_blank">View Plan of Study</a></p>
                      <?php endif ?>

                      <div class="asu-degree-subplans">
                      <?php if (isset($node_info['field_asu_degree_subplan_url']['#items'])): ?>
                        <div class='asu-degree-sublplans'><p><b>Subplans</b><br/></div>
                          <?php foreach ($node_info['field_asu_degree_subplan_url']['#items'] as $sp) {
                            if ($sp['title'] != $sp['url']) {
                              echo '<a href="'.$sp['url'].'">'.$sp['title'].'</a><br/>';
                            }
                            else {
                              echo '<a href="'.$sp['url'].'">Online</a><br/>';
                            }
                          }
                        echo '</p>';
                      endif ?>
                      </div>
                    </div>
                    <div class="col-sm-6 col-md-4">

                      <?php if (isset($node_info['field_asu_degree_grad_app']['#items'][0]['safe_value'])): ?>
                          <?php echo $node_info['field_asu_degree_grad_app']['#items'][0]['safe_value']; ?>
                      <?php endif ?>

                    </div>
                    <div class="col-sm-6 col-md-4">

                      <?php if (isset($node_info['field_asu_degree_grad_financing']['#items'][0]['safe_value'])): ?>
                          <?php echo $node_info['field_asu_degree_grad_financing']['#items'][0]['safe_value']; ?>
                      <?php endif ?>

                    </div>
                  </div>
                </div>
              </div>

              <div class="container">
                <?php print render($page['asu_degree_marketing']); ?>
              </div>

              <div class="container space-top-xl space-bot-xl">
                <div class="col-md-8">

                  <?php if (isset($node_info['field_asu_degree_grad_text_area']['#items'][0]['safe_value'])): ?>
                      <?php echo $node_info['field_asu_degree_grad_text_area']['#items'][0]['safe_value']; ?>
                  <?php endif ?>

                </div>
                <?php if (isset($node_info['field_asu_degree_relatedprograms'])): ?>
                  <div class="col-md-4">
                    <div class="pane-menu-tree">
                      <h4>Related Programs</h4>
                      <?php for ($it = 0; $it < 1000; $it++) {
                        if (isset($node_info['field_asu_degree_relatedprograms'][$it]['#markup'])) {
                          $rp_result = $node_info['field_asu_degree_relatedprograms'][$it]['#markup'];
                        }
                        if (!empty($rp_result)) {
                          print $rp_result;
                          unset($rp_result);
                        } else {
                          break 1;
                        }
                      ?>
                      <br>
                      <?php } ?>
                    </div>
                  </div>
                <?php endif; ?>

                  <div class="col-md-4">
                    <?php print render($page['asu_degree_sidebar']); ?>
                  </div>
                </div>

                <div class="container">
                  <?php print render($page['prefooter']); ?>
                </div>

              </div>
            </div>
            <!-- /#main, /#main-wrapper -->

        <?php else: ?>
		        <!-- do nothing, it has no degree program assigned -->
	      <?php endif; ?>
    <?php endif; ?>
    <!-- end of PROGRAM DECIDER - UNDERGRADUATE or GRADUATE -->


    <!-- Page Footer -->
    <footer id="page-footer">
      <div class="container">
        <div class="row row-full">
          <?php print render($page['footer']); ?>
        </div>
      </div>
    </footer>
    <!-- /#footer -->

    <?php print render($page['closure']); ?>

  </div>
</div>
<!-- /#page, /#page-wrapper -->
