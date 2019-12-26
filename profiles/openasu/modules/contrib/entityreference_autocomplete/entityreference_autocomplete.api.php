<?php

/**
 * @file
 * API documentation for Entity Reference Autocomplete.
 */

/**
 * Allows modules to alter AJAX results returned by "entityreference" fields.
 *
 * Use this hook to alter the data returned to users in an "entityreference"
 * field, for example to add some nice markup to the data, or prevent some
 * results from being returned at all.
 *
 * @param string[] $matches
 *   An associative array of results to return in an "entityreference" field.
 * @param array $context
 *   An associative with metadata about every result contained in $matches. Each
 *   index in the array maps to an index in the $matches variables, and contains
 *   the following data:
 *   - entity: full entity object, as loaded via EFQ.
 *   - entity_id: ID of referenced entity.
 *   - entity_type: type of referenced entity.
 *   - entity_bundle: bundle that referenced entity belongs to.
 *   - rendered_html: HTML returned in the AJAX selection window.
 *
 * @see entityreference_autocomplete_autocomplete_callback()
 */
function hook_entityreference_autocomplete_matches_alter(array &$matches, array $context) {
  foreach ($context as $match_key => $data) {
    // Look for an offensive entity label.
    if (strstr($data['rendered_html'], 'Offensive Label')) {
      // Disable this match. Don't want offensive titles in the kids section ;D.
      unset($matches[$match_key]);
    }

    // Change colour of old entities.
    if ($data['entity_id'] < 500) {
      // Alter the html to render.
      $new_html = '<div class="clearfix" style="height: 25px; background: #bbb;">';
      $new_html .= $matches[$match_key];
      $new_html .= '</div>';

      // Replace the original html with the new one.
      $matches[$match_key] = $new_html;
    }
  }
}
