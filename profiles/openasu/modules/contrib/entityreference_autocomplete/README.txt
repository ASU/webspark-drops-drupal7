
Written by Salvador Molina <salvador.molinamoreno@codeenigma.com>
                           <drupal.org: https://drupal.org/user/826088>


CONTENTS OF THIS FILE
---------------------

 * INTRODUCTION
 * INSTALLATION
 * USAGE
 * ELEMENT PROPERTIES
 * REPORTED ISSUES WITH OTHER MODULES


INTRODUCTION
------------

This module defines a new form element type, called "entityreference", that
allows developers to add autocomplete fields to forms, so that users can
reference any entity in the same way they would do through an Entity Reference
field.


INSTALLATION
------------

To install the Entity Reference Autocomplete module:

 1. Place its entire folder into the "sites/all/modules/contrib" folder of your
    drupal installation.

 2. In your Drupal site, navigate to "admin/modules", search the "Entity
    Reference Autocomplete" module, and enable it.

 3. Click on "Save configuration".


USAGE
-----

After installing the module:

  1. Create any form you want in the usual way through drupal_get_form().

  2. To define an entityreference field, declare it as any other form element,
     specifying 'entityreference' in the '#type' property of the element. E.g:

        $form['my_entity_reference'] = array(
          '#type' => 'entityreference',
          '#title' => t('My Reference'),
          '#era_entity_type' => 'user',  // Mandatory.
          '#era_bundles' => array(), // Optional (Any bundle by default).
          '#era_cardinality' => 3,       // Optional (1 By default).
          '#era_query_settings' => array(
            'limit' => 15, // Default is 50.
            'property_conditions' => array(
              // 'entity property', 'filter value', 'operator'.
              array('uid', 30, '>'),
            ),
            'field_conditions' => array(
              // 'field name', 'column', 'value', 'op', 'delta', 'language'.
              array('field_test_field', 'value', 'test'),
            ),
          ),
        );

  3. When the form is rendered, you should have the autocomplete field ready to
     use.

  4. For a detailed explanation of the meaning of every '#era_{property}'
     property, see the "ELEMENT PROPERTIES" section of this README.


ELEMENT PROPERTIES
------------------

Explanation of the custom properties used in an 'entityreference' form element,
and any Form API standard properties which use might not be clear:

'#era_entity_type':  The Entity Type to be referenced: Like "user", "node",
                     "comment", "file", "taxonomy_term", etc...

'#era_bundles':      Serves to specify that only entities of a given bundle will
                     be returned in the autocomplete field. For nodes, it would
                     be the content type, like "story", "page", etc...

'#era_cardinality':  The maximum number of items (references) that the field
                     will accept. The user will be able to reference more items
                     than this number in the browser, but then the form won't
                     validate on submission, and an error message will appear on
                     the page telling him about this restriction.

                     For unlimited values, use ERA_CARDINALITY_UNLIMITED or -1.

'#era_query_settings':  Serves to specify certain settings that will affect the
                        results returned by the autocomplete callback. This
                        property MUST be an associative array, in which every
                        key is the name of a supported setting. At the moment,
                        the settings supported are:

              - 'limit':  Limits the number of results returned by the callback.
                          This is useful when there are a lot of entities that
                          match the text entered by the users, so that the
                          request doesn't make a big impact when querying the
                          database (it translates to a $query->range(0, limit)).
                          The default value is 50, but it can be set to any
                          integer value. Unset it, or set it to NULL for no
                          limits.

              - 'property_conditions':  Allows to filter the results returned in
                          the query, by any property of the entity type. This
                          property is meant to be an array, in which each
                          element is an array of the arguments to pass to the
                          propertyCondition() method of the EntityFieldQuery.
                          Example of use:

                                '#era_query_settings' => array(
                                  'property_conditions' => array(
                                    // 'entity property', 'value', 'operator'.
                                    array('uid', 5, '<'),
                                  ),
                                ),

              - 'field_conditions':  Allows to filter the results returned in
                          the query, based on the value of any field of the of
                          the entity. This property is meant to be an array, in
                          which each element is an array of the arguments to
                          pass to the fieldCondition() method of the
                          EntityFieldQuery class.
                          Example of use:

                                '#era_query_settings' => array(
                                  'field_conditions' => array(
                                    // 'field name', 'column', 'value'.
                                    array('field_test_field', 'value', 'test'),
                                  ),
                                ),

                          For further information, see the documentation of the
                          fieldCondition() method of the EntityFieldQuery class.


'#default_value':    If references to any entities are provided by default, it
                     should be as Entity IDs. For single values, just pass the
                     ID of the referenced entity. For multiple values, an array
                     of Entity IDs is expected.

KNOWN ISSUES WITH OTHER MODULES
-------------------------------

1.- A performance issue has been reported when using this module and the
entityreference module alongside Fast 404 module.

Reported Issue: https://www.drupal.org/node/2544794
Proposed solution: Add the following line to your settings.php.

$conf['fast_404_string_whitelisting'] = array('entityreference_autocomplete/autocomplete', 'entityreference/autocomplete' 'system/ajax');
