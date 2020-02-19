<?php
/**
 * @file
 * Parses and maps ASU eAdvisor feed.
 */

// Multigroup display in views: http://drupal.org/node/692186#comment-2563668

class ASUeAdvisorFeedParser extends FeedsParser {

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

      // Accelerated degrees
      if (count($data['accelerateDegrees'])) {
        $acceleratedDegree = array();
        $parsed_data[$key]['acceleratedDegree'] = 1;
      }

      // Concurrent degrees
      if (count($data['concurrentDegrees'])) {
        $concurrentDegree = array();
        $parsed_data[$key]['concurrentDegree'] = 1;
      }

      // New degrees
      if (count($data['DegreeNew'])) {
        $newDegree = array();
        $ndVal = $data['DegreeNew'];
        if ($ndVal == 1) {
          $parsed_data[$key]['newDegree'] = 1;
        }
      }

      // Whether or not the campus is part of WUE (boolean)
      if (count($data['CampusWueInfo'])) {
        $wueCampusConfirmed = array();
        foreach ($data['CampusWueInfo'] as $cwi) {
          if ($cwi['isCampusWue'] == 1) {
            $parsed_data[$key]['wueCampusConfirmed'] = 1;
          }
        }
      }

      // Additional admission information
      if (count($data['DescrlongExtns'])) {
        $additionalAdmissions = array();
        $parsed_data[$key]['additionalAdmissions'] = 1;
      }

      // Campuses
      if (count($data['CampusStringArray'])) {
        foreach ($data['CampusStringArray'] as $campus_key => $value) {
          switch (trim(strtoupper($value))) {
            case 'ONLNE':
              $value = 'Online';
              break;
            case 'DOWNTOWN':
            case 'DTPHX':
              $value = 'Downtown';
              break;
            case 'POLY':
              $value = 'Polytechnic';
              break;
            case 'TMPE':
            case 'TEMPE':
              $value = 'Tempe';
              break;
            case 'WEST':
              $value = 'West';
              break;
            case 'CALHC':
              $value = 'Lake Havasu City';
              break;
            case 'CAC':
              $value = 'ASU@Pinal';
              break;
            case 'EAC':
              $value = 'ASU@TheGilaValley';
              break;
            case 'TUCSN':
              $value = 'ASU@Tucson';
              break;
            case 'AWC':
              $value = 'ASU@Yuma';
              break;
            case 'TBIRD':
              $value = 'Thunderbird';
              break;
            case 'YAVAP':
              $value = 'ASU@Yavapai';
              break;
            case 'PIMA':
              $value = 'ASU@Pima';
              break;
            case 'COCHS':
              $value = 'ASU@Cochise';
              break;
            //Add case for missing campus from degree feed
            default:
              $value = $value;
              break;
          }
          if ($value == 'Online') {
            unset($parsed_data[$key]['CampusStringArray'][$campus_key]);
            array_push($parsed_data[$key]['CampusStringArray'],$value);
          } else {
            $parsed_data[$key]['CampusStringArray'][$campus_key] = $value;
          }
        }
        $parsed_data[$key]['CampusStringArray'] = array_values($parsed_data[$key]['CampusStringArray']);
      }

      // CollegeDescr100Joint
      if (count($data['CollegeDescr100Joint'])) {
        foreach ($data['CollegeDescr100Joint'] as $college_key => $value) {
            $parsed_data[$key]['CollegeDescr100Joint'][$college_key] = $value;
        }
        $parsed_data[$key]['CollegeDescr100Joint'] = array_values($parsed_data[$key]['CollegeDescr100Joint']);
      }

      // CollegeUrlJoint
      if (count($data['CollegeUrlJoint'])) {
        foreach ($data['CollegeUrlJoint'] as $college_key => $value) {
            $parsed_data[$key]['CollegeUrlJoint'][$college_key] = $value;
        }
        $parsed_data[$key]['CollegeUrlJoint'] = array_values($parsed_data[$key]['CollegeUrlJoint']);
      }

      // DepartmentCodeJoint
      if (count($data['DepartmentCodeJoint'])) {
        foreach ($data['DepartmentCodeJoint'] as $college_key => $value) {
            $parsed_data[$key]['DepartmentCodeJoint'][$college_key] = $value;
        }
        $parsed_data[$key]['DepartmentCodeJoint'] = array_values($parsed_data[$key]['DepartmentCodeJoint']);
      }

      // DepartmentNameJoint
      if (count($data['DepartmentNameJoint'])) {
        foreach ($data['DepartmentNameJoint'] as $college_key => $value) {
            $parsed_data[$key]['DepartmentNameJoint'][$college_key] = $value;
        }
        $parsed_data[$key]['DepartmentNameJoint'] = array_values($parsed_data[$key]['DepartmentNameJoint']);
      }

