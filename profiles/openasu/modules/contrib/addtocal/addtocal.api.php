<?php
/**
 * @file
 * Hooks provided by the addtocal module.
 */

/**
 * Alter the addtocal info array.
 *
 * @param $info
 *   An array representing the addtocal data used to generate the button
 *  information.
 * @param $entity_type
 *   The current entity type to be rendered with addtocal button.
 * @param $entity
 *   The current entity to be rendered with addtocal button.
 */
function hook_addtocal_extract_event_info_alter(&$info, $entity_type, $entity) {
  // Change the event description.
  $info['description'] = 'New event description';
}

