<?php

/**
 * @file
 * Provides entity metadata integration.
 */

/**
 * Provides metadata for membership types.
 */
class MembershipEntityTypeMetadataController extends EntityDefaultMetadataController {
  /**
   * Overrides EntityDefaultMetadataController::entityPropertyInfo().
   */
  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    unset($properties['url']);

    $properties['id']['label'] = t('Internal id');

    return $info;
  }
}
