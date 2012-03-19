<?php

/**
 * @file
 * Display Suite 3 column stacked template HTML 5 version.
 */
?>
<div class="ds-3col-stacked-html5 <?php print $classes;?> clearfix">

  <?php if (isset($title_suffix['contextual_links'])): ?>
  <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>

  <?php if ($header): ?>
    <header class="group-header<?php print $header_classes; ?>">
      <?php print $header; ?>
    </header>
  <?php endif; ?>

  <?php if ($left): ?>
    <aside class="group-left<?php print $left_classes; ?>">
      <?php print $left; ?>
    </aside>
  <?php endif; ?>

  <?php if ($middle): ?>
    <section class="group-middle<?php print $middle_classes; ?>">
      <?php print $middle; ?>
    </section>
  <?php endif; ?>

  <?php if ($right): ?>
    <aside class="group-right<?php print $right_classes; ?>">
      <?php print $right; ?>
    </aside>
  <?php endif; ?>

  <?php if ($footer): ?>
    <footer class="group-footer<?php print $footer_classes; ?>">
      <?php print $footer; ?>
    </footer>
  <?php endif; ?>
</div>