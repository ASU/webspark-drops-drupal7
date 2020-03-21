<?php /** @noinspection PhpUnusedLocalVariableInspection */
/** @noinspection PhpUnused */

/**
 * Generates a Form API element for a single field from pre-determined list of
 * RFI form elements.
 *
 * To create multi-tiered elements for fieldsets (i.e. My Interest -> Major),
 * first use _asu_rfi_form_elements_multiple_keys to establish the array element
 * structure and then call this function for the elements contents.
 *
 * @param $name - Name of form element desired
 * @param bool $session - TRUE if #default_value is supposed to be set by $_SESSION
 * values IF they exist. Defaults to FALSE.
 * @param mixed $value
 * - For non-hidden FAPI elements: POSSIBLE Default values generated for form element;
 *   Usually for <select> element
 * - For hidden FAPI elements: Single, static value passed in manually.
 * @return mixed (array, bool) - Form API array element if exists, or returns FALSE if $name is not matched.
 */
function _asu_rfi_form_base_components($name, $session = FALSE, $value = '') {
  switch ($name) {
    // Category bases
    case 'about_me':
      return array(
        '#type' => 'fieldset',
        '#title' => 'About me...',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
      );
      break;
    case 'address_info':
      return array(
        '#type' => 'fieldset',
        '#title' => 'Please also send me information to the following address...',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
      );
      break;
    case 'my_interest':
      return array(
        '#type' => 'fieldset',
        '#title' => 'I\'m interested in...',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#size' => 10,
      );
      break;

    // Individual fields
    //////////////////////
    case 'req_header_text':
      return array(
        '#type' => 'item',
        '#markup' => _asu_rfi_form_header_text(),
      );
      break;
    case 'req_helper':
      return array(
        '#type' => 'markup',
        '#markup' => '<p>Fields marked with <span class="form-required">*</span> are required.</p>',
        '#prefix' => '<div id="edit-req-helper" class="alert form-type-item form-item form-group">',
        '#suffix' => '</div>',
      );
      break;
    case 'campus':
      return array( // Addon(s)
        '#type' => 'select',
        '#title' => t('My campus of choice is'),
        '#options' => (isset($value)) ? $value : array(),
        '#empty_option' => ' - Select - ',
        '#empty_value' => '',
        '#attributes' => array('class' => array('reqinfo_campus', 'chosen-disable')),
        // For AJAX updates of fields
        '#prefix' => '<div id="asu-rfi-campus-ajax-wrapper">',
        '#suffix' => '</div>',
        '#ajax' => array(
          'callback' => 'asu_rfi_campus_ajax_callback',
          'wrapper' => 'asu-rfi-start-date-ajax-wrapper',
          'method' => 'replace',
          'effect' => 'fade',
        ),
      );
      break;
    case 'student_type':
      $student_type = array(
        '#type' => 'select',
        '#title' => t('I will be a future'),
        '#options' => array(
          'First Time Freshman' => 'First Time Freshman',
          'Transfer' => 'Transfer',
          'Readmission' => 'Readmission'
        ),
        '#attributes' => array('class' => array('reqinfo_student_type', 'chosen-disable')),
      );
      // DEFAULT
      break;
    case 'start_date':
      $start_date = array(
        '#type' => 'select',
        '#title' => t('My start date'),
        '#options' => (isset($value)) ? $value : array(),
        '#attributes' => array('class' => array('chosen-disable')),
        // For AJAX updates
        '#prefix' => '<div id="asu-rfi-start-date-ajax-wrapper">',
        '#suffix' => '</div>',
      );
      break;
    case 'first_name':
      return array( // addon
        '#type' => 'textfield',
        '#title' => t('First name'),
        '#size' => 30,
        '#maxlength' => 50,
        '#required' => TRUE,
        '#prefix' => '<div id ="req_info_form">',
      );
      break;
    case 'last_name':
      $last_name = array(
        '#type' => 'textfield',
        '#title' => t('Last name'),
        '#size' => 30,
        '#maxlength' => 64,
        '#required' => TRUE,
      );
      // DEFAULT
      break;
    case 'email':
      $email = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#size' => 30,
        '#maxlength' => 100,
        '#required' => TRUE,
        // DEFAULT
      );
      break;
    case 'phone':
      $phone = array(
        '#prefix' => '<div class="phone_field_rfi">',
        '#suffix' => '</div>',
        '#type' => 'textfield',
        '#title' => t('Preferred phone number'),
        '#description' => t('USA Format: xxx-xxx-xxxx'),
        '#size' => 30,
        '#maxlength' => 40,
        '#required' => TRUE,
        '#attributes' => array('class' => array('rfi_phone')),
      );
      // DEFAULT
      break;
    case 'mobile_check':
      $mobile_check = array(
        '#type' => 'checkbox',
        '#title' => t('This is a USA mobile number and I would like to receive information via SMS text messaging'),
        '#title_display' => 'after',
        '#size' => 30,
        '#maxlength' => 30,
        '#required' => FALSE,
        '#attributes' => array('class' => array('rfi_mobile')),
      );
      // DEFAULT
      break;
    case 'address':
      return array(
        '#type' => 'textfield',
        '#title' => t('Address'),
        '#size' => 30,
        '#maxlength' => 64,
      );
      break;
    case 'city':
      return array(
        '#type' => 'textfield',
        '#title' => t('City'),
        '#size' => 30,
        '#maxlength' => 30,
      );
      break;
    case 'state':
      $state = array(
        '#id' => 'rfi-state',
        '#type' => 'select',
        '#options' => (isset($value)) ? $value : array(),
        '#title' => t('State/Province'),
        '#required' => FALSE,
      );
      // DEFAULT
      break;
    case 'zipcode':
      $zipcode = array( // Add-on
        '#type' => 'textfield',
        '#title' => t('Postal code'),
        '#size' => 30,
        '#maxlength' => 15,
        '#states' => array(
          'required' => array(
            ':input[name="country"]' => array('value' => 'United States'),
          ),
        ),
      );
      // DEFAULT
      break;
    case 'country':
      $country = array(
        '#id' => 'rfi-country',
        '#type' => 'select',
        '#options' => (isset($value)) ? $value : array(),
        '#title' => t('Country'),
        '#attributes' => array('class' => array('chosen-disable')),
      );
      // DEFAULT
      break;
    case 'citizenship':
      return array(
        '#type' => 'checkbox',
        '#title' => t('I am not a U.S. citizen and do not have a green card.'),
        '#title_display' => 'after',
      );
      break;
    case 'military':
      return array(
        '#type' => 'radios',
        '#title' => t('U.S. Veteran admission information and services'),
        '#options' => array(
          "None" => "None",
          "Active Duty" => "Active Duty",
          "National Guard" => "National Guard",
          "Veteran" => "Veteran",
          "Armed forces reserve" => "Armed forces reserve",
          "Spouse/Dependent" => "Spouse/Dependent"
        ),
        '#size' => 30,
      );
      break;
    case 'birthdate':
      return array(
        '#type' => 'textfield',
        '#title' => t('Date of birth'),
        '#description' => t('Format: mm/dd/yyyy'),
        '#title_display' => 'invisible',
        '#size' => 30,
        '#maxlength' => 30,
      );
    case 'questions':
      return array(
        '#type' => 'textarea',
        '#title' => t('I also need assistance with the following:'),
        '#cols' => 60,
        '#resizable' => TRUE,
        '#rows' => 5,
        '#description' => '(Limit of 255 characters)',
      );
      break;
    case 'gdpr_message':
      return array(
        '#type' => 'item',
        '#markup' => _asu_rfi_get_gdpr_markup()
      );
      break;

    // HIDDEN fields
    //////////////////
    case 'degree_type':
      return array(
        '#type' => 'hidden',
        '#size' => 30,
        '#maxlength' => 64,
        '#default_value' => (isset($value)) ? (string) $value : '', // $form_type
      );
      break;
    case 'domain':
      return array(
        '#type' => 'hidden',
        '#size' => 30,
        '#maxlength' => 64,
        '#default_value' => (string) $_SERVER['HTTP_HOST'],
      );
      break;
    case 'nid':
      return array(
        '#type' => 'hidden',
        '#maxlength' => 16,
        '#default_value' => (isset($value)) ? (string) $value : '',
        '#size' => 16,
      );
    case 'enterpriseclientid':
      // Will be filled in using JS to obtain from GA, per EdPlus.
      // See WEBSPARK-1198.
      return array(
        '#type' => 'hidden',
        '#maxlength' => 255,
        '#default_value' => '',
        '#size' => 60,
      );
      break;
    case 'first_enity_id':
      return array(
        '#type' => 'hidden',
        '#default_value' => (isset($value)) ? (string) $value : '',
      );
      break;
    case 'ip_address':
      return array(
        '#type' => 'hidden',
        '#size' => 30,
        '#maxlength' => 64,
        '#default_value' => $_SERVER['REMOTE_ADDR'],
      );
      break;
    case 'type_of_form':
      return array(
        '#type' => 'hidden',
        '#size' => 30,
        '#maxlength' => 64,
        '#default_value' => (isset($value)) ? (string) $value : '',
      );
      break;
    case 'webform_url':
      return array(
        '#type' => 'hidden',
        '#size' => 30,
        '#maxlength' => 64,
        '#default_value' => $_SERVER['HTTP_HOST'],
      );
      break;
    default:
      flogger('asu_rfi', 'Form element @name cannot be found and rendered',
        array('@name' => $name), WATCHDOG_ERROR);
      return FALSE;
      break;
  }
  // HAVE #default_value set and not returned yet.
  if (isset(${$name})) {
    if ($session) {
      ${$name}['#default_value'] = (isset($_SESSION['rfi_data'][$name])) ? $_SESSION['rfi_data'][$name] : NULL;
    }
    return ${$name};
  }
  return FALSE;
}


