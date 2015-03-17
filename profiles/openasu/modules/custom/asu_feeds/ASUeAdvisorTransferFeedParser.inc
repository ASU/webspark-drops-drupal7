<?php
/**
 * @file
 * Parses and maps ASU eAdvisor feed.
 */

// Multigroup display in views: http://drupal.org/node/692186#comment-2563668

class ASUeAdvisorTransferFeedParser extends FeedsParser {

  /**
   * Implementation of FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    
    $batch = $fetcher_result;
    
    $result = $batch->getRaw();
    //error_log( print_r($result, true) );
    $parsed_data = $result;
    if (!count($parsed_data)) {
      return new FeedsParserResult($parsed_data);
    }

    // Parse the items - flatten where necessary
    foreach ($parsed_data as $key => $data) {

      // Unique ID for the plan
      $parsed_data[$key]['guid'] = md5($parsed_data[$key]['AcadPlan']);

      if (count($data['accelerateDegrees'])) {
        $ad = array();
        $parsed_data[$key]['ad'] = 1;
      }

      if (count($data['CampusWueInfo'])) {
        $wueCampusConfirmed = array();
        foreach ($data['CampusWueInfo'] as $cwi) {
          if ($cwi['isCampusWue'] == 1) {
            $parsed_data[$key]['wueCampusConfirmed'] = 1;
          }
        }
      }

/*      if (count($data['DegreeNew'])) {
        $degreeIsNew = array();
        foreach ($data['DegreeNew'] as $dn) {
          $parsed_data[$key]['degreeIsNew'] = 1;
        }
      }*/

      if (count($data['DescrlongExtn5'])) {
        $additionalAdmissions = array();
        $parsed_data[$key]['additionalAdmissions'] = 1;
      }

      // Campuses
      if(count($data['CampusStringArray'])){
        foreach($data['CampusStringArray'] as $campus_key => $value){
          switch(trim(strtoupper($value))){
            case 'ONLNE':
              $value = 'Online';
              break;
            //case 'DOWNTOWN':
            case 'DTPHX':
              $value = 'Downtown';
              break;
            case 'POLY':
              $value = 'Polytechnic';
              break;
            case 'WEST':
              $value = 'West';
              break;
            case 'TMPE':
            case 'TEMPE':
              $value = 'Tempe';
              break;
            case 'CALHC':
              $value = 'Lake Havasu';
              break;
            case 'EAC':
              $value = 'Eastern Arizona College';
              break;
            //Add case for missing campus from degree feed
            default:
              $value = $value;
              break;
          }
          if($value == 'Online'){
            unset($parsed_data[$key]['CampusStringArray'][$campus_key]);
            array_push($parsed_data[$key]['CampusStringArray'],$value);
          }else{
            $parsed_data[$key]['CampusStringArray'][$campus_key] = $value;
          }
        }
        $parsed_data[$key]['CampusStringArray'] = array_values($parsed_data[$key]['CampusStringArray']);
      }

      // Format careerData
      if (count($data['careerData'])) {
        $parsed_data[$key]['careerData'] = json_encode($data['careerData']);

      }

      // Transfer agreements
      $parsed_data[$key]['transferAgreementInfo.type'] = array();
      $parsed_data[$key]['transferAgreementInfo.year'] = array();
      $parsed_data[$key]['transferAgreementInfo.url'] = array();
      $parsed_data[$key]['transferAgreementInfo.communityCollege'] = array();
      if (count($data['transferAgreementInfo'])) {
        foreach ($data['transferAgreementInfo'] as $agreement) {
          foreach ($agreement['transferAgreementYearsUrls'] as $year_url) {
            $type = $agreement['transferAgreementType'];
            $year = $year_url[0];
            $url = $year_url[1];
            $college = $agreement['tACommunityCollege'];
            $parsed_data[$key]['transferAgreementInfo.type'][] = $type;
            $parsed_data[$key]['transferAgreementInfo.year'][] = $year;
            $parsed_data[$key]['transferAgreementInfo.url'][] = $url;
            $parsed_data[$key]['transferAgreementInfo.communityCollege'][] = $college;
          }
        }
      }

      // Build URL for the degree page at ASU Degree Search site - Chizuko
      if ( $batch->getCert() ) {
        $cert = "true";
      }
      else {
        $cert = "false";
      }
      $parsed_data[$key]['degreeSearchURL'] = "https://webapp4.asu.edu/programs/t5/majorinfo/ASU00/" . $parsed_data[$key]['AcadPlan'] . "/" . $batch->getProgram() . "/" . $cert;

      // Program (Undergrad or Graduate) and Cert (True or False). Useful when creating views. - Chizuko
      $parsed_data[$key]['program'] = $batch->getProgram();
      $parsed_data[$key]['cert'] = $cert;

