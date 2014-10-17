<div id="tb-megamenu-admin-mm-toolsub" class="admin-toolbox">
  <h3><?php print t('Submenu Configuration') ?> (<a href="#" class="back-megamenu-toolbox"><?php print t("MegaMenu Toolbox");?></a>)</h3>
  <p><?php print t('Contains all the level 2+ items. Allows you to: add and remove row, set the submenu’s position, have it styled, edit its width...') ?></p>
  <ul>
    <li title="<?php print t('Add row') . ' - ' . t('Add a new row to the selected submenu') ?>">
      <label class="hasTip"><?php print t('Add row') ?></label>
      <fieldset class="btn-group">
        <a href="" class="btn toolsub-addrow toolbox-action" data-action="addRow"><i class="icon-plus"></i></a>
      </fieldset>
    </li>
  </ul>
  <ul>
    <li>
      <label class="hasTip" title="<?php print t('Hide when collapse') . ' - ' . t('Hide this column when the menu is collapsed on small screens') ?>"><?php print t('Hide when collapse') ?></label>
      <fieldset class="radio btn-group toolsub-hidewhencollapse">
        <input type="radio" id="togglesubHideWhenCollapse0" class="toolbox-toggle" data-action="hideWhenCollapse" name="togglesubHideWhenCollapse" value="0" checked="checked"/>
        <label for="togglesubHideWhenCollapse0" title="<?php print t('Keep showing this submenu when the menu is collapsed on small screens') ?>"><?php print t('No') ?></label>
        <input type="radio" id="togglesubHideWhenCollapse1" class="toolbox-toggle" data-action="hideWhenCollapse" name="togglesubHideWhenCollapse" value="1"/>
        <label for="togglesubHideWhenCollapse1" title="<?php print t('Hide this submenu when the menu is collapsed on small screens') ?>"><?php print t('Yes') ?></label>
      </fieldset>
    </li>
  </ul>                    
  <ul>
    <li title="<?php print t('Submenu width (px)') . ' - ' . t('Set submenu width (in pixel), this field must be a integer') ?>">
      <label class="hasTip"><?php print t('Submenu width (px)') ?></label>
      <fieldset class="">
        <input type="text" class="toolsub-width toolbox-input input-small" name="toolsub-width" data-name="width" value="" />
      </fieldset>
    </li>
  </ul>
  <ul>
    <li title="<?php print t('Alignment') . ' - ' . t('Align this submenu') ?>">
      <label class="hasTip"><?php print t('Alignment') ?></label>
      <fieldset class="toolsub-alignment">
        <div class="btn-group">
        <a class="btn toolsub-align-left toolbox-action" href="#" data-action="alignment" data-align="left" title="<?php print t('Left') ?>"><i class="icon-align-left"></i></a>
        <a class="btn toolsub-align-right toolbox-action" href="#" data-action="alignment" data-align="right" title="<?php print t('Right') ?>"><i class="icon-align-right"></i></a>
        <a class="btn toolsub-align-center toolbox-action" href="#" data-action="alignment" data-align="center" title="<?php print t('Center') ?>"><i class="icon-align-center"></i></a>
        <a class="btn toolsub-align-justify toolbox-action" href="#" data-action="alignment" data-align="justify" title="<?php print t('Justify') ?>"><i class="icon-align-justify"></i></a>
        </div>
      </fieldset>
    </li>
  </ul>          
  <ul>
    <li title="<?php print t('Extra class') . ' - ' . t('Add extra class to style megamenu') ?>">
      <label class="hasTip"><?php print t('Extra class') ?></label>
      <fieldset class="">
        <input type="text" class="toolsub-exclass toolbox-input input-medium" name="toolsub-exclass" data-name="class" value="" />
      </fieldset>
    </li>
  </ul>
</div>
