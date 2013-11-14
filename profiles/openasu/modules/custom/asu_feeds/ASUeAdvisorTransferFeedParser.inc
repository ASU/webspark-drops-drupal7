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

      // Campuses
      if (count($data['CampusStringArray'])) {
        foreach ($data['CampusStringArray'] as $campus_key => $value) {
          if ($value == 'ONLNE') {
            $value = 'Online';
          }
          if ($value == 'DTPHX') {
            $value = 'Downtown';
          }
          if ($value == 'POLY') {
            $value = 'Polytechnic';
          }
          $parsed_data[$key]['CampusStringArray'][$campus_key] = ucwords(strtolower($value));
        }
      }
      else {
        $parsed_data[$key]['CampusStringArray'] = array();
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

    } // End of foreach

    //error_log(print_r($parsed_data, true));
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
      'AsuCareerOpp' => array('name' => t('Career opporunities')),
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
    );
  }
}
