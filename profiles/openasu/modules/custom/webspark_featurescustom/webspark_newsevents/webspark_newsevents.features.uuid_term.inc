<?php
/**
 * @file
 * webspark_newsevents.features.uuid_term.inc
 */

/**
 * Implements hook_uuid_features_default_terms().
 */
function webspark_newsevents_uuid_features_default_terms() {
  $terms = array();

  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Competiton</div><div class="field-item field-item-1">Contest</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '0097281e-a14b-4011-8513-95f4de88f9f5',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/competitoncontest',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Info session',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '0b8e7226-5341-46ab-a9bb-7f5474733473',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/info-session',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Workshops',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '0bef5e25-e63b-4861-a2e9-253344f255c9',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/workshops',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Concert',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '0ea6c02d-7afa-4453-9f4f-7089f28be40d',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/concert',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Education',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '13f7fa03-336e-4688-b9f4-a9a3b0be5eb0',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/education',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Lecture</div><div class="field-item field-item-1">Literature</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '141a6579-55ed-4171-8400-a40542c179a7',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/lectureliterature',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Lecture',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '1936eb60-cf25-4b86-8c38-ce4f70e46e86',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/lecture',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Health',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '19da184f-e8f1-4114-bfcf-5d24ca63243c',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/health',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Law',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '1c6eb26a-8310-4e0d-b40a-6a73c56d8e2c',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/law',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Staff',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '215247ce-9805-4530-ad58-0a5fc2105f14',
    'vocabulary_machine_name' => 'asu_events_audience',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-audience/staff',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Performance</div><div class="field-item field-item-1">Student Recital</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '288a5162-6a8f-4168-b0bc-c80e1788cc43',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/performancestudent-recital',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Latin</div><div class="field-item field-item-1">Lecture</div><div class="field-item field-item-2">Presentation</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '2a5ebb08-7d5c-4e65-ac80-823490cfdd88',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/latinlecturepresentation',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Performance</div><div class="field-item field-item-1">Play</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '2b20a1d3-2c3e-4513-b7ab-e5103e93e9e6',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/performanceplay',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Students',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '2b7fdbeb-9133-4da6-91b0-251f13f1bd1d',
    'vocabulary_machine_name' => 'asu_events_audience',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-audience/students',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Sustainability',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '2c3f6847-5b50-4fc5-adf5-8f5e29b38f76',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/sustainability',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Panel',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '2d00fb7a-22a3-472d-891e-70b74290c424',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/panel',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Sun Devil Athletics',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '3075ca82-7ea5-4aef-b021-89bd8f732c96',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/sun-devil-athletics',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Meeting',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '37ce367b-f7e7-4867-af7c-d43e4c40ea1b',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/meeting',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Commencement',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '383986e6-9c44-4c9b-b638-cf9bc50f27c3',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/commencement',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Humanities',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '388e955a-8618-401b-b633-7c864b9b68da',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/humanities',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Guest Artist</div><div class="field-item field-item-1">Info session</div><div class="field-item field-item-2">Lecture</div><div class="field-item field-item-3">Presentation</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '395e8156-0002-4ffb-9e1d-956d17decfa6',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/guest-artistinfo-sessionlecturepresentation',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'International',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '3d6c6d7e-4db0-4fb4-892b-716103115f9a',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/international',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Guest Artist',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '40a725ff-fbe0-4b1b-abd5-7406cbca013b',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/guest-artist',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Diversity',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '4265d1f3-0574-414c-b126-13954f7988dc',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/diversity',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">English Club</div><div class="field-item field-item-1">Workshops</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '437d30bf-dc46-4f13-b4ef-a40cf00a32fd',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/english-clubworkshops',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Lecture</div><div class="field-item field-item-1">Off-campus</div><div class="field-item field-item-2">Presentation</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '4781f962-14f5-49c1-b5ac-5cfef442541b',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/lectureoff-campuspresentation',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Presentation',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '48a8d3d0-bc4e-477a-a850-6e2e01105898',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/presentation',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Lecture</div><div class="field-item field-item-1">Literature</div><div class="field-item field-item-2">Presentation</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '4fd27e02-83a2-4fe8-98a3-be327447dfdc',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/lectureliteraturepresentation',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Sports',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '50334d5f-135f-4a79-839d-656ec4bfd2c4',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/sports',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Awards Ceremony',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '54bddedf-db3e-42aa-842a-e8757b38cdd8',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/awards-ceremony',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Career Events',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '641c41b0-9c59-4270-91ef-b2c82c2a1a85',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/career-events',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Literature',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '648cf305-abee-49c8-9832-7ea41f866963',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/literature',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Guest Artist</div><div class="field-item field-item-1">Performance</div><div class="field-item field-item-2">Workshops</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '64b51f2c-9a21-4d72-91a8-7bb7811babb8',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/guest-artistperformanceworkshops',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Energy',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '666f522c-bd6f-4d8f-b3ef-e6eac16a8f32',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/energy',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Reading',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '6df96d4e-8f94-4956-ae34-de4f42a4c93d',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/reading',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Alumni',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '70fba8ee-c2cb-47bb-a645-24340c0d2ade',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/alumni',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Arts and Culture',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '7606f7e6-7e9a-447c-a62e-49446e8132b7',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/arts-and-culture',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Alumni',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '7630e55a-ec0a-400b-9f65-b6b8a91a176a',
    'vocabulary_machine_name' => 'asu_events_audience',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-audience/alumni',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Fall Welcome',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '796e90e8-d0fa-499c-a552-7a80dbe3ae7b',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/fall-welcome',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Off-campus',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '807679bf-8705-4ab0-8b2d-d201ffa137ca',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/campus',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Journalism',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '8119d554-6c1c-4ef5-9ab8-5164024cd46d',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/journalism',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Convocation',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '817c3f9a-6348-4269-8d31-24fa01f1ee2a',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/convocation',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Entrepreneurship',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '89acb024-fb34-4787-9bcf-523cb4761a63',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/entrepreneurship',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Colloquium</div><div class="field-item field-item-1">Conference</div><div class="field-item field-item-2">Lecture</div><div class="field-item field-item-3">Symposium</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '8c6027a4-0cd1-4769-bf55-818e912fb495',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/colloquiumconferencelecturesymposium',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">English Education</div><div class="field-item field-item-1">Lecture</div><div class="field-item field-item-2">Literature</div><div class="field-item field-item-3">Presentation</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '8e2ce1f4-93d2-4b08-a6b4-eac686410547',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/english-educationlectureliteraturepresentation',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Community',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '8f7d01f2-436b-4617-a0f5-cd6d63ba2a5d',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/community',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Film</div><div class="field-item field-item-1">Guest Artist</div><div class="field-item field-item-2">Literature</div><div class="field-item field-item-3">Performance</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '8fd6f282-19fa-4795-9d3a-78377fc96bfa',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/filmguest-artistliteratureperformance',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Play',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '910abd9c-ae26-47bd-8dd1-de4841f0aab2',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/play',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Other',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '926f2509-be5b-43b3-ae54-29d4dcc46a47',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/other',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Student Life',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '94174fc7-908f-42a1-82d0-bd68666eb683',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/student-life',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Performance',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '94fed2f5-9885-447b-ab60-d381ae694468',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/performance',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Conference</div><div class="field-item field-item-1">Linguistics</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '99b30f9f-1464-4b08-8665-c705e33ee9f6',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/conferencelinguistics',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Faculty',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => '9e619e17-0ebb-4da4-8597-82ee72238ed8',
    'vocabulary_machine_name' => 'asu_events_audience',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-audience/faculty',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Film',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'aacddb9a-05b6-46ff-b714-9a1df044eed3',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/film',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Colloquium',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'ac9b6833-46bb-407a-bff3-6bdb7e48cacf',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/colloquium',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'b65bb2dd-5459-491a-a039-ccc564e1e58a',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Exhibit',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'bb2c4a55-4185-4578-9179-7363cc211866',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/exhibit',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Community Service',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'be6ac320-2049-4c3a-a365-ee8adbb74178',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/community-service',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Conference',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'c1d572ea-7013-49ef-9de1-ca8fdb3ea46d',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/conference',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Symposium',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'c6bd9687-7494-432e-8e46-797d00fa9810',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/symposium',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Technology',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'd0879723-e8aa-4d6e-aa66-64fc467c89a3',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/technology',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Engineering',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'd0e550bf-ed99-4681-9eca-fea8c865ff34',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/engineering',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Science',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'd5e7a100-5a39-40bb-ad9e-3118bc13095c',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/science',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Brown Bag',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'd643af46-82de-4168-807e-57beb70a7156',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/brown-bag',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Homecoming Event',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'e4b5b095-2412-4d31-b556-9887cd5026c9',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/homecoming-event',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Spirit and traditions',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'eb5d4121-2522-47e4-98ac-ae2a6d058b05',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/spirit-and-traditions',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Research',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'ed18e746-aaad-46db-9a3d-68366e43f776',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/research',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Changemaker Central',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'f31487d2-7c5b-4aa5-a941-244a27571785',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/changemaker-central',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Career fair',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'f34cca71-7c09-4a74-a585-9c84d240c665',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/career-fair',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => '<div class="field-item field-item-0">Reading</div><div class="field-item field-item-1">Workshops</div>',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'fbe21dd0-df02-4880-b7ed-31e8c496dbbf',
    'vocabulary_machine_name' => 'asu_events_type',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-type/readingworkshops',
        'language' => 'und',
      ),
    ),
  );
  $terms[] = array(
    'name' => 'Business',
    'description' => NULL,
    'format' => NULL,
    'weight' => 0,
    'uuid' => 'fc8cdab5-c24e-4e48-9bd8-3970d1b0106d',
    'vocabulary_machine_name' => 'asu_events_category',
    'url_alias' => array(
      0 => array(
        'alias' => 'asu-events-category/business',
        'language' => 'und',
      ),
    ),
  );
  return $terms;
}
