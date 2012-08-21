<?php

/**
 * @file
 * Responsive layout builder for Panels.
 */

$plugin = array(
  'title' => t('Responsive'),
  'category' => t('Builders'),
  'icon' => 'responsive.png',
  'theme' => 'layout_responsive',
  'admin theme' => 'layout_responsive_admin',
  'css' => 'responsive.css',
  'admin css' => 'responsive-admin.css',
  'regions function' => 'layout_responsive_panels',
  'settings form' => 'layout_responsive_settings_form',
  'settings submit' => 'layout_responsive_settings_form_submit',

  // Reusable layout Builder specific directives.
  'builder' => TRUE,
  'builder tab title' => 'Add responsive layout',

  // Sublayout code almost exactly copied from flexible layouts.
  'get child' => 'layout_responsive_get_sublayout',
  'get children' => 'layout_responsive_get_sublayouts',

);

/**
 * Form callback. Add our form elements for data interchange.
 */
function layout_responsive_settings_form($display, $layout, $layout_settings) {
  // We never draw stored responsive layouts in admin mode; they must be edited
  // from the stored layout UI at that point. This can happen if the layout is
  // displayed in an admin context, but not to administer the layout per say but
  // to administer other thigns on top of the layout, such as rearranging panes
  // when switching layouts or when adding new panes.
  if (!empty($layout['layout'])) {
    return;
  }

  layout_responsive_merge_default_settings($layout_settings, $layout);

  $layoutdata = array();
  $default_regions = layout_region_load_all();
  foreach ($layout_settings['regions'] as $name => $name) {
    $layoutdata['regions'][] = array(
      'name' => $name,
      'admin_title' => $default_regions[$name]->admin_title,
    );
  }
  $layoutdata['overrides'] = $layout_settings['overrides'];

  $form = array();
  $form['layout_responsive_regions'] = array(
    '#type' => 'textarea',
    '#title' => t('Region and breakpoint configuration'),
    '#default_value' => drupal_json_encode($layoutdata),
  );

  return $form;
}

/**
 * Form submission. Process the changes to the layout.
 */
function layout_responsive_settings_form_submit(&$layout_settings, $display, $layout, $old_layout_settings) {

  $default_regions = layout_region_load_all();
  $new_layout_settings = drupal_json_decode($layout_settings['layout_responsive_regions']);

  if (!empty($new_layout_settings)) {
    foreach ($new_layout_settings['regions'] as $region) {
      $layout_settings['regions'][$region['name']] = $region['name'];

      // Save region in common regions list in case it is new.
      if (!isset($default_regions[$region['name']])) {
        $region = (object) array(
          'name' => $region['name'],
          'admin_title' => $region['admin_title'],
        );
        layout_region_save($region);
      }
    }
    $layout_settings['overrides'] = $new_layout_settings['overrides'];
  }

  // Clean out this value that was only used for communication, so it is not
  // saved with the layout.
  unset($layout_settings['layout_responsive_regions']);
}

/**
 * Merge the main responsive plugin with a layout to create a sub plugin.
 *
 * This is used for both layout_responsive_get_sublayout and
 * layout_responsive_get_sublayouts.
 */
function layout_responsive_merge_plugin($plugin, $layout) {
  $plugin['name'] = 'responsive:' . $layout->name;
  $plugin['category'] = !empty($layout->category) ? check_plain($layout->category) : t('Responsive');
  $plugin['title'] = check_plain($layout->admin_title);
  $plugin['description'] = check_plain($layout->admin_description);
  $plugin['layout'] = $layout;
  $plugin['builder'] = FALSE;
  $plugin['builder tab title'] = NULL;
  return $plugin;
}

/**
 * Callback to provide a single stored responsive layout.
 */
function layout_responsive_get_sublayout($plugin, $layout_name, $sublayout_name) {
  // Do not worry about caching; Panels is handling that for us.
  ctools_include('export');
  $item = ctools_export_crud_load('panels_layout', $sublayout_name);
  if ($item) {
    return layout_responsive_merge_plugin($plugin, $item);
  }
}

/**
 * Callback to provide all stored responsive layouts.
 */
function layout_responsive_get_sublayouts($plugin, $layout_name) {
  $layouts[$layout_name] = $plugin;
  ctools_include('export');
  $items = ctools_export_load_object('panels_layout', 'conditions', array('plugin' => 'responsive'));
  foreach ($items as $name => $item) {
    $layouts['responsive:' . $name] = layout_responsive_merge_plugin($plugin, $item);
  }

  return $layouts;
}

