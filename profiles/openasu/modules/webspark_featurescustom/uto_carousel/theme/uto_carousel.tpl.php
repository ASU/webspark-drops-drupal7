<?php
/**
 * @file
 * Default output for a FlexSlider object.
*/
?>
<div
    Blah Blah Blah
    <?php print drupal_attributes($settings['attributes'])?>>



  <?php print theme('uto_carousel_list', array('items' => $items, 'settings' => $settings)); ?>
</div>
