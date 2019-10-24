<?php

/**
 * arrayRecursiveDiff($a, $b) - Recursively finds the difference between two
 *                              arrays. Shamelessly stolen from Stack Overflow
 *                              :/
 *
 * @param $arr1 - First array that is compared to $arr2
 * @param $arr2 - Second array that is being compared from $arr1
 *
 * @return $outputDiff - Returns an array that holds elements found in $arr1
 *                       not found in $arr2
 */
function arrayRecursiveDiff($arr1, $arr2)
{
  $unsupportedDiff = [];
  $misplacedDiff = [];

  foreach ($arr1 as $key1 => $value1)
  {
    $found = false;

    foreach ($arr2 as $key2 => $value2)
    {
      if ($value1['name'] == $value2['name'] &&
        $value1['type'] == $value2['type'] &&
        $value1['filename'] != $value2['filename'])
          $misplacedDiff[] = array('name' => $value1['name'], 'filename' => $value1['filename']);

      else if ($value1['name'] == $value2['name'] &&
          $value1['type'] == $value2['type'] &&
          $value1['filename'] == $value2['filename'])
        $found = true;
    }

    if (!$found)
      $unsupportedDiff[] = array('name' => $value1['name'], 'type' => $value1['type']);
  }

  return array($unsupportedDiff, $misplacedDiff);
}
