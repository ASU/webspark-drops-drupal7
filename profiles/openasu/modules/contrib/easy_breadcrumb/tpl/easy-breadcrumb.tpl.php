<?php

/**
 * @file
 * Easy breadcrumb template file.
 */

if ($segments_quantity > 0): ?>
  <div itemscope class="easy-breadcrumb" itemtype="<?php print $list_type; ?>">
    <?php foreach ($breadcrumb as $i => $item): ?>
      <span itemprop="itemListElement" itemscope itemtype="http://schema.org/ListItem">
        <?php print $item; ?>
        <meta itemprop="position" content="<?php print $i; ?>" />
      </span>
      <?php if ($i < $segments_quantity - $separator_ending): ?>
         <span class="easy-breadcrumb_segment-separator"><?php print $separator; ?></span>
      <?php
      endif; ?>
    <?php
    endforeach; ?>
  </div>
<?php
endif; ?>
