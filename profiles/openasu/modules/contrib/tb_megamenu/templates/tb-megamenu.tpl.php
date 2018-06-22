<div <?php print $attributes;?> class="<?php print $classes;?>" role="navigation">
  <?php if($section == 'frontend') :?>
    <div class="nav-collapse <?php print $block_config['always-show-submenu'] ? ' always-show' : '';?>">
  <?php endif;?>
  <?php print $content;?>
  <?php if($section == 'frontend') :?>
    </div>
  <?php endif;?>
</div>
