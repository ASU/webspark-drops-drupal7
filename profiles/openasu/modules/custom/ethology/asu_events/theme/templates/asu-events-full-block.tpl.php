<?php
/**
 * ASU Events Full block tpl
 **/
?>
<div <?php print $attributes;?> class="<?php print $class . " " . $classes;?>row">
  <div class="asu-block-left col-md-6">
    <?php print render($featured); ?>
  </div>
  <div class="asu-block-right col-md-6">
    <?php print render($events_items); ?>
  </div>
</div>
