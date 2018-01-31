<div class="jumbotext-wrapper position-<?php print render($content['field_webspark_jumbo_position']['#items'][0]['value']); ?> <?php print $classes; ?>"<?php print $attributes; ?>>
  <?php // Title only addition to default fieldable-panels-pane.tpl.php; Same as webspark banner TPL.
  print render($elements['title']);
  ?>
  <?php print render($title_suffix); ?>
  <?php print render($content); ?>
</div>
