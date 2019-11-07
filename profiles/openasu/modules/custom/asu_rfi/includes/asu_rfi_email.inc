<?php /** @noinspection PhpUnusedLocalVariableInspection */
/** @noinspection PhpUnused */

/**
 * Generate undergrad email
 *
 * @param string $prog_plan The program code selected by the user in the RFI form
 * @param string $e_email The email address entered by the user
 * @param string $humanName The name of the form requester
 * @return boolean Email generation success status
 */
function asu_rfi_undergrad_email($prog_plan, $e_email, $humanName) {
  if (!isset($e_email)) {
    watchdog('asu_rfi', 'An undergraduate RFI form attempted to
     send an email without an destination address.');
    return FALSE;
  }

  if (!empty($prog_plan)) {
    $data = xmlrpc('https://webapp4.asu.edu/programs/XmlRpcServer',
      array('eAdvisorDSFind.findDegreeByAcadPlanMapArray' => array($prog_plan)));
    foreach ($data as $ball_arr) {
      $name = $ball_arr["Descr100"];
      $degree = $ball_arr["Degree"];
      $desc = $ball_arr["DescrlongExtns"];
      if (isset($name) && strstr($name, ', ')) {
        list($degree_name_before_comma, $degree_name_after_comma) = explode(", ", $name);
        $name = $degree_name_before_comma;
      }
      if (isset($desc)) {
        $description = "<strong><i> Program description</strong> </i><br />" . $desc;
      }
    }
  }

  if (!isset($description)) {
    $description = '';
  }

  $degree_search_link = (isset($name) && isset($degree))
    ? "<a href='https://webapp4.asu.edu/programs/t5/majorinfo/ASU00/" . $prog_plan
    . "/undergrad/false'><h3>" . $name . ", " . $degree . "</h3></a>"
    : '';

  $message_start = " <p>" . $humanName . ",</p>";
  $message_middle = " <p> Thank you for your interest in pursuing a degree at <a href='https://www.asu.edu'>Arizona State University</a>. U.S. News & World Report ranks ASU the #1 most innovative school in the country, ahead of Stanford and MIT. From engaging in meaningful, innovative research and entrepreneurial projects to collaborating with classmates and faculty, you will be elevating your career when you enroll in undergraduate studies at ASU. </p>
    <p>With <a href='https://webapp4.asu.edu/programs/'>more than 350 excellent undergraduate degree programs and certificates</a>, including new degree programs in emerging fields, there is a degree path here to fit your career goals.</p><p>Below you will find a link to degree search, which has more information about the degree program in which you indicated interest.</p>
    " . $degree_search_link . "
    <p>As you learn more about ASU, we invite you to get a full view of the Sun Devil experience. We'll keep you updated on student life, academic opportunities and admission timelines, and send you special invitations to events near you.</p>";
  $message_end = "<p>Sincerely,</p>
                  <p>Matthew R. López<br>
                     Executive Director<br>
                     Admission Services
                  </p>";
  $helpfulResources = "<p><strong><i>Helpful Resources for Future Sun Devils</i></strong><br>
                        <i>Interactive viewbook and general information</i></p>
                        <ul>
                            <li><a href='https://www.asu.edu/myfuture'>my future</a></li>
                            <li><a href='http://www.asu.edu/prospective/video/'>about ASU (Video)</a></li>
                            <li><a href='https://students.asu.edu/tuition'>cost calculator</a> and <a href='https://students.asu.edu/scholarships/estimator '>scholarship estimator</a></li>
                        </ul>
                        <p><strong>Explore the campus for your degree:</strong><br>
                            <a href='https://www.asu.edu/tour/'>Take a tour</a>
                        </p>";


  $footer = "<br /><div style='color:grey;'>This message sent by <a href = 'mailto:asurecruitment@asu.edu' >asurecruitment@asu.edu</a> is the result of your request for more information on the ASU website.
  By providing your email address, you gave Arizona State University permission to send this email.Arizona State University | Admission Services | PO Box 870112 | Tempe, AZ 85287-0112 Subscription Center | Unsubscribe | Privacy Policy</div>";

  // Compile email body
  $params['body'] = $message_start . $message_middle . $message_end . $description . $helpfulResources . $footer;

  // Get email configuration variable values from the rfi admin settings page
  $from_email = variable_get('asu_rfi_from_email_field');
  $from = (!empty($from_email)) ? $from_email : 'asurecruitment@asu.edu';

  $subject = variable_get('asu_rfi_email_subject_field');
  $params['subject'] = (!empty($subject)) ? $subject : 'Your requested ASU degree information.';

  // send the mail to the user
  try {
    $my_module = 'mimemail';
    $my_mail_token = '';
    $MimeMailSystem = drupal_mail_system($my_module, $my_mail_token);
    $message = array(
      'module' => 'mimemail',
      'id' => $my_module . '_' . $my_mail_token,
      'from' => $from,
      'key' => '',
      'subject' => $params['subject'],
      'body' => array($params['body']),
      'to' => $e_email,
      'headers' => array(
        'From' => $from,
        'Sender' => $from,
        'Return-Path' => $from,
        'Content-Type' => 'text/html; charset=UTF-8;',
        'to' => $e_email
      ),
    );

    $message = $MimeMailSystem->format($message);
    $result = $MimeMailSystem->mail($message);
  } catch (Exception $e) {
    watchdog('asu_rfi', 'An undergraduate form failed to send to generate an email: '
      . $e->getMessage());
  }
  if (isset($result)) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}


/**
 * Generate graduate email
 *
 * @param string $prog_plan The program code selected by the user in the RFI form
 * @param string $e_email The email address entered by the user
 * @param string $humanName The name of the form requester
 * @return boolean Email generation success status
 */
function asu_rfi_grad_email($prog_plan, $e_email, $humanName) {
  if (!isset($e_email)) {
    watchdog('asu_rfi', 'An undergraduate RFI form attempted to send
     an email without a destination address.', array(), WATCHDOG_INFO);
    return FALSE;
  }
  if (!empty($prog_plan)) {
    $data = xmlrpc('https://webapp4.asu.edu/programs/XmlRpcServer',
      array('eAdvisorDSFind.findDegreeByAcadPlanMapArray' => array($prog_plan)));

    foreach ($data as $ball_arr) {
      $name = $ball_arr["Descr100"];
      $degree = $ball_arr["Degree"];
      $desc = $ball_arr["DescrlongExtns"];
      if (isset($name) && strstr($name, ', ')) {
        list($degree_name_before_comma, $degree_name_after_comma) = explode(", ", $name);
        $name = $degree_name_before_comma;
      }
      if (isset($desc)) {
        $description = "<strong><em> Program description</em></strong><br />" . $desc;
      }
    }
  }

  if (!isset($description)) {
    $description = '';
  }

  $degree_search_link = (isset($name) && isset($degree))
    ? "<a href='https://webapp4.asu.edu/programs/t5/majorinfo/ASU00/" . $prog_plan
    . "/graduate/false'><h3>" . $name . ", " . $degree . "</h3></a>"
    : $degree_search_link = '';

  $message_start = " <p>" . $humanName . ",</p>";
  $message_middle = " <p> Thank you for your interest in pursuing an advanced degree at <a href='https://students.asu.edu/graduate'>Arizona State University</a>. U.S. News & World Report ranks ASU the #1 most innovative school in the country, ahead of Stanford and MIT. From engaging in meaningful, innovative research and entrepreneurial projects to collaborating with classmates and faculty, you will be elevating your career when you enroll in graduate studies at ASU. </p>
    <p>With <a href='https://webapp4.asu.edu/programs/t5/graduate/false'>more than 450 excellent graduate degree programs and certificates</a>, including new degree programs in emerging fields, there is a degree path here to fit your career goals.</p>
    <p>Following is a link to Degree Search which has more information about the degree program in which you indicated interest.</p>
    " . $degree_search_link . "
    <p>If you have any questions about a degree program, feel free to <a href='mailto:gograd@asu.edu'>contact us</a> or the academic department for the program. We are all happy to help you take the next step toward your graduate degree.</p>";
  $message_end = "<p>Sincerely,</p>
                  <p>Michael Mobley<br>
                     Director, Graduate Admissions<br>
                     Admission Services
                  </p>";
  $helpfulResources = "<p><strong><i>Review these additional resources</i></strong><br>
                            <a href='https://students.asu.edu/graduate'>How and When to Apply for ASU Graduate Admission</a><br>
                            <a href='https://graduate.asu.edu/egss'>Preparing for Graduate School Seminars</a><br>
                            <a href='https://students.asu.edu/tuition'>Cost Estimator</a> and <a href='https://students.asu.edu/graduate/finances'>Graduate Funding Options</a></p>

                        <p><strong>Explore the campus for your degree:</strong><br>
                            <a href='https://www.asu.edu/tour/'>Take a tour</a>
                        </p>";


  $footer = "<br /><div style='color:grey;'>This message sent by <a href = 'mailto:asurecruitment@asu.edu' >asurecruitment@asu.edu</a> is the result of your request for more information on the ASU website.
  By providing your email address, you gave Arizona State University permission to send this email.
  Please add <a href = 'mailto:asurecruitment@asu.edu' >asurecruitment@asu.edu</a> to your address book or safe sender list. Arizona State University, Undergraduate Admissions, PO Box 870112, Tempe, AZ 85287-0112.</div>";

  // Compile email body
  $params['body'] = $message_start . $message_middle . $message_end . $description . $helpfulResources . $footer;

  // Get email configuration variable values from the rfi admin settings page
  $from_email = variable_get('asu_rfi_from_email_field');
  $from = (!empty($from_email)) ? $from_email : 'asurecruitment@asu.edu';

  $subject = variable_get('asu_rfi_email_subject_field');
  $params['subject'] = (!empty($subject)) ? $subject : 'Your requested ASU degree information.';

  // send the mail to the user
  try {
    $my_module = 'mimemail';
    $my_mail_token = '';
    $MimeMailSystem = drupal_mail_system($my_module, $my_mail_token);
    $message = array(
      'module' => 'mimemail',
      'id' => $my_module . '_' . $my_mail_token,
      'from' => $from,
      'key' => '',
      'subject' => $params['subject'],
      'body' => array($params['body']),
      'to' => $e_email,
      'headers' => array(
        'From' => $from,
        'Sender' => $from,
        'Return-Path' => $from,
        'Content-Type' => 'text/html; charset=UTF-8;',
        'to' => $e_email
      ),
    );

    $message = $MimeMailSystem->format($message);

    $result = $MimeMailSystem->mail($message);
  } catch (Exception $e) {
    watchdog('asu_rfi', 'A graduate form failed to send to generate an email: ' . $e->getMessage());
  }

  if (isset($result)) {
    return TRUE;
  }
  else {
    return FALSE;
  }

}
