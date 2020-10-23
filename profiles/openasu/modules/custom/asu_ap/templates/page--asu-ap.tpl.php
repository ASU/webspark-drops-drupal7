<?php /** @noinspection PhpUnhandledExceptionInspection */
/** @noinspection PhpUndefinedVariableInspection */

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

<?php if (isset($node_info['field_asu_ap_program']['#items'][0]['value'])): ?>

  <?php
  $program_type = (string) ($node_info['field_asu_ap_program']['#items'][0]['value']);
  $special_categories = 0; // Degree have special classifications?
  $accelerated_degree_value = 0;
  $concurrent_degree_value = 0;
  $online_program_value = '';
  $new_degree_value = 0;
  $joint_programs_value = 0;
  $wue_program_value = 0;
  ?>
  <?php if (isset($node_info['field_asu_ap_cert']['#items'][0]['value'])): ?>
    <?php $cert_val = ($node_info['field_asu_ap_cert']['#items'][0]['value']); ?>
  <?php endif; ?>

    <!-- Page Main -->
    <div id="main-wrapper" class="clearfix">
      <div id="main" class="clearfix main-asu-ap">
        <a id="main-content"></a>
        <!-- Top Banner image (TB) -->
        <!--suppress CssUnknownTarget -->
        <div class="asu-degree-banner-image"
             style="background-image:url(/sites/default/files/<?php
             echo $node_info['field_asu_banner_image']['#items'][0]['filename'];
             ?>)">
          <div class="container">
            <div class="row">
              <div class="col-md-12">
    <?php if (($no_panels || $always_show_page_title) && $title): ?>
                <h1 id="page-title" class="title">
      <?php if ($program_type == 'undergrad'): ?>
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
      <?php elseif ($program_type === 'graduate'): ?>
        <?php print $title; ?>
      <?php endif; ?>
                </h1>
                <div class="asu-ap-special-categories">
      <?php if (isset($node_info['field_asu_ap_acc_program']['#items'][0]['value'])): // Displaying 'Accelerated Program' field if true, displaying nothing if false  ?>
        <?php $accelerated_degree_value = (int) $node_info['field_asu_ap_acc_program']['#items'][0]['value']; ?>
        <?php if (!empty($accelerated_degree_value)): ?>
                  <div class="asu-ap-special-category">
                    <a id="accelerated-degree" href="#asu-ap-accelerated-degree">
                      <span class="fa fa-location-arrow"></span>
                      <span class="asu-ap-program-flag" title="What is an accelerated program?">Accelerated Program</span>
                    </a>
                  </div>
          <?php $special_categories++; ?>
        <?php endif; ?>
      <?php endif; ?>
      <?php if (isset($node_info['field_asu_ap_conc_program']['#items'][0]['value'])): // Displaying 'Concurrent Program' field if true, displaying nothing if false ?>
        <?php $concurrent_degree_value = (int) $node_info['field_asu_ap_conc_program']['#items'][0]['value']; ?>
        <?php if ($concurrent_degree_value === 1): ?>
                  <div class="asu-ap-special-category">
                    <a id="concurrent-degree" href="#asu-ap-concurrent-degree">
                      <span class="fa fa-star"></span>
                      <span class="asu-ap-program-flag" title="What is a concurrent program?">Concurrent Program</span>
                    </a>
                  </div>
          <?php $special_categories++; ?>
        <?php endif; ?>
      <?php endif; ?>
      <?php if (isset($node_info['field_asu_ap_campus']['#items']) && count($node_info['field_asu_ap_campus']['#items']) > 0): // Displaying 'Online Program' field if true, displaying nothing if false ?>
        <?php
        $is_online = 0;
        foreach ($node_info['field_asu_ap_campus']['#items'] as $campus) {
          if ($campus['safe_value'] === 'Online') {
            $online_program_value = (!empty($node_info['field_asu_ap_curriculum_url']['#items'][0]['url']))
              ? $node_info['field_asu_ap_curriculum_url']['#items'][0]['url']
              : 'https://asuonline.asu.edu/';
            $is_online = 1;
            break;
          }
        } ?>
        <?php if ($is_online === 1): ?>
                  <div class="asu-ap-special-category">
                    <?php
                    if (isset($node_info['field_asu_ap_campus']['#items'][0]['value'])) {
                      $campus_count = count($node_info['field_asu_ap_campus']['#items']);
                      $anchor_title = ($campus_count > 1) ? 'Online option is available' : 'Online degree program';
                    }
                    ?>
                    <a id="online-program" title="<?php print $anchor_title; ?>" href="#asu-ap-online-program">
                      <span class="fa fa-globe"></span>
                      <span class="asu-ap-program-flag" title="<?php print $anchor_title; ?>">Online Program</span>
                    </a>
                  </div>
          <?php $special_categories++; ?>
        <?php endif; ?>
      <?php endif; ?>
      <?php if (isset($node_info['field_asu_ap_new_program']['#items'][0]['value'])): // Displaying 'New Program' field if true, displaying nothing if false ?>
        <?php $new_degree_value = (int) $node_info['field_asu_ap_new_program']['#items'][0]['value']; ?>
        <?php if ($new_degree_value === 1): ?>
                  <div class="asu-ap-special-category">
                    <!--suppress HtmlUnknownAnchorTarget -->
                    <a id="new-program" href="#asu-ap-new-program">
                      <span class="fa fa-retweet"></span>
                      <span class="asu-ap-program-flag" title="What does this mean?">New Program</span>
                    </a>
                  </div>
          <?php $special_categories++; ?>
        <?php endif; ?>
      <?php endif; ?>
                </div>
    <?php endif ?>
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
        <div class="container container-breadcrumb">
          <div class="row row-full">
    <?php
    if (module_exists('easy_breadcrumb')) {
      print theme('easy_breadcrumb');
    } else {
      print theme('breadcrumb', array('breadcrumb' => drupal_get_breadcrumb()));
    } ?>
          </div>
        </div>

          <!-- START degree content  #################################### -->
        <div class="container container-top">
  <?php // Top white section - Marketing + body content MB
  if (isset($node_info['field_asu_ap_url_4']['#items'][0]['video_url'])
    && variable_get('asu_ap_ds_marketing_video') === 'marketing_top') {
    $ds_marketing_text_cols = array(
      'text' => 7,
      'video' => 5);
  } else {
    $ds_marketing_text_cols = array(
      'text' => 12,
      'video' => 0);
  }

  ?>
  <?php // LOCAL Marketing text YES
  if (isset($node_info['field_asu_ap_short_desc']['#items'][0]['safe_value'])): ?>
          <div class="row row-yes row-full row-local-market-data">
      <?php $cols = array('short_desc' => 12, 'video' => 0); ?>
      <?php // LOCAL video URL? YES
      if (isset($node_info['field_asu_ap_grad_desc_video']['#items'][0]['safe_value'])): ?>
        <?php $cols = array('short_desc' => 8, 'video' => 4); ?>
      <?php endif; ?>
            <div class="col-md-<?php print $cols['short_desc'] ?>">
              <div class="asu-ap-short-description">
        <?php print render($node_info['field_asu_ap_short_desc']['#items'][0]['safe_value']); ?>
              </div>
            </div>
      <?php if ($cols['video'] === 4): ?>
            <div class="col-md-<?php echo $cols['video']; ?>">
        <?php echo $node_info['field_asu_ap_grad_desc_video']['#items'][0]['safe_value']; ?>
            </div>
      <?php endif; ?>
          </div>
          <!-- Degree Search data -->
          <div class="row row-yes row-full row-ds-marketing-data">
            <div class="asu-ap-read-more">
              <a href="#degree-collapse" data-toggle="collapse" aria-expanded="false">Read More</a>
            </div>
            <div id="degree-collapse" class="collapse">
              <div class="container">
                <div class="row row-yes-sub row-ds-marketing-video-text">
      <?php if (isset($node_info['field_asu_ap_market_text']['#items'][0]['safe_value'])): // @TODO toggle visibility in config ?>
                    <div class="col-md-<?php print $ds_marketing_text_cols['text']; ?>">
        <?php print render($node_info['field_asu_ap_market_text']); ?>>
                    </div>
      <?php endif; ?>
      <?php if ($ds_marketing_text_cols['video'] === 5): // SHOW Degree Search URL-based video @TODO toggle visibility in a config form ?>
                    <div class="col-md-<?php print $ds_marketing_text_cols['video'] ?>">
        <?php print render($node_info['field_asu_ap_url_4']); ?>
                    </div>
      <?php endif; ?>
                </div>
      <?php if (isset($node_info['body'])): // Program description (aka body field) ?>
                  <div class="row row-yes-sub row-ds-body">
                    <div class="col-md-12">
        <?php print render($node_info['body']); ?>
                    </div>
                  </div>
      <?php endif; ?>
              </div>
            </div>
          </div>

    <?php // LOCAL marketing text NO
    else: ?>
      <?php // Is there DS marketing text? YES
      if (isset($node_info['field_asu_ap_market_text']['#items'][0]['safe_value'])): ?>
          <div class="row row-no row-ds-marketing-video-text">
            <div class="col-md-<?php print $ds_marketing_text_cols['text']; ?>">
        <?php print render($node_info['field_asu_ap_market_text']); ?>
            </div>
        <?php if ($ds_marketing_text_cols['video'] === 5): // Is there a DS URL-based video ?>
            <div class="col-md-<?php print $ds_marketing_text_cols['video'] ?>">
              <div class="ds-video-shell">
          <?php print render($node_info['field_asu_ap_url_4']); ?>
              </div>
            </div>
        <?php endif; ?>
          </div>
      <?php endif; ?>
      <?php if (isset($node_info['body'])): // Program description (aka body field) ?>
          <div class="row row-no row-ds-body">
            <div class="col-md-12">
        <?php print render($node_info['body']); ?>
            </div>
          </div>
      <?php endif; ?>
    <?php endif; ?>
  <?php // CTA Buttons ?>
          <div class="row space-bot-lg asu-ap-page-buttons">
            <div class="col-sm-6 col-md-4 space-bot-md">
    <?php $cta_information = (isset($node_info['field_asu_ap_cta_information']['#items'][0]['url']))
      ? $node_info['field_asu_ap_cta_information']['#items'][0]['url']
      : "#rfi-form"; ?>
              <form><button type="submit" formaction="<?php print $cta_information; ?>" class="btn btn-gold btn-block btn-lg">Request information</button></form>
            </div>
            <div class="col-sm-6 col-md-4 space-bot-md">
    <?php $cta_visit = (isset($node_info['field_asu_ap_cta_visit']['#items'][0]['url']))
      ? $node_info['field_asu_ap_cta_visit']['#items'][0]['url']
      : 'https://visit.asu.edu/'; ?>
              <form><button type="submit" formaction="<?php print $cta_visit ?>" class="btn btn-gold btn-block btn-lg">Schedule a visit</button></form>
            </div>
            <div class="col-sm-6 col-md-4 space-bot-md">
    <?php $cta_apply = (isset($node_info['field_asu_ap_cta_apply']['#items'][0]['url']))
      ? $node_info['field_asu_ap_cta_apply']['#items'][0]['url']
      : "https://students.asu.edu/apply"; ?>
              <form><button type="submit" formaction="<?php print $cta_apply?>" class="btn btn-gold btn-block btn-lg">How and when to apply</button></form>
            </div>
          </div>
        </div>

          <!-- Middle gray section (MG) -->
        <div class="asu-ap-grey-section">
          <div class="container">
            <div class="row row-full">
              <div class="col-sm-6 col-md-4">

  <?php // Column 1 ?>

                <h2>At A Glance</h2>
                  <div class="asu-ap-page-degree-offered">
                  <h4>
    <?php if (isset($node_info['field_asu_ap_awarded']['#items'][0]['value'])): ?>
      <?php if ($program_type == 'undergrad'): ?>
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
      <?php elseif ($program_type === 'graduate'): ?>
        <?php print render($node_info['field_asu_ap_awarded']['#items'][0]['value']); ?>
      <?php endif; ?>
    <?php endif; ?>
                  </h4>
                  <ul>
  <?php
  if (isset($node_info['field_asu_ap_college_j']['#items'][0]['value'])) {
    print "<li><strong>Offered by</strong>: ";
    $college_count = count($node_info['field_asu_ap_college_j']['#items']) - 1;
    $college_index = 0;
    foreach ($node_info['field_asu_ap_college_j']['#items'] as $college_name) {
      $college_raw = $college_name['value'];
      list($college_suffix, $college_prefix) = explode(", ", $college_raw);
      $college = $college_prefix . " " . $college_suffix;
      // Build in college URL if it exists
      if (isset($node_info['field_asu_ap_college_url_j']['#items'][$college_index]['url'])) {
        if (valid_url($node_info['field_asu_ap_college_url_j']['#items'][$college_index]['url'], TRUE)) {
          $college = l(t($college), $node_info['field_asu_ap_college_url_j']['#items'][$college_index]['url'],
            array('attributes' => array('target' => '_blank')));
        }
      }
      echo $college;
      if ($college_index < $college_count) {
        echo ', ';
      }
      ++$college_index;
    }
    print "</li>";
  }
  if (isset($node_info['field_asu_ap_campus']['#items'][0]['value'])) {
    print "<li><strong>Location</strong>: ";
    $c = count($node_info['field_asu_ap_campus']['#items']) - 1;
    $i = 0;
    foreach ($node_info['field_asu_ap_campus']['#items'] as $campus) {
      $a = true;
      switch ($campus['value']) {

        case 'Tempe':
          echo '<a href="//tours.asu.edu/tempe">' . $campus['value'] . '</a>';
          break;
        case 'Downtown':
          echo '<a href="//tours.asu.edu/downtown">' . $campus['value'] . '</a>';
          break;
        case 'Polytechnic':
          echo '<a href="//tours.asu.edu/polytechnic">' . $campus['value'] . '</a>';
          break;
        case 'Thunderbird': // legacy
          echo '<a href="//tours.asu.edu/thunderbird">' . $campus['value'] . '</a>';
          break;
        case 'West':
          echo '<a href="//tours.asu.edu/west">' . $campus['value'] . '</a>';
          break;
        case 'Online':
          $online_url = (!empty($node_info['field_asu_ap_curriculum_url']['#items'][0]['url']))
            ? $node_info['field_asu_ap_curriculum_url']['#items'][0]['url']
            : '//asuonline.asu.edu/';
          echo '<a href="' . $online_url . '" target="_blank">' . $campus['value'] . '</a>';
          break;
        case 'ASU@Cochise':
          echo '<a href="//admission.asu.edu/transfer/asu-cochise">' . $campus['value'] . '</a>';
          break;
        case 'ASU@Lake Havasu':
          echo '<a href="//tours.asu.edu/havasu">' . $campus['value'] . '</a>';
          break;
        case 'ASU@MexicoCity':
          echo '<a href="//mexico.asu.edu">' . $campus['value'] . '</a>';
          break;
        case 'ASU@Pima':
          echo '<a href="//admission.asu.edu/transfer/pima">' . $campus['value'] . '</a>';
          break;
        case 'ASU@Pinal':
          echo '<a href="//admission.asu.edu/transfer/central-arizona">' . $campus['value'] . '</a>';
          break;
        case 'ASU@TheGilaValley':
          echo '<a href="//admission.asu.edu/transfer/eastern-arizona">' . $campus['value'] . '</a>';
          break;
        case 'ASU@Tucson':
          echo '<a href="//transfer.asu.edu/asutucson">' . $campus['value'] . '</a>';
          break;
        case 'ASU@Washington, D.C.':
          echo '<a href="//washingtondc.asu.edu/facilities">' . $campus['value'] . '</a>';
          break;
        case 'ASU@Yavapai':
          echo '<a href="//admission.asu.edu/transfer/asuyavapai">' . $campus['value'] . '</a>';
          break;
        case 'ASU@Yuma':
          echo '<a href="//admission.asu.edu/transfer/arizona-western">' . $campus['value'] . '</a>';
          break;
        // Check ASU Feeds Parser. The campus being used doesn't exist.
        default:
          echo $campus['value'];
          break;
      }
      if($i < $c && $a) {
        echo ', ';
      }
      ++$i;
    }
    print "</li>";
  }
  if (isset($node_info['field_asu_ap_program_fee']['#items'][0]['value'])
  && $node_info['field_asu_ap_program_fee']['#items'][0]['value'] === 'Y') {
    print "<li><strong>Additional Program fees</strong>: Yes</li>\n";
  }
  if (isset($node_info['field_asu_ap_second_language']['#items'][0]['value'])
    && $node_info['field_asu_ap_second_language']['#items'][0]['value'] === 'Y') {
    print "<li><strong>Second Language requirement</strong>: Yes</li>\n";
  }
  if (isset($node_info['field_asu_ap_min_math']['#items'][0]['value'])) {
    print "<li><strong>First Required Math Course</strong>: ";
    print check_plain($node_info['field_asu_ap_min_math']['#items'][0]['value']) . '</li>';
  }
  if (isset($node_info['field_asu_ap_math_intensity']['#items'][0]['value'])) {
    print '<li><strong>Math Intensity</strong>: <span class="asu-ap-math-intensity">';
    $math_intensity_label = check_plain($node_info['field_asu_ap_math_intensity'][0]['#markup']);
    $math_intensity = check_plain($node_info['field_asu_ap_math_intensity']['#items'][0]['value']);
    print $math_intensity_label . '<span class="asu-ap-math-intensity-graph">';
    print '<img src="/' . drupal_get_path('module', 'asu_ap_feature')
      . '/images/math_intensity_' . $math_intensity . '.png" alt="Math intensity: '
      . $math_intensity . '" /></span>';
    print '</span></li>';
  }
  print '</ul>';

  // Major maps or Plan of Study - undergrad
  ///////////////////
  // show if NOT a certificate/minor
  if ($cert_val !== 'true') { // Show if not a cert/minor
    if ($program_type === 'undergrad') {
      $major_map_urls = array();
      if (isset($node_info['field_asu_ap_major_map_url'])) {
        print '<h2>Required Courses</h2>';
        print "<p>A major map outlines a major's critical requirements, courses, and optimal course
        sequence and aids students in remaining on track to graduation.</p>
        <p>While circumstances vary between students and their paths towards graduation
        (utilizing placement testing to fulfill required math or foreign language
        courses, fulfilling multiple General Studies requirements with one course,
        etc.), completing the courses listed in a major map fulfills all of the
        requirements for graduation.</p>";
        print _asu_ap_feature_map_urls_create($node_info);
      } elseif (isset($node_info['field_asu_ap_asuds_url'])) {
        print '<h2>Plan of study</h2>';
        print '<p>The Plan of study is the required curriculum to complete the program.</p>';
        /** @noinspection HtmlUnknownAnchorTarget */
        print '<p><a href="#plan-of-study">View Plan of Study</a></p>';
      }
    }
    // Major maps or Plan of Study -- Graduate
    //////
    elseif ($program_type === 'graduate') {
      if (isset($node_info['field_asu_ap_asuds_url'])) {
        print '<h2>Plan of study</h2>';
        print '<p>The Plan of study is the required curriculum to complete this graduate level program.</p>';
        /** @noinspection HtmlUnknownAnchorTarget */
        print '<p><a href="#plan-of-study">View Plan of Study</a></p>';
      }
    }
  }
