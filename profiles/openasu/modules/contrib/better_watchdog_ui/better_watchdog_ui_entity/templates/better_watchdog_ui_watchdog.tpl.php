<?php

/**
 * @file
 * Template for detailed watchdog entity.
 */
?>
<div id="better_watchdog_ui_watchdog-<?php echo $wid; ?>" class="better_watchdog_ui_watchdog-detail">
  <table>
    <tbody>
      <?php foreach ($items as $title => $value):?>
        <tr>
          <th><?php echo $title; ?></th>
          <td><?php echo $value; ?></td>
        </tr>
      <?php endforeach; ?>
    </tbody>
  </table>
</div>