/**
 * Generates a single Form API element that is nested in a <fieldset>.
 *
 * - Only handles two levels (name, sub_name) for FAPI array keys.
 * - Passes FAPI element generation to _asu_rfi_form_base_components().
 *
 * @param $name - Fieldset key
 * @param $sub_name - Form element name
 * @param bool $session - TRUE if #default_value is supposed to be set by $_SESSION
 * values IF they exist. Defaults to FALSE.
 * @param null $value - default values generated for form element; Usually for <select> element
 * @return array|bool - Form API array element if exists, or returns FALSE if $name is not matched.
 * @return mixed
 */
function _asu_rfi_form_elements_multiple_keys($name, $sub_name, $session = FALSE, $value = NULL) {
  switch ($name) {
    case 'my_interest':
      switch ($sub_name) {
        case 'campus':
          return _asu_rfi_form_base_components('campus', $session, $value);
          break;
        case 'student_type':
          return _asu_rfi_form_base_components('student_type', $session, $value);
          break;
        case 'start_date':
          return _asu_rfi_form_base_components('start_date', $session, $value);
          break;
        default:
          // none
          break;
      }
      break;
    case 'about_me':
      switch ($sub_name) {
        case 'first_name':
          return _asu_rfi_form_base_components('first_name', $session, $value);
          break;
        case 'last_name':
          return _asu_rfi_form_base_components('last_name', $session, $value);
          break;
        case 'email':
          return _asu_rfi_form_base_components('email', $session, $value);
          break;
        case 'phone':
          return _asu_rfi_form_base_components('phone', $session, $value);
          break;
        case 'mobile_check':
          return _asu_rfi_form_base_components('mobile_check', $session, $value);
          break;
        case 'country':
          return _asu_rfi_form_base_components('country', $session, $value);
          break;
        case 'zipcode':
          return _asu_rfi_form_base_components('zipcode', $session, $value);
          break;
        case 'birthdate':
          return _asu_rfi_form_base_components('birthdate', $session, $value);
          break;
        case 'citizenship':
          return _asu_rfi_form_base_components('citizenship', $session, $value);
          break;
        case 'military':
          return _asu_rfi_form_base_components('military', $session, $value);
          break;
        default:
          // none
          break;
      }
      break;
    case 'address_info':
      switch ($sub_name) {
        case 'address':
          return  _asu_rfi_form_base_components('address', $session, $value);
          break;
        case 'city':
          return _asu_rfi_form_base_components('city', $session, $value);
          break;
        case 'state':
          return _asu_rfi_form_base_components('state', $session, $value);
          break;
        case 'country':
          return _asu_rfi_form_base_components('country', $session, $value);
          break;
        case 'zipcode':
          return _asu_rfi_form_base_components('zipcode', $session, $value);
          break;
        default:
          // none
          break;
      }
      break;
    default:
      flogger('asu_rfi', 'Form element @name -> @sub_name cannot be found and rendered',
        array('@name' => $name, '@sub_name' => $sub_name), WATCHDOG_ERROR);
      return FALSE;
      break;
  }
  return FALSE;
}
