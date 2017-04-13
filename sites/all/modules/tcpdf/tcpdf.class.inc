<?php

/**
 * @file
 * Contains \TCPDF\TCPDFDrupal.
 */

/**
 * Do not create a new instance of this class manually. Use tcpdf_get_instance().
 * @see tcpdf_get_instance()
 */
class TCPDFDrupal extends TCPDF {


  protected $drupalHeader = array(
    'html' => NULL,
    'callback' => NULL,
  );
  protected $drupalFooter = array(
    'html' => NULL,
    'callback' => NULL,
  );
  /**
   * Sets a bunch of commonly used propeties in the TCPDF object. The propeties
   *   set by this function can be safely changed after calling the method. This
   *   method also let's the developer to change the header or footer of the pdf
   *   document without making his/her own class.
   *
   * @param array $options
   *   Associative array containing basic settings.
   *     'title' => Title of the document
   *     'subject' => Subject of the document
   *     'author' => Author of the document
   *     'logo_path' => Path to a logo wich is placed to the header
   *     'keywords' => Comma separated list of keywords
   *     'header' => Array
   *        'html' => Html code of the header.
   *        'callback' => Function that generates the header. If 'html' is set, it's ignored. Note: Not working.
   *     'footer' => Array
   *        'html' => Html code of the footer.
   *        'callback' => Function that generates the footer. If 'html' is set, it's ignored. Note: Not working.
   */
  function DrupalInitialize($options) {
    $title = isset($options['title']) ? $options['title'] : variable_get('site_name', 'Drupal');
    $author = isset($options['author']) ? $options['author'] : variable_get('site_name', 'Drupal');
    $subject = isset($options['subject']) ? $options['subject'] : variable_get('site_name', 'Drupal') ;
    $keywords = isset($options['keywords']) ? $options['keywords'] : 'pdf, drupal';
    $this->drupalHeader = isset($options['header']) ? $options['header'] : $this->drupalHeader;
    $this->drupalFooter = isset($options['footer']) ? $options['footer'] : $this->drupalFooter;

    // set document information
    $this->SetCreator(PDF_CREATOR);
    $this->SetAuthor($author);
    $this->SetTitle($title);
    $this->SetSubject($subject);
    $this->SetKeywords($keywords);

    // set default header data

    $this->setFooterFont(Array(PDF_FONT_NAME_DATA, '', 6));

    // set default monospaced font
    $this->SetDefaultMonospacedFont(PDF_FONT_MONOSPACED);

    //set margins
    $this->SetMargins(PDF_MARGIN_LEFT, 28, PDF_MARGIN_RIGHT);
    $this->SetHeaderMargin(PDF_MARGIN_HEADER);
    $this->SetFooterMargin(PDF_MARGIN_FOOTER);

    //set auto page breaks
    $this->SetAutoPageBreak(TRUE, PDF_MARGIN_BOTTOM);

    //set image scale factor
    $this->setImageScale(PDF_IMAGE_SCALE_RATIO);

    // set font
    $this->SetFont('dejavusans', '', 8);
    $this->AddPage();
  }

  /**
   * Sets the header of the document.
   * @return NULL
   */
  public function Header() {
    if (!$this->DrupalGenRunningSection($this->drupalHeader)) {
      return parent::Header();
    }
  }

  /**
   * Sets the footer of the document.
   * @return NULL
   */
  public function Footer() {
    if (!$this->DrupalGenRunningSection($this->drupalFooter)) {
      return parent::Footer();
    }
  }

  /**
   * Generates a header or footer for the pdf document.
   *
   * @param array $container
   * @see DrupalInitialize()
   *
   * @return FALSE if the container did not store any useful information to generate
   *   the document.
   */
  private function DrupalGenRunningSection($container) {
    if (!empty($container['html'])) {
      $this->writeHTML($container['html']);
      return TRUE;
    }
    elseif (!empty($container['callback'])) {
      $that = &$this;
      if (is_array($container['callback'])) {
        if (function_exists($container['callback']['function'])) {
          call_user_func($container['callback']['function'], $that, $container['callback']['context']);
        }
      }
      elseif (function_exists($container['callback'])) {
        call_user_func($container['callback'], $that);
      }
      return TRUE;
    }
    return FALSE;
  }
}
