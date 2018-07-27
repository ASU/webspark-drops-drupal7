<?php
/**
 * ASU Events Full block tpl
 **/

?>
<div <?php print $attributes;?> class="<?php print $class . " " . $classes;?> row">
  <?php print render($events_items); ?>
</div>
