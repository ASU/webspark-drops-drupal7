<?php drupal_add_css(drupal_get_path('module', 'webspark_panels_styles') . '/plugins/styles/customstyles/css/customstyles.css', array('scope' => 'header', 'weight' => 99, 'group' => CSS_DEFAULT)); ?>

<?php drupal_add_js(drupal_get_path('module', 'webspark_panels_styles') . '/plugins/styles/customstyles/js/customstyles.js', array('scope' => 'footer', 'group' => JS_THEME, 'weight' => 98)); ?>

<div class="customstyles-region work-region-it  <?php print $classes; ?> <?php print (isset($settings['fullwidthbg'])) ? $settings['fullwidthbg'] : 'max-payne'; ?>
<?php print (isset($settings['panerowpad'])) ? $settings['panerowpad'] : ''; ?>
<?php print (isset($settings['panespace'])) ? $settings['panespace'] : ''; ?>">
  <?php print render($content); ?>
</div>
