<?php

/**
 * @file
 * Display Suite fluid 2 column stacked template.
 */
?>
<?php
  // Add sidebar classes so that we can apply the correct width in css.
  if (($left && !$right) || ($right && !$left)) {
    $classes .= ' group-one-column';
  }
?>
<div class="ds-2col-stacked-fluid <?php print $classes;?> clearfix">

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