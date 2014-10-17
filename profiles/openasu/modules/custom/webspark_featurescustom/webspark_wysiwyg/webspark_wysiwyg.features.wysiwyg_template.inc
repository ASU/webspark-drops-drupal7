<?php
/**
 * @file
 * webspark_wysiwyg.features.wysiwyg_template.inc
 */

/**
 * Implements hook_wysiwyg_template_default_templates().
 */
function webspark_wysiwyg_wysiwyg_template_default_templates() {
  $templates = array();
  $templates['explore_programs_box'] = array(
    'title' => 'Explore Our Programs Box',
    'description' => 'Replace the button links and text with your own.',
    'weight' => 0,
    'fid' => 0,
    'body' => '<div class="panel explore-programs"><div class="panel-body"><h3>Explore Our Programs</h3><p><a href="https://webapp4.asu.edu/programs/t5/undergrad" class="btn btn-blue btn-block">Undergraduate programs</a> <a href="https://webapp4.asu.edu/programs/t5/graduate/false" class="btn btn-blue btn-block">Graduate programs</a></p></div></div>',
    'name' => 'explore_programs_box',
    'content_types' => array(),
  );
  return $templates;
}
