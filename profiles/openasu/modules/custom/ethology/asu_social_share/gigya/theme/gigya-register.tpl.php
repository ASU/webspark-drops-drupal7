<?php

/**
 * @file gigya-register.tpl.php
 * Default theme implementation for displaying a gigya registration form.
 *
 * Available variables:
 * - $title: Title of the form.
 * - $message: Explanatory text for the form.
 * - $registration_form: The user registration form.
 * - $link_accounts_form: Form to link networks to account.
 *
 * @see template_preprocess_gigya_register()
 */
?>

<h3><?php print $title; ?></h3>
<p><?php print $message; ?></p>

<?php print drupal_render($registration_form); ?>

<?php print $link_accounts_form; ?>