/**
 * Return the actual list of regions for this responsive panel.
 */
function layout_responsive_panels($display, $settings, $layout) {
  $items = array();
  layout_responsive_merge_default_settings($settings, $layout);

  // Resolve machine names to names for visual presentation in panels.
  $default_regions = layout_region_load_all();
  $region_names = array();
  foreach ($settings['regions'] as $name => $overrides) {
    $region_names[$name] = $default_regions[$name]->admin_title;
  }

  return $region_names;
}

/**
 * Merge current settings with defualt settings.
 */
function layout_responsive_merge_default_settings(&$settings, &$layout) {
  // This indicates that this is a layout that they used the checkbox
  // on. The layout is still 'flexible' but it's actually pointing
  // to another stored one and we have to load it.
  if (!empty($settings['layout'])) {
    $layout = panels_get_layout('responsive:' . $settings['layout']);
  }

  if (!empty($layout['layout'])) {
    $settings = $layout['layout']->settings;
    if ($settings) {
      return $settings;
    }
  }

  if (empty($settings)) {
    // "Clone" the regions and overrides from a default layout. This lets
    // people edit the default layout as a base for all new layouts. The default
    // implementation of the default layout is in an exported responsive layout
    // in layout.module (see layout_default_panels_layout()).
    ctools_include('plugins', 'panels');
    $default_layout_name = variable_get('layout_default_responsive_layout', 'responsive:default');
    $default_layout = panels_get_layout($default_layout_name);
    if (!empty($default_layout)) {
      $settings['regions'] = $default_layout['layout']->settings['regions'];
      $settings['overrides'] = $default_layout['layout']->settings['overrides'];
    }
  }

  return $settings;
}
/**
 *
 */
function layout_responsive_html_head_alter(&$head_elements) {
  $head_elements['viewport'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width,initial-scale=1',
    ),
  );
}
/**
 * Draw the responsive layout.
 *
 * @todo
 *   Embeddig the grid CSS inline is evil. Fix it.
 */
function theme_layout_responsive($vars) {
  $css_id = $vars['css_id'];
  $content = $vars['content'];
  $settings = $vars['settings'];
  $display = $vars['display'];
  $layout = $vars['layout'];
  $handler = $vars['renderer'];

  layout_responsive_merge_default_settings($settings, $layout);

  $breakpoints = layout_breakpoint_load_all();
  $grids = gridbuilder_load_all();

  // Render the regions ordered as configured with minimal wrappers.
  $output = '';
  $breakpoint_counters = array();
  foreach ($content as $name => $rendered) {
    if (!empty($rendered)) {
      // Add a minimal wrapper with some common classes + configured custom classes.
      // The custom classes are used for grid placement.
      $classes = array();
      $classes[] = 'layout-responsive-region';
      $classes[] = 'layout-responsive-region-' . $name;
      $classes[] = 'rld-col';
      // Add breakpoint specific column number classes.
      foreach ($settings['overrides'] as $breakpoint_name => $breakpoint_overrides) {

        // Initialize breakpoint counter. We use this counter to figure out when
        // to inject 'first' regions depending on breakpoints. This ensures the
        // spacing of regions is properly maintained.
        if (!isset($breakpoint_counters[$breakpoint_name])) {
          $breakpoint_counters[$breakpoint_name] = 0;
        }

        // Assume that this column will span the whole width.
        $this_column = $all_columns = $grids[$breakpoints[$breakpoint_name]->grid_name]->columns;

        // If the existing counters indicate we were at the end of a row with
        // the previous region, mark this one up as being the first.
        if (is_int($breakpoint_counters[$breakpoint_name] / $all_columns)) {
          $classes[] = 'rld-span-' . $breakpoint_name . '_first';
        }

        // Check if we have region specific overrides for this breakpoint.
        foreach ($breakpoint_overrides as $region_override) {
          if ($region_override['name'] == $name) {
            // Found a region override. Modify the column width to this value.
            $this_column = $region_override['columns'];
            break;
          }
        }
        $classes[] = 'rld-span-' . $breakpoint_name . '_' . $this_column;
        $breakpoint_counters[$breakpoint_name] += $this_column;
      }
      $output .= '<div class="' . join(' ', $classes) . '">';
      $output .= $rendered;
      $output .= '</div>';
    }
  }

  // Embed the grid css inline for now. Yeah, I know this is evil.
  // It is just a prototype for now, ok? I know it is evil. Yes.
  $grid_css = layout_breakpoint_get_css();
  drupal_add_css($grid_css, array('type' => 'inline'));

  return '<div class="panel-responsive clearfix">' . $output . '</div>';
}

