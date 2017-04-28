<?php

// Plugin definition
$plugin = array(
  'title' => t('iSearch Profile 2 Column'),
  'icon' => 'isearch-profile-2col.png',
  'css' => 'isearch-profile-2col.css',
  'category' => t('Panopoly'),
  'theme' => 'isearch_profile_2col',
  'regions' => array(
    'header' => t('Title/Header'),
    'photo' => t('Profile Photo'),
    'contact' => t('Contact'),
    'social' => t('Social'),
    'affiliations' => t('Affiliations'),
    'sidebar' => t('Sidebar'),
    'maincontent' => t('Main Content'),
  ),
);
