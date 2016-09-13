<?php

/**
 * @file gigya-login-block.tpl.php
 * Default theme implementation for displaying a gigya login form.
 *
 * Available variables:
 * - $login_div: Contents of the login block.
 * - $title: Title to display, if not suppressed.
 *
 * @see template_preprocess_gigya_login_block()
 */
?>

<?php if (isset($title)) : ?>
<h2><?php print $title; ?></h2>
<?php endif; ?>
<div class="gigya-login"><?php print $login_div; ?></div>
