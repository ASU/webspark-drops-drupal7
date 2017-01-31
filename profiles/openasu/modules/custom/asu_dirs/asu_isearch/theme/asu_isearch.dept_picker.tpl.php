<?php
/**
 * @file
 * Default output for an ASU Spotlight object.
 */
?>
<div class="field-type-asu-isearch-dept-picker">
    <label><?php print isset($label) ? $label : '' ?></label>

    <div class="actions">
        <input id="asu-isearch-dept-picker-trigger" type="button"
               class="form-submit" value="Browse">
    </div>
    <ul id="asu-isearch-dept-picker-list"></ul>

    <div class="asu-dept-picker">
      <?php print theme('asu_isearch_dept_tree', array(
        'items' => $items,
        'settings' => $settings,
      )); ?>
    </div>
</div>
