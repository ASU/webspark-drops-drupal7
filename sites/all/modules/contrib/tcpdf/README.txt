TCPDF is a wrapper module for the popular TCPDF library. It is meant to use by
module developers.

In most cases it is enough to get a TCPDFDrupal instance with tpdf_get_instance, and
use it as it were a normal instance of TCPDF class. In order to achieve that, some
extra functionality were added to the library. Every new function and propety has
the "drupal" prefix to prevent any accidental override, and avoid breaking the
compatibility to the original class.

DrupalInitialize() is a multifunctional method of TCPDFDrupal and provides an
easy way to set some common variables of the tcpdf document, like title or keywords.
It is also possible to create a Header or a Footer for the document with it.

If it is still necessary to extend the TCPDF class, it is possible tell tpdf_get_instance()
to make an instance of a custom class instead of TCPDFDrupal. This class should extend TCPDFDrupal.

Note that the latest TCPDF version that this module was tested with is 6.0.021.
While in most cases it should work with later versions, if you encounter any
issues, and you are using a newer version of TCPDF, try downgrading it.