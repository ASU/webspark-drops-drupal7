<?php

/**
 * @file
 * Implementation of Feeds mapping API for office_hours
 */

define( 'MOREHOURS', '1'); // index to differentiate hours vs. morehours

/**
 * Implements hook_feeds_processor_targets_alter().
 *
 * @see FeedsNodeProcessor::getMappingTargets().
 */
function office_hours_feeds_processor_targets_alter(&$targets, $entity_type, $bundle_name) {
  foreach (field_info_instances($entity_type, $bundle_name) as $name => $instance) {
    $info = field_info_field($name);
    if ($info['type'] == 'office_hours') {

      $targets[$name . ':day'] = array(
        'name' => $instance['label'] . ': Day',
        'callback' => 'office_hours_feeds_set_target',
        'description' => t('The day for the @name field.',
          array('@name' => $instance['label'])),
        'real_target' => $name,
      );

      $targets[$name . ':hours'] = array(
        'name' => $instance['label'] . ': Hours',
        'callback' => 'office_hours_feeds_set_target',
        'description' => t('The first set of hours for the @name field, if using start and end in 1 field.',
          array('@name' => $instance['label'])),
        'real_target' => $name,
      );
      $targets[$name . ':morehours'] = array(
        'name' => $instance['label'] . ': More hours',
        'callback' => 'office_hours_feeds_set_target',
        'description' => t('The second set of hours for the @name field, if using start and end in 1 field.',
          array('@name' => $instance['label'])),
        'real_target' => $name,
      );

      $targets[$name . ':hours:start'] = array(
        'name' => $instance['label'] . ': Hours start',
        'callback' => 'office_hours_feeds_set_target',
        'description' => t('The start date for the @name field. Also use if mapping both start and end.',
          array('@name' => $instance['label'])),
        'real_target' => $name,
      );
      $targets[$name . ':hours:end'] = array(
        'name' => $instance['label'] . ': Hours end',
        'callback' => 'office_hours_feeds_set_target',
        'description' => t('The end date for the @name field.', array('@name' => $instance['label'])),
        'real_target' => $name,
      );

      $targets[$name . ':morehours:start'] = array(
        'name' => $instance['label'] . ': More hours start',
        'callback' => 'office_hours_feeds_set_target',
        'description' => t('The start date for the @name field. Also use if mapping both start and end.',
          array('@name' => $instance['label'])),
        'real_target' => $name,
      );
      $targets[$name . ':morehours:end'] = array(
        'name' => $instance['label'] . ': More hours end',
        'callback' => 'office_hours_feeds_set_target',
        'description' => t('The end date for the @name field.', array('@name' => $instance['label'])),
        'real_target' => $name,
      );
    }
  }
}

/**
 * Implements hook_feeds_set_target().
 */
