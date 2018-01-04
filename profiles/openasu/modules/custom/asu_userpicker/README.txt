DESCRIPTION
--------------------------
Provides a custom user field widget for picking users in Drupal, Solr,
and creating those not yet in Drupal. ASU LDAP can also be configured as a userpicker search service if the ldap_servers and
cas_ldap modules are installed.

INSTALLATION
--------------------------
Install the module as usual, see http://drupal.org/node/70151 for further
information.

Configuration
--------------------------
The ASU Userpicker module creates an AJAX autoocomplete userpicker widget
and is easily assignable using the Fields managment UI in Drupal. Solr autocomplete is enabled by
default without any configuration.

LDAP requires the CAS Attributes, LDAP Servers and User Reference modules to
be enabled, and at least one LDAP Server to be configured.

Using the ASU Userpicker with non-Field API managed fields requires custom
code to map it into place:

Implement a form_alter() to change an existing userpicker field's
'#autocomplete_path' to 'autocomplete/asu/user' and the '#element_validate'
field to 'asu_userpicker_autocomplete_validate'.

Like so:
$form['my_picker_field']['#autocomplete_path'] = 'autocomplete/asu/user/solr';
$form['my_picker_field']['#element_validate'] = array('asu_userpicker_autocomplete_validate');

Additional configurations for the module can be made using the devel/php tool,
as there is no admin UI for these ASU Userpicker variables:

variable_set('asu_userpicker_ldap_server', 'your_server_machinename');
variable_set('asu_userpicker_referenceable_roles', 
    serialize(array(
      2 => '2', // Authenticated user
      3 => '0',
    )));
variable_set('asu_userpicker_referenceable_status', 
    serialize(array(
      1 => '1', // Active users
      0 => '0',
    )));
variable_set('asu_userpicker_referenceables_view', 'your_view_name');
variable_set('asu_userpicker_label', 'USER');
variable_set('asu_userpicker_search_user_fields', array('field_first_name', 'field_last_name', 'another_field_machine_name'));

PERMISSIONS
--------------------------

PAGES
--------------------------

TABLES
--------------------------

BLOCKS
--------------------------
None.

HOOKS
--------------------------
See the API file...  [ TODO ]

CREDITS
--------------------------
ASU Userpicker was created by Michael Samuelson <mlsamuel@asu.edu> /
<mlsamuelson@gmail.com> (http://mlsamuelson.com).


