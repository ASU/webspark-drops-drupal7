<?php

/**
 * There are four essential components to set up in your constructor:
 *  $this->source - An instance of a class derived from MigrateSource, this
 *    will feed data to the migration.
 *  $this->destination - An instance of a class derived from MigrateDestination,
 *    this will receive data that originated from the source and has been mapped
 *    by the Migration class, and create Drupal objects.
 *  $this->map - An instance of a class derived from MigrateMap, this will keep
 *    track of which source items have been imported and what destination objects
 *    they map to.
 *  Mappings - Use $this->addFieldMapping to tell the Migration class what source
 *    fields correspond to what destination fields, and additional information
 *    associated with the mappings.
 */
class MigrateIsearchProfileMigration extends Migration {

  private static $expertiseAreasCache = array();
  private static $expertiseVocabulary = NULL;

  private static $titleRanksCache = array();
  private static $titleRanksVocabulary = NULL;

  private $profilePhotoDirectory = NULL;

  public $forceUpdate = FALSE;

  public static $currentFeedUrl = NULL;

  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Migrates iSearch profiles by department.');

    // Create a map object for tracking the relationships between source rows
    // and their resulting Drupal objects. Usually, you'll use the MigrateSQLMap
    // class, which uses database tables for tracking. Pass the machine name
    // of this migration to use in generating map and message tables.
    // And, pass schema definitions for the primary keys of the source and
    // destination - we need to be explicit for our source, but the destination
    // class knows its schema already

