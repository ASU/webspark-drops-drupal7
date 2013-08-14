<?php
/**
 * @file
 * OpenASU Bootstrap's primary theme functions and alterations.
 */

/**
 * Load Kalatheme dependencies.
 *
 * Implements template_preprocess_html().
 */
function openasu_bootstrap_preprocess_html(&$variables) {
  // Load student CSS if this is a student template
  if (variable_get('asu_brand_is_student', 'default') == 'student') {
    drupal_add_css(drupal_get_path('theme', 'openasu_bootstrap') . '/css/student/' .
      variable_get('asu_brand_is_student', 'default') .  '.css', array(
      'group' => CSS_THEME,
      'media' => 'screen',
      'weight' => '100',
      )

    );
    // Load menu CSS for student header
    if (variable_get('asu_brand_student_color', 'black') != 'black') {
      drupal_add_css(drupal_get_path('theme', 'openasu_bootstrap') . '/css/student/menu/' .
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
function openasu_bootstrap_ctools_plugin_post_alter(&$plugin, &$info) {
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
function openasu_bootstrap_preprocess_page(&$variables) {
  $variables['asu_picture'] = '';
  $variables['asu_local_navicon'] = '';

  // Make sure default picture gets responsive panopoly stylingz
  if (theme_get_setting('default_picture', 'openasu_bootstrap') && theme_get_setting('picture_path', 'openasu_bootstrap')) {
    $variables['asu_picture'] = theme('image_style', array(
      'style_name' => 'panopoly_image_full',
      'path' => theme_get_setting('picture_path', 'openasu_bootstrap'),
    )
    );
  }

  // Parse sitename for color
  $variables['site_name_first'] = '';
  $variables['site_name_last'] = '';
  $middle = strrpos(substr($variables['site_name'], 0, floor(strlen($variables['site_name']) / 2)), ' ') + 1;
  $variables['site_name_first'] = substr($variables['site_name'], 0, $middle);  // "The Quick : Brown Fox "
  $variables['site_name_last'] = substr($variables['site_name'], $middle);  // "Jumped Over The Lazy / Dog"

  // Build the navicon if applicable
  if (!theme_get_setting('hide_local_menu_navicon', 'openasu_bootstrap')) {
    $variables['asu_local_navicon'] = str_replace('href="/"', 'href="#"', l("<span class='icon-bar'></span><span class='icon-bar'></span><span class='icon-bar'></span>", NULL,
      array(
        'attributes' => array(
          'data-target' => '.nav-collapse',
          'data-toggle' => 'collapse',
          'class' => 'btn btn-navbar'
        ),
        'html' => TRUE
      )
    ));
  }
}

/**
 * Override or insert variables into the page template.
 *
 * Implements template_process_page().
 */
function openasu_bootstrap_preprocess_block(&$variables) {
  $block = $variables['block'];
  if ($block->delta == 'main-menu' && $block->module == 'system' && $block->status == 1 && $block->theme = 'openasu_bootstrap') {
    // Get the entire main menu tree.
    $main_menu_tree = array();
    $main_menu_tree = menu_tree_all_data('main-menu', NULL, 2);
    // Add the rendered output to the $main_menu_expanded variable.
    $main_menu_asu = menu_tree_output($main_menu_tree);
    $variables['content'] = theme('links__system_main_menu', array(
      'links' => $main_menu_asu,
      'attributes' => array(
        'class' => array('nav pull-left'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      ),));
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
function openasu_bootstrap_block_view_alter(&$data, $block) {
  // Add the attributes if applicable
  if (($block->module == 'asu_brand') && ($block->delta == 'asu_brand_header')) {
    if (theme_get_setting('hide_local_menu_navicon', 'openasu_bootstrap')) {
      $data['content'] = str_replace('<a href="javascript:toggleASU();">', '<a href="javascript:toggleASU();" data-target=".hidden-collapse" data-toggle="collapse">', $data['content']);
    }
  }
}


/**
 * Implements theme_links__system_main_menu.
 */
function openasu_bootstrap_links__system_main_menu($variables) {
  $links = $variables['links'];
  $attributes = $variables['attributes'];
  $heading = $variables['heading'];
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
      if (!empty($link['#below'])) {
        $class[] = 'dropdown';
        //$link['#attributes']['data-toggle'] = 'dropdown';
        $link['#attributes']['class'][] = 'dropdown-toggle';
        //$link['#href'] = NULL;
      }
      $options['attributes'] = $link['#attributes'];

      $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';

      if (isset($link['#href'])) {
        // Pass in $link as $options, they share the same keys.
        $output .= l($link['#title'], $link['#href'], array('attributes' => $link['#attributes']));
      }
      // Put in empty anchor for dropdown.
      elseif ($link['#attributes']['data-toggle'] && !isset($link['#href'])) {
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

      if (!empty($link['#below'])) {
        $output .= theme('links__system_main_menu', array(
          'links' => $link['#below'],
          'attributes' => array(
            'class' => array('dropdown-menu'),
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

/**
 * Implements hook_form_FORM_ID_alter().
 */
function openasu_bootstrap_form_panels_edit_style_settings_form_alter(&$form, &$form_state) {
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

