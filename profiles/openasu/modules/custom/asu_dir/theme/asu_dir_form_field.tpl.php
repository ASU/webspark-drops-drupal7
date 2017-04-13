<?php
/**
 * @file
 * Default output for an ASU Spotlight object.
 */
?>

<div class="row btn-group">
  <h4>Customize</h4>

  <div class="btn-group col-md-12" role="group"
       id="asu_directory_admin_toggles">
    <button type="button" id="asu_directory_show_tree" class="btn btn-default">
      Show Tree in Display
    </button>
    <button type="button" id="asu_directory_show_managers"
            class="btn btn-default"> Default to Rank Sort
    </button>
    <button type="button" id="asu_directory_show_breadcrumbs"
            class="btn btn-default">Show Breadcrumbs
    </button>
    <button type="button" id="asu_directory_custom_query"
            class="btn btn-default">Use Custom Query
    </button>
  </div>
</div>

<div class="row asu_directory_custom_group">
  <div class="input-group col-md-12">
    <span class="input-group-addon" id="basic-addon1"> q = </span>
    <input type="text" class="form-control asu_directory_q asu_directory_input"
           placeholder="Query" aria-describedby="basic-addon1">
  </div>

  <div class="input-group col-md-12">
    <span class="input-group-addon" id="basic-addon1"> fq = </span>
    <input type="text" class="form-control asu_directory_fq asu_directory_input"
           placeholder="Filter Query" aria-describedby="basic-addon1">
  </div>
  <div class="input-group col-md-12">
    <span class="input-group-addon" id="basic-addon1"> sort = </span>
    <input type="text"
           class="form-control asu_directory_sort asu_directory_input"
           placeholder="Filter Query" aria-describedby="basic-addon1">
  </div>

  <button type="button" id="asu_directory_custom_q_submit"
          class="btn btn-default has-spinner"><span class="spinner"><i
        class="fa fa-spinner fa-spin"></i></span><span class="custom-status">Run/Save</span>
  </button>
</div>


<div class="row" id="asu_directory_employee_type_select">
  <h4>Select employee types to be shown</h4>

  <?php for ($count = 0; $count < 3; $count++): ?>

    <?php foreach ($settings['employee_types_col_' . $count] as $type): ?>
      <div class="col-md-4 btn-group-vertical">
        <button type="button"
                class="btn-group btn btn-default asu_directory_type_select"
                value="<?php print $type['node']['name']; ?>">
          <?php print $type['node']['name']; ?>
        </button>
      </div>
    <?php endforeach; ?>

  <?php endfor; ?>
</div>

<div class="row">
  <a type="button" role="link" class="btn dept-mgr-btn"
     href="https://isearch.asu.edu/asu_dept_mgr" target="_blank">Go To ASU
    Directory Admin Tool</a>
</div>

<div class="asu_directory_toggle_subdirectory">Showing this department
  <span id="asu_directory_show_subs"> + Sub-Departments
      <i class="fa fa-arrow-circle-down"></i>
  </span>
</div>

<div class="field-type-asu-directory">

  <div class="row">
    <div class="col-md-4">
      <?php print theme('asu_dir_dept_tree', array(
        'items' => $items,
        'settings' => $settings
      )); ?>
    </div>

    <div class="col-md-8">
      <?php print theme('asu_dir_people_list', array(
        'items' => $items,
        'settings' => $settings
      )); ?>
    </div>
  </div>


</div>
