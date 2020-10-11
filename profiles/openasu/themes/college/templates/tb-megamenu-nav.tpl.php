<?php
/**
 * Override TB Megamenu module's main nav TPL
 * Logo: ASU main logo
 * Unit: (OPTIONAL) If parent of main site's focus is required.
 * Title: Main site title
 */
?>
<div id="tb-megamenu-ws2-shell" class="tb-megamenu-ws2-shell">
  <div class="ws2-global-header-logo">
    <a href="https://www.asu.edu/">
      <img src="/profiles/openasu/themes/college/images/ASU-logo-stacked-2x.png" alt="Arizona State University" width="93" height="72" />
    </a>
  </div>

<?php if(isset($site_unit_name) && !empty($site_unit_name)) :?>
  <div class="ws2-global-header-unit"><?php print $site_unit_output ?></div>
<?php endif; ?>

  <div class="ws2-global-header-title subdomain-name <?php print $site_name_extra_class; ?>">
  <?php print $site_name_output; ?></div>
  <ul <?php print $attributes;?> class="<?php print $classes;?>">
    <?php print $lis;?>
  </ul>
</div>
