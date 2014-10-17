<?php

function tb_megamenu_request() {
  $action = isset($_POST['action']) ? $_POST['action'] : NULL;
  switch($action) {
    case 'load':
      $block = tb_megamenu_render_block($_POST['menu_name']);
      print($block['content']['#markup']);
      break;
    case 'save':
      $menu_config = isset($_POST['menu_config']) ? $_POST['menu_config'] : NULL;
      $block_config = isset($_POST['block_config']) ? $_POST['block_config'] : NULL;
      $menu_name = isset($_POST['menu_name']) ? $_POST['menu_name'] : NULL;
      if($menu_config && $menu_name) {
        $tb_megamenu = db_select('tb_megamenus', 't')->fields('t')->condition('menu_name', $menu_name)->execute()->fetchObject();
        if($tb_megamenu) {
          db_update('tb_megamenus')->fields(array('menu_config' => $menu_config, 'block_config' => $block_config))->condition('menu_name', $menu_name)->execute();
        }
        else {
          db_insert('tb_megamenus')->fields(array('menu_name' => $menu_name, 'block_config' => $block_config, 'menu_config' => $menu_config))->execute();
        }
      }
      break;
    case 'load_block':
      $block_key = isset($_POST['block_key']) ? $_POST['block_key'] : NULL;
      $id = isset($_POST['id']) ? $_POST['id'] : NULL;
      $showblocktitle = isset($_POST['showblocktitle']) ? $_POST['showblocktitle'] : NULL;
      if($block_key) {
        $content = json_encode(array('content' => theme('tb_megamenu_block', array('block_key' => $block_key, 'section' => 'backend', 'showblocktitle' => $showblocktitle)), 'id' => $id));
        print($content);
      }
      break;
  }
  exit;
}