    // Define the source schema
    $this->map = new MigrateSQLMap($this->machineName, array(
      'eid' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
        'description' => 'Employee ID',
      ),
    ),
      MigrateDestinationNode::getKeySchema()
    );

    // query and store the title ranks vocabulary id
    if (is_null(self::$titleRanksVocabulary)) {
      self::$titleRanksVocabulary = taxonomy_vocabulary_machine_name_load('isearch_ranks');
      $ranks_term_tree = taxonomy_get_tree(self::$titleRanksVocabulary->vid, 0, NULL, TRUE);

      foreach ($ranks_term_tree as $term) {
        $termKey = $term->field_isearch_rank_tid[LANGUAGE_NONE][0]['value'];
        self::$titleRanksCache[$termKey] = $term;
      }
    }

    // query and store the expertise areas vocabulary id
    if (is_null(self::$expertiseVocabulary)) {
      self::$expertiseVocabulary = taxonomy_vocabulary_machine_name_load('isearch_expertise');
      $expertise_term_tree = taxonomy_get_tree(self::$expertiseVocabulary->vid, 0, NULL, TRUE);

      foreach ($expertise_term_tree as $term) {
        $termKey = $term->field_isearch_expertise_tid[LANGUAGE_NONE][0]['value'];
        self::$expertiseAreasCache[$termKey] = $term;
      }
    }

    // Create a MigrateSource object, which manages retrieving the input data.
    $source = ASU_ISEARCH_MASTER_FILE_ENDPOINT;

    $master = asu_isearch_get_master_source();

    // check the local source -- if empty, fill it
    if (empty($master)) {
      $tracker = asu_isearch_get_dept_tracker();
      _asu_isearch_build_migrate_master($tracker);
    }

    $this->setMigrateSource($source);
    $this->destination = new MigrateDestinationNode('asu_isearch_profile');

    // Setup profile photo directory
    $this->setupProfilePhotoDirectory();
    $this->addFieldMapping('status', 'status');
    $this->addFieldMapping('field_isearch_displayname', 'displayName');
    $this->addFieldMapping('field_isearch_firstname', 'firstName');
    $this->addFieldMapping('field_isearch_lastname', 'lastName');
    $this->addFieldMapping('field_isearch_employment_title', 'primaryTitle');
    $this->addFieldMapping('field_isearch_eid', 'eid');
    $this->addFieldMapping('field_isearch_asurite_id', 'asuriteId');
    $this->addFieldMapping('field_isearch_email', 'emailAddress');
    $this->addFieldMapping('field_isearch_phone', 'phone');
    $this->addFieldMapping('field_isearch_fax', 'fax');
    $this->addFieldMapping('field_isearch_campus_building', 'addressLine1');
    $this->addFieldMapping('field_isearch_campus_room', 'addressLine2');
    $this->addFieldMapping('field_isearch_addr_line_three', 'addressLine3');
    $this->addFieldMapping('field_isearch_city', 'city');
    $this->addFieldMapping('field_isearch_photo_preference', 'photoPreference');
    $this->addFieldMapping('field_isearch_photo_permission', 'photoPermission');
    $this->addFieldMapping('field_isearch_social_twitter', 'twitter');
    $this->addFieldMapping('field_isearch_social_facebook', 'facebook');
    $this->addFieldMapping('field_isearch_social_linkedin', 'linkedin');
    $this->addFieldMapping('field_isearch_social_googleplus', 'googlePlus');
    $this->addFieldMapping('field_isearch_social_personalweb', 'website');
    $this->addFieldMapping('field_isearch_short_bio', 'shortBio');
    $this->addFieldMapping('field_isearch_bio', 'bio');
    $this->addFieldMapping('field_isearch_education', 'education');
    $this->addFieldMapping('field_isearch_cv_url', 'cvUrl');
    $this->addFieldMapping('field_isearch_google_scholar', 'googleScholar');
    $this->addFieldMapping('field_isearch_rsrch_website', 'researchWebsite');
    $this->addFieldMapping('field_isearch_rsrch_interests', 'researchInterests');
    $this->addFieldMapping('field_isearch_rsrch_group', 'researchGroup');
    $this->addFieldMapping('field_isearch_rsrch_activity', 'researchActivity');
    $this->addFieldMapping('field_isearch_rsrch_publications', 'publications');
    $this->addFieldMapping('field_isearch_tch_website', 'teachingWebsite');
    $this->addFieldMapping('field_isearch_tch_courses', 'courses');
    $this->addFieldMapping('field_isearch_tch_presentations', 'presentations');
    $this->addFieldMapping('field_isearch_honors_awards', 'honorsAwards');
    $this->addFieldMapping('field_isearch_editorships', 'editorships');
    $this->addFieldMapping('field_isearch_prof_associations', 'professionalAssociations');
    $this->addFieldMapping('field_isearch_graduate_faculties', 'gradFaculties');
    $this->addFieldMapping('field_isearch_work_history', 'workHistory');
    $this->addFieldMapping('field_isearch_service', 'service');
    $this->addFieldMapping('field_consulting', 'consulting');
    $this->addFieldMapping('field_board', 'board');
    $this->addFieldMapping('field_industry_positions', 'industryPositions');
    $this->addFieldMapping('field_pro_bono', 'probono');
    $this->addFieldMapping('field_executive_courses', 'executiveCourses');

    $this->addFieldMapping('field_executive_courses:format', 'htmlFormat');
    $this->addFieldMapping('field_consulting:format', 'htmlFormat');
    $this->addFieldMapping('field_board:format', 'htmlFormat');
    $this->addFieldMapping('field_industry_positions:format', 'htmlFormat');
    $this->addFieldMapping('field_pro_bono:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_bio:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_editorships:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_education:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_honors_awards:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_rsrch_activity:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_rsrch_group:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_rsrch_interests:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_rsrch_publications:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_service:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_short_bio:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_tch_presentations:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_prof_associations:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_work_history:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_graduate_faculties:format', 'htmlFormat');
    $this->addFieldMapping('field_isearch_tch_courses:format', 'coursesFormat');
    $this->addFieldMapping('field_isearch_hash', 'migrateHash');
  }

  public function setMigrateSource($urls) {
    $this->source = new MigrateSourceJSON($urls, 'eid', $this->getSourceFields(), array('reader_class' => 'IsearchProfileJSONReader'));
  }

  public function processImport(array $options = array()) {
    $this->forceUpdate = (isset($options['force']) && $options['force']);
    parent::processImport($options);
  }

  public function getSourceFields() {
    $source_fields = array(
      'eid' => 'Profile identifier',
      'displayName' => 'The profile display name',
      'firstName' => 'First name',
      'lastName' => 'Last name',
      'emailAddress' => 'Email address',
      'asuriteId' => 'ASURITE ID',
      'primaryTitle' => 'Primary title',
      'phone' => 'Phone',
      'fax' => 'Fax',
      'addressLine1' => 'Building',
      'addressLine2' => 'Room',
      'addressLine3' => 'Address Line 3',
      'city' => 'City',
      'primaryJobCampus' => 'Primary job campus',
      'shortBio' => 'Short bio',
      'bio' => 'Biography',
      'education' => 'Education',
      'cvUrl' => 'CV url',
      'website' => 'Personal website',
      'twitter' => 'Profile twitter link',
      'facebook' => 'Profile facebook link',
      'linkedin' => 'Profile linkedin link',
      'googlePlus' => 'Profile googleplus link',
      'googleScholar' => 'Profile googlescholar link',
      'photoPreference' => 'Photo preference',
      'photoPermission' => 'Photo permission',
      'researchInterests' => 'Research interests',
      'researchGroup' => 'Research group',
      'researchActivity' => 'Research activity',
      'publications' => 'Publications',
      'researchWebsite' => 'Research website',
      'courses' => 'Courses',
      'presentations' => 'Presentations',
      'teachingWebsite' => 'Teaching website',
      'honorsAwards' => 'Honors awards',
      'editorships' => 'Editorships',
      'professionalAssociations' => 'Professional associations',
      'gradFaculties' => 'Graduate Faculties',
      'workHistory' => 'Work history',
      'service' => 'Service',
      'primaryAffiliation' => 'PrimaryAffiliation',
      'departmentIds' => 'DepartmentIds',
      'departments' => 'Departments',
      'vpAreas' => 'VP areas',
      'campuses' => 'Campuses',
      'mailCodes' => 'Mail codes',
      'employeeTypes' => 'Employee types',
      'personalWebsite' => 'Personal website',
      'consulting' => 'Consulting',
      'board' => 'Board',
      'industryPositions' => 'Industry Positions',
      'probono' => 'Pro Bono',
      'executiveCourses' => 'Executive Education Courses',
      'htmlFormat' => 'Placeholder source field used for setting HTML format on text fields',
      'migrateHash' => 'Migrate hash used to determine if the entity should be updated or skipped on import',
    );

    return $source_fields;
  }

  private function isDevMode() {
    return variable_get('asu_isearch_devmode', FALSE);
  }

  private function setupProfilePhotoDirectory() {
    // Setup other variables we need
    $this->profilePhotoDirectory = file_build_uri('asu_isearch_photos');

    if (!file_exists($this->profilePhotoDirectory)) {
      drupal_mkdir($this->profilePhotoDirectory);
    }
  }

  // This method gives us an opportunity to modify the raw source data
  // to create additional fields that will get mapped possibly
  public function prepareRow($row) {

    // placeholder to set isearch_html as body format
    $row->htmlFormat = 'isearch_html';

    // keep courses field as full_html
    $row->coursesFormat = 'full_html';

    if (isset($row->phone)) {
      // format phone number
      $row->phone = asu_isearch_format_phone($row->phone);
    }

    // We have enough information to generate a hash from
    $row_hash = (array) $row;
    sort($row_hash);
    $row_hash = md5(serialize($row_hash));

    $row->migrateHash = $row_hash;

    // lets see if we need to update this record at all
    $query = new EntityFieldQuery();
    $result = $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'asu_isearch_profile')
      ->fieldCondition('field_isearch_eid', 'value', $row->eid)
      ->fieldCondition('field_isearch_hash', 'value', $row_hash)
      ->execute();

    if ($this->forceUpdate === FALSE && isset($result['node'])) {
      // Fetch and store profile photo

      $entity = node_load(current($result['node'])->nid);
      $this->fetchProfilePhoto($entity, $row);

      return FALSE;
    }

    // prepare affiliations array
    $row->affiliations_info = array();
    $additional_titles = array();

    $pull_weights = variable_get('isearch_pull_isearch_weights', FALSE);

    if (isset($row->deptids)) {
      foreach ($row->deptids as $index => $department_id) {
        $affiliation = new stdclass();
        $affiliation->id = $department_id;
        $affiliation->deptId = $department_id;
        $affiliation->deptName = $row->departments[$index];


        $titlesource = 'workingTitle';

        if (isset($row->titleSource)) {
          $titlesource = $row->titleSource[$index];
        }

        $custom_title = $row->titles[$index];

        if ($titlesource == 'titles') {
          $affiliation->title = $custom_title;
        }
        else {
          if (isset($row->workingTitle) && !empty($row->workingTitle)) {
            $affiliation->title = $row->workingTitle;
          }
          else {
            if (isset($row->primaryTitle) && !empty($row->primaryTitle)) {
              $affiliation->title = $row->primaryTitle;
            }
            else {

              // it's possible that courtesy affiliates might not have any titlesource value,
              // but have a titles array value, so we use the custom title as a final fallback
              $affiliation->title = $custom_title;
            }
          }
        }

        $affiliation->vpArea = $row->vpAreas[$index];
        $affiliation->campus = $row->primaryJobCampus;
        $affiliation->mailCode = $row->primaryMailCode;
        $affiliation->employeeType = $row->employeeTypes[$index];
        $affiliation->employeeTypeKey = preg_replace('/[^a-zA-Z]/', '_', trim($row->employeeTypes[$index]));
        $affiliation->isManager = $row->managers[$index];
        $affiliation->isRankTenure = $row->departmentTitleRanksTenure[$index];
        $affiliation->ranksTid = $row->departmentTitleRanksTids[$index];
        $affiliation->ranksWeight = $row->departmentTitleRanksWeight[$index];
        $affiliation->affilHide = $row->affilHide[$index];
        $affiliation->affilWeight = $row->affilWeight[$index];

        // Only add the employeeweight to the local weight field if it has been configured
        // to do so, it has been set in iSearch, it is less than rank weight,
        // and it less than the 999 placeholder
        if ($pull_weights && !empty($row->employeeWeight) && is_numeric($row->employeeWeight[$index])) {

          $weight = $affiliation->ranksWeight;
          $eweight = intval($row->employeeWeight[$index]);

          if ((!is_numeric($weight) || $eweight < intval($weight)) && $eweight < 999) {
            $affiliation->employeeWeight = $eweight;
          }
        }

        $affiliation->isPrimary = ($row->departments[$index] == $row->primaryiSearchDepartmentAffiliation);

        $row->affiliations_info[$affiliation->id] = $affiliation;

        // store additional titles into the additional titles array in case shortBio field is empty
        // we don't want to include it if it's the primary title
        if (!$affiliation->isPrimary && $affiliation->title != $row->primaryTitle) {
          $additional_titles[] = $affiliation->title;
        }
      }
    }

    preg_match('/\/([0-9]+)?$/', self::$currentFeedUrl, $matches);
    $row->localPrimaryAffiliation = $matches[1];

    // prepare expertise areas array
    $row->expertise = array();

    if (isset($row->expertiseAreaTids)) {
      foreach ($row->expertiseAreaTids as $index => $expertise_key) {
        $expertiseArea = new stdclass();
        $expertiseArea->id = $expertise_key;
        $expertiseArea->name = $row->expertiseAreas[$index];

        $row->expertise[$expertiseArea->id] = $expertiseArea;
      }
    }

    // prepare rank title array
    $row->titleranks = array();

    if (isset($row->departmentTitleRanksTids)) {
      foreach ($row->departmentTitleRanksTids as $index => $rank_key) {

        $name = $row->departmentTitleRanks[$index];

        if (!empty($rank_key) && is_numeric($rank_key) && $name != NULL) {
          $titleRank = new stdclass();
          $titleRank->name = $row->departmentTitleRanks[$index];
          $titleRank->id = $rank_key;
          $titleRank->tid = $row->departmentTitleRanksTids[$index];
          $titleRank->weight = $row->departmentTitleRanksWeight[$index];
          $titleRank->tenure = $row->departmentTitleRanksTenure[$index];
          $row->titleranks[$titleRank->id] = $titleRank;
        }
      }
    }
  }

  // This will get called just before the destination entity is saved
  public function prepare($entity, stdClass $row) {

    // If this is an existing entity, then we need to re-associate the affiliation
    // field collections, since they are not explicitly mapped and loaded on the
    // migration entity. See https://www.drupal.org/project/field_collection/issues/2183961
    if (isset($entity->nid)) {
      // load the original node object
      $node = node_load($entity->nid);

      // add original field collection data to our current node object
      $entity->field_isearch_affiliations = $node->field_isearch_affiliations;
      $entity->field_isearch_video = $node->field_isearch_video;

      module_invoke_all('asu_isearch_prepare_migration', $entity, $node, $row);
    }

    // set the title as the displayname
    $entity->title = $row->displayName;

    // Set Student Information.
    $solr_record = (array) $row;
    $student_info = NULL;

    if (isset($solr_record['careers']) && is_array($solr_record['careers'])) {

      $student_info = '';

      foreach ($solr_record['careers'] as $key => $career) {
        $student_info .= check_plain($career) . '<br>';

        if (isset($solr_record['majors']) && is_array($solr_record['majors']) && isset($solr_record['majors'][$key])) {
          $student_info .= check_plain($solr_record['majors'][$key]) . '<br>';
        }

        if (isset($solr_record['programs']) && is_array($solr_record['programs']) && isset($solr_record['programs'][$key])) {
          $student_info .= check_plain($solr_record['programs'][$key]) . '<br><br>';
        }
      }
    }

    if ($student_info != NULL) {
      $entity->field_isearch_student_info[LANGUAGE_NONE][0]['format'] = 'full_html';
      $entity->field_isearch_student_info[LANGUAGE_NONE][0]['value'] = '<div class="is-profile-student-info">' . $student_info . '</div>';
    }

    // Setup expertise taxonomy terms
    $this->setupExpertiseAreas($entity, $row);

    // Setup title rank terms
    $this->setupTitleRanks($entity, $row);
  }

  // This will get called after the destination entity has been created,
  // giving access to the entity id to perform other operations
  public function complete($entity, stdClass $row) {

    // set up the video Urls field collections
    $this->setupVideos($entity, $row);

    // Setup affiliations
    $this->setupAffiliations($entity, $row);

    // Fetch and store profile photo
    $this->fetchProfilePhoto($entity, $row);
  }

  //run after migration
  public function postImport() {
    parent::postImport();

    $num = $this->total_successes;

    // make sure that we're always removing from the list. we don't want to
    // stagnate if records keep getting skipped or ignored
    if ($num < ASU_ISEARCH_MASTER_IMPORT_MINIMUM) {
      $num = ASU_ISEARCH_MASTER_IMPORT_MINIMUM;
    }

    // get the master source, and remove the records which were successfully
    // processed
    $themaster = asu_isearch_get_master_source();
    $themaster = array_slice($themaster, $num);
    _asu_isearch_refresh_source($themaster);

    //watchdog log the result
    watchdog('asu_isearch', "Successfully processed '[@num]' nodes.", array('@num' => $this->total_successes), WATCHDOG_INFO);
  }

  // queues up the the process to fetch the profile photo for a given
  // profile node
  private function fetchProfilePhoto($entity, stdClass $row) {

    if ($row->photoPreference != 'none') {
      $eid = $row->eid;

      $destination = $this->profilePhotoDirectory . "/{$eid}.jpg";
      $photo_url = ASU_ISEARCH_DIRECTORY_PHOTO_ENDPOINT . $eid;

      $data = array(
        'destination' => $destination,
        'photo_url' => $photo_url,
        'entity' => $entity->nid,
      );

      $queue = DrupalQueue::get('isearch_fetch_profile_photo');

      if ($queue->numberOfItems() < ASU_ISEARCH_QUEUE_SIZE_LIMIT) {
        $queue->createItem($data);
      }
    }
  }

  private function setupExpertiseAreas($entity, stdClass $row) {

    // keeps track of existing expertise values
    $existing_expertise = array();
    //watchdog('migrate_debug','<pre>'.print_r(self::$expertiseAreasCache,TRUE).'</pre>');


    // Loop through the expertise areas we received from $row and add if necessary
    foreach ($row->expertise as $expertise_key => $item) {
      // if this value already exists for this entity, continue (no need to create/update)
      if (isset($existing_expertise[$expertise_key])) {
        continue;
      }

      // this wasn't an existing expertise, but we already are aware of the term
      // add it to existing_expertise and continue
      if (isset(self::$expertiseAreasCache[$expertise_key]) && is_object(self::$expertiseAreasCache[$expertise_key])) {
        $existing_expertise[$expertise_key] = self::$expertiseAreasCache[$expertise_key]->tid;
        if ($item->name != self::$expertiseAreasCache[$expertise_key]->name) {
          self::$expertiseAreasCache[$expertise_key]->name = $item->name;
          taxonomy_term_save(self::$expertiseAreasCache[$expertise_key]);
        }
        continue;
      }

      $term = new stdclass();
      $term->vid = self::$expertiseVocabulary->vid;
      $term->field_isearch_expertise_tid[LANGUAGE_NONE][0] = array('value' => $expertise_key);

      // We set the name property here in case the label was changed on feed
      $term->name = $item->name;
      taxonomy_term_save($term);

      // add to list of expertise we will save on entity
      $existing_expertise[$expertise_key] = $term->tid;

      // store these values in our cache
      self::$expertiseAreasCache[$expertise_key] = $term->tid;
    }

    $expertise_areas = array();
    foreach ($existing_expertise as $term_id) {

      if ($term_id !== NULL) {
        $expertise_areas[] = array('tid' => $term_id);
      }
    }

    $entity->field_isearch_expertise_areas[LANGUAGE_NONE] = $expertise_areas;
  }

  private function setupTitleRanks($entity, stdClass $row) {

    // keeps track of existing expertise values
    $existing_ranks = array();

    // Loop through the expertise areas we received from $row and add if necessary
    foreach ($row->titleranks as $rank_key => $item) {
      // if this value already exists for this entity, continue (no need to create/update)
      if (isset($existing_ranks[$rank_key])) {
        continue;
      }

      // this wasn't an existing expertise, but we already are aware of the term
      // add it to existing_ranks and continue
      if (isset(self::$titleRanksCache[$rank_key])) {
        $existing_ranks[$rank_key] = self::$titleRanksCache[$rank_key]->tid;

        // do we need to update the name of this existing term?
        if ($item->name != self::$titleRanksCache[$rank_key]->name) {
          self::$titleRanksCache[$rank_key]->name = $item->name;
          taxonomy_term_save(self::$titleRanksCache[$rank_key]);
        }
        continue;
      }

      // ensure we don't have a blank term name
      if (trim($item->name) == '') {
        continue;
      }

      $term = new stdclass();
      $term->vid = self::$titleRanksVocabulary->vid;
      $term->field_isearch_rank_tid[LANGUAGE_NONE][0]['value'] = intval($item->tid);
      $term->field_isearch_rank_weight[LANGUAGE_NONE][0]['value'] = intval($item->weight);
      $term->field_isearch_rank_tenure[LANGUAGE_NONE][0]['value'] = intval($item->tenure) ? 1 : 0;

      // We set the name property here in case the label was changed on feed
      $term->name = $item->name;
      taxonomy_term_save($term);

      // add to list of ranks we will save on entity
      $existing_ranks[$rank_key] = $term->tid;

      // store these values in our cache
      self::$titleRanksCache[$rank_key] = $term;
    }

    $row->existing_ranks = $existing_ranks;
  }

  /***
   * Since the video data from iSearch is broken up into 2 multi-valued Solr
   * fields, this maps the Solr fields to the Video embed field of the profile
   *
   * @param $entity
   * @param \stdClass $row
   */
  private function setupVideos($entity, stdClass $row) {

    $videos = array();
    $titles = array();
    $update_vids = array();
    $changed = FALSE;

    if (isset($row->videoUrls)) {
      $videos = $row->videoUrls;
      $titles = $row->videoTitles;
    }

    // Check existing video field collections, and delete if needed
    if (!empty($entity->field_isearch_video)) {

      $evids = $entity->field_isearch_video[LANGUAGE_NONE];

      // loop through existing affiliations and see if we need to delete or update them
      foreach ($evids as $index => $item) {

        // if the affil failed to load, unset it, delete it, and continue to next
        $vidurl = $item['video_url'];

        // If existing video is not found on Solr profile, delete it
        if (!in_array($vidurl, $videos)) {
          unset($entity->field_isearch_video[LANGUAGE_NONE][$index]);
          $changed = TRUE;
        }
        else {
          $update_vids[$vidurl] = $index;
        }
      }
    }

    // Add or update video field collections
    if (!empty($videos)) {
      foreach ($videos as $i => $v) {
        if (isset($update_vids[$v])) {
          // update an existing affiliation
          $index = $update_vids[$v];
          $entity->field_isearch_video[LANGUAGE_NONE][$index]['description'] = $titles[$i];
        }
        else {
          $next = count($entity->field_isearch_video[LANGUAGE_NONE]);
          $entity->field_isearch_video[LANGUAGE_NONE][$next]['video_url'] = $v;
          $entity->field_isearch_video[LANGUAGE_NONE][$next]['description'] = $titles[$i];
        }

        $changed = TRUE;
      }
    }

    if ($changed) { node_save($entity); }
  }

  private function setupAffiliations($entity, stdClass $row) {
    $update_affiliations = array();
    $pull_weights = variable_get('isearch_pull_isearch_weights', FALSE);
    $affils = array();

    if (isset($entity->field_isearch_affiliations[LANGUAGE_NONE])) {
      $affils = $entity->field_isearch_affiliations[LANGUAGE_NONE];
    }

    // determine if we need to update or delete existing affiliations
    if (!empty($affils)) {

      // loop through existing affiliations and see if we need to delete or update them
      foreach ($affils as $index => $item) {

        $affiliation = field_collection_item_load($item['value']);

        // if the affil failed to load, unset it, delete it, and continue to next
        if (empty($affiliation)) {

          unset($entity->field_isearch_affiliations[LANGUAGE_NONE][$index]);
          entity_delete('field_collection_item', $item['value']);

          // might have orphaned reference, so we'll delete it from affiliations table
          $deleted = db_delete('field_data_field_isearch_affiliations')
            ->condition('field_isearch_affiliations_value', $item['value'])
            ->execute();

          watchdog('asu_isearch', "Removed @num orphaned iSearch affiliation(s).", array('@num' => $deleted));
          continue;

        } else {

          $affiliation_key = $affiliation->field_isearch_affil_dept_id[LANGUAGE_NONE][0]['value'];

          if (!isset($row->affiliations_info[$affiliation_key])) {
            entity_delete('field_collection_item', $item['value']);
          }
          else {
            $update_affiliations[$affiliation_key] = $affiliation;
          }
        }
      }
    }

    // create/update new affiliations

    foreach ($row->affiliations_info as $affiliation_key => $item) {
      if (isset($update_affiliations[$affiliation_key])) {
        // update an existing affiliation
        $affiliation = $update_affiliations[$affiliation_key];
      }
      else {
        // this affiliation does not exist, create it
        $affiliation = entity_create('field_collection_item', array('field_name' => 'field_isearch_affiliations'));
        $affiliation->setHostEntity('node', $entity);
      }

      // store the affiliation title
      $affiliation_title = trim($item->title);

      // if this is a tenure rank affiliation, and the affiliation title
      // was left blank, set it to the rank title
      if ($affiliation_title == '' && $item->ranksTid) {
        $rank = taxonomy_term_load($row->existing_ranks[$item->ranksTid]);
        $affiliation_title = $rank->name;
      }

      $affiliation->field_isearch_affil_dept_id[LANGUAGE_NONE][0]['value'] = $item->deptId;
      $affiliation->field_isearch_affil_dept_name[LANGUAGE_NONE][0]['value'] = $item->deptName;
      $affiliation->field_isearch_affil_title[LANGUAGE_NONE][0]['value'] = $affiliation_title;
      $affiliation->field_isearch_affil_campus[LANGUAGE_NONE][0]['value'] = $item->campus;
      $affiliation->field_isearch_affil_empl_type[LANGUAGE_NONE][0]['value'] = $item->employeeType;
      $affiliation->field_isearch_affil_empl_key[LANGUAGE_NONE][0]['value'] = $item->employeeTypeKey;
      $affiliation->field_isearch_affil_mailcode[LANGUAGE_NONE][0]['value'] = $item->mailCode;
      $affiliation->field_isearch_affil_manager[LANGUAGE_NONE][0]['value'] = ($item->isManager) ? 1 : 0;
      $affiliation->field_isearch_affil_primary[LANGUAGE_NONE][0]['value'] = ($item->isPrimary) ? 1 : 0;
      $affiliation->field_isearch_affil_rank_tenure[LANGUAGE_NONE][0]['value'] = ($item->isRankTenure) ? 1 : 0;


      if (variable_get('isearch_import_affil_weights', FALSE)) {
        $affiliation->field_isearch_affil_weight[LANGUAGE_NONE][0]['value'] = $item->affilWeight;
      }

      if (variable_get('isearch_import_affil_hide', FALSE)) {
        $affiliation->field_isearch_affil_hide[LANGUAGE_NONE][0]['value'] = ($item->affilHide) ? 1 : 0;
      }

      if ($pull_weights && !empty($item->employeeWeight)) {
        $affiliation->field_isearch_affil_local_weight[LANGUAGE_NONE][0]['value'] = intval($item->employeeWeight);
      }

      if ($item->ranksTid && isset($row->existing_ranks[$item->ranksTid])) {
        $affiliation->field_isearch_affil_rank[LANGUAGE_NONE][0]['tid'] = $row->existing_ranks[$item->ranksTid];
      }

      $affiliation->save();

      if ($row->localPrimaryAffiliation == $item->deptId) {
        $entity->field_isearch_primary_aff[LANGUAGE_NONE][0]['target_id'] = $affiliation->item_id;
        node_save($entity);
      }
    }
  }
}

class IsearchProfileJSONReader extends MigrateJSONReader {
  /**
   * Implements MigrateJSONReader::next().
   */
  public function next() {
    // Do the default fetch.
    parent::next();

    // If we need to tweak
  }

  public function current() {
    $row = parent::current();
    MigrateIsearchProfileMigration::$currentFeedUrl = $this->url;

    if ($row->eid == 'debugging') {
      $row->rand = mktime();
    }

    return $row;
  }
}
