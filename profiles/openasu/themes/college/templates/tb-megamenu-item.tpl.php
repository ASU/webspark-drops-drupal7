<?php
if ($item['link']['title'] === 'Buttons-Links') {
//  dpm(get_defined_vars());
}
//dpm($level, 'level');
?>
<li <?php print $attributes;?> class="<?php print $classes;?>" aria-level="<?php print $level; ?>">
  <a href="<?php print in_array($item['link']['href'], array('<nolink>')) ? "#" : url($item['link']['href'], $item['link']['options']);?>" <?php echo drupal_attributes($item['link']['#attributes']); ?><?php if ($submenu): ?> aria-haspopup="true"<?php endif; ?>>
    <?php if(!empty($item_config['xicon'])) : ?>
      <span class="<?php print $item_config['xicon'];?>"></span>
    <?php endif;?>
    <?php print t($item['link']['title']);?>
    <?php if($submenu && $block_config['auto-arrow'] && $level === 1) :?>
      <span class="fa fa-chevron-down"></span>
    <?php endif;?>
    <?php if(!empty($item_config['caption'])) : ?>
      <span class="mega-caption"><?php print t($item_config['caption']);?></span>
    <?php endif;?>
  </a>
  <?php print $submenu ? $submenu : "";?>
</li>
