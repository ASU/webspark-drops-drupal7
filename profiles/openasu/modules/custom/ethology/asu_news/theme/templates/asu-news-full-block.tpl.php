<?php
/**
 * ASU News Full block tpl
 **/

?>
<div <?php print $attributes;?> class="<?php print $classes;?> row">
  <div class="asu-block-left col-md-7">
    <?php print render($featured); ?>
  </div>
  <div class="asu-block-right col-md-5">
    <?php print render($news_items); ?>
  </div>
</div>
