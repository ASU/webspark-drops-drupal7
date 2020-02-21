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

      // Parsing data from similar feed structures needing to return TRUE if values exist
      /*
      <member>
          <name>concurrentDegrees</name>
          <value>
              <array>
                  <data>
                      <value>
                          <struct>
                              <member>
                                  <name>subplanDeadlines</name>
                                  <value>
                                      <struct/>
                                  </value>
                              </member>
                          </struct>
                      </value>
                  </data>
              </array>
          </value>
      </member>
       */
      // Accelerated degrees
      // Concurrent degrees
      $toBeProcessed = array('accelerateDegrees', 'concurrentDegrees');
      foreach ($toBeProcessed as $field) {
        if (count($data[$field])) {
          $parsed_data[$key][$field] = 1;
        }
      }

      // Parsing data from similar <array> structures in the feed
      /*
       <member>
          <name>CollegeUrlJoint</name>
          <value>
              <array>
                  <data>
                      <value>http://clas.asu.edu/</value>
                  </data>
              </array>
          </value>
      </member>
      <member>
          <name>gradAdditionalRequirements</name>
          <value>
              <array>
                  <data/>
              </array>
          </value>
      </member>
       */
      // CollegeAcadOrgJoint
      // CollegeDescr100Joint
      // CollegeUrlJoint
      // DepartmentCodeJoint
      // DepartmentNameJoint
      // planCatDescr
      $toBeProcessed = array(
        'CollegeAcadOrgJoint',
        'CollegeDescr100Joint',
        'CollegeDescrlongJoint',
        'CollegeUrlJoint',
        'DepartmentCodeJoint',
        'DepartmentNameJoint',
        'planCatDescr',
        'psDeadlines',
        'secondMajors',
      );
      foreach ($toBeProcessed as $field) {
        if (count($data[$field])) {
          foreach ($data[$field] as $college_key => $value) {
            $parsed_data[$key][$field][$college_key] = $value;
          }
          $parsed_data[$key][$field] = array_values($parsed_data[$key][$field]);
        }
      }

      // Parsing data from similar <array> structures to return serialized array
      /*
      <member>
          <name>applyInfo</name>
          <value>
              <struct>
                  <member>
                      <name>AWC:REG:2204</name>
                      <value>2020 Summer:null:null:2020-05-18:2020-05-18</value>
                  </member>
                  <member>
                      <name>EAC:REG:2207</name>
                      <value>2020 Fall:null:null:2020-08-20:2020-08-20</value>
                  </member>
              </struct>
          </value>
      </member>
      <member>
          <name>graduateAllApplyDates</name>
          <value>
              <struct/>
          </value>
      </member>
      */
      // Apply Info
      // Graduate All Apply Dates
      // Plan Deadlines
      $toBeProcessed = array(
        'graduateAllApplyDates',
        'graduateApplyDates',
        'applyInfo',
        'planDeadlines',
        'subplanDeadlines',
      );
      foreach ($toBeProcessed as $field) {
        if (count($data[$field])) {
          $temp = array();
          foreach ($data[$field] as $code => $dates) {
            $temp[$code] = $dates;
          }
          $parsed_data[$key][$field] = serialize($temp);
        }
        else {
          $parsed_data[$key][$field] = array();
        }
      }

      // Check boolean value and then RETURN boolean based on that response (two levels)
      // New degrees (aka DegreeNew)
      if (count($data['DegreeNew'])) {
        $ndVal = $data['DegreeNew'];
        if ($ndVal == 1) {
          $parsed_data[$key]['DegreeNew'] = 1;
        }
      }

      // Custom one-off feed value processing
      ////////////////////////

      // Unique ID for the plan
      $parsed_data[$key]['guid'] = md5($parsed_data[$key]['AcadPlan']);

      // Whether or not the campus is part of WUE (boolean)
      if (count($data['CampusWueInfo'])) {
        foreach ($data['CampusWueInfo'] as $cwi) {
          if ($cwi['isCampusWue'] == 1) {
            $parsed_data[$key]['wueCampusConfirmed'] = 1;
          }
        }
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
              break;
          }
          if ($value == 'Online') {
            unset($parsed_data[$key]['CampusStringArray'][$campus_key]);
            array_push($parsed_data[$key]['CampusStringArray'], $value);
          } else {
            $parsed_data[$key]['CampusStringArray'][$campus_key] = $value;
          }
        }
        $parsed_data[$key]['CampusStringArray'] = array_values($parsed_data[$key]['CampusStringArray']);
      }

      // NOT IN USE ANYWHERE?
      // Additional admission information
      if (count($data['DescrlongExtns'])) {
        $parsed_data[$key]['additionalAdmissions'] = 1;
      }

      // Format careerData (JSON)
      if (count($data['careerData'])) {
        $parsed_data[$key]['careerData'] = json_encode($data['careerData']);
      }

      // Filter out MediaAmp videos for now - @TODO add MediaAMP support
      if (isset($data['Url4'])) {
        if (strpos($data['Url4'], 'mediaamp.org') !== FALSE) {
          $parsed_data[$key]['Url4'] = '';
          drupal_set_message($data['Descr'] . ' - A MediaAMP URL was removed because'
          . ' they are not currently supported in Webspark.', 'notice');
        } elseif (strpos($data['Url4'], 'player.vimeo.com') !== FALSE) {
          // Vimeo refactoring for player.vimeo.com URLs
          $data['Url4'] = preg_replace('|^(https?)://player.(vimeo.com)/video/(\d+)$|',
            '$1://$2/$3', $data['Url4']);
        }
        watchdog('asu_feeds2', print_r($data['Url4']));
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

      // Program (Undergrad or Graduate) and Cert (True or False). Useful when creating views.
      $parsed_data[$key]['program'] = $batch->getProgram();
      $parsed_data[$key]['cert'] = $cert;

      // Clean up marketing text input for display in degree pages.
      if (isset($data['marketText'])) {
//        $parsed_data[$key]['marketText'] = filter_xss(html_entity_decode($data['marketText']));
      }

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
      // if subplan.code == subPlnMajorMaps.SubplnMajorMapSubplanCode then replace code with name
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
    } // END FOREACH of all data
    // DEBUG
    //error_log(print_r($parsed_data, true));
    watchdog('A2P Debug', '<pre>'. print_r($parsed_data, true) .'</pre>');

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
      'accelerateDegrees' => array('name' => t('Accelerated Degrees')), // NEW - Replaces acceleratedDegree
      'AdmissionsDegRequirements' => array('name' => t('Admission requirements')),
      'applyInfo' => array('name' => t('Apply Information')), // NEW -- @TODO Needs processing
      'asuAcadpLrfText' => array('name' => t('AcadpLrfText')), // NEW
      'asuAcadpMrfText' => array('name' => t('AcadpMrfText')), // NEW
      'AsuAdmReqUrl' => array('name' => t('Admissions Req Url')), // NEW
      'AsuCareerOpp' => array('name' => t('Career opportunities')),
      'asuChooseSndMjrFlg' => array('name' => t('Choose Second Major Flg')), // NEW
      'AsuCritTrackUrl' => array('name' => t('Major map URL')),
      'AsuCustomText' => array('name' => t('Custom text')), // NEW
      'AsuDegSrchFlg' => array('name' => t('Degree search flag')), // NEW
      'AsuLangReqFlag' => array('name' => t('Second language requirement')),
      'AsuMailCode' => array('name' => t('ASU Mail Code')), // NEW
      'asuMathReqFlag' => array('name' => t('Math Req Flag')), // NEW
      'AsuNactvAppOvrd' => array('name' => t('AsuNactvAppOvrd')), // NEW
      'AsuOfficeLoc' => array('name' => t('Office location')), // NEW
      'AsuProgramFee' => array('name' => t('Additional program fee')),
      'CampusStringArray' => array('name' => t('Campus')),
      'careerData' => array('name' => t('Example careers')),
      'cert' => array('name' => t('Certificate option: True or False')), // Not in feed; Custom source value generated above
      'CatalogUrl' => array('name' => t('Catalog URL')), // NEW
      'ChangeMajor' => array('name' => t('Change major')), // NEW
      'CipCode' => array('name' => t('CIP Code')), // NEW
      'CollegeAcadOrg' => array('name' => t('College Academic Org')), // NEW
      'CollegeAcadOrgJoint' => array('name' => t('College Academic Org (joint)')), // NEW
      'CollegeDescr100' => array('name' => t('College name')),
      'CollegeDescr100Joint' => array('name' => t('College name (joint)')),
      'CollegeDescrlong' => array('name' => t('College Description long')), // NEW
      'CollegeDescrlongJoint' => array('name' => t('College Description long (joint)')), // NEW
      'CollegeUrl' => array('name' => t('College URL')),
      'CollegeUrlJoint' => array('name' => t('College URL (joint)')),
      'committeeId' => array('name' => t('Committee ID')), // NEW
      'concurrentDegrees' => array('name' => t('Concurrent Degrees')), // NEW - replaced concurrentDegree
      'concurrentDegreesMap' => array('name' => t('Concurrent Degrees map')), // NEW
      'CurriculumUrl' => array('name' => t('Curriculum URL'), 'description' => t('Online campus ONLY'),),
      'Degree' => array('name' => t('Degree'),'description' => t('BA / BFA / MFA / etc'),),
      'DegreeDescr' => array('name' => t('Degree description')),
      'DegreeDescrformal' => array('name' => t('Degree Description - formal')), // NEW
      'DegreeDescrlong' => array('name' => t('Degree Description - long')), // NEW
      'DegreeDescrshort' => array('name' => t('Degree Description - short')), // NEW
      'DegreeEducationLvl' => array('name' => t('Degree Education level')), // NEW
      'degreeMajorMap' => array('name' => t('Program Requirements')),
      'DegreeNew' => array('name' => t('New degree')), // NEW - replaces newDegree
      'DepartmentCode' => array('name' => t('Department code')),
      'DepartmentCodeJoint' => array('name' => t('Department code (joint)')),
      'DepartmentName' => array('name' => t('Department name')),
      'DepartmentNameJoint' => array('name' => t('Department name (joint)')),
      'Descr' => array('name' => t('Description')), // NEW
      'Descr100' => array('name' => t('Description (100)')),
      'Descr254' => array('name' => t('Description (254)')), // NEW
      'Descrlong' => array('name' => t('Description (long)')), // NEW
      'DescrlongExtn5' => array('name' => t('Description long (Extn5)')), // NEW
      'DescrlongExtns' => array('name' => t('Degree description (extended)')),
      'Descrshort' => array('name' => t('Description (short)')), // NEW
      'DiplomaDescr' => array('name' => t('Diploma description')),
      'DiplomaIndentInteger' => array('name' => t('Diploma Indent Integer')), // NEW
      'DiplomaPrintFl' => array('name' => t('Diploma Print Fl')), // NEW
      'EffStatus' => array('name' => t('Eff Status')), // NEW
      'EmailAddr' => array('name' => t('Email address')), // NEW
      'EvaluatePlan' => array('name' => t('EvaluatePlan')), // NEW
      'FirstTermValid' => array('name' => t('FirstTermValid')), // NEW
      'gradAdditionalRequirements' => array('name' => t('Grad Additional Requirements')), // NEW
      'graduateAllApplyDates' => array('name' => t('Graduate All Apply Dates'),'description' => t('All future available terms and their application dates - by campus.'),),
      'graduateApplyDates' => array('name' => t('Graduate Apply Dates')), // NEW
      'HegisCode' => array('name' => t('Hegis code')), // NEW
      'Institution' => array('name' => t('Institution')), // NEW
      'InternalDegree' => array('name' => t('Internal Degree')), // NEW
      'managedOnlineCampus' => array('name' => t('Managed Online campus')), // NEW
      'marketText' => array('name' => t('Marketing Text')), // NEW
      'MathIntensity' => array('name' => t('Math Intensity')), // NEW
      'MinMathReq' => array('name' => t('Minimum math requirement')),
      'Notes' => array('name' => t('Notes')), // NEW
      'Phone' => array('name' => t('Phone')), // NEW
      'planCatDescr' => array('name' => t('Plan category description')), // NEW
      'planDeadlines' => array('name' => t('Plan deadlines')), // NEW
      'PlanUrl' => array('name' => t('Plan URL')), // NEW
      'PlnReqtrmDflt' => array('name' => t('Plan Req trm Dflt')), // NEW
      'psDeadlines' => array('name' => t('PS deadlines')), // NEW
      'Reqdescr' => array('name' => t('Requirement description')),
      'secondMajors' => array('name' => t('Second majors')), // NEW
      'SMISUrl' => array('name' => t('SMIS Url')), // NEW
      'StudyField' => array('name' => t('Study Field')), // NEW
      'subplanDeadlines' => array('name' => t('Subplan deadlines')), // NEW
      'TranscriptLevel' => array('name' => t('Transcript Level')), // NEW
      'TrnscrDescr' => array('name' => t('Transcript Description')), // NEW
      'TrnscrIndentInteger' => array('name' => t('TrnscrIndentInteger')), // NEW
      'TrnscrPrintFl' => array('name' => t('TrnscrPrintFl')), // NEW
      'Url1' => array('name' => t('Url1')), // NEW
      'Url2' => array('name' => t('Url2')), // NEW
      'Url3' => array('name' => t('Url3')), // NEW
      'Url4' => array('name' => t('Url4')), // NEW

      /////////////////////////
      // Not in feed; Custom source value generated above
      /////////////////////////
      'degreeSearchURL' => array('name' => t('ASU Degree Search URL')),
      'program' => array('name' => t('Program: Undergrad or Graduate')),
      'subplan.code' => array('name' => t('Subplan code')),
      'subplan.name' => array('name' => t('Subplan name')),
      // 'SubPlnMajorMaps' => array('name' => t('Subplan Major Maps')),  // NEW - Not included, but parsed out and passed onto the feed below
      'subPlnMajorMaps.SubplnMajorMapSubplanCode' => array('name' => t('Subplan code for URL')),
      'subPlnMajorMaps.SubplnMajorMapSubplanName' => array('name' => t('Subplan name for URL')),
      'subPlnMajorMaps.SubPlnMajorMapUrl' => array('name' => t('Subplan major map URL')),
      // 'transferAgreementInfo' => array('name' => t('Transfer agreement information')), // NEW - Not included, but parsed out and passed onto the feed below
      'transferAgreementInfo.type' => array('name' => t('Transfer agreement type')),
      'transferAgreementInfo.year' => array('name' => t('Transfer agreement year')),
      'transferAgreementInfo.url' => array('name' => t('Transfer agreement URL')),
      'transferAgreementInfo.communityCollege' => array('name' => t('Transfer agreement community college')),
      //'CampusWueInfo' => array('name' => t('Campus WUE info')), // NEW - Not included, but parsed out and passed into the field below as a boolean.
      'wueCampusConfirmed' => array('name' => t('WUE Confirmed')),
    );
  }
}
