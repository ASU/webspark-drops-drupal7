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
  $outputDiff = [];

  foreach ($arr1 as $key1 => $value1)
  {
    $found = false;

    foreach ($arr2 as $key2 => $value2)
    {
      if (count(array_diff_assoc($value1, $value2)) < 1)
        $found = true;
    }

    if (!$found)
      $outputDiff[] = $value1;
  }

  return $outputDiff;
}
