<?php
if(variable_get('cybersource_server_mode', 'Test') == 'Test') 
{
	variable_set('cybersource_secret_key', 'e66e41ca98514eb5b32e79d6af13c14058e55fc8961143979e3d9375cff463a154d56c7f92504c058a22dbb4651eaa6b22b23ae7eda9468dad7f75138ab74fd1a7d342a7a5f049f2adc9b664f7561ba507b7246781f341a4977becfa6d8311e17718c9b2fa7a447cbf7b21816000e0aeae0f5519922842c08f8e287d4a6df2a0');
	variable_set('cybersource_access_key', '565bcb7fbb5c3847870dae471f53186b');
	variable_set('cybersource_profile_id', '45CD38A9-54AC-45C7-ACBC-014E322D3AB1');
	variable_set('cybersource_url', 'https://testsecureacceptance.cybersource.com/pay');
} 
else 
{
	variable_set('cybersource_secret_key', '037b0d74e92749fabb13b0cac37c83cc783b7968cc024cfc85d910a09d7426d6dc325bc9a16848cabae4ad3caf627bd040a815dc75ae444c8cca083e8a66082d038f52aef52a410f8deee826b71e6891781d6fc25a6e4c34b900664530bd45beaba0d9a5e16e4a85988ab048d36c0642b8eb75d786214e1cac46c20194ba267e');
	variable_set('cybersource_access_key', '0a7432b83c7634398f1b159c6ca3f8d9');
	variable_set('cybersource_profile_id', '1B38457E-37E6-4F56-9751-F6AB1D09F5EA');
	variable_set('cybersource_url', 'https://secureacceptance.cybersource.com/pay');
}

class AsuFoundationGateway extends PaymentGateway 
{
	public function getKey() 
  {
		return 'asuf';
	}

	public function getName() 
  {
		return t('ASU Foundation');
	}

	public function getCartName() 
  {
		return t('ASU Foundation Cart');
	}

	public function getCartCheckoutMessage() 
  {
		return t("When you click 'Check Out' you will be directed to the CyberSource's secure payment site.");
	}

	public function canRedirect($user, $order) 
  {
		return 
      $order->total > 0 && 
      variable_get('cybersource_secret_key', null) != null && 
      variable_get('cybersource_access_key', null) != null && 
      variable_get('cybersource_profile_id', null) != null && 
      variable_get('cybersource_url', null) != null;
	}

	public function redirectToCompletePayment($user, $order) 
  {
		$formParams = array(
			'merchant_defined_data10' => '99', // Note: This was hard-coded to 99 for the old gateway. Might need to change.
			'merchant_defined_data11' => $order->gift_total,
			'merchant_defined_data12' => $order->order_id,
			'access_key' => variable_get('cybersource_access_key', ''),
			'profile_id' => variable_get('cybersource_profile_id', ''),
			'transaction_uuid' => uniqid(),
			'signed_field_names' => 'access_key,profile_id,transaction_uuid,signed_field_names,unsigned_field_names,signed_date_time,locale,transaction_type,reference_number,amount,currency',
			'unsigned_field_names' => 'merchant_defined_data10,merchant_defined_data11,merchant_defined_data12',
			'signed_date_time' => gmdate("Y-m-d\TH:i:s\Z"),
			'locale' => 'en',
			'transaction_type' => 'sale',
			'reference_number' => '99', // Note: This was hard-coded to 99 for the old gateway. Might need to change.
			'amount' => number_format($order->total, 2, '.', ''),
			'currency' => 'USD'
		);

		$formParams['signature'] = $this->sign($formParams);
		
		$hiddenForm = '
      <html xmlns="http://www.w3.org/1999/xhtml">
        <head>
              <script type="text/javascript">
                  function submitHiddenForm() {
                      document.forms["redirectPost"].submit();
                  }
              </script>
          </head>
          <body onload="submitHiddenForm();">
            <div>You are being taken to a secure page on cybersource.com to complete this transaction. Please wait.</div>
          <form name="redirectPost" method="post" action="' . variable_get('cybersource_url', '') . '">';
      
          foreach ($formParams as $name => $value) {
            $hiddenForm .= '<input type="hidden" id="' . $name . '" name="' . $name . '" value="' . $value . '"/>';
          }
		
		$hiddenForm .= '
          </form>
        </body>
      </html>';
		
		echo $hiddenForm;
	}

	public function processPaymentResponse($args = NULL) 
  {
		// Process response
		$query = 
      'UPDATE {ace_order} ' . 
      "SET transaction_id = %d, status = '%s', notification_time = %d " .
      'WHERE order_id = %d';

		$result = db_query($query, $args['transaction_id'], $args['status'], time(), $args['order_id']);
		
		if (!$result) 
    {
			watchdog('CyberSource', 'Payment response failed DB update.', array(), WATCHDOG_DEBUG);
			return array(
				'response_code' => 'failure',
				'order_id' => $args['order_id']
			);
		}
		
		$query = 
      'SELECT successful ' .
      'FROM {ace_order_status} ' .
      'WHERE status = %d';

		$payment_success = (boolean) db_query($query, $args['status'])->fetchField();
		
		return array(
			'response_code' => 'success',
			'order_id' => $args['order_id'],
			'payment_success' => $payment_success
		);
	}

	public function sign($params) 
  {
		return 
      $this->signData(
        $this->buildDataToSign($params), variable_get('cybersource_secret_key', '')
      );
	}

	private function signData($data, $secretKey) 
  {
		return base64_encode(hash_hmac('sha256', $data, $secretKey, true));
	}

	private function buildDataToSign($params) 
  {
		$signedFieldNames = explode(",", $params["signed_field_names"]);

		foreach ($signedFieldNames as $field) 
    {
			$dataToSign[] = $field . "=" . $params[$field];
		}

		return $this->commaSeparate($dataToSign);
	}

	private function commaSeparate($dataToSign) 
  {
		return implode(",", $dataToSign);
	}
}
