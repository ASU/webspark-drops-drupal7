<!DOCTYPE html>
<!--[if IEMobile 7]><html class="iem7" <?php print $html_attributes; ?>><![endif]-->
<!--[if lte IE 6]><html class="lt-ie9 lt-ie8 lt-ie7" <?php print $html_attributes; ?>><![endif]-->
<!--[if (IE 7)&(!IEMobile)]><html class="lt-ie9 lt-ie8" <?php print $html_attributes; ?>><![endif]-->
<!--[if IE 8]><html class="lt-ie9" <?php print $html_attributes; ?>><![endif]-->
<!--[if (gte IE 9)|(gt IEMobile 7)]><!--><html <?php print $html_attributes . $rdf_namespaces; ?>><!--<![endif]-->
<head>
<?php print $head; ?>
<title><?php print $head_title; ?></title>
<meta http-equiv="x-ua-compatible" content="IE=edge">
  <?php $use_responsive_behaviors = TRUE; if ($use_responsive_behaviors): ?>
<meta name="viewport" content="width=device-width, initial-scale=1.0" />
  <?php else: ?>
<meta name="viewport" content="width=1000" />
  <?php endif; ?>
<?php print $styles; ?>
<?php print $scripts; ?>
<?php print $polyfills; ?>
  <!--[if lte IE 8]>
<script type="text/javascript">
  var os_c = document.createElement;os_c('header');os_c('nav');os_c('section');os_c('article');os_c('aside');os_c('footer');os_c('hgroup');os_c('figure');
</script>
  <![endif]-->
</head>
<body class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div id="skip-link">
    <a href="<?php print $skip_link_target; ?>" class="element-invisible element-focusable" tabindex="1"><?php print t('Skip to main content'); ?></a>
  </div>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>