/**
 * Draw the responsive layout admin interface.
 *
 * @todo
 *   Embeddig the grid CSS inline is evil. Fix it.
 */
function theme_layout_responsive_admin($vars) {
  $css_id = $vars['css_id'];
  $content = $vars['content'];
  $settings = $vars['settings'];
  $display = $vars['display'];
  $layout = $vars['layout'];
  $handler = $vars['renderer'];

  // We never draw stored responsive layouts in admin mode; they must be edited
  // from the stored layout UI at that point. This can happen if the layout is
  // displayed in an admin context, but not to administer the layout per say but
  // to administer other thigns on top of the layout, such as rearranging panes
  // when switching layouts or when adding new panes.
  if (!empty($layout['layout'])) {
    return theme_layout_responsive(array('css_id' => $css_id, 'content' => $content, 'settings' => $settings, 'display' => $display, 'layout' => $layout, 'renderer' => $handler));
  }

  layout_responsive_merge_default_settings($settings, $layout);

  // Add required libraries.
  drupal_add_library('system', 'ui.dialog');
  // JSON2 is required for stringifying JavaScript data structures in older browsers.
  $name = 'json2';
  if (!libraries_detect($name)) {
    watchdog('responsive', 'The JSON-js library is recommended for this module to function properly. Some older browsers do not provide the JSON function natively. Please visit !url to obtain this library.',
      array(
        '!url' => l('JSON-js (Github)', 'https://github.com/douglascrockford/JSON-js',
          array(
            'absolute' => TRUE,
            'external' => TRUE
          )
        )
      ),
      WATCHDOG_NOTICE
    );
  }
  else {
    libraries_load($name);
  }

  // Add the ResponsiveLayoutDesigner application.
  layout_responsive_load_rld_application($layout['path']);
  // Add integration code for Drupal.
  drupal_add_js($layout['path'] . '/responsive-admin.js');

  // Add data about the layout and global list of regions.
  $default_regions = layout_region_load_all();
  $default_breakpoints = layout_breakpoint_load_all();
  $default_grids = gridbuilder_load_all();

  drupal_add_js(array(
    'responsiveLayout' => array(
      'settings' => $settings,
      'defaultRegions' => $default_regions,
      'defaultBreakpoints' => $default_breakpoints,
      'defaultGrids' => $default_grids,
    )
  ), 'setting');

  drupal_add_library('system', 'ui.sortable');

  // Embed the grid css inline for now. Yeah, I know this is evil.
  // It is just a prototype for now, ok? I know it is evil. Yes.
  $grid_css = layout_breakpoint_get_css(FALSE);
  drupal_add_css($grid_css, array('type' => 'inline'));

  // This is filled in on the client side.
  return '<div id="responsive-layout-designer"></div>';
}
/**
 * Load the files necessary to launch a ResponsiveLayoutDesigner application.
 */
function layout_responsive_load_rld_application($path) {
  // This is a messy, messy list of files. Eventually we'll want to package
  // this app up into a single JavaScript file or wrap it in a Drupal library
  // indirection. And minify it for inclusion on the release.
  drupal_add_css($path . '/ResponsiveLayoutDesigner/assets/css/application.css');
  drupal_add_css($path . '/ResponsiveLayoutDesigner/assets/css/grid.css');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/assets/js/plugins/breakup/jquery.breakup.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/main.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/libs/Utils/Utils.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/libs/LayoutManager/LayoutManager.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/libs/LayoutPreviewer/LayoutPreviewer.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/libs/LayoutList/LayoutList.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/libs/LayoutStep/LayoutStep.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/libs/StepManager/StepManager.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/libs/StepList/StepList.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/libs/Step/Step.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/libs/RegionList/RegionList.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/libs/Region/Region.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/libs/GridList/GridList.js');
  drupal_add_js($path . '/ResponsiveLayoutDesigner/app/libs/Grid/Grid.js');
}
