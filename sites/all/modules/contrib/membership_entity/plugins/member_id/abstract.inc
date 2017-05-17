<?php

/**
 * @file
 * Contains the abstract member_id plugin class.
 */

/**
 * Additional member_id formats for a membership type.
 */
interface MembershipEntityMemberIdInterface {
  /**
   * Determines the next available member id.
   *
   * @param MembershipEntity $membership
   *   The membership object used for tokens.
   *
   * @return string
   *   The next available member id.
   */
  public function next($membership);

  /**
   * Builds the settings form this handler.
   */
  public function settingsForm(&$form_state);

  /**
   * Validates the plugin settings form.
   */
  public function validateSettings(&$element, &$form_state);
}

/**
 * An abstract implementation of MembershipEntityMemberId.
 */
abstract class MembershipEntityMemberIdAbstract implements MembershipEntityMemberIdInterface {
  /**
   * The settings options.
   */
  protected $settings;

  /**
   * Default constructor.
   *
   * @param array $settings
   *   An array of default plugin settings.
   */
  public function __construct($settings) {
    $this->settings = $settings;
  }

  /**
   * Implements MembershipEntityMemberIdInterface::next().
   */
  public function next($membership) {}

  /**
   * Implements MembershipEntityMemberIdInterface::settingsForm().
   */
  public function settingsForm(&$form_state) {
    return array();
  }

  /**
   * Implements MembershipEntityMemberIdInterface::validateSettings().
   */
  public function validateSettings(&$element, &$form_state) {}
}

/**
 * A broken implementation of MembershipEntityMemberId.
 */
class MembershipEntityMemberIdBroken extends MembershipEntityMemberIdAbstract {
  /**
   * {@inheritdoc}}
   */
  public function next($membership) {}

  /**
   * {@inheritdoc}
   */
  public function settingsForm(&$form_state) {
    $form['member_id_broken'] = array(
      '#markup' => t('The selected member_id handler is broken.'),
    );
    return $form;
  }
}
