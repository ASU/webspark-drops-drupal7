<?php
/**
 * Override TB Megamenu module's main nav TPL
 * Logo: ASU main logo
 * Unit: (OPTIONAL) If parent of main site's focus is required.
 * Title: Main site title
 */
//dpm(get_defined_vars(), 'TB MM nav TPL');;
if (isset($variables['site_unit_name']) && !empty($variables['site_unit_name'])) {
  $unit_name = $variables['site_unit_name'];
  $site_name_extra_class = 'ws2-has-unit-name';
} else {
  $unit_name = '';
  $site_name_extra_class = 'ws2-no-unit-name';
}
?>
<div class="tb-megamenu-ws2-shell">
<div class="ws2-global-header-logo">
  <a href="https://www.asu.edu/">
    <img src="/profiles/openasu/themes/elpuente/images/ASU-logo-stacked-2x.png" alt="Arizona State University" width="93" height="72" />
  </a>
</div>

<?php if(!empty($unit_name)) :?>
  <div class="ws2-global-header-unit"><?php print $unit_name ?></div>
<?php endif; ?>
<div class="ws2-global-header-title subdomain-name <?php print $site_name_extra_class; ?>"><?php print $site_name; ?></div>
<ul <?php print $attributes;?> class="<?php print $classes;?>">
  <?php print $lis;?>
</ul>
</div>
