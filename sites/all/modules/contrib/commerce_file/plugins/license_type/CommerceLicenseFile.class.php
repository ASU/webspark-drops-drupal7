<?php

/**
 * File license type.
 */
class CommerceLicenseFile extends CommerceLicenseBase  {

  /**
   * Implements CommerceLicenseInterface::isConfigurable().
   */
  public function isConfigurable() {
    return FALSE;
  }

  /**
   * Implements CommerceLicenseInterface::accessDetails().
   */
  public function accessDetails() {
    // Display the files.
    $product = $this->wrapper->product->value();
    $display = array(
      'label' => 'hidden',
      'type' => 'commerce_file',
      'settings' => array(
        // The access check confirms that the product has a license.
        // Since we're calling this formatter from a license, there is no
        // point in performing that check.
        'check_access' => FALSE,
      ),
    );
    $output = field_view_field('commerce_product', $product, 'commerce_file', $display);
    return drupal_render($output);
  }

  /**
   * Implements CommerceLicenseInterface::checkoutCompletionMessage().
   */
  public function checkoutCompletionMessage() {
    // Store the uid in the session. The file access function will use it
    // if the user is anonymous, allowing the download to proceed.
    $_SESSION['commerce_license_uid'] = $this->uid;

    $product = $this->wrapper->product->value();
    $message = t('Thank you for purchasing %product.', array('%product' => $product->title)) . '<br />';
    $message .= t('Download now:');
    return $message . $this->accessDetails();
  }

  /**
   * Implements CommerceLicenseInterface::renew().
   */
  public function renew($expires) {
    parent::renew($expires);

    // Clear the download log in order to reset download limits.
    commerce_file_download_log_clear(array('license_id' => $this->license_id));
  }
}
