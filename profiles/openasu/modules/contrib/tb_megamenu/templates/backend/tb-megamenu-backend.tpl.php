<div id="tb-megamenu-admin" class="hidden tb-megamenu-admin tb-megamenu">
  <div class="admin-inline-toolbox clearfix">
    <div class="tb-megamenu-admin-mm-row clearfix">
      <div id="tb-megamenu-admin-mm-tb">
        <div id="toolbox-loading" class="toolbox-loading">&nbsp;</div>
        <div id="toolbox-message" class="toolbox-message">&nbsp;</div>
        <div id="tb-megamenu-admin-mm-intro" class="pull-left admin-toolbox">
          <h3><?php print t('MegaMenu Toolbox') ?></h3>
          <p><?php print t('This toolbox includes all settings of megamenu, just select menu then configure. There are 3 level of configuration: sub-megamenu setting, column setting and menu item setting.') ?></p>
          <ul>
            <li id="tb-megamenu-style-wrapper" title="<?php print t('Select style for this megamenu');?>">
              <label class="hasTip"><?php print t('Style') ?></label>
              <fieldset class="btn-group">
                <div class="controls tb-controls">
                  <select name="tb-megamenu-style">
                    <?php print $style_options;?>
                  </select>
                </div>
              </fieldset>
            </li>
            <li id="tb-megamenu-animation-wrapper" title="<?php print t('Select animation for this megamenu - CSS3 Animation');?>">
              <label class="hasTip"><?php print t('Animation') ?></label>
              <fieldset class="btn-group">
                <div class="controls tb-controls">
                  <select name="tb-megamenu-animation">
                    <?php print $animation_options;?>
                  </select>
                </div>
              </fieldset>
            </li>
            <li id="tb-megamenu-delay-wrapper" style="display: <?php print $block_config['animation'] == 'none' ? 'none' : 'inline-block';?>;" title="<?php print t('Delay time of the animation - this field must be an integer.');?>">
              <label class="hasTip"><?php print t('Delay (ms)') ?></label>
              <fieldset class="btn-group">
                <div class="controls tb-controls">
                  <input class="input-medium toolitem-delay toolbox-input" name="tb-megamenu-delay" type="text" value="<?php print $block_config['delay'];?>" data-name="delay"></input>
                </div>
              </fieldset>
            </li>
            <li id="tb-megamenu-duration-wrapper" style="display: <?php print $block_config['animation'] == 'none' ? 'none' : 'inline-block';?>;" title="<?php print t('Duration of the animation - this field must be an integer.');?>">
              <label class="hasTip"><?php print t('Duration (ms)') ?></label>
              <fieldset class="btn-group">
                <div class="controls tb-controls">
                  <input class="input-medium toolitem-duration toolbox-input" name="tb-megamenu-duration" type="text" value="<?php print $block_config['duration'];?>" data-name="duration"></input>
                </div>
              </fieldset>
            </li>
            <li>
              <label class="hasTip" title="<?php print t('Show/hide the arrow next to items that have submenu.');?>"><?php print t('Auto arrow') ?></label>
              <fieldset class="radio btn-group toolitem-auto-arrow" data-auto-arrow="<?php print $block_config['auto-arrow'];?>">
                <input type="radio" <?php print $block_config['auto-arrow'] ? '' : 'checked="checked"';?> value="0" name="tb-megamenu-auto-arrow" data-action="toggleAutoArrow" class="toolbox-toggle" id="toggleAutoArrow0">
                <label for="toggleAutoArrow0" class="btn <?php print $block_config['auto-arrow'] ? '' : 'active btn-danger';?>" title="<?php print t('Hide the arrow next to items that have submenu.');?>">No</label>
                <input type="radio" <?php print $block_config['auto-arrow'] ? 'checked="checked"' : '';?> value="1" name="tb-megamenu-auto-arrow" data-action="toggleAutoArrow" class="toolbox-toggle" id="toggleAutoArrow1">
                <label for="toggleAutoArrow1" class="btn <?php print $block_config['auto-arrow'] ? 'active btn-success' : '';?>" title="<?php print t('Show the arrow next to items that have submenu.');?>">Yes</label>
              </fieldset>
            </li>
            <li>
              <label class="hasTip" title="<?php print t('Show or collapse submenus when browsing on small screens');?>"><?php print t('Always show submenu') ?></label>
              <fieldset class="radio btn-group toolitem-always-show-submenu" data-always-show-submenu="<?php print $block_config['always-show-submenu'];?>">
                <input type="radio" <?php print $block_config['always-show-submenu'] ? '' : 'checked="checked"';?> value="0" name="tb-megamenu-always-show-submenu" data-action="toggleAlwayShowSubmenu" class="toolbox-toggle" id="toggleAlwayShowSubmenu0">
                <label for="toggleAlwayShowSubmenu0" class="btn <?php print $block_config['always-show-submenu'] ? '' : 'active btn-danger';?>" title="<?php print t('Collapse submenus when browsing on small screens');?>">No</label>
                <input type="radio" <?php print $block_config['always-show-submenu'] ? 'checked="checked"' : '';?> value="1" name="tb-megamenu-always-show-submenu" data-action="toggleAlwayShowSubmenu" class="toolbox-toggle" id="toggleAlwayShowSubmenu1">
                <label for="toggleAlwayShowSubmenu1" class="btn <?php print $block_config['always-show-submenu'] ? 'active btn-success' : '';?>" title="<?php print t('Show submenus when browsing on small screens');?>">Yes</label>
              </fieldset>
            </li>
          </ul>
        </div>
        <?php print $item_toolbox;?>
        <?php print $submenu_toolbox;?>
        <?php print $column_toolbox;?>
      </div>

      <div class="toolbox-actions-group">
        <button class="btn btn-success toolbox-action toolbox-saveConfig" data-action="saveConfig"><i class="fa fa-save"></i> <?php print t('Save') ?></button>
        <button class="btn btn-danger toolbox-action toolbox-resetConfig" data-action="resetConfig"><i class="fa fa-undo"></i> <?php print t('Reset') ?></button>
      </div>
      <div class="toolbox-links-groups">
        <a href="<?php print $edit_menu;?>" target="_blank">Edit menu</a>
        <a href="<?php print $edit_links;?>" target="_blank">Edit links</a>
      </div>

    </div>
  </div>

  <div id="tb-megamenu-admin-mm-container" class="navbar clearfix">
    <?php print $menu_content;?>
  </div>
</div>