?>
                  <div class="asu-ap-subplans">
  <?php
  if (isset($node_info['field_asu_ap_subplan_url']['#items'])): ?>
              <div class='asu-ap-subplans'>
                <p><b>Subplans</b></p>
    <?php
    foreach ($node_info['field_asu_ap_subplan_url']['#items'] as $sp) {
      if ($sp['title'] != $sp['url']) {
        echo '<a href="'.$sp['url'].'">'.$sp['title'].'</a><br />';
      }
      else {
        echo '<a href="'.$sp['url'].'">Online</a><br />';
      }
    }
    ?>
              </div>
  <?php endif; ?>
                  </div>
                </div>
              </div>

              <?php // Column 2 ?>

              <div class="col-sm-6 col-md-4">
  <?php if ($program_type === 'undergrad'): ?>
                <h2>Application requirements</h2>
    <?php if (isset($node_info['field_asu_ap_addl_req']['#items'][0]['safe_value'])): ?>
                <p><?php print render($node_info['field_asu_ap_addl_req']['#items'][0]['safe_value']); ?></p>
    <?php endif; ?>
                <p>All students are required to meet general university admission requirements:</p>
                <ul>
                  <li><a href="https://students.asu.edu/freshman">Freshman</a></li>
                  <li><a href="https://transfer.asu.edu/">Transfer</a></li>
                  <li><a href="https://students.asu.edu/international">International</a></li>
                  <li><a href="https://students.asu.edu/readmission">Readmission</a></li>
                </ul>
  <?php elseif ($program_type === 'graduate'): ?>
      <?php // Show manually entered data if exists; otherwise, show info from Degree Search
        if (isset($node_info['field_asu_ap_grad_app']['#items'][0]['safe_value'])): ?>
        <?php echo $node_info['field_asu_ap_grad_app']['#items'][0]['safe_value']; ?>
      <?php endif; ?>
    <?php endif; ?>
              </div>

  <?php // Column 3 ?>

              <div class="col-sm-6 col-md-4">
  <?php if ($program_type === 'undergrad'): ?>
                <h2>Affording college</h2>
                <p>
    <?php if (isset($node_info['field_asu_ap_sl']['#items'][0]['url'])): ?>
                  <a href="<?php echo $node_info['field_asu_ap_sl']['#items'][0]['url'] ?>">Scholarships</a><br>
  <?php else: ?>
                  <a href="<?php echo 'https://scholarships.asu.edu/colleges' ?>">Scholarships</a><br>
  <?php endif; ?>Find and apply for relevant scholarships.
                </p>

    <?php if (isset($node_info['field_asu_ap_wue_available']['#items'][0]['value']) && $node_info['field_asu_ap_wue_available']['#items'][0]['value'] == 1): ?>
                <p><a href="<?php echo 'https://students.asu.edu/admission/wue' ?>">WUE eligible program</a><br>
                Undergraduate students from western states who enroll in this
                program are eligible for a discounted tuition rate.</p>
    <?php endif; ?>
                <p><a href="<?php echo 'https://students.asu.edu/financialaid' ?>">Financial Aid</a><br>
                ASU has many financial aid options. Almost everyone, regardless
                of income, can qualify for some form of financial aid. In fact,
                more than 70 percent of all ASU students receive some form of
                financial assistance every year.</p>

  <?php elseif ($program_type === 'graduate'): ?>
    <?php if (isset($node_info['field_asu_ap_grad_financing']['#items'][0]['safe_value'])): ?>
      <?php echo $node_info['field_asu_ap_grad_financing']['#items'][0]['safe_value']; ?>
    <?php endif ?>
  <?php endif; ?>
              </div>
            </div>
          </div>
        </div>

      <!-- Bottom white section (BW) -->

        <div class="container space-top-xl space-bot-sm">

  <?php
  // Which content to show and how.
  $careers_half = ((isset($node_info['field_asu_ap_example_careers']))
    XOR (isset($node_info['field_asu_ap_career_opps']))) ? TRUE : FALSE;
  $related_programs = (isset($node_info['field_asu_ap_related_programs'])) ? TRUE : FALSE;
  $related_programs_status = ($related_programs) ? "waiting" : "ok";

  // Generate Related Programs menu pane
  if ($related_programs === TRUE) {
    $related_programs_output = '<div class="pane-menu-tree">' . "\n";
    $related_programs_output .= '  <h4>Related Programs</h4>' . "\n";
    for ($it = 0; $it < count($node_info['field_asu_ap_related_programs']); $it++) {
      if (isset($node_info['field_asu_ap_related_programs'][$it]['#label'])) {
        $rp_result = $node_info['field_asu_ap_related_programs'][$it]['#label'];
      }
      if (!empty($rp_result)) {
        $related_programs_output .= '    <a href="/' . $node_info['field_asu_ap_related_programs'][$it]['#uri']['path'] . '">' . $rp_result . '</a>' . "\n";
        unset($rp_result);
      }
      else {
        break;
      }
      $related_programs_output .= "  <br>\n";
    }
    $related_programs_output .= "</div>\n";
  } ?>
          <div class="row">
            <div class="col-md-12" id="plan-of-study">
  <?php if ($related_programs === TRUE
    && (isset($node_info['field_asu_ap_prog_req']['#items'][0]['safe_value']))): ?>
              <div class="col-md-4 col-sm-12 asu-ap-related-programs asu-ap-related-programs-solo">
    <?php
      print $related_programs_output;
      $related_programs_status = "ok";
    ?>
              </div>
  <?php endif; ?>
            </div>
          </div>

          <div class="row">
            <div class="col-md-12" id="ap-degree-requirements">

  <?php // Program requirements (minors/certs)
  // Degree (or Enrollment for minors/certs) requirements
  $label = 'Admission';
  if ($cert_val === 'true'): ?>
    <?php if (isset($node_info['field_asu_ap_prog_req']['#items'][0]['safe_value'])): ?>
              <h3>Program requirements</h3>
      <?php
        print _asu_ap_feature_map_urls_create($node_info, $cert_val);
        print $node_info['field_asu_ap_prog_req']['#items'][0]['safe_value'];
        $label = 'Enrollment';
      ?>
    <?php endif; ?>
  <?php endif; ?>

  <?php // Degree requirements (confusingly, field_asu_ap_admission_req)
  if (isset($node_info['field_asu_ap_admission_req']['#items'][0]['safe_value'])): ?>
              <h3>Degree requirements</h3>
    <?php print $node_info['field_asu_ap_admission_req']['#items'][0]['safe_value']; ?>
  <?php endif; ?>
  <?php if (isset($node_info['field_asu_ap_req_desc']['#items'][0]['safe_value'])): ?>
              <h3><?php print $label ?> requirements</h3>
    <?php print $node_info['field_asu_ap_req_desc']['#items'][0]['safe_value']; ?>
  <?php endif; ?>

  <?php // Transfer admission requirements
  if ($program_type === 'undergrad'): ?>
    <?php if (isset($node_info['asu_ap_transfer_admis_req']['#items'][0]['safe_value'])): ?>
              <h4>Transfer admission requirements</h4>
      <?php print $node_info['asu_ap_transfer_admis_req']['#items'][0]['safe_value']; ?>
    <?php endif; ?>
  <?php endif; ?>

  <?php // Grad Additional requirement
  if ($program_type === 'graduate'): ?>
    <?php if (isset($node_info['field_asu_ap_grad_addl_req']['#items'][0]['safe_value'])): ?>
              <h4>Additional requirements</h4>
      <?php print $node_info['field_asu_ap_grad_addl_req']['#items'][0]['safe_value']; ?>
    <?php endif; ?>
  <?php endif; ?>
            </div>
          </div>

  <?php if ($program_type === 'undergrad'): ?>
    <?php $career_cols = ($careers_half) ? 12 : 6; ?>
    <?php if ($related_programs_status !== 'ok'): ?>
          <div class="row">
            <div class="col-md-12 col-sm-12 asu-ap-related-programs">
      <?php
      print $related_programs_output . "\n";
      $related_programs_status = "ok";
      ?>
            </div>
          </div>
    <?php endif; ?>
          <div class="row">
    <?php if (isset($node_info['field_asu_ap_career_opps'])): ?>
            <div class="col-md-<?php print $career_cols ?> asu-ap-careers">
              <h3>Career outlook</h3>
      <?php if (isset($node_info['field_asu_ap_career_outlook']['#items'][0]['safe_value'])): ?>
        <?php print render($node_info['field_asu_ap_career_outlook']['#items'][0]['safe_value']); ?>
      <?php elseif (isset($node_info['field_asu_ap_career_opps'])): ?>
        <?php print render($node_info['field_asu_ap_career_opps']); ?>
      <?php endif; ?>
            </div>
    <?php endif; ?>
    <?php if (isset($node_info['field_asu_ap_example_careers'])): ?>
            <div class="col-md-<?php print $career_cols ?> asu-ap-careers">
      <?php if (isset($node_info['field_asu_ap_ex_car_tf']['#items'][0]['value'])
                  && $node_info['field_asu_ap_ex_car_tf']['#items'][0]['value'] == 1): ?>
              <h3>Example careers</h3>
        <?php print render($node_info['field_asu_ap_example_careers']); ?>
      <?php endif; ?>
            </div>
    <?php endif; ?>
          </div>

  <?php elseif ($program_type === 'graduate'): ?>
          <div class="row">
            <div class="col-md-12" id="grad-text-area">
    <?php if (isset($node_info['field_asu_ap_grad_text_area']['#items'][0]['safe_value'])): ?>
      <?php echo $node_info['field_asu_ap_grad_text_area']['#items'][0]['safe_value']; ?>
    <?php endif; ?>
            </div>
          </div>
  <?php endif; ?>
        </div>

        <div class="container">
          <div class="row">
  <?php print render($page['prefooter']); ?>
          </div>
        </div>

  <?php // Additional help text?>
  <?php if ($special_categories > 0): ?>
        <div class="asu-ap-grey-section">
          <div class="container container-asu-ap-q-a">
            <div class="row row-full">
              <div class="column col-md-12">
    <?php if ($accelerated_degree_value): ?>
                <div id="asu-ap-accelerated-degree">
                  <h4>What are Accelerated Programs at ASU?</h4>
                  <div class="programs_term_content no-display" id="programs_term_accelerate">
                    <p>ASU students may accelerate their studies by earning a bachelor’s and a master’s degree
                      in as little as five years (for some programs) or by earning a bachelor’s degree in 2.5 or 3 years.</p>
                    <p>Accelerated bachelor's and master's degree programs are designed for high-achieving
                      undergraduate students who want the opportunity to combine undergraduate coursework with
                      graduate coursework to accelerate completion of their master’s degree. These programs, featuring the
                      same high-quality curriculum taught by ASU's world-renowned faculty, allow students to obtain both
                      a bachelor's and a master's degree in as little as five years.</p>
                    <p>Accelerated bachelor’s degree programs allow students to choose either a 2.5- or a
                      3-year path while participating in the same high-quality educational experience of a 4-year option.
                      Students can opt to fast-track their studies after acceptance into a participating program by
                      connecting with their academic advisor.</p>
                  </div>
                </div>
    <?php endif; ?>
    <?php if ($concurrent_degree_value === 1): ?>
                <div id="asu-ap-concurrent-degree">
                  <h4>What are Concurrent Programs at ASU?</h4>
                  <div class="programs_term_content no-display" id="programs_term_concurrent">
                    <p>Students pursuing concurrent degrees earn two distinct degrees and receive two diplomas.
                      ASU offers students two ways to earn concurrent degrees: by choosing a predetermined combination
                      or creating their own combination.  Predetermined combinations have a single admissions
                      application and one easy to follow major map.  To add a concurrent degree to your existing
                      degree, work with your academic advisor. Either way, concurrent degrees allow students to
                      pursue their own personal or professional interests.</p>
                  </div>
                </div>
    <?php endif; ?>
    <?php if ($joint_programs_value !== 0): ?>
                <div id="asu-ap-joint-programs">
                  <h4>What are Joint Programs at ASU?</h4>
                  <div class="programs_term_content no-display" id="programs_term_joint">
                    <p>Joint programs, or jointly conferred degrees, are offered by more than one college and provide
                      opportunities for students to take advantage of the academic strengths of two academic units.
                      Upon graduation, students are awarded one degree and one diploma conferred by two colleges. </p>
                  </div>
                </div>
    <?php endif; ?>
    <?php if ($new_degree_value !== 0): ?>
                <div id="asu-ap-new-degree">
                  <h4>What constitutes a New Program for ASU?</h4>
                  <div class="programs_term_content no-display" id="programs_term_new">
                    <p>ASU adds new programs to Degree Search frequently. Come back often and look for the “New Programs” option.</p>
                  </div>
                </div>
    <?php endif; ?>
    <?php if (!empty($online_program_value)): ?>
                <div id="asu-ap-online-program">
                  <h4>What are ASU's Online Programs?</h4>
                  <div class="programs_term_content no-display" id="programs_term_online">
                    <p><a href="https://asuonline.asu.edu/" target="_blank">ASU Online</a> offers programs like <?php print $title; ?>
                      in an entirely online format with multiple enrollment sessions throughout the year.</p>
                    <p>More information on the program is available <a href="<?php print $online_program_value ?>" target="_blank">directly
                        from ASU Online.</p>
                  </div>
                </div>
    <?php endif; ?>
    <?php if ($wue_program_value !== 0): ?>
                <div id="asu-ap-wue-program">
                  <h4>What is the Western Undergraduate Exchange (WUE)?</h4>
                  <div class="programs_term_content no-display">
                    <p>The Western Undergraduate Exchange (WUE) is a program in which residents of western states
                      (other than Arizona) may be eligible for reduced nonresident tuition. See more information
                      and eligibility requirements on the <a href="http://students.asu.edu/admission/wue" target="_blank">Western Undergraduate
                        Exchange (WUE) program.</a></p>
                  </div>
                </div>
    <?php endif; ?>
              </div>
            </div>
          </div>
        </div>
  <?php endif; ?>
<?php // End of degree content processing and rendering
endif; ?>

        <!-- /#main, /#main-wrapper -->
      </div>
    </div>
  </div>

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
<!-- /#page, /#page-wrapper -->
