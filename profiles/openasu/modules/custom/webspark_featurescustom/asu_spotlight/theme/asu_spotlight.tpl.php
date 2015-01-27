<?php
/**
 * @file
 * Default output for an ASU Spotlight object.
*/
?>

<div <?php print drupal_attributes($settings['attributes'])?>>
  <?php print theme('asu_spotlight_list', array('items' => $items, 'settings' => $settings)); ?>
</div>
