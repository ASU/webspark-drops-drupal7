<?php
/**
 * @file
 * A common-usage table for displaying ACE "products": courses,
 * task force meetings, events, etc.
 */
class ProductTable {

  public $products;
  public $show_category = TRUE;
  public $show_register = TRUE;
  public $show_prices = 'register'; //'register', true, or false. if 'register', the value of show_register will be used.
  public $show_agenda = TRUE;
  public $show_files = FALSE;
  public $show_type = FALSE;
  public $show_time = FALSE;
  public $title_text = 'Course Title';
  public $table_class = 'products';
  public $sort_ascending = TRUE;
  public $show_all_dates = FALSE;

  public function display_prices($node = NULL) {
    return ($this->show_prices === 'register')? $this->show_register : $this->show_prices;
  }
  
  public function toHtml() {
    $path = drupal_get_path('module', 'ace_common');
    drupal_add_css("$path/styles/course-listing.css");

    if (!empty($this->products)) {
      drupal_add_css("$path/styles/tablesorter-theme.css");
      drupal_add_js("$path/scripts/course-listing.js");
      drupal_add_js("$path/scripts/jquery.tablesorter.min.js");
      drupal_add_js("$path/scripts/jquery.metadata.js");

      $class = $this->table_class;
      if (!$this->sort_ascending) {
        $class .= ' descendingSort';
      }
      
      $attribs = array (
        'class' => $class,
      );
      $header = $this->header();
      $html .= theme('table', $header, $this->products_to_data_rows(), $attribs);
      $html .= $this->details(count($header));
    } else {
      $html .= '<div class="no-products">';
      $html .= t('None listed at this time.');
      $html .= '</div>';
    }
    return $html;
  }

  private function header() {
    $head = array();
    $head[] = array(
      'data' => t('Date'),
      'class' => 'date',
      'width' => '90',
    );
    if ($this->show_category) {
      $head[] = array(
        'data' => t('Category'),
        'class' => 'category',
        'width' => '90',
      );
    }
    $head[] = array(
      'data' => t($this->title_text),
      'class' => 'title',
    );
    if ($this->display_prices()) {
      $head[] = array(
        'data' => t('Member'),
        'class' => 'member-price',
        'width' => '65',
      );
      $head[] = array(
        'data' => t('Non-<br/>member'),
        'class' => 'non-member-price',
        'width' => '65',
      );
    }
    if ($this->show_register) {
      $head[] = array(
        'data' => '',
        'class' => 'register',
        'width' => '80',
      );
    }
    return $head;
  }

  private function products_to_data_rows() {
    $data_rows = array();
    foreach($this->products as $p) {
      $row = array();

      // Date.
      $delta = is_numeric($p->date_display_delta) ? $p->date_display_delta : 0;
      
      $date_of_product = '';
      if($this->show_all_dates) {
      	foreach($p->field_date as $pd) {
    		$date_of_product .= $this->date_to_html($pd) . "\n";
      	} 
      } else {
      	$date_of_product = $this->date_to_html($p->field_date[$delta]);
      }
      
      
      $row[] = array(
        'data' => $date_of_product,
        'class' => 'date',
      );

      // Category.
      if ($this->show_category) {
        $cat_data = '';
        foreach ($p->taxonomy as $term) {
          $cat_data .= $term->name . ', ';
        }
        $cat_data = trim($cat_data, ', ');
        $row[] = array(
          'data' => $cat_data,
          'class' => 'category',
        );
      }

      // Link.
      $title = $p->title;
      if ($this->show_type) {
        ace_common_node_type($p, $type_display);
        $title .= " ($type_display)";
      }
      $row[] = array(
        'data' => l($title, 'node/' . $p->nid),
        'class' => 'title',
      );

      // Prices.
      if ($this->display_prices()) {
        if ($p->field_price_member[0]['value']) {
          $member_price = '$' . $p->field_price_member[0]['value'];
        } else {
          $member_price = '';
        }
        if ($p->field_price_nonmember[0]['value']) {
          $nonmember_price = '$' . $p->field_price_nonmember[0]['value'];
        } else {
          $nonmember_price = '';
        }
        $row[] = array(
          'data' => $member_price,
          'class' => 'member-price',
        );
        $row[] = array(
          'data' => $nonmember_price,
          'class' => 'non-member-price',
        );
      }

      if ($this->show_register) {
        $row[] = $this->final_column($p);
      }

      $data_rows[] = array(
        'data' => $row,
        'id' => $p->nid,
      );
    }
    return $data_rows;
  }
  
