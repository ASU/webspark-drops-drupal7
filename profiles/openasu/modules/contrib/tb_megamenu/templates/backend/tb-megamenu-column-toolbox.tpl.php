<div id="tb-megamenu-admin-mm-toolcol" class="admin-toolbox">
  <h3><?php print t('Column Configuration') ?> (<a href="#" class="back-megamenu-toolbox"><?php print t("MegaMenu Toolbox");?></a>)</h3>
  <p><?php print t('Allows you to: add and remove column, set grid, add block to column and style the column with extra class') ?></p>
  <ul>
    <li>
      <label class="hasTip" title="<?php print t('Add/remove Column') . ' - ' . t('Click + to add a new column on the right of the selected column. Click - to remove the selected column') ?>"><?php print t('Add/remove Column') ?></label>
      <fieldset class="btn-group">
        <a href="" class="btn toolcol-addcol toolbox-action first" data-action="addColumn" title="<?php print t('Add a new column on the right of the selected column') ?>"><i class="fa fa-plus"></i></a>
        <a href="" class="btn toolcol-removecol toolbox-action last" data-action="removeColumn" title="<?php print t('Remove the selected column') ?>"><i class="fa fa-minus"></i></a>
      </fieldset>
    </li>
  </ul>
  <ul>
    <li>
      <label class="hasTip" title="<?php print t('Hide when collapse') . ' - ' . t('Hide this column when the menu is collapsed on small screen') ?>"><?php print t('Hide when collapse') ?></label>
      <fieldset class="radio btn-group toolcol-hidewhencollapse">
        <input type="radio" id="toggleHideWhenCollapse0" class="toolbox-toggle" data-action="hideWhenCollapse" name="toggleHideWhenCollapse" value="0" checked="checked"/>
        <label for="toggleHideWhenCollapse0" title="<?php print t('Keep showing this column when the menu is collapsed on small screen') ?>"><?php print t('No') ?></label>
        <input type="radio" id="toggleHideWhenCollapse1" class="toolbox-toggle" data-action="hideWhenCollapse" name="toggleHideWhenCollapse" value="1"/>
        <label for="toggleHideWhenCollapse1" title="<?php print t('Hide this column when the menu is collapsed on small screen') ?>"><?php print t('Yes') ?></label>
      </fieldset>
    </li>
  </ul>
  <ul>
    <li id="tb-megamenu-grid-wrapper" title="<?php print t('Grid (1-12)') . ' - ' . t('Set number of grid columns the selected column spans') ?>">
      <label class="hasTip"><?php print t('Grid (1-12)') ?></label>
      <fieldset class="">
        <select class="toolcol-width toolbox-input toolbox-select input-mini" name="toolcol-width" data-name="width">
          <option value="1">1</option>
          <option value="2">2</option>
          <option value="3">3</option>
          <option value="4">4</option>
          <option value="5">5</option>
          <option value="6">6</option>
          <option value="7">7</option>
          <option value="8">8</option>
          <option value="9">9</option>
          <option value="10">10</option>
          <option value="11">11</option>
          <option value="12">12</option>
        </select>
      </fieldset>
    </li>
  </ul>
  <ul>
    <li id="tb-megamenu-block-wrapper" title="<?php print t('Blocks') . ' - ' . t('Add/replace a block to the selected column') ?>">
      <label class="hasTip"><?php print t('Blocks') ?></label>
      <fieldset class="btn-group">
        <select class="toolcol-block toolbox-input toolbox-select input-medium" name="toolcol-block" data-name="block" data-placeholder="<?php print t('Select Block') ?>" style="width: 200px;">
          <option value=""></option>
          <?php
          foreach ($blocks_options as $block_key => $block) {
            print "<option value=\"{$block_key}\">" . $block . "</option>\n";
          }
          ?>
        </select>
      </fieldset>
    </li>
  </ul>
  <ul>
    <li>
      <label class="hasTip" title="<?php print t('Show block title');?>"><?php print t('Show block title') ?></label>
      <fieldset class="radio btn-group toolcol-showblocktitle">
        <input type="radio" id="toggleShowBlockTitle0" class="toolbox-toggle" data-action="showBlockTitle" name="toggleShowBlockTitle" value="0"/>
        <label for="toggleShowBlockTitle0"><?php print t('No') ?></label>
        <input type="radio" id="toggleShowBlockTitle1" class="toolbox-toggle" data-action="showBlockTitle" name="toggleShowBlockTitle" value="1" checked="checked"/>
        <label for="toggleShowBlockTitle1"><?php print t('Yes') ?></label>
      </fieldset>
    </li>
  </ul>
  <ul>
    <li title="<?php print t('Extra class') . ' - ' . t('Add extra class to style megamenu') ?>">
      <label class="hasTip"><?php print t('Extra class') ?></label>
      <fieldset class="">
        <input type="text" class="input-medium toolcol-exclass toolbox-input" name="toolcol-exclass" data-name="class" value="" />
      </fieldset>
    </li>
  </ul>
</div>
