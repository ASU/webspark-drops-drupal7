<?php

/**
 * @file
 * Provides a controller for building an entity overview form.
 */

/**
 * Default controller for providing UI.
 */
class CommerceFileLicenseEntityUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();

    // unset base path to allow views to control it
    unset($items[$this->path]);

    // alter add path
    unset($items[$this->path . '/add']['title callback'], $items[$this->path . '/add']['title arguments']);
    $items[$this->path . '/add'] = array(
      'title' => 'Add a file license',
      'description' => 'Add a new file license.',
    ) + $items[$this->path . '/add'];

    return $items;
  }
}
