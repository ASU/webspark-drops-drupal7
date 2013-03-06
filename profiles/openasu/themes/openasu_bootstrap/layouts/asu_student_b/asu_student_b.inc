<?php
// Plugin definition
$plugin = array(
  'title' => t('ASU Student Layout B'),
  'icon' => 'asu_student_b.png',
  'category' => t('ASU Student Layouts'),
  'theme' => 'asu_student_b',
  'css' => 'asu_student_b.css',
  'regions' => array(
    'header' => t('Header'),
    'menu' => t('Menu'),
    'sidebar' => t('Sidebar'),
    'contentmain' => t('Content'),
  ),
);
