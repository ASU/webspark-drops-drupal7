<?php 
/** 
 * @file 
 * Primary pre/preprocess functions and alterations.
 */ 

function ace_preprocess_page(&$variables) {
  if (isset($variables['node']->type)) {
    if ($variables['node']->type == "ace_task_force_meeting") {
      drupal_add_js(path_to_theme() . "/js/ace.js");
    }
  }
}