<?php
// Plugin definition
$plugin = array(
  'title' => t('ASU Student Layout A'),
  'icon' => 'asu_student_a.png',
  'category' => t('ASU Student Layouts'),
  'theme' => 'asu_student_a',
  'css' => 'asu_student_a.css',
  'regions' => array(
    'header' => t('Header'),
    'menu' => t('Menu'),
    'sidebar' => t('Sidebar'),
    'contentmain' => t('Content'),
  ),
);
