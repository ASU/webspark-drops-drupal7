<div id="tb-megamenu-admin-mm-toolitem" class="admin-toolbox">
  <h3><?php print t('Item Configuration') ?> (<a href="#" class="back-megamenu-toolbox"><?php print t("MegaMenu Toolbox");?></a>)</h3>
  <p><?php print t('This allows you to configure each link you added in the Drupal core menu. You can: add block, have it styled by adding extra class, set icon (Bootstrap icons) and add description.') ?></p>
  <ul id="toogle-submenu-wrapper">
    <li>
      <label class="hasTip" title="<?php print t('Submenu') . ' - ' . t('Enable or disable submenu') ?>"><?php print t('Submenu') ?></label>
      <fieldset class="radio btn-group toolitem-sub">
        <input type="radio" id="toggleSub0" class="toolbox-toggle" data-action="toggleSub" name="toggleSub" value="0"/>
        <label for="toggleSub0" title="<?php print t('Disable submenu') ?>"><?php print t('No') ?></label>
        <input type="radio" id="toggleSub1" class="toolbox-toggle" data-action="toggleSub" name="toggleSub" value="1" checked="checked"/>
        <label for="toggleSub1" title="<?php print t('Enable submenu') ?>"><?php print t('Yes') ?></label>
      </fieldset>
    </li>
  </ul>
  <ul id="toogle-group-wrapper">
    <li>
      <label class="hasTip" title="<?php print t('Group') . ' - ' . t('Configure how this item’s submenu display.') ?>"><?php print t('Group') ?></label>
      <fieldset class="radio btn-group toolitem-group">
        <input type="radio" id="toggleGroup0" class="toolbox-toggle" data-action="toggleGroup" name="toggleGroup" value="0" checked="checked"/>
        <label for="toggleGroup0" title="<?php print t('Submenu items show only when hover/click on this tem.') ?>"><?php print t('No') ?></label>
        <input type="radio" id="toggleGroup1" class="toolbox-toggle" data-action="toggleGroup" name="toggleGroup" value="1"/>
        <label for="toggleGroup1" title="<?php print t('Submenu items are visible under this item.') ?>"><?php print t('Yes') ?></label>
      </fieldset>
    </li>
  </ul>
  <ul id="toogle-break-column-wrapper">
    <li>
      <label class="hasTip" title="<?php print t('Break column') . ' - ' . t('Move the item to the left/right column, create new column if there’s none on the chosen side.') ?>"><?php print t('Break column') ?></label>
      <fieldset class="btn-group">
        <a href="" class="btn toolitem-moveleft toolbox-action" data-action="moveItemsLeft" title="<?php print t('Move the items to the left column.') ?>"><i class="icon-arrow-left"></i></a>
        <a href="" class="btn toolitem-moveright toolbox-action" data-action="moveItemsRight" title="<?php print t('Move the items to the right column.') ?>"><i class="icon-arrow-right"></i></a>
      </fieldset>
    </li>
  </ul>
  <ul>
    <li title="<?php print t('Extra class') . ' - ' . t('Add extra class to style megamenu.') ?>">
      <label class="hasTip"><?php print t('Extra class') ?></label>
      <fieldset class="">
        <input type="text" class="input-medium toolitem-exclass toolbox-input" name="toolitem-exclass" data-name="class" value="" />
      </fieldset>
    </li>
  </ul>
  <ul>
    <li title="<?php print t('Icon') . ' - ' . t('Add Icon for Menu Item. Click Icon label to visit Bootstrap icons page and get Icon Class. E.g.: icon-search') ?>">
      <label class="hasTip">
        <a href="http://twitter.github.com/bootstrap/base-css.html#icons" target="_blank"><i class="icon-search"></i><?php print t('Icon') ?></a>
      </label>
      <fieldset class="">
        <input type="text" class="input-medium toolitem-xicon toolbox-input" name="toolitem-xicon" data-name="xicon" value="" />
      </fieldset>
    </li>
  </ul>
  <ul>
    <li title="<?php print t('Item caption') . ' - ' . t('Add caption to this item'); ?>">
      <label class="hasTip">
        <?php print t('Item caption') ?>
      </label>
      <fieldset class="">
        <input type="text" class="input-large toolitem-caption toolbox-input" name="toolitem-caption" data-name="caption" value="" />
      </fieldset>
    </li>
  </ul>
</div>
