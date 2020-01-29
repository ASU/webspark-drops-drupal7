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

// Add subsection of $page['content'] for metatags
if (module_exists('metatag')) {
  print render($page['content']['metatags']);
}

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

    <?php //dpm($page['content']['system_main']['nodes'][arg(1)]); ?>

    <?php if (isset($node_info['field_asu_ap_program']['#items'][0]['value'])): ?>
	    <?php $program_decider_value = ($node_info['field_asu_ap_program']['#items'][0]['value']); ?>
      <?php if (isset($node_info['field_asu_ap_cert']['#items'][0]['value'])): ?>
        <?php $cert_val = ($node_info['field_asu_ap_cert']['#items'][0]['value']); ?>

      <!-- Page Main -->
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
                      <?php if ($program_decider_value == 'undergrad'): ?>
                        <?php if ($cert_val == 'false'): ?>
                          <?php print $title; ?>,
                          <?php if (isset($node_info['field_asu_ap']['#items'][0]['value'])): ?>
                            <?php print render($node_info['field_asu_ap']['#items'][0]['value']); ?>
                          <?php endif; ?>
                        <?php elseif ($cert_val == 'true'): ?>
                          <?php print $title; ?>
                          <?php if (isset($node_info['field_asu_ap']['#items'][0]['value'])): ?>
                            (<?php print render($node_info['field_asu_ap']['#items'][0]['value']); ?>)
                          <?php endif; ?>
                        <?php endif; ?>
                      <?php elseif ($program_decider_value == 'graduate'): ?>
                        <?php print $title; ?>
                      <?php endif; ?>
                      <!-- Displaying 'Accelerated Program' field if true, displaying nothing if false -->
                      <?php if (isset($node_info['field_asu_ap_acc_program']['#items'][0]['value'])): ?>
                        <?php $accelerated_degree_value = ($node_info['field_asu_ap_acc_program']['#items'][0]['value']); ?>
                        <?php if ($accelerated_degree_value == '1'): ?>
                          <br>
                          <i class="fa fa-location-arrow"></i>
                          <span class="asu-ap-program-flag">Accelerated Program</span>
                        <?php else: ?>
                          <!-- do nothing, it's not an accelerated degree -->
                        <?php endif; ?>
                      <?php endif; ?>
                      <!-- Displaying 'Concurrent Program' field if true, displaying nothing if false -->
                      <?php if (isset($node_info['field_asu_ap_conc_program']['#items'][0]['value'])): ?>
                        <?php $concurrent_degree_value = ($node_info['field_asu_ap_conc_program']['#items'][0]['value']); ?>
                        <?php if ($concurrent_degree_value == '1'): ?>
                          <?php if ($accelerated_degree_value == '1'): ?>
                            <i class="fa fa-star"></i>
                            <span class="asu-ap-program-flag">Concurrent Program</span>
                          <?php else: ?>
                            <br>
                            <i class="fa fa-star"></i>
                            <span class="asu-ap-program-flag">Concurrent Program</span>
                          <?php endif; ?>
                        <?php else: ?>
                          <!-- do nothing, it's not a concurrent degree -->
                        <?php endif; ?>
                      <?php endif; ?>
                      <!-- Displaying 'New Program' field if true, displaying nothing if false -->
                      <?php if (isset($node_info['field_asu_ap_new_program']['#items'][0]['value'])): ?>
                        <?php $new_degree_value = ($node_info['field_asu_ap_new_program']['#items'][0]['value']); ?>
                        <?php if ($new_degree_value == '1'): ?>
                          <?php if (($accelerated_degree_value || $concurrent_degree_value) == '1'): ?>
                            <i class="fa fa-retweet"></i>
                            <span class="asu-ap-program-flag">New Program</span>
                          <?php else: ?>
                            <br>
                            <i class="fa fa-retweet"></i>
                            <span class="asu-ap-program-flag">New Program</span>
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

        <!-- Breadcrumb -->
        <div class="asu-degrees-breadcrumb-container">
          <?php
            if (module_exists('easy_breadcrumb')) {
              print theme('easy_breadcrumb');
            } else {
              print theme('breadcrumb', array('breadcrumb' => drupal_get_breadcrumb()));
            }
          ?>
        </div>
        <!-- /Breadcrumb -->

        <!--Start degree content-->
        <div class="container">

          <?php if ($program_decider_value == 'undergrad'): ?>
            <?php if (isset($node_info['field_asu_ap_short_desc']['#items'][0]['safe_value'])): ?>
              <div class="asu-ap-short-description">
                <?php print render($node_info['field_asu_ap_short_desc']['#items'][0]['safe_value']); ?>
                <div class="asu-ap-read-more">
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

          <?php elseif ($program_decider_value == 'graduate'): ?>
            <!-- Start optional description video display -->
            <?php if (isset($node_info['field_asu_ap_grad_desc_video']['#items'][0]['safe_value'])): ?>

              <!-- IF VIDEO IS PRESENT -->
              <div class="row">
                  <div class="col-md-8">
                    <?php if (isset($node_info['field_asu_ap_short_desc']['#items'][0]['safe_value'])): ?>
                      <div class="asu-ap-short-description">
                        <?php print render($node_info['field_asu_ap_short_desc']['#items'][0]['safe_value']); ?>
                        <div class="asu-ap-read-more">
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
                    <?php echo $node_info['field_asu_ap_grad_desc_video']['#items'][0]['safe_value']; ?>
                  </div>
              </div>

            <?php else: ?>

              <!-- IF VIDEO IS NOT PRESENT -->
              <?php if (isset($node_info['field_asu_ap_short_desc']['#items'][0]['safe_value'])): ?>
                <div class="asu-ap-short-description">
                  <?php print render($node_info['field_asu_ap_short_desc']['#items'][0]['safe_value']); ?>
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
          <?php endif; ?>
            <div class="row space-bot-lg">
              <div class="col-sm-6 col-md-4 space-bot-md">
                <?php if (isset($node_info['field_asu_ap_cta_information']['#items'][0]['url'])): ?>
                  <a href="<?php echo $node_info['field_asu_ap_cta_information']['#items'][0]['url'] ?>"
                     class="btn btn-gold btn-block btn-lg">Request information</a>
                <?php else: ?>
                  <a href="#asu-rfi-form-data" id="take-me-to-rfi"
                     class="btn btn-gold btn-block btn-lg">Request information</a>
                <?php endif; ?>
              </div>
              <div class="col-sm-6 col-md-4 space-bot-md">
                <?php if (isset($node_info['field_asu_ap_cta_visit']['#items'][0]['url'])): ?>
                  <a href="<?php echo $node_info['field_asu_ap_cta_visit']['#items'][0]['url'] ?>"
                     class="btn btn-gold btn-block btn-lg">Schedule a visit</a>
                <?php else: ?>
                  <a href="https://visit.asu.edu/"
                     class="btn btn-gold btn-block btn-lg">Schedule a visit</a>
                <?php endif; ?>
              </div>
              <div class="col-sm-6 col-md-4 space-bot-md">
                <?php if (isset($node_info['field_asu_ap_cta_apply']['#items'][0]['url'])): ?>
                  <a href="<?php echo $node_info['field_asu_ap_cta_apply']['#items'][0]['url'] ?>"
                     class="btn btn-gold btn-block btn-lg">How and when to apply</a>
                <?php else: ?>
                  <a href="https://students.asu.edu/apply"
                     class="btn btn-gold btn-block btn-lg">How and when to apply</a>
                <?php endif; ?>
              </div>
            </div>
        </div>
        <div class="asu-ap-grey-section">
          <div class="container">
            <div class="row">
              <div class="col-sm-6 col-md-4">
                <h2>Program offered</h2>

                <div class="asu-ap-page-degree-offered">
                  <p>
                    <strong>
                      <?php if (isset($node_info['field_asu_ap_awarded']['#items'][0]['value'])): ?>
                        <?php if ($program_decider_value == 'undergrad'): ?>
                          <?php if (isset($node_info['field_asu_ap_cert']['#items'][0]['value'])): ?>
                            <?php if ($cert_val == 'false'): ?>
                              <?php print render($node_info['field_asu_ap_awarded']['#items'][0]['value']); ?>,
                              <?php if (isset($node_info['field_asu_ap']['#items'][0]['value'])): ?>
                                <?php print render($node_info['field_asu_ap']['#items'][0]['value']); ?>
                              <?php endif; ?>
                            <?php elseif ($cert_val == 'true'): ?>
                              <?php print render($node_info['field_asu_ap_awarded']['#items'][0]['value']); ?>
                              <?php if (isset($node_info['field_asu_ap']['#items'][0]['value'])): ?>
                                (<?php print render($node_info['field_asu_ap']['#items'][0]['value']); ?>)
                              <?php endif; ?>
                            <?php endif; ?>
                          <?php endif; ?>
                        <?php elseif ($program_decider_value == 'graduate'): ?>
                          <?php print render($node_info['field_asu_ap_awarded']['#items'][0]['value']); ?>
                        <?php endif; ?>
                      <?php endif; ?>
                    </strong>
                    <br><br>
                    <b>Offered by</b><br>
                    <?php
                      if (isset($node_info['field_asu_ap_college_j']['#items'][0]['value'])) {
                        // $cc --> college_count; $ci --> college_index; $cn --> college_name
                        $cc = count($node_info['field_asu_ap_college_j']['#items']) - 1;
                        $ci = 0;
                        foreach ($node_info['field_asu_ap_college_j']['#items'] as $cn) {
                          $asu_college_raw = $cn['value'];
                          list($asu_college_suffix, $asu_college_prefix) = explode(", ", $asu_college_raw);
                          $asu_college = $asu_college_prefix . " " . $asu_college_suffix;
                          echo $asu_college;
                          if ($ci < $cc) {
                            echo ', ';
                          }
                          ++$ci;
                        }
                      }
                    ?>
                  </p>
                </div>
                <p>
                  <b>Location</b><br>
                  <?php
                    if (isset($node_info['field_asu_ap_campus']['#items'][0]['value'])) {
                      $c = count($node_info['field_asu_ap_campus']['#items']) - 1;
                      $i = 0;
                      foreach ($node_info['field_asu_ap_campus']['#items'] as $campus) {
                        $a = true;
                        switch ($campus['value']) {
                          case 'Downtown':
                            echo '<a href="//tours.asu.edu/downtown">'.$campus['value'].'</a>';
                            break;
                          case 'Lake Havasu City':
                            echo '<a href="//tours.asu.edu/havasu">'.$campus['value'].'</a>';
                            break;
                          case 'Polytechnic':
                            echo '<a href="//tours.asu.edu/polytechnic">'.$campus['value'].'</a>';
                            break;
                          case 'Tempe':
                            echo '<a href="//tours.asu.edu/tempe">'.$campus['value'].'</a>';
                            break;
                          case 'Thunderbird':
                            echo '<a href="//tours.asu.edu/thunderbird">'.$campus['value'].'</a>';
                            break;
                          case 'West':
                            echo '<a href="//tours.asu.edu/west">'.$campus['value'].'</a>';
                            break;
                          case 'ASU@TheGilaValley':
                            echo '<a href="//admission.asu.edu/transfer/eastern-arizona">'.$campus['value'].'</a>';
                            break;
                          case 'ASU@Pinal':
                            echo '<a href="//admission.asu.edu/transfer/central-arizona">'.$campus['value'].'</a>';
                            break;
                          case 'ASU@Tucson':
                            echo '<a href="//transfer.asu.edu/asutucson'.$campus['value'].'</a>';
                            break;
                          case 'ASU@Yuma':
                            echo '<a href="//admission.asu.edu/transfer/arizona-western">'.$campus['value'].'</a>';
                            break;
                          case 'ASU@Yavapai':
                            echo '<a href="//admission.asu.edu/transfer/asuyavapai">'.$campus['value'].'</a>';
                            break;
                          case 'ASU@Cochise':
                            echo '<a href="//admission.asu.edu/transfer/asu-cochise">'.$campus['value'].'</a>';
                            break;
                          case 'ASU@Pima':
                            echo '<a href="//admission.asu.edu/transfer/pima">'.$campus['value'].'</a>';
                            break;
                          case 'Online':
                            echo '<a href="//asuonline.asu.edu/">'.$campus['value'].'</a>';
                            break;
                          //Check ASU Feeds Parser.  The campus being used doesn't exist.
                          default:
                            echo $campus['value'];
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

                <?php if ($program_decider_value == 'undergrad'): ?>
                  <?php if (isset($node_info['field_asu_ap_major_map_url'])): ?>
                    <h2>Major map</h2>
                    <p>A major map outlines the degree’s requirements for graduation.</p>
                    <p><a href="<?php echo $node_info['field_asu_ap_major_map_url']['#items'][0]['url']; ?>">View Major Map</a></p>
                  <?php else: ?>
                    <?php if (isset($node_info['field_asu_ap_asuds_url'])): ?>
                      <h2>Plan of study</h2>
                      <p>The Plan of study is the required curriculum to complete the program.</p>
                      <p><a href="<?php echo $node_info['field_asu_ap_asuds_url']['#items'][0]['url']; ?>">View Plan of Study</a></p>
                    <?php endif; ?>
                  <?php endif; ?>
                <?php elseif ($program_decider_value == 'graduate'): ?>
                  <?php if (isset($node_info['field_asu_ap_asuds_url'])): ?>
                    <h2>Plan of study</h2>
                    <p>The Plan of study is the required curriculum to complete the program.</p>
                    <p><a href="<?php echo $node_info['field_asu_ap_asuds_url']['#items'][0]['url']; ?>">View Plan of Study</a></p>
                  <?php endif; ?>
                <?php endif; ?>

                <div class="asu-ap-subplans">
                <?php if (isset($node_info['field_asu_ap_subplan_url']['#items'])): ?>
                  <div class='asu-ap-sublplans'><p><b>Subplans</b><br/></div>
                    <?php foreach ($node_info['field_asu_ap_subplan_url']['#items'] as $sp) {
                      if ($sp['title'] != $sp['url']) {
                        echo '<a href="'.$sp['url'].'">'.$sp['title'].'</a><br/>';
                      }
                      else {
                        echo '<a href="'.$sp['url'].'">Online</a><br/>';
                      }
                    }
                  echo '</p>';
                endif; ?>
                </div>
              </div>
              <div class="col-sm-6 col-md-4">
                <?php if ($program_decider_value == 'undergrad'): ?>
                  <h2>Application requirements</h2>

                    <?php if (isset($node_info['field_asu_ap_addl_req']['#items'][0]['safe_value'])): ?>
                      <p>
                        <?php print render($node_info['field_asu_ap_addl_req']['#items'][0]['safe_value']); ?>
                      </p>
                    <?php endif; ?>

                    <p>All students are required to meet general university admission requirements:</p>
                    <ul>
                      <li><a href="https://students.asu.edu/freshman">Freshman</a></li>
                      <li><a href="https://transfer.asu.edu/">Transfer</a></li>
                      <li><a href="https://students.asu.edu/international">International</a></li>
                      <li><a href="https://students.asu.edu/readmission">Readmission</a></li>
                    </ul>
                <?php elseif ($program_decider_value == 'graduate'): ?>
                  <?php if (isset($node_info['field_asu_ap_grad_app']['#items'][0]['safe_value'])): ?>
                      <?php echo $node_info['field_asu_ap_grad_app']['#items'][0]['safe_value']; ?>
                  <?php endif ?>
                <?php endif; ?>
              </div>
              <div class="col-sm-6 col-md-4">
                <?php if ($program_decider_value == 'undergrad'): ?>
                  <h2>Affording college</h2>

                  <p>
                    <?php if (isset($node_info['field_asu_ap_sl']['#items'][0]['url'])): ?>
                      <a href="<?php echo $node_info['field_asu_ap_sl']['#items'][0]['url'] ?>">Scholarships</a><br>
                    <?php else: ?>
                      <a href="<?php echo 'https://scholarships.asu.edu/colleges' ?>">Scholarships</a><br>
                    <?php endif; ?>
                    Find and apply for relevant scholarships.
                  </p>

                  <?php if (isset($node_info['field_asu_ap_wue_available']['#items'][0]['value']) && $node_info['field_asu_ap_wue_available']['#items'][0]['value'] == 1): ?>
                    <p>
                        <a href="<?php echo 'https://students.asu.edu/admission/wue' ?>">WUE eligible program</a><br>
                      Undergraduate students from western states who enroll in this
                      program are eligible for a discounted tuition rate.
                    </p>
                  <?php endif; ?>

                  <p>
                      <a href="<?php echo 'https://students.asu.edu/financialaid' ?>">Financial Aid</a><br>
                    ASU has many financial aid options. Almost everyone, regardless
                    of income, can qualify for some form of financial aid. In fact,
                    more than 70 percent of all ASU students receive some form of
                    financial assistance every year.
                  </p>
                <?php elseif ($program_decider_value == 'graduate'): ?>
                  <?php if (isset($node_info['field_asu_ap_grad_financing']['#items'][0]['safe_value'])): ?>
                      <?php echo $node_info['field_asu_ap_grad_financing']['#items'][0]['safe_value']; ?>
                  <?php endif ?>
                <?php endif; ?>
              </div>
            </div>
          </div>
        </div>

        <div class="container">
          <?php //print render($page['asu_ap_marketing']); ?>
        </div>

        <div class="container space-top-xl space-bot-xl">
          <div class="col-md-8">

            <?php if (isset($node_info['field_asu_ap_prog_req']['#items'][0]['safe_value'])): ?>
                <h2>Program requirements</h2>
                <?php print $node_info['field_asu_ap_prog_req']['#items'][0]['safe_value']; ?>
            <?php elseif (isset($node_info['field_asu_ap_admission_req']['#items'][0]['safe_value'])): ?>
                <h2>Program requirements</h2>
                <?php print $node_info['field_asu_ap_admission_req']['#items'][0]['safe_value']; ?>
            <?php endif; ?>
            <?php if ($program_decider_value == 'undergrad'): ?>
              <?php if (isset($node_info['field_asu_ap_career_opps'])): ?>
                <h2>Career outlook</h2>
                <?php if (isset($node_info['field_asu_ap_career_outlook']['#items'][0]['safe_value'])): ?>
                    <?php print render($node_info['field_asu_ap_career_outlook']['#items'][0]['safe_value']); ?>
                <?php elseif (isset($node_info['field_asu_ap_career_opps'])): ?>
                  <?php print render($node_info['field_asu_ap_career_opps']); ?>
                <?php endif; ?>
              <?php endif; ?>
              <?php if (isset($node_info['field_asu_ap_example_careers'])): ?>
                <?php if (isset($node_info['field_asu_ap_ex_car_tf']['#items'][0]['value']) && $node_info['field_asu_ap_ex_car_tf']['#items'][0]['value'] == 1): ?>
                  <h2>Example careers</h2>
                  <?php print render($node_info['field_asu_ap_example_careers']); ?>
                <?php endif; ?>
              <?php endif; ?>
            <?php elseif ($program_decider_value == 'graduate'): ?>
              <?php if (isset($node_info['field_asu_ap_grad_text_area']['#items'][0]['safe_value'])): ?>
                  <?php echo $node_info['field_asu_ap_grad_text_area']['#items'][0]['safe_value']; ?>
              <?php endif; ?>
            <?php endif; ?>
          </div>
          <?php if (isset($node_info['field_asu_ap_related_programs'])): ?>
            <div class="col-md-4">
              <div class="pane-menu-tree">
                <h4>Related Programs</h4>
                <?php for ($it = 0; $it < count($node_info['field_asu_ap_related_programs']); $it++) {
                  if (isset($node_info['field_asu_ap_related_programs'][$it]['#label'])) {
                    $rp_result = $node_info['field_asu_ap_related_programs'][$it]['#label'];
                  }
                  if (!empty($rp_result)) {
                    echo '<a href="/'.$node_info['field_asu_ap_related_programs'][$it]['#uri']['path'].'">'.$rp_result.'</a>';
                    unset($rp_result);
                  } else {
                    break;
                  }
                ?>
                <br>
                <?php } ?>
              </div>
            </div>
          <?php endif; ?>

            <div class="col-md-4">
              <?php //print render($page['asu_ap_sidebar']); ?>
            </div>
          </div>

          <div class="container">
            <?php print render($page['prefooter']); ?>
          </div>

        </div>
      </div>
      <!-- /#main, /#main-wrapper -->
      <?php endif; ?>
    <?php endif; ?>


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