      // Sub-plan code and subplan major map url - [SubPlnMajorMaps]
      $parsed_data[$key]['subPlnMajorMaps.SubplnMajorMapSubplanCode'] = array();
      $parsed_data[$key]['subPlnMajorMaps.SubPlnMajorMapUrl'] = array();
      if (count($data['SubPlnMajorMaps'])) {
        foreach ($data['SubPlnMajorMaps'] as $subplan_url) {
          if(isset($subplan_url['SubplnMajorMapSubplanCode'])){
            $parsed_data[$key]['subPlnMajorMaps.SubplnMajorMapSubplanCode'][] = $subplan_url['SubplnMajorMapSubplanCode'];
          }
          if(isset($subplan_url['SubPlnMajorMapUrl'])){
            $parsed_data[$key]['subPlnMajorMaps.SubPlnMajorMapUrl'][] = $subplan_url['SubPlnMajorMapUrl'];
          }
        }
      }

      // Sub-plans - [SubPln]
      $parsed_data[$key]['subplan.code'] = array();
      $parsed_data[$key]['subplan.name'] = array();
      if (count($data['SubPln'])) {
        foreach ($data['SubPln'] as $the_code => $subplan) {
          $parsed_data[$key]['subplan.code'][] = $the_code;
          $parsed_data[$key]['subplan.name'][] = $subplan;
        }
      }

      //if subplan.code == subPlnMajorMaps.SubplnMajorMapSubplanCode then replace code with name
      if (count($parsed_data[$key]['subplan.name'])) {
        $parsed_data[$key]['subPlnMajorMaps.SubplnMajorMapSubplanName'] = array();
        foreach($parsed_data[$key]['subPlnMajorMaps.SubplnMajorMapSubplanCode'] as $sn){
          $i = 0;
          while ($i <= count($parsed_data[$key]['subplan.name'])) {
            if ($sn == $parsed_data[$key]['subplan.code'][$i]) {
              $parsed_data[$key]['subPlnMajorMaps.SubplnMajorMapSubplanName'][] = $parsed_data[$key]['subplan.name'][$i];
              $i == count($parsed_data[$key]['subplan.name']);
            }
            $i++;
          }
          unset($i);
        }
      }



    } // End of foreach

    //error_log(print_r($parsed_data, true));
    //watchdog('ASU Degrees Debug', '<pre>'. print_r($parsed_data, true) .'</pre>');
    //watchdog('keith $v', '<pre>' . print_r($v, true) . '</pre>');
    return new FeedsParserResult($parsed_data);
  }

  /**
   * Return mapping sources.
   */
  public function getMappingSources() {
    return array(
      'guid' => array('name' => t('GUID - Unique ID for the transfer agreement')),
      'AcadPlan' => array('name' => t('Academic plan')),
      'AcadProg' => array('name' => t('Academic program')),
      'CampusStringArray' => array('name' => t('Campus')),
      'AsuCareerOpp' => array('name' => t('Career opportunities')),
      'CollegeDescr100' => array('name' => t('College name')),
      'CollegeUrl' => array('name' => t('College URL')),
      'Descr100' => array('name' => t('Description (100)')),
      'DegreeDescr' => array('name' => t('Degree description')),
      'DescrlongExtns' => array('name' => t('Degree description (extended)')),
      'Degree' => array(
        'name' => t('Degree'),
        'description' => t('BA / BFA / MFA / etc'),
      ),
      'DiplomaDescr' => array('name' => t('Diploma description')),
      'keywords' => array('name' => t('Keywords')),
      'transferAgreementInfo.type' => array('name' => t('Transfer agreement type')),
      'transferAgreementInfo.year' => array('name' => t('Transfer agreement year')),
      'transferAgreementInfo.url' => array('name' => t('Transfer agreement URL')),
      'transferAgreementInfo.communityCollege' => array('name' => t('Transfer agreement community college')),
      //Chizuko added the following for eAdvisor Degree Feed:
      'DepartmentName' => array('name' => t('Department name')),
      'DepartmentCode' => array('name' => t('Department code')),
      'AsuCritTrackUrl' => array('name' => t('Major map URL')),
      'degreeSearchURL' => array('name' => t('ASU Degree Search URL')),
      'program' => array('name' => t('Program: Undergrad or Graduate')),
      'cert' => array('name' => t('Certificate option: True or False')),
      'Reqdescr' => array('name' => t('Requirement description')),
      'AdmissionsDegRequirements' => array('name' => t('Admission requirements')),
      'AsuProgramFee' => array('name' => t('Additional program fee')),
      'AsuLangReqFlag' => array('name' => t('Second language requirement')),
      'MinMathReq' => array('name' => t('Minimum math requirement')),
      'careerData' => array('name' => t('Example Careers')),
      'subPlnMajorMaps.SubPlnMajorMapUrl' => array('name' => t('Subplan major map URL')),
      'subplan.code' => array('name' => t('Subplan code')),
      'subplan.name' => array('name' => t('Subplan name')),
      'majorMapDefaultYear' => array('name' => t('Major map year')),
      'subPlnMajorMaps.SubplnMajorMapSubplanCode' => array('name' => t('Subplan code for URL')),
      'subPlnMajorMaps.SubplnMajorMapSubplanName' => array('name' => t('Subplan name for URL')),
      'wueCampusConfirmed' => array('name' => t('WUE Confirmed')),
      'ad' => array('name' => t('Accelerated Degree')),
      //not quite working yet
      //'degreeIsNew' => array('name' => t('Degree New')),
    );
  }
}
