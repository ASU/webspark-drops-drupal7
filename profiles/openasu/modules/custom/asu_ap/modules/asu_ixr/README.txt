// $Id$

DESCRIPTION
------------------------
This module provides several wrapper methods for using the IXR - The Inutio 
XML-RPC Library, a PHP-based library for performing remote XML-RPC transactions.  
It is simply an API and doesn't directly provide any functionality on its own.


INSTALLATION
------------------------
Due to license incompatabilities, the IXR Library must be downloaded separately 
and placed into this module's 'includes' folder (i.e. 
'sites/all/modules/ixr/includes/IXR_Library.php').
The library can be obtained from the locations below.

The original library:
http://scripts.incutio.com/xmlrpc/

A more recent version with SSL support (recommended):
http://griffin.oobleyboo.com/projects/xmlrpc/

Please note, for PHP 7+ support, you'll need to update from PHP 4 style
constructors (where the constructor has the same name as the class), to the
modern PHP practice of "__constructor()".

EXAMPLE USAGE
------------------------
function mymodule_remote_call($method, $args) {
  $server = variable_get('mymodule_xmlrpc_server', 'example.com');
  $path = variable_get('mymodule_xmlrpc_path', '/XmlRpcServer');
  $port = variable_get('mymodule_xmlrpc_port', 80);
  
  $ws = ixr_create_client($server, $path, $port);
  
  if ($ws->query("myobject.$method", $args)) {
    return $ws->getResponse();
  } 
  else {
    trigger_error($ws->getErrorMessage(), E_USER_WARNING);
    return null;
  }
}