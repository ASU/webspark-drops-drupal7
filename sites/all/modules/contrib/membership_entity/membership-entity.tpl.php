<?php

/**
 * @file
 * Default theme implementation to display a membership.
 *
 * Available variables:
 * - $member_id: The unique membership id.
 * - $content: An array of membership fields.
 * - $classes: A string of classes that can be used to style the membership.
 *
 * Other variables:
 * - $membership_entity: The full membership entity object.
 * - $primary_member: Formatted username of the primary member.
 * - $classes_array: An array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * Status variables:
 * - $view_mode: Membership view mode. For example, "full", "account".
 *
 * @see template_preprocess()
 * @see template_preprocess_membership_entity()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
<div id="membership-<?php print $membership_entity->mid; ?>" class="<?php print $classes; ?> clearfix">
  <div class="content">
    <?php
      hide($content['links']);
      print render($content);
    ?>
  </div>
  <?php print render($content['links']); ?>
</div>
