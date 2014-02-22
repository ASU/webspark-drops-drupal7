<?php
/**
 * @file
 * asu_webspark_bootstrap's primary theme functions and alterations.
 */

/**
 * Load Kalatheme dependencies.
 *
 * Implements template_preprocess_html().
 */
function asu_webspark_bootstrap_preprocess_html(&$variables) {
  // Add IE meta tag to force IE rendering mode
  $meta_ie_render_engine = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'content' =>  'IE=edge,chrome=1',
      'http-equiv' => 'X-UA-Compatible',
    )
  );
  drupal_add_html_head($meta_ie_render_engine, 'meta_ie_render_engine');

  // Add conditional stylesheets for IE
  drupal_add_css(path_to_theme() . '/css/ie9.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'IE 9', '!IE' => FALSE), 'preprocess' => FALSE));
  drupal_add_css(path_to_theme() . '/css/ie8.css', array('group' => CSS_THEME, 'browsers' => array('IE' => 'IE 8', '!IE' => FALSE), 'preprocess' => FALSE));

  // Load student CSS if this is a student template
  if (variable_get('asu_brand_is_student', 'default') == 'student') {
    drupal_add_css(drupal_get_path('theme', 'asu_webspark_bootstrap') . '/css/student/' .
      variable_get('asu_brand_is_student', 'default') .  '.css', array(
      'group' => CSS_THEME,
      'media' => 'screen',
      'weight' => '100',
      )

    );
    // Load menu CSS for student header
    if (variable_get('asu_brand_student_color', 'black') != 'black') {
      drupal_add_css(drupal_get_path('theme', 'asu_webspark_bootstrap') . '/css/student/menu/' .
        variable_get('asu_brand_student_color', 'black') .  '.css', array(
        'group' => CSS_THEME,
        'media' => 'screen',
        'weight' => '200',
        )
      );
    }
  }
}

/**
 * Implements hook_ctools_plugin_post_alter()
 */
function asu_webspark_bootstrap_ctools_plugin_post_alter(&$plugin, &$info) {
  if ($info['type'] == 'styles') {
    if ($plugin['name'] == 'kalacustomize') {
      $plugin['title'] = 'ASU Customize';
    }
  }
}

/**
 * Override or insert variables into the page template.
 *
 * Implements template_process_page().
 */
function asu_webspark_bootstrap_preprocess_page(&$variables) {
  $variables['asu_picture'] = '';
  $variables['asu_local_navicon'] = '';

  // Make sure default picture gets responsive panopoly stylingz
  if (theme_get_setting('default_picture', 'asu_webspark_bootstrap') && theme_get_setting('picture_path', 'asu_webspark_bootstrap')) {
    $image_style = module_exists('asu_cas') ? 'asu_header_image' : 'panopoly_image_full';
    $variables['asu_picture'] = theme('image_style', array(
      'style_name' => $image_style,
      'path' => theme_get_setting('picture_path', 'asu_webspark_bootstrap'),
    )
    );
  }

  // Parse sitename for color
  $variables['site_name_first'] = '';
  $variables['site_name_last'] = '';
  if (strpos($variables['site_name'], ' ') !== FALSE) {
    $site_name_words = explode(" ", $variables['site_name']);
    $middle = floor(count($site_name_words) / 2);
    $variables['site_name_first'] = implode(" ", array_slice($site_name_words, 0, $middle));
    $variables['site_name_last'] = implode(" ", array_slice($site_name_words, $middle, count($site_name_words) - $middle));
  }
  else {
    $variables['site_name_last'] = $variables['site_name'];
  }

}


/**
 * Override or insert variables into the page template.
 *
 * Implements template_process_page().
 */
function asu_webspark_bootstrap_preprocess_block(&$variables) {
  $block = $variables['block'];
  if ($block->delta == 'main-menu' && $block->module == 'system' && $block->status == 1 && $block->theme = 'asu_webspark_bootstrap') {
    // Get the entire main menu tree.
    $main_menu_tree = array();
    $main_menu_tree = menu_tree_all_data('main-menu', NULL, 2);
    // Add the rendered output to the $main_menu_expanded variable.
    //
    $main_menu_asu = menu_tree_output($main_menu_tree);
    $pri_attributes = array(
      'class' => array(
        'nav',
        'navbar-nav',
        'links',
        'clearfix',
      ),
    );
    $variables['content'] = theme('links__system_main_menu', array(
      'links' => $main_menu_asu,
      'attributes' => $pri_attributes,
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),
    ));
    $block->subject = '';
  }
}

