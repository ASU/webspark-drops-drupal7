<?php
/**
 * @file Panels-pane.tpl.php
 * Main panel pane template.
 *
 * Variables available:
 * - $pane->type: the content type inside this pane
 * - $pane->subtype: The subtype, if applicable. If a view it will be the
 *   view name; if a node it will be the nid, etc.
 * - $title: The title of the content
 * - $content: The actual content
 * - $links: Any links associated with the content
 * - $more: An optional 'more' link (destination only)
 * - $admin_links: Administrative links associated with the content
 * - $feeds: Any feed icons or associated with the content
 * - $display: The complete panels display object containing all kinds of
 *   data including the contexts and all of the other panes being displayed.
 */
/** Only adding to College theme just in case some super-custom work should be done in the TPL. */
/**
 * Added preliminary $title processing to place it within the pane-content div if desired.
 */
  $title_rendered = render($title_prefix);
    if ($title) {
      $title_rendered .= '<' . $title_heading . $title_attributes . '>'
        . $title . '</' . $title_heading . '>';
    }
  $title_rendered .= render($title_suffix);
?>
<?php if ($pane_prefix): ?>
  <?php print $pane_prefix; ?>
<?php endif; ?>
<div class="<?php print $classes; ?>" <?php print $id; ?> <?php print $attributes; ?>>
  <?php if ($admin_links): ?>
    <?php print $admin_links; ?>
  <?php endif; ?>

  <?php if ($variables['title_placement'] === 'default'): ?>
    <?php print $title_rendered; ?>
  <?php endif; ?>

<?php if ($feeds): ?>
  <div class="feed">
    <?php print $feeds; ?>
  </div>
<?php endif; ?>

<div class="pane-content">
  <?php if ($variables['title_placement'] === 'in-content'): ?>
    <?php print $title_rendered; ?>
  <?php endif; ?>
  <?php print render($content); ?>
</div>

<?php if ($links): ?>
  <div class="links">
    <?php print $links; ?>
  </div>
<?php endif; ?>

<?php if ($more): ?>
  <div class="more-link">
    <?php print $more; ?>
  </div>
<?php endif; ?>
</div>
<?php if ($pane_suffix): ?>
  <?php print $pane_suffix; ?>
<?php endif; ?>
