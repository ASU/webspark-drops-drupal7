<?php
/**
 * @file
 * Parses and maps ASU Directory Feed.
 */
class ASUDirectoryFeedParser extends FeedsParser {

  /**
   * Implementation of FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
		
		$batch = $fetcher_result;

    $eids   = $batch->getEids();
    $t_term = $batch->getT_term();
		
    $people = array();

    // When only one Employee ID was entered or when department code was entered, then, use $result = $batch->getRaw();	
    if ($eids == "") {

      $result = $batch->getRaw();

      /* Simple XML */
      $sx = NULL;
      $sx = new SimpleXMLElement($result);

      foreach ($sx->{'asu-directory-person'} as $person) {
        $p = array();
        $attributes = $person->attributes();
        $p['eid'] = (string) $attributes['eid'];
        $p['guid'] = $p['eid'];
        $p['url'] = 'https://webapp4.asu.edu/directory/person/' . $p['eid'];
        $p['t_term'] = $t_term;

        $children = $person->children();
        foreach ($children as $child) {
          $attributes = $child->attributes();
          $key = (string) $attributes['name'][0]; // Cast Simple XML object to string
          $p[$key] = (string) $child;
        }

        /* Simple XML for Bio */
        $sx = new SimpleXMLElement("https://webapp4.asu.edu/directory-ws/services/public/profile/v1.0?eid=" . $p['eid'], NULL, TRUE );
        foreach ($sx->{'asu-directory-profile'} as $profile) {
          $attributes = $profile->attributes();
          $children = $profile->children();
          foreach ($children as $child) {
            $attributes = $child->attributes();
            $key = (string) $attributes['name'][0];
            $p[$key] = (string) $child;
          }
        }

        /* Profile image */
        $p['imageurl'] = "https://webapp4.asu.edu/directory-ws/services/public/image/v1.0?eid=" . $p['eid'];

        $people[] = $p;
      } // End of foreach ($sx->{'asu-directory-person'} as $person)

    } // End of if($eids =="")


    // When multiple Employee IDs are entered
    else {

      $eid_array = explode( ",", $eids);

      foreach ($eid_array as $each_eid) {
        $each_eid = trim($each_eid);

        // Create SimpleXML object for each person
        $sx = NULL;
        $sx = new SimpleXMLElement("https://webapp4.asu.edu/directory-ws/services/public/person/v1.0?eid=" . $each_eid, NULL, TRUE );

        foreach ($sx->{'asu-directory-person'} as $person) {
          $p = array();
          $attributes = $person->attributes();
          $p['eid'] = (string) $attributes['eid'];
          $p['guid'] = $p['eid'];
          $p['url'] = 'https://webapp4.asu.edu/directory/person/' . $p['eid'];
          $p['t_term'] = $t_term;

          $children = $person->children();
          foreach ($children as $child) {
            $attributes = $child->attributes();
            $key = (string) $attributes['name'][0];
            $p[$key] = (string) $child;
          }

          /* Simple XML for Bio */
          $sx = new SimpleXMLElement("https://webapp4.asu.edu/directory-ws/services/public/profile/v1.0?eid=" . $p['eid'], NULL, TRUE );
          foreach ($sx->{'asu-directory-profile'} as $profile) {
            $attributes = $profile->attributes();
            $children = $profile->children();
            foreach ($children as $child) {
              $attributes = $child->attributes();
              $key = (string) $attributes['name'][0];
              $p[$key] = (string) $child;
            }
          }

          /* Profile image */
          $p['imageurl'] = "https://webapp4.asu.edu/directory-ws/services/public/image/v1.0?eid=" . $p['eid'];

          $people[] = $p;

        } // End of foreach ($sx->{'asu-directory-person'} as $person)

      } // End of foreach($eid_array as $each_eid)

    } // End of else

    $parsed_data = $people;
		
		return new FeedsParserResult($parsed_data);

  } // End of parse


  /**
   * Return mapping sources.
   */
  public function getMappingSources() {
    return array(
      'guid' => array('name' => t('GUID - Unique ID for the ASU Directory person')),
      'url' => array('name' => t('URL to directory page')),
      'eid' => array('name' => t('Employee ID')),
      'displayname' => array('name' => t('Display name')),
      'firstname' => array('name' => t('First name')),
      'lastname' => array('name' => t('Last name')),
      'asuriteid' => array('name' => t('ASURITE ID')),
      'primaryaffiliation' => array('name' => t('Primary affiliation')),
      'affiliationdescription' => array('name' => t('Affiliation description')),
      'company' => array('name' => t('Company')),
      'title' => array('name' => t('Title')),
      'department' => array('name' => t('Department')),
      'departmentcode' => array('name' => t('Department code')),
      'email' => array('name' => t('Email')),
      'phone' => array('name' => t('Phone')),
      'biography' => array('name' => t('Bio')),
      'researchinterest' => array('name' => t('Research interest')),
      'imageurl' => array('name' => t('Profile image')),
      't_term' => array('name' => t('Taxonomy term')),
    );
  } // End of getMappingSources

} // End of class ASUDirectoryFeedParser class
