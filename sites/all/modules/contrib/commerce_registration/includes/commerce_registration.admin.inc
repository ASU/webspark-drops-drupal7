<?php
/**
 * @file
 * Commerce Registration admin page functions.
 */

/**
 * Admin page.
 * Shows all completed registrations that have a Commerce Order ID.
 */
function commerce_registration_admin_overview() {
  // Set breadcrumbs since they don't always show.
  $crumb[] = l(t('Home'), '');
  $crumb[] = l(t('Administration'), 'admin');
  $crumb[] = l(t('Store'), 'admin/commerce');
  drupal_set_breadcrumb($crumb);
  $view = views_get_view('commerce_registration_admin_regs', TRUE);
  $view->set_display('commerce_regs_w_order');
  $out = "<h2>" . $view->get_title() . "</h2>" . views_embed_view('commerce_registration_admin_regs', 'commerce_regs_w_order');
  return $out;
}

/**
 * Admin page.
 * Shows all registrations regardless of Commerce Order ID.
 */
function commerce_registration_admin_overview_all() {
  // Set breadcrumbs since they don't always show.
  $crumb[] = l(t('Home'), '');
  $crumb[] = l(t('Administration'), 'admin');
  $crumb[] = l(t('Store'), 'admin/commerce');
  drupal_set_breadcrumb($crumb);
  $view = views_get_view('commerce_registration_admin_regs', TRUE);
  $view->set_display('commerce_regs_all');
  $out = "<h2>" . $view->get_title() . "</h2>" . views_embed_view('commerce_registration_admin_regs', 'commerce_regs_all');
  return $out;
}
