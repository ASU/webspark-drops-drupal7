<?php

/**
 * @file gigya-raas-block.tpl.php
 * Default theme implementation for displaying a gigya rass links.
 *
 * Available variables:
 * - $links: Contents of the login block.
 * - $title: Title to display, if not suppressed.
 *
 *
 */
 ?>

 <?php if (isset($title)) : ?>
 <h2><?php print $title; ?></h2>
 <?php endif; ?>

 <div class="gigya-raas">
   <span class="gigya-raas">
     <?php if (!empty($links['login'])) : ?>
     <?php print $links['login']?>
     <?php endif; ?>
   </span>
   <span class="gigya-raas">
     <?php if (!empty($links['register'])) : ?>
     <?php print $links['register']?>
     <?php endif; ?>
   </span>
   <span class="gigya-raas">
     <?php if (!empty($links['profile'])) : ?>
     <?php print $links['profile']?>
     <?php endif; ?>
   </span>
 </div>
