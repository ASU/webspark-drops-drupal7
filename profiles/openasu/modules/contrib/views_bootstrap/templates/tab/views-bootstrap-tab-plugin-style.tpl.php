<?php if (!empty($title)): ?>
  <h3><?php print $title ?></h3>
<?php endif ?>

<div id="views-bootstrap-tab-<?php print $id ?>" class="<?php print $classes ?>">
  <ul class="nav nav-<?php print $tab_type?> <?php if ($justified) print 'nav-justified' ?>">
    <?php foreach ($tabs as $key => $tab): ?>
     <li class="<?php if ($key == $first_key) print 'active'?>">
       <a href="#tab-<?php print "{$id}-{$key}" ?>" data-toggle="tab"><?php print $tab ?></a>
     </li>
    <?php endforeach ?>
  </ul>
  <div class="tab-content">
    <?php foreach ($rows as $key => $row): ?>
      <div class="tab-pane <?php if ($key == $first_key) print 'active'?>" id="tab-<?php print "{$id}-{$key}" ?>">
        <?php print $row ?>
      </div>
    <?php endforeach ?>
  </div>
</div>

