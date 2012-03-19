<?php

/**
 * @file
 * Two col swentel layout test.
 */

// Plugin definition
$plugin = array(
  'title' => t('Swentel'),
  'category' => t('Columns: 2'),
  'icon' => 'twocol_swentel.png',
  'theme' => 'panels_twocol_swentel',
  'css' => 'twocol_swentel.css',
  'regions' => array(
    'left' => t('Left swentel'),
    'right' => t('Right swentel')
  ),
);
