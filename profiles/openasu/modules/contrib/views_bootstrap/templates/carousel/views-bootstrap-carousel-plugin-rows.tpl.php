<?php print $image ?>

<?php if (!empty($title) || !empty($description)): ?>
  <div class="carousel-caption">
    <?php if (!empty($title)): ?>
      <h3><?php print $title ?></h3>
    <?php endif ?>

    <?php if (!empty($description)): ?>
      <p><?php print $description ?></p>
    <?php endif ?>
  </div>
<?php endif ?>