  protected function final_column($p) {
    // Register link.
    return array(
      'data' => coursereg_make_link($p->field_cac[0]['value'], $p),
      'class' => 'register',
    );
  }

  protected function date_to_html($date) {
    if (empty($date['value'])) {
      return 'Any time';
    }
    
    $date_from = ace_get_cck_date($date, 'field_date', 'value');
    $date_to = ace_get_cck_date($date, 'field_date', 'value2');
    
    $html .= '<span class="date">';
   	$html .= date_format_date($date_from, 'custom', 'm/d/Y');
    $html .= '</span>';
    if ($this->show_time) {
      $html .= '<span class="time">';
      $html .= date_format_date($date_from, 'custom', 'g:i a');
      $html .= ' - <br/>';
      $html .= date_format_date($date_to, 'custom', 'g:i a');
      $html .= '</span>';
    }
    return $html;
  }
  
  protected function details($colspan) {
    $row_data = array();
    foreach ($this->products as $p) {
      $location_name = $p->field_location_name[0]['value'];
      $location = $p->field_location[0]['value'];
      $data = '';
      if ($this->show_agenda && Agenda::isActiveForNid($p->nid)) {
        $data .= '<div class="agenda-button">';
        $data .= agenda_make_link($p->nid);
        $data .= '</div>';
      }
      
      if (count($p->field_date) > 1) {
      	$data .= '<div class="dates-title">Dates</div>';
      	$data .= '<div class="dates">';

      	foreach($p->field_date as $pd) {
      		$date_from = ace_get_cck_date($pd, 'field_date', 'value');
      		$date_to = ace_get_cck_date($pd, 'field_date', 'value2');
      		
    		$data .= date_format_date($date_from, 'custom', 'm/d/Y g:i a') . ' - ';
    		$data .= date_format_date($date_to, 'custom', 'g:i a');
    		$data .= "<br/>";
      	} 
      	
      	$data .= '</div>';
      }
      
      if (!empty($location) || !empty($location_name)) {
        $data .= '<div class="location-title">Location</div>';
        $data .= '<div class="location">';
        if (!empty($location_name)) {
          $data .= "<span class='locationName'>${location_name}</span><br/>";
        }
        if (!empty($location)) {
          $data .= "<span class='locationAddress'>";
          $data .= coursereg_make_map_link($location);
          $data .= '</span>';
        }
        $data .= '</div>';
      };
      
      if (!empty($p->teaser)) {
        $data .= '<div class="description-title">Description</div>';
        $data .= '<div class="description">' . $p->teaser . '</div>';
      }
      
      if ($this->show_files) {
        $data .= $this->render_files_block($p);
      }
      
      $data .= '<div class="more">';
      $data .= '[';
      $data .= l('more', 'node/' . $p->nid, array('attributes' => array('class' => 'more')));
      $data .= ']';
      if (user_access('administer nodes')) {
        $data .= ' [';
        $data .= l('edit', "node/{$p->nid}/edit", array('attributes' => array('class' => 'edit')));
        $data .= ']';
      }
      $data .= '</div>';
      
      $row = array(
        array(
          'data' => $data,
          'colspan' => $colspan,
        ),
      );
      
      $row_data[] = array(
        'data' => $row,
        'id' => "details_{$p->nid}",
        'class' => 'details',
      );
    }
    
    $html = '<div class="product-details-hidden">';
    $html .= theme('table', NULL, $row_data);
    $html .= '</div>';
    return $html;
  }
  
  private function render_files_block($node) {
    $node_files = file_library__get_attached_to($node);
    $node_files = file_library__sift_view($node_files);
    
    if (empty($node_files)) {
      return;
    }
    
    $output .= '<div class="files-title">Downloads</div>';
    $output .= '<div class="files">';
    $output .= '<ul>';
    foreach ($node_files as $file) { 
      $output .= '<li>';
      $output .= l($file->node->title, $file->node->path, array('attributes' => array('class' => 'file')));
      $output .= ' <span class="file-price">' . $file->getPriceLabel() . '</span>';
      $output .= '</li>';
    }
    $output .= '</ul>';
    $output .= '</div>';
    return $output;
  }
}