/**
 * Implements hook_block_view_alter().
 *
 * We are using this to inject the bootstrap data-toggle/data-target attributes into the ASU
 * Header so that it can also activate the local menu.
 *
 */
function asu_webspark_bootstrap_block_view_alter(&$data, $block) {
  // Add the attributes if applicable
  if (($block->module == 'asu_brand') && ($block->delta == 'asu_brand_header')) {
    $data['content'] = str_replace('<a href="javascript:toggleASU();">', '<a href="javascript:toggleASU();" data-target=".navbar-collapse" data-toggle="collapse">', $data['content']);
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function asu_webspark_bootstrap_form_panels_edit_style_settings_form_alter(&$form, &$form_state) {
  // Add some extra ASU styles if extra styles are on
  if (isset($form['general_settings']['settings']['title'])) {
    $styles = array('title', 'content');
    foreach ($styles as $style) {
      $form['general_settings']['settings'][$style]['attributes']['#options'] += array(
        'featured-text' => 'ASU FEATURED TEXT',
      );
    }
  }
}

/**
 * Implements theme_links__system_main_menu.
 */
function asu_webspark_bootstrap_links__system_main_menu($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
  $trail = menu_get_active_trail();
  array_shift($trail);
  unset($links['#sorted']);
  unset($links['#theme_wrappers']);
  global $language_url;
  $output = '';

  if (count($links) > 0) {
    $output = '';

    // Treat the heading first if it is present to prepend it to the
    // list of links.
    if (!empty($heading)) {
      if (is_string($heading)) {
        // Prepare the array that will be used when the passed heading
        // is a string.
        $heading = array(
          'text' => $heading,
          // Set the default level of the heading.
          'level' => 'h2',
        );
      }
      $output .= '<' . $heading['level'];
      if (!empty($heading['class'])) {
        $output .= drupal_attributes(array('class' => $heading['class']));
      }
      $output .= '>' . check_plain($heading['text']) . '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 1;

    foreach ($links as $key => $link) {
      $class = array($key);
      $link['#attributes'] = (isset($link['#localized_options']['attributes'])) ? $link['#localized_options']['attributes'] : array();

      // Add first/last/active classes to help out themers.
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['#href']) && ($link['#href'] == $_GET['q'] || ($link['#href'] == '<front>' && drupal_is_front_page()))
        && (empty($link['#language']) || $link['#language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      // Check for, and honor active states set by context menu reactions
      if (module_exists('context')) {
        $contexts = context_active_contexts();
        foreach ($contexts as $context) {
          if ((isset($context->reactions['menu']))) {
            if ($link['#href'] == $context->reactions['menu']) {
              $class[] = 'active';
            }
          }
        }
      }
      $options['attributes'] = $link['#attributes'];
      // Make list item a dropdown if we have child items.
      if (!empty($link['#below'])) {
        $class[] = 'dropdown';
        $class[] = 'clearfix';
      }
      if ($link['#original_link']['mlid'] == $trail[0]['mlid']) {
        $class[] = 'active';
      }
      $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

      if (isset($link['#href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['#title'], $link['#href'], array('attributes' => $link['#attributes']));
      }
      elseif (!empty($link['#title'])) {
        // Wrap non-<a> links in <span> for adding title and class attributes.
        if (empty($link['#html'])) {
          $link['#title'] = check_plain($link['#title']);
        }
        $span_attributes = '';
        if (isset($link['#attributes'])) {
          $span_attributes = drupal_attributes($link['#attributes']);
        }
        $output .= '<span' . $span_attributes . '>' . $link['#title'] . '</span>';
      }

      // If link has child items, print a toggle and dropdown menu.
      if (!empty($link['#below'])) {
        $dropdown_id = 'main-menu-dropdown-' . $i;
        $output .= '<a href="#" class="dropdown-toggle pull-right" data-toggle="dropdown" id="' . $dropdown_id. '"><span class="caret"></span></a>';
        $output .= theme('links__system_main_menu', array(
          'links' => $link['#below'],
          'attributes' => array(
            'class' => array('dropdown-menu'),
            'role' => 'menu',
            'aria-labelledby' => $dropdown_id
          ),
        ));
      }

      $i++;
      $output .= "</li>\n";
    }

    $output .= '</ul>';
  }

  return $output;
}

