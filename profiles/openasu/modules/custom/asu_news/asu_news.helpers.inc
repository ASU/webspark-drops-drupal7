<?php
/**
 *  Helper functions for asu_news module
 **/

 /**
  * Helper function to get news
  * @param  int     $max_range max number of items to retrieve
  * @param  array   $fields    field names, column id, value, and op to filter by
  * @param  string  $order_by  field name to sort by
  * @param  boolean $pager     to have or not a pager returned with results
  * @return array              news nodes in an array format
  */
function _asu_news_get_asunews_items($max_range, $fields = NULL, $order_by = NULL, $pager = FALSE) {
  $news_items = array();
  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'asu_news')
    ->propertyCondition('status', NODE_PUBLISHED);

  if (!empty($fields)) {
    foreach ($fields as $field) {
      $query->fieldCondition($field['name'], $field['id'], $field['value'], $field['op']);
    }
  }

  if (!empty($order_by)){
    $query->fieldOrderBy('field_photo', 'fid', 'DESC');
  }
  else {
    $query-> propertyOrderBy('created', 'DESC');
  }

  $query->range(0, $max_range);

  if ($pager) {
    $query->pager(10);
  }

  $result = $query->execute();

  if (isset($result['node'])) {
    $news_items_nids = array_keys($result['node']);
    $news_items = entity_load('node', $news_items_nids);
  }

  return $news_items;
}

/**
 * Helper function to retrieve images with styles
 * @param  string         $image_style Name of the image style
 * @param  object         $node        Node object that contains the image
 * @return render array()              Render array with the image information
 */
function _asu_news_get_image($image_style, $node) {
  $image = '';
  $images = field_get_items('node', $node, 'field_asunews_image');
  if(!empty($images)) {
    $image = field_view_value('node', $node, 'field_asunews_image', $images[0], array(
        'type' => 'image',
        'settings' => array(
          'image_style' => $image_style, // could be 'thumbnail'
        ),
      )
    );
    $image['#item']['attributes'] = array(
      'data-object-fit' => 'cover',
    );
  }
  else {
    $default_img_path = drupal_get_path('module', 'asu_news') . '/theme/images/asu_watermark_logo.png';

    $image = array(
      '#theme' => 'image',
      '#path' => $default_img_path,
      '#attributes' => array(
        'data-object-fit' => 'cover',
      ),
    );
  }

  return $image;
}

/**
 * Adding proper variables to our $vars array
 * @param array $vars array with variables for rendering
 */
