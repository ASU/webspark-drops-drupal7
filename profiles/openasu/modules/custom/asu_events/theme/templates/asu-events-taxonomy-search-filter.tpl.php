<?php
/**
 * ASU Events Taxonomy Search Categories
 **/
  $top_filters = $filters['top'];
?>
<div class="event-search-filters">
  <ul class="event-category-filters <?php print $filters['class'] ?>">
  <?php foreach ($top_filters as $top_filter ) { ?>
    <li class="<?php print $top_filter['active'] ?>">
      <a href="#">
        <img class="category-image" src="<?php print $top_filter['img'] ?>" alt="<?php print $top_filter['title'] ?>">
        <span class="category-name"><?php print $top_filter['title'] ?></span>
        <span class="fa fa-plus"></span>
      </a>
    </li>
  <?php } ?>
  </ul>
</div>