      // Format careerData
      if (count($data['careerData'])) {
        $parsed_data[$key]['careerData'] = json_encode($data['careerData']);
      }

      // Graduate All Apply Dates
      if (count($data['graduateAllApplyDates'])) {
        $gAAD = array();
        foreach ($data['graduateAllApplyDates'] as $code => $dates) {
          $gAAD[$code] = $dates;
        }
        $parsed_data[$key]['graduateAllApplyDates'] = serialize($gAAD);
      } else {
        $parsed_data[$key]['graduateAllApplyDates'] = array();
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
    watchdog('A2P Debug', '<pre>'. print_r($parsed_data, true) .'</pre>');
    //watchdog('keith $v', '<pre>' . print_r($v, true) . '</pre>');
    return new FeedsParserResult($parsed_data);
  }

  /**
   * Return mapping sources.
   */
  public function getMappingSources() {
    return array(
      'guid' => array('name' => t('GUID - Unique ID for the transfer agreement')),
      'keywords' => array('name' => t('Keywords')),
      'AcadPlan' => array('name' => t('Academic plan')),
      'AcadProg' => array('name' => t('Academic program')),
      'acceleratedDegree' => array('name' => t('Accelerated Degree')),
      'AdmissionsDegRequirements' => array('name' => t('Admission requirements')),
      'AsuCareerOpp' => array('name' => t('Career opportunities')),
      'AsuCritTrackUrl' => array('name' => t('Major map URL')),
      'AsuLangReqFlag' => array('name' => t('Second language requirement')),
      'AsuProgramFee' => array('name' => t('Additional program fee')),
      'CampusStringArray' => array('name' => t('Campus')),
      'careerData' => array('name' => t('Example Careers')),
      'cert' => array('name' => t('Certificate option: True or False')),
      'CollegeDescr100' => array('name' => t('College name')),
      'CollegeDescr100Joint' => array('name' => t('College name (joint)')),
      'CollegeUrl' => array('name' => t('College URL')),
      'CollegeUrlJoint' => array('name' => t('College URL (joint)')),
      'concurrentDegree' => array('name' => t('Concurrent Degree')),
      'CurriculumUrl' => array('name' => t('Curriculum URL'), 'description' => t('Online campus ONLY'),),
      'Degree' => array('name' => t('Degree'),'description' => t('BA / BFA / MFA / etc'),),
      'DegreeDescr' => array('name' => t('Degree description')),
      'degreeMajorMap' => array('name' => t('Program Requirements')),
      'degreeSearchURL' => array('name' => t('ASU Degree Search URL')),
      'DepartmentCode' => array('name' => t('Department code')),
      'DepartmentCodeJoint' => array('name' => t('Department code (joint)')),
      'DepartmentName' => array('name' => t('Department name')),
      'DepartmentNameJoint' => array('name' => t('Department name (joint)')),
      'Descr100' => array('name' => t('Description (100)')),
      'DescrlongExtns' => array('name' => t('Degree description (extended)')),
      'DiplomaDescr' => array('name' => t('Diploma description')),
      'graduateAllApplyDates' => array('name' => t('Graduate All Apply Dates'),'description' => t('All future available terms and their application dates - by campus.'),),
      'majorMapDefaultYear' => array('name' => t('Major map year')),
      'MinMathReq' => array('name' => t('Minimum math requirement')),
      'newDegree' => array('name' => t('New Degree')),
      'program' => array('name' => t('Program: Undergrad or Graduate')),
      'Reqdescr' => array('name' => t('Requirement description')),
      'subplan.code' => array('name' => t('Subplan code')),
      'subplan.name' => array('name' => t('Subplan name')),
      'subPlnMajorMaps.SubplnMajorMapSubplanCode' => array('name' => t('Subplan code for URL')),
      'subPlnMajorMaps.SubplnMajorMapSubplanName' => array('name' => t('Subplan name for URL')),
      'subPlnMajorMaps.SubPlnMajorMapUrl' => array('name' => t('Subplan major map URL')),
      'transferAgreementInfo.type' => array('name' => t('Transfer agreement type')),
      'transferAgreementInfo.year' => array('name' => t('Transfer agreement year')),
      'transferAgreementInfo.url' => array('name' => t('Transfer agreement URL')),
      'transferAgreementInfo.communityCollege' => array('name' => t('Transfer agreement community college')),
      'wueCampusConfirmed' => array('name' => t('WUE Confirmed')),
    );
  }
}