function _asu_news_set_full_view_vars($vars) {
  $articleAuthorName = '';
  $articleDepartment = '';
  $articleAuthorTitle = '';
  $articleAuthorPhone = '';
  $articleAuthorEmail = '';
  $authorPicture = '';
  $author_info = array();
  $user = '';

  if ($vars['node']->uid > 1) {
    $user = user_load($vars['node']->uid);

    if (!empty($user->field_contrib_contact_name)) {
        $articleAuthorName = $user->field_contrib_contact_name;

    }

    if (!empty($user->field_contrib_contact_email)) {
        $articleAuthorEmail = $user->field_contrib_contact_email;
    }

    if (!empty($user->field_contrib_contact_phone)) {
        $articleAuthorPhone = $user->field_contrib_contact_phone;

    }

    if (!empty($user->field_contrib_professional_title) && !empty($user->field_contrib_contact_dept) > 0) {
        $articleAuthorTitle = $user->field_contrib_professional_title[LANGUAGE_NONE][0]['safe_value'];
        $articleDepartment = $user->field_contrib_contact_dept[LANGUAGE_NONE][0]['safe_value'];
    }

    $authorPicture = '';
    if (!empty($user) && $user->picture != null) {
        $authorPicture = field_view_field('user', $user, 'field_user_picture', array('settings' => array('image_style' => 'asu_news_profile_image')));
    }
  }
  elseif (!empty($vars['field_asunews_contri_email'])) {
    $user = user_load_by_mail($vars['field_asunews_contri_email'][0]['safe_value']);
    $authorPicture = '';
    if (!empty($user) && $user->picture != null) {
        $authorPicture = field_view_field('user', $user, 'field_user_picture', array('settings' => array('image_style' => 'asu_news_profile_image')));
    }

    if(!empty($vars['field_asunews_contri_affiliation'])) {
      $articleDepartment = field_view_field('node', $vars['node'], 'field_asunews_contri_affiliation');
    }
    if(!empty($vars['field_asunews_contri_name'])) {
      $articleAuthorName = field_view_field('node', $vars['node'], 'field_asunews_contri_name');
    }
    if(!empty($vars['field_asunews_contri_email'])) {
      $articleAuthorEmail = field_view_field('node', $vars['node'], 'field_asunews_contri_email');
    }
    if(!empty($vars['field_asunews_contri_phone'])) {
      $articleAuthorPhone = field_view_field('node', $vars['node'], 'field_asunews_contri_phone');
    }
  }
  $articleAuthorName = field_view_field('node', $vars['node'], 'field_asunews_contri_name');
  $articleAuthorPhone = field_view_field('node', $vars['node'], 'field_asunews_contri_phone');
  $articleDepartment = field_view_field('node', $vars['node'], 'field_asunews_contri_affiliation');
  $articleAuthorEmail = field_view_field('node', $vars['node'], 'field_asunews_contri_email');
  $author_info['picture'] = $authorPicture;
  $author_info['dept'] = $articleDepartment;
  $author_info['email'] = $articleAuthorEmail;
  $author_info['title'] = $articleAuthorTitle;
  $author_info['name'] = $articleAuthorName;
  $author_info['phone'] = $articleAuthorPhone;

  foreach ($author_info as $key=>$element) {
    if (!empty($element)) {
      $element['#label_display'] = 'hidden';
      $author_info[$key] = $element;
    }
  }

  $vars['content']['author_info'] = $author_info;

  $vars['content']['boilerplate'] = field_view_field('node', $vars['node'], 'field_boilerplate');
  $vars['content']['boilerplate']['#label_display'] = 'hidden';

  $vars['content']['sub_title'] = field_view_field('node', $vars['node'], 'field_sub_title');
  $vars['content']['sub_title']['#label_display'] = 'hidden';

  $img_quote = field_view_field('node', $vars['node'], 'field_asunews_image_quote');
  $img_quote['#label_display'] = 'hidden';

  if (preg_match("/<img[^>]+>/i", $vars['content']['body'][0]['#markup'])){

  }
  else {
    $pos = field_get_items('node', $vars['node'], 'field_news_image_paragraph');
    $pos_num = 4;
    if (!empty($pos)) {
      $pos_num = $pos[0]['value'];
    }
    $full = FALSE;
    $full_display = field_get_items('node', $vars['node'], 'field_news_image_full_display');
    if (!empty($full_display)) {
      if ($full_display[0]['value']) {
        $full = TRUE;
      }
    }

    $vars['content']['body'][0]['#markup'] = _asu_news_insert_image(
      $vars['content']['body']['#items'][0]['value'],
      $vars['field_asunews_image'][LANGUAGE_NONE][0],
      $img_quote,
      'panopoly_image_full',
      $pos_num,
      $full);
  }

  return $vars;
}

/**
 * Inerts an image in a certain position with a given qoute
 * @param  string $body_markup Markup for the body of the content.
 * @param  array  $image       Render image array.
 * @param  string $quote       Qoute to be attached to the given Image.
 * @param  string $style_name  Image style name.
 * @param  int    $pos         Position paragrah the image should be inserted into
 * @return string              Body markup with image and qoute inserted.
 */
function _asu_news_insert_image($body_markup, $image, $quote, $style_name, $pos, $full) {
  $output = '';
  $p_count = 1;
  $body_markup = str_replace('</p>', '', $body_markup);
  $paragraphs = explode('<p>', $body_markup);
  $class_container = array('caption');
  $class_container_inner = array();
  if (!$full) {
    $class_container[] = 'caption-left';
    $class_container_inner[] = 'caption-inner';
  }

  foreach($paragraphs as $p) {
    if ($p_count == $pos) {
      $image_markup = theme('image_style', array(
        'path' => $image['uri'],
        'style_name' => $style_name,
        'attributes' => array('class'=> array('media-element', 'file-responsive-image'))
      ));
      $caption_container = array(
        '#type' => 'container',
        '#attributes' => array(
          'class' => $class_container,
        ),
        'width' => array(
          '#type' => 'container',
          '#attributes' => array(
            'class' => array('caption-width-container'),
          ),
          'inner' => array(
            '#type' => 'container',
            '#attributes' => array(
              'class' => $class_container_inner,
            ),
          ),
        ),
      );

      if (!empty($quote)) {
        $caption_container['width']['inner']['quote'] = $quote;
      }

      $caption_container['width']['inner']['image'] = array(
        '#type' => 'markup',
        '#markup' => $image_markup,
        'weight' => -100,
      );

      $output .= render($caption_container);
    }

    $output .= '<p>' . $p . '</p>';
    $p_count++;
  }

  return $output;
}
