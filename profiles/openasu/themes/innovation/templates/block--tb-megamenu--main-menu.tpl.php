<div <?php print $attributes;?> class="<?php print $classes;?>">
  <?php 
    if(!isset($section)){
        $section = '';
    }
    if($section == 'frontend') :?>

    <div class="nav-collapse collapse<?php print $block_config['always-show-submenu'] ? ' always-show' : '';?>">
  <?php endif;?>
  <?php
      
        $tempContent = str_replace(
    '<button data-target=".nav-collapse" data-toggle="collapse" class="btn btn-navbar tb-megamenu-button" type="button">
      <i class="icon-reorder"></i>
    </button>'
          ,'',$content);

        print $tempContent;
        ?>
  <?php if($section == 'frontend') :?>
    </div>
  <?php endif;?>
</div>
