<?php

/**
 * Represents a PaymentGateway and provides the means by which to interface with it.
 * @author Tyler Coles
 */
abstract class PaymentGateway {
  
  /**
   * Returns the key that should be used to access this gateway.
   */
  abstract public function getKey();
  
  /**
   * Returns a name for this gateway.
   */
  abstract public function getName();
  abstract public function getCartName();
  abstract public function getCartCheckoutMessage();
  
  /**
   * Returns a boolean flag indicating if the user should be forwarded to to complete 
   * payment.
   * 
   * @param $user the user being payed for.
   * @param $order the order being payed for.
   * @return a boolean flag
   */
  abstract public function canRedirect($user, $order);
  
  /**
   * Forwards the user to complete payment for his/her order.
   *
   * @param $user the user being payed for.
   * @param $order the order being payed for.
   * @return a boolean flag
   */
  abstract public function redirectToCompletePayment($user, $order);
  
  /**
   * Handles a returned notification with information about the status
   * of a payment. Information may either be in the $_POST or $args 
   * variable. Further details will be defined by the sub-class.
   */
  abstract public function processPaymentResponse($args = NULL);
}