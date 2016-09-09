<?php

/**
 * @file gigya-link-accounts.tpl.php
 * Default theme implementation for displaying a Gigya account link form.
 *
 * Available variables:
 * - $form_title: Title text for the form.
 * - $form: Complete Gigya account linking form.
 * - $register_link: Link to the register page.
 * @see template_preprocess_gigya_link_accounts()
 */
?>

<h3><?php print $form_title; ?></h3>
<?php print drupal_render($form); ?>
<?php print $password_link; ?>
