<li <?php print $attributes;?> class="<?php print $classes;?>">
  <a href="<?php print in_array($item['link']['href'], array('<nolink>')) ? "#" : url($item['link']['href'], $item['link']['options']);?>" <?php echo drupal_attributes($item['link']['#attributes']); ?>>
    <?php if(!empty($item_config['xicon'])) : ?>
      <i class="<?php print $item_config['xicon'];?>"></i>
    <?php endif;?>    
    <?php print t($item['link']['title']);?>
    <?php if($submenu && $block_config['auto-arrow']) :?>
      <span class="caret"></span>
    <?php endif;?>
    <?php if(!empty($item_config['caption'])) : ?>
      <span class="mega-caption"><?php print t($item_config['caption']);?></span>
    <?php endif;?>
  </a>
  <?php print $submenu ? $submenu : "";?>
</li>
