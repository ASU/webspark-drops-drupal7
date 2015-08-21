<?php
/**
 * @file
 * Default output for an ASU Spotlight object.
 */
?>

<div class="field-type-asu-directory">


  <div id="asu_directory_people_controls_top"
       class="asu_directory_people_controls">

    <span class="asu_directory_people_search_group">
    <div class="asu_directory_people_search_group">
      <input class="input-main-search form-control form-text"
             id="asu_directory_people_search_box" placeholder="Search"/>
      <button id="asu_directory_people_search_btn"
              class="btn-main-search btn btn-primary asu_directory_people_button">
        <i class="fa fa-search"></i></button>
      '
    </div>
  </div>

  <div class="row">

    <?php if ($items[0]['directory_config']['show_tree']): ?>
    <div class="col-md-4">
      <?php print theme('asu_dir_dept_tree', array(
        'items' => $items,
        'settings' => $settings
      )); ?>
    </div>
    <div class="col-md-8">
      <?php else: ?>
      <div class="col-md-12">
        <?php endif; ?>
        <?php print theme('asu_dir_people_list', array(
          'items' => $items,
          'settings' => $settings
        )); ?>
      </div>

    </div>

  </div>
