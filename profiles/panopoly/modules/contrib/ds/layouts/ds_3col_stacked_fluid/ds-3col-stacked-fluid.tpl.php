<?php

/**
 * @file
 * Display Suite fluid 3 column 25/50/25 stacked template.
 */
?>
<?php
  // Add sidebar classes so that we can apply the correct width to the center region in css.
  if (($left && !$right) || ($right && !$left)) $classes .= ' group-one-sidebar';
  if ($left && $right) $classes .= ' group-two-sidebars';
  if ($left) $classes .= ' group-sidebar-left';
  if ($right) $classes .= ' group-sidebar-right';
?>
<div class="ds-3col-stacked-fluid <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if ($header): ?>
    <div class="group-header<?php print $header_classes; ?>">
      <?php print $header; ?>
    </div>
  <?php endif; ?>

  <?php if ($left): ?>
    <div class="group-left<?php print $left_classes; ?>">
      <?php print $left; ?>
    </div>
  <?php endif; ?>

  <?php if ($middle): ?>
    <div class="group-middle<?php print $middle_classes; ?>">
      <?php print $middle; ?>
    </div>
  <?php endif; ?>

  <?php if ($right): ?>
    <div class="group-right<?php print $right_classes; ?>">
      <?php print $right; ?>
    </div>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="group-footer<?php print $footer_classes; ?>">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>
</div>
