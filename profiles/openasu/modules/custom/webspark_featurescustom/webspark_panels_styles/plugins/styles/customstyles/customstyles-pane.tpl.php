<?php
/**
 * @file panestyles-pane.tpl.php
 * template file for pane styles defined in panestyles plugin
 *
 * Variables available:
 * - $settings['my_pane_classes']: CSS Classes for Panes
 * - $settings['heading_classes']: CSS Classes for Headings
 * - $content->title: The title of the panel pane
 * - $content: An object containing the actual content of the pane
 * - $links: Any links associated with the content
 * - $more: An optional 'more' link (destination only)
 * - $admin_links: Administrative links associated with the content
 * - $feeds: Any feed icons or associated with the content
 * - $display: The complete panels display object containing all kinds of
 *   data including the contexts and all of the other panes being displayed.
 */

?>
<div class="panel-pane <?php print $classes; ?> <?php print (isset($settings['fullwidthbg'])) ? $settings['fullwidthbg'] . ' maxpayne ': ''; ?> 
 <?php print (isset($settings['panerowpad'])) ? $settings['panerowpad'] : ''; ?> 
 <?php print (isset($settings['panespace'])) ? $settings['panespace'] : ''; ?>">

  <?php if (isset($content->title)): ?>
  <h2 class="pane-title"><?php print $content->title; ?></h2>
  <?php endif; ?>

  <div class="pane-content">
    <?php print render($content->content); ?>
  </div>

</div>
