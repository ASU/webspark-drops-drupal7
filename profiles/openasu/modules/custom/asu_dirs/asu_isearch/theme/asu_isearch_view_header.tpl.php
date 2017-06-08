<?php
/**
 * @file
 * Custom header output for ASU iSearch directory list header
 */

$column_widths = asu_isearch_get_view_column_widths($display_options);
?>
<?php if ($display_options->display_header): ?>
    <div class="views-row views-row-1 views-row-odd views-row-first row">
      <?php if ($display_options->display_photo): ?>
          <div
                  class="views-field views-field-field-isearch-photo-url col-md-<?php print $column_widths['photo']; ?> user-photo"></div>
      <?php endif; ?>
      <?php if ($display_options->display_name): ?>
          <div
                  class="views-field views-field-nothing-1 col-md-<?php print $column_widths['name']; ?> user-name">
              <span class="field-content"><div class="name">Name</div></span>
          </div>
      <?php endif; ?>
      <?php if ($display_options->display_contact): ?>
          <div
                  class="views-field views-field-nothing col-md-<?php print $column_widths['contact']; ?> user-contact">
              <span class="field-content"><div
                          class="email">Contact</div></span>
          </div>
      <?php endif; ?>
      <?php if ($display_options->display_expertise): ?>
          <div
                  class="views-field views-field-field-isearch-expertise-areas col-md-<?php print $column_widths['expertise']; ?> user-expertise">
        <span class="field-content"><div class="expertise">Expertise
          </div></span>
          </div>
      <?php endif; ?>
    </div>
<?php endif; ?>