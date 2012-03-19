<?php

/**
 * @file
 * Display Suite 4 column template.
 */
?>
<div class="ds-4col <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if ($first): ?>
    <div class="group-first<?php print $first_classes; ?>">
      <?php print $first; ?>
    </div>
  <?php endif; ?>

  <?php if ($second): ?>
    <div class="group-second<?php print $second_classes; ?>">
      <?php print $second; ?>
    </div>
  <?php endif; ?>

  <?php if ($third): ?>
    <div class="group-third<?php print $third_classes; ?>">
      <?php print $third; ?>
    </div>
  <?php endif; ?>

  <?php if ($fourth): ?>
    <div class="group-fourth<?php print $fourth_classes; ?>">
      <?php print $fourth; ?>
    </div>
  <?php endif; ?>
</div>