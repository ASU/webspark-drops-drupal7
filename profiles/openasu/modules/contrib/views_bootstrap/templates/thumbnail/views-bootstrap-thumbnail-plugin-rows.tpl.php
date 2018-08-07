<?php
/**
 * @file views-bootstrap-thumbnail-plugin-rows.tpl.php
 * Default simple view template to display Bootstrap Thumbnails.
 *
 * @ingroup views_templates
 */
?>

<?php print $image ?>

<?php if (!empty($title) || !empty($content)): ?>
  <div class="caption">
    <?php if (!empty($title)): ?>
      <h3><?php print $title ?></h3>
    <?php endif ?>

    <?php foreach ($content as $field): ?>
      <?php if (!empty($field)): ?>
        <?php print $field ?>
      <?php endif ?>
    <?php endforeach ?>
  </div>
<?php endif ?>
