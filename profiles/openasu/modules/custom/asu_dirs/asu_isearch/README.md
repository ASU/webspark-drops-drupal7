### NOTE: * currently under development *
Be sure to test in development environment!

# ASU iSearch Local Directory module

## Requirements
ASU Webspark `1.27.1` (Ismay)

## Important Note!
For all Webspark versions prior to `1.27` (Montana/Ismay) use the `v7.x-1.4` tag.

HOOKS
--------------------------
/**
 * Implements hook_asu_isearch_prepare_migration().
 * Modify, or fix mappings, of migration data before a row is processed
 */
function MODULENAME_asu_isearch_prepare_migration(&$entity, $node, $row) {
  // modify the entity before it is processed
}
