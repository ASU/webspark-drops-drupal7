# Flogger module

When more than one type of logging is wanted (specifically two or more of watchdog, drush, and Drupal_set_message) for specific section of code, this module can generate multiple log types with one line of code and a few parameters.

## Usage

Replace your watchdog, drupal_set_message, and drush_log calls with one function call: flogger_log.

### All Parameters

#### Required
 * @param string $module - machine name of module
 * @param $message - Message text. If dynamic parameters are being passed in to sanitize, they need to be included in $message. (See t() documentation for more information on sanitizing incoming variables.)
 
#### Optional
 * @param array $msg_params (OPTIONAL) - array of tokens/values to sanitize in $message (see t() documentation for more on this.)
 * @param int $severity (OPTIONAL) - 0-8, matching WATCHDOG_* constants integer values. Defaults to WATCHDOG_INFO. Use 8 for "success" for Drush.
 * @param bool $drupal_message (OPTIONAL) - Create a drupal_set_message. FALSE by default.
 * @param bool $drush (OPTIONAL) - Create a drush_log message. TRUE by default.
  * @param bool $watchdog (OPTIONAL) - Create a watchdog message. TRUE by default.
 * @param bool $dsm_admin_only (OPTIONAL) - Only show to users with /admin access. Defaults to TRUE.
 
 ## Examples

### Basic example

flogger_log('my_module', 'Some random thing happened.');

This defaults to logging the message in the watchdog table and to the Drush output (if Drush is being used), using a status of "info" (watchdog) and "ok" (drush), respectively.

### Complex example

flogger_log('my_module', 'Node ID @nid did not load.', array('@nid' => $nid), WATCHDOG_ERROR, TRUE, FALSE, TRUE, FALSE);

This would put an error message of "Node ID 12345 did not load." in watchdog and on the next page load, that is visible to all (but no Drush logging).

### Variation of message types

There are at least eight (8) predefined message type across the three different functions (watchdog, drush_log, drupal_set_message).

Use the closest corresponding watchdog constant (WATCHDOG_NOTICE, WATCHDOG_ERROR, etc.) and the module will convert them into the closest matching value for drush and drupal_set_message. (NOTE: If you must have a "Success" message type for Drush, set the value of $type === 8 (vs. a watchdog constant). It will be mapped to the closest watchdog and drush values.
