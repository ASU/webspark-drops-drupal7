<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
	<?php // Title is addition to default fieldable-panels-pane.tpl.php
  print render($elements['title']);
  ?>
  <?php print render($title_suffix); ?>
  <?php print render($content); ?>
</div>
