<?php
// $Id: asu_rfi.pages.inc 

/**
 * @file
 * Request info form generation using form API
 */


/* Implementation of hook_form **/

function asu_rfi_email($prog_plan, $e_email){

 if(!empty($prog_plan)){   
 $data = xmlrpc('https://webapp4.asu.edu/programs/XmlRpcServer', array('eAdvisorDSFind.findDegreeByAcadPlanMapArray' => array($prog_plan)));

        foreach($data as $ball_arr)
         {
  
           $name = $ball_arr["Descr100"];
           $degree = $ball_arr["Degree"];
           $desc  = $ball_arr["DescrlongExtns"];
	   if(isset($ball_arr["AsuCareerOpp"])){
	      $career = $ball_arr["AsuCareerOpp"];
	   }
	   else{
	    $career = '';
	   }
           if(isset($ball_arr["AsuCritTrackUrl"])){
	      $major_map = $ball_arr["AsuCritTrackUrl"];
	   }
	   else{
	      $major_map = '';
	   }
           
           $prog_fee = $ball_arr["AsuProgramFee"];
           if($prog_fee == "N")
                 $prog_fee = "No";
            if($prog_fee == "Y")
               $prog_fee = "Yes";
              $lang_require = $ball_arr["AsuLangReqFlag"];
            if($lang_require == "N")
                  $lang_require = "No";
            if($lang_require == "Y")
                  $lang_require = "Yes";
		  if(isset($ball_arr["MinMathReq"])){
		      $math_req = $ball_arr["MinMathReq"].". ";
		  }
		  else{
		    $math_req = '';
		  }
                
             if(gettype($ball_arr["asuAcadpMrfText"]) <> "array")
                $asu_add_requ = $ball_arr["asuAcadpMrfText"];
		if(isset($ball_arr["Reqdescr"])){
                  $additional_req = $ball_arr["Reqdescr"];
		   $addition_req = "<br /><strong><i> Additional Requirements </i></strong> <br />".$additional_req;
		}
        
            // get the transfer data
            foreach($ball_arr["transferAgreementInfo"] as $agree){

                 if(!empty($agree)){
        
                           $maricopa_aff = $agree["tACommunityCollege"];
 
                      }
              }
              
             // get the wue data
            foreach($ball_arr["CampusWueInfo"] as $wufu){
		   if(!empty($wufu['wueDescrs'])){
		      $wufu_data = $wufu['wueDescrs']."<br /><br />";
		   }
		   else{
		     $wufu_data = '';
		   }
                }
                
            $newdata = asu_rfi_career($data); // career data function
            $short_desc = "<br /><strong> Your Degree Information: </strong><br /><i> <h4>". $name .", ".$degree."</h4></i>";
            $description = "<strong><i> Program description</strong> </i><br />".$desc;
            $career_format = "<strong><i>  Career Opportunities </i></strong> <br />".$career;
            if(!empty($newdata)){ //add this additional text if there is a career summary data
                 $table = "<table><tr><th> </th><th> *growth &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</th><th> *median salary </th></tr>";
               
                 $json_data = "<span>Example Careers: Students who complete this degree program may be prepared for the following careers.
  Advanced degrees or certifications may be required for academic or clinical positions. Career examples include but are not limited to the following:</span><br /><br />";
           $career_format = $career_format.$json_data.$table;
            }
           
            if(!empty($asu_add_requ)){
            $require_math = $math_req.$asu_add_requ;
            }
            else{
               $require_math = $math_req;
            }
         
            $fee = " <span> Additional Program Fee: </span> "."  ". $prog_fee ."<br />";
            $lang = "<span> Second Language Requirement: </span> " ."   ".$lang_require ."<br />";
            if(!empty($require_math)){
              $math_requ = "<span> First Required Math Course: </span>" ."   ".$require_math ."<br /><br />";
            }
           
            
            /// check if this program is partnered with any other institutes
            if(!empty($maricopa_aff)){
                 $mari = " <br /><strong><i> Transfer Agreements </i></strong> <br /><br />ASU has partnered with the following institutions to enable you to do a seamless transfer. <br /><br />";
                 if(sizeof($maricopa_aff) > 1){
                 foreach($maricopa_aff as $mari_aff){
                    $transfer_data = $mari_aff;
                    if($transfer_data == "Central Arizona College"){
                      $transfer_dataurl = "<a href='http://transfer.asu.edu/central-az'>".$transfer_data."</a>";
                    }
                    if($transfer_data == "Cochise College"){
                      $transfer_dataurl = "<a href='http://transfer.asu.edu/cochise'>".$transfer_data."</a>";
                    }
                    if($transfer_data == "Maricopa County Community College District"){
                      $transfer_dataurl = "<a href='http://transfer.asu.edu/maricopa'>".$transfer_data."</a>";
                    }
                    if($transfer_data == "Arizona Western College"){
                      $transfer_dataurl = "<a href='http://transfer.asu.edu/az-western'>".$transfer_data."</a>";
                    }
                    if($transfer_data == "Coconino Community College"){
                      $transfer_dataurl = "<a href='http://transfer.asu.edu/coconino'>".$transfer_data."</a>";
                    }
                    if($transfer_data == "Mohave Community College"){
                      $transfer_dataurl = "<a href='http://transfer.asu.edu/mohave'>".$transfer_data."</a>";
                    }
                    if($transfer_data == "Eastern Arizona College"){
                      $transfer_dataurl = "<a href='http://transfer.asu.edu/eastern-az'>".$transfer_data."</a>";
                    }
                    if($transfer_data == "Yavapai College"){
                      $transfer_dataurl = "<a href='http://transfer.asu.edu/yavapai'>".$transfer_data."</a>";
                    }
                    if($transfer_data == "Pima Community College"){
                      $transfer_dataurl = "<a href='http://transfer.asu.edu/pima'>".$transfer_data."</a>";
                    }
                    if($transfer_data == "Northland Pioneer College"){
                      $transfer_dataurl = "<a href='http://transfer.asu.edu/northland-pioneer'>".$transfer_data."</a>";
                    }
                    $mari = $mari.$transfer_dataurl."<br />";
                   }
               }
            else{
                   if($maricopa_aff == "Central Arizona College"){
                      $transfer_sinlgedataurl = "<a href='http://transfer.asu.edu/central-az'>".$maricopa_aff."</a>";
                    }
                    if($maricopa_aff == "Cochise College"){
                      $transfer_sinlgedataurl = "<a href='http://transfer.asu.edu/cochise'>".$maricopa_aff."</a>";
                    }
                    if($maricopa_aff == "Maricopa County Community College District"){
                      $transfer_sinlgedataurl = "<a href='http://transfer.asu.edu/maricopa'>".$maricopa_aff."</a>";
                    }
                    if($maricopa_aff == "Arizona Western College"){
                      $transfer_sinlgedataurl = "<a href='http://transfer.asu.edu/az-western'>".$maricopa_aff."</a>";
                    }
                    if($maricopa_aff == "Coconino Community College"){
                      $transfer_sinlgedataurl = "<a href='http://transfer.asu.edu/coconino'>".$maricopa_aff."</a>";
                    }
                    if($maricopa_aff == "Mohave Community College"){
                      $transfer_sinlgedataurl = "<a href='http://transfer.asu.edu/mohave'>".$maricopa_aff."</a>";
                    }
                    if($maricopa_aff == "Eastern Arizona College"){
                      $transfer_sinlgedataurl = "<a href='http://transfer.asu.edu/eastern-az'>".$maricopa_aff."</a>";
                    }
                    if($maricopa_aff == "Yavapai College"){
                      $transfer_sinlgedataurl = "<a href='http://transfer.asu.edu/yavapai'>".$maricopa_aff."</a>";
                    }
                    if($maricopa_aff == "Pima Community College"){
                      $transfer_sinlgedataurl = "<a href='http://transfer.asu.edu/pima'>".$maricopa_aff."</a>";
                    }
                    if($maricopa_aff == "Northland Pioneer College"){
                      $transfer_sinlgedataurl = "<a href='http://transfer.asu.edu/northland-pioneer'>".$maricopa_aff."</a>";
                    }
                  $mari = $mari.$transfer_sinlgedataurl. "<br />";
             }
                
            }
	    else{
	     $mari = '';
	    }

            $map = "<br /><strong><i> Listing of Required Courses: </i> </strong> <br /><a href= ".$major_map."> <br /><strong> View major map </strong> </a><br /><br />";
            
     
            if(!empty($additional_req)){ // check if there are any additional requirments
                $whole_body = $short_desc.$description.$wufu_data.$fee.$lang.$math_requ.$addition_req.$mari.$map.$career_format;
	    }
            else
	    {
                $whole_body = $short_desc. $description.$wufu_data.$fee.$lang.$math_requ.$mari.$map.$career_format;
	    }
         }
 }
  $message_start = "<p> Thank you for your interest in attending Arizona State University.";
  $message_middle = " Below you will find additional resources for new students and information about the degree in which you have expressed an interest. ";
  $message_end = "</p><p> If you submitted a question on your request information form, an ASU representative will contact you soon.</p>
            
            <h4> Helpful Resources for Future Sun Devils: </h4>
            <i> Interactive viewbook and general information: </i>
            <ul><li><a href = 'http://www.asu.edu/myfuture/index-desktop.html'> My future</a>   </li>
                <li><a href = 'http://www.asu.edu/prospective/video/'>  About ASU (Video) </a>   </li>
            </ul> <br />
            
            <i> ASU admission requirements: </i>
          
            <ul><li><a href = 'https://students.asu.edu/freshman/requirements'>Freshman </a> </li>
            <li><a href = 'http://transfer.asu.edu/transferrequirements'> Transfer</a>  </li>
            <li><a href = 'http://global.asu.edu/future/undergrad'>International</a> </li>
            </ul> <br />
            
            <i>Paying for college: </i>
            <ul><li> <a href = 'https://students.asu.edu/costs'> Cost calculator </a> </li>
            <li><a href = 'https://students.asu.edu/scholarships/estimator'> Freshman scholarship estimator </a>  </li>
            <li><a href = 'https://students.asu.edu/financialaid/apply'>How to apply for financial aid</a> </li>
            </ul> <br />";
            
  $footer = "<br /><div style='color:grey;'>This message sent by <a href = 'mailto:asurecruitment@asu.edu' >asurecruitment@asu.edu</a> as a result of your request for more information on the ASU website.
  By providing your email address, you gave Arizona State University permission to send this email.
  Please add <a href = 'mailto:asurecruitment@asu.edu' >asurecruitment@asu.edu</a> to your address book or safe sender list. Arizona State University - Undergraduate Admissions - PO Box 870112 - Tempe, AZ 85287-0112.</div>";

//if(!empty($prog_plan)){
 /*       $message = $message_start.$message_middle;
      }
  else{
       $message = $message_start.$message_end.$footer;
       $params['body'] = $message;
    }*/
 if(!empty($newdata)){
    $table_end = "</table>";
   
    foreach($newdata as $survey){
    $row = $survey;
    $whole_body = $whole_body.$row;  
    }
   $params['body'] = $message_start.$message_middle.$whole_body.$table_end.$message_end.$footer;
   }
  else{
   $whole_body = $whole_body;
   $params['body'] = $message_start.$message_middle.$whole_body.$message_end.$footer;
  }
//}
 //Get email configuration varible values from the rfi admin settings page
  $from_email = variable_get('asu_rfi_from_email_field');
  if(!empty($from_email)){
    $from = $from_email;
  }
  else{
    $from = 'asurecruitment@asu.edu';
  }
  
  $sender_name = variable_get('asu_rfi_from_name_field');
  if(!empty($sender_name)){
    $sender = $sender_name;
  }
  else{
    $sender = 'Arizona State University';
  }
  
  $subject = variable_get('asu_rfi_email_subject_field');
  if(!empty($subject)){
    $params['subject'] = $subject;
  }
  else{
    $params['subject'] = 'Your requested ASU degree information.';
  }
   
   if(isset($e_email)){
        $to = $e_email;

   }
   
   // send the mail to the user
  
    $my_module = 'mimemail';
    $my_mail_token = '';
    $MimeMailSystem = drupal_mail_system($my_module, $my_mail_token);
    $default_from = variable_get('site_mail', ini_get('sendmail_from'));
    $message = array(
            'module' => 'mimemail',
	    'id' => $my_module . '_' . $my_mail_token,
	    'from' => $from,
	    'key' => '',
	    'subject' => $params['subject'],
	    'body' => array($params['body']),
	    'to' => $to,  
	    'headers' => array(
              'From' => $from,
              'Sender' => $from,
              'Return-Path' => $from,
	      'Content-Type' => 'text/html; charset=UTF-8;',
	      'to' => $to  
            ),
	);
	
	$message = $MimeMailSystem->format($message);
	
          if ($MimeMailSystem->mail($message)) {
           
          } else {
          
          }

}


//function to to get career summary data 
function asu_rfi_career($data){
   foreach($data as $var_arr){
 
     foreach($var_arr["careerData"] as $career_summary){
  
       $careerdata_title = $career_summary["careerDataOnetTitle"];
	   
            $growth = $career_summary["careerDataGrowth"];
	    
            $median = $career_summary["careerDataSalary"];
            $type = gettype($median);
            if(!empty($growth)){
                $growth = $growth."%";
            }
            if($growth < 0){
              $growth = "";
            }
             if(empty($median)){
               $median = "not available";
            }
            $career_option[] = "<tr><td>".$careerdata_title."&nbsp;&nbsp;&nbsp;&nbsp;</td><td>".$growth."</td><td>". $median."</td></tr>";
         }
        }
     if(isset($career_option)){
       $option = $career_option;
     }
     else{
      $option = '';
     }
     return $option;
}
 