function office_hours_feeds_set_target($source, $entity, $target, $feed_element) {
  static $sv_vid = NULL; // remember current entity-id
  static $sv_day = 0; // remember current day
  static $sv_office_hours = NULL; // collect OH while building
  static $sv_index = NULL; // index of array

  if (is_array($feed_element)) {
    $feed_element = $feed_element[0];
  }

//  list($field_name, $sub_field, $start_end_field) = explode(':', $target, 3);
  $field = explode(':', $target, 3);
  $field_name      = isset($field[0]) ? $field[0] : '' ;
  $sub_field       = isset($field[1]) ? $field[1] : '' ;
  $start_end_field = isset($field[2]) ? $field[2] : '' ;

  $morehours = 0; // for hours / morehours
  
  switch ($sub_field) {
    case 'day':
      // each OfficeHours-feeds line MUST start with a day-field; set new line
        if ($entity->vid != $sv_vid) {
           // this is a new entity
          $sv_vid = $entity->vid;
          unset($entity->{$field_name});  // clear officeHours field - this should have been done before.
          $sv_index = 0;
        } 
        else {
          // this is a new line in an existing entity
          $sv_index++;
        }

      // convert day to day number
      // @todo: better way to process texts, perhaps only first 3 characters
      // @todo: test for collaboration with Feeds Tamper
      // @todo: support other first day of week
      if (!is_numeric($feed_element)) {
        // day is passed as text
        switch (strtolower(substr($feed_element, 0, 3))) {
          case 'sun': //en
          case 'zon': //nl
          case 'søn': //da
            $sv_day = '0'; 
            break;
          case 'mon': //en
          case 'maa': //nl
          case 'man': //da
            $sv_day = '2';
            break;
          case 'tue': //en
          case 'din': //nl
          case 'tir': //da
            $sv_day = '4'; 
            break;
          case 'wed': 
          case 'woe':  
          case 'ons':
            $sv_day = '6';
            break;
          case 'thu':
          case 'don':
          case 'tor':
            $sv_day = '8'; 
            break;
          case 'fri':
          case 'vri':
          case 'fre':
            $sv_day = '10';
            break;
          case 'sat':
          case 'zat': 
          case 'lør':
            $sv_day = '12';
            break;
        }
      }
      else {
        // day is passed as day number: sunday: 1->0; monday: 2->2; tuesday: 3->4; etc.
        $sv_day = ( $feed_element - 1 ) * 2 ;
      }

//      $sv_office_hours['day'] = $sv_day;
      break;

    case 'morehours': 
      // set warning if Morehours is processed, but Hours is not set yet.
      if (!isset($entity->{$field_name}[$entity->language][$sv_index])) {
        watchdog('feeds office_hours', 'only morehours is set, not hours for nid = %nid', array( '%nid' => $entity->vid));
      }
      $sv_index++;  // open a new line for the 'morehours'
      $morehours = MOREHOURS;
      //break;  // do not break, proceed with 'hours'

    case 'hours': 
      //$morehours = 0;  // already set
      // remove time delimiters & spaces: ' 10:00 - 18:00  ' --> '1000-1800'  
      // the following is not sufficient to strip all unvisible characters, therefor intval() is used later on
      $feed_element = str_replace( ' ' , '' , $feed_element); 
      $feed_element = str_replace( ':' , '' , $feed_element);
      $feed_element = str_replace( '.' , '' , $feed_element);
      switch ($start_end_field) {
        case 'start':
            $entity->{$field_name}[$entity->language][$sv_index]['day'] = $sv_day + $morehours;
            $entity->{$field_name}[$entity->language][$sv_index]['starthours'] = intval($feed_element);
//          $sv_office_hours[$morehours]['starthours'] = intval($feed_element);
          break;
        case 'end':
            $entity->{$field_name}[$entity->language][$sv_index]['day'] = $sv_day + $morehours;
            $entity->{$field_name}[$entity->language][$sv_index]['endhours'] = intval($feed_element);
//          $sv_office_hours[$morehours]['endhours'] = intval($feed_element);
          break;
        default:
          // $feed_element contains both start and end
          list($hours_start, $hours_end) = explode('-', $feed_element, 2);
            $entity->{$field_name}[$entity->language][$sv_index]['day'] = $sv_day + $morehours;
            $entity->{$field_name}[$entity->language][$sv_index]['starthours'] = intval($hours_start);
            $entity->{$field_name}[$entity->language][$sv_index]['endhours'] = intval($hours_end);
//          $sv_office_hours[$morehours]['starthours'] = intval($hours_start);
//          $sv_office_hours[$morehours]['endhours'] = intval($hours_end);
          break;
      }
      break;
    default:
      watchdog('feeds office_hours', 'field %field element %element is not correct', array( '%field' => '$sub_field', '%element' => $feed_element));
      break;
  }

  if (isset($sv_office_hours['day']) && 1 == 0 ) {
    // 
    $morehours = 0;
    $entity->{$field_name}[$entity->language][$sv_index]['day'] = $sv_office_hours['day'];

    $entity->{$field_name}[$entity->language][$sv_index]['starthours'] = isset($sv_office_hours[$morehours]['starthours']) ? $sv_office_hours[$morehours]['starthours'] : NULL;
    $entity->{$field_name}[$entity->language][$sv_index]['endhours']   = isset($sv_office_hours[$morehours]['endhours'])   ? $sv_office_hours[$morehours]['endhours'] : NULL;

    $sv_index++;

    if (isset($sv_office_hours[MOREHOURS])) {
      $morehours = MOREHOURS;
      $entity->{$field_name}[$entity->language][$sv_index]['day'] = $sv_office_hours['day'];

      $entity->{$field_name}[$entity->language][$sv_index]['starthours'] = isset($sv_office_hours[$morehours]['starthours']) ? $sv_office_hours[$morehours]['starthours'] : NULL;
      $entity->{$field_name}[$entity->language][$sv_index]['endhours']   = isset($sv_office_hours[$morehours]['endhours'])   ? $sv_office_hours[$morehours]['endhours'] : NULL;

      $sv_index++;
    }

    // prepare data for next day of office hours 
    $sv_office_hours = NULL;  // apparently above line does not clear the whole structure..
  }

  return $entity;
}