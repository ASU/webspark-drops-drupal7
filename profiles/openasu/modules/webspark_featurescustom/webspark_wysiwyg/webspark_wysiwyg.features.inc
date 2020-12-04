<?php
/**
 * @file
 * webspark_wysiwyg.features.inc
 */

/**
 * Implements hook_image_styles_alter().
 */
function webspark_wysiwyg_image_styles_alter(&$data) {
  if (isset($data['wysiwyg_template_thumbnail'])) {
    if (!isset($data['wysiwyg_template_thumbnail']['storage']) || $data['wysiwyg_template_thumbnail']['storage'] == IMAGE_STORAGE_DEFAULT) {
      $data['wysiwyg_template_thumbnail']['label'] = 'wysiwyg_template_thumbnail';
    }
  }
}

/**
 * Implements hook_wysiwyg_default_profiles_alter().
 */
function webspark_wysiwyg_wysiwyg_default_profiles_alter(&$data) {
  if (isset($data['panopoly_html_text'])) {
    $data['panopoly_html_text']['settings']['theme_advanced_blockformats'] = 'p,h2,h3,h4,h5,h6'; /* WAS: 'h1,h2,h3,h4,h5,h6' */
    $data['panopoly_html_text']['settings']['buttons']['linkit'] = array(
      'linkit' => 1,
    ); /* WAS: '' */
    $data['panopoly_html_text']['preferences']['show_toggle'] = 1; /* WAS: 0 */
    $data['panopoly_html_text']['preferences']['user_choose'] = 1; /* WAS: 0 */
    unset($data['panopoly_html_text']['settings']['buttons']['default']['link']);
    unset($data['panopoly_html_text']['settings']['buttons']['default']['stroke']);
  }
  if (isset($data['panopoly_wysiwyg_text'])) {
    $data['panopoly_wysiwyg_text']['settings']['theme_advanced_blockformats'] = 'p,h2,h3,h4,h5,h6'; /* WAS: 'h1,h2,h3,h4,h5,h6' */
    $data['panopoly_wysiwyg_text']['preferences']['show_toggle'] = 1; /* WAS: 0 */
    $data['panopoly_wysiwyg_text']['preferences']['user_choose'] = 1; /* WAS: 0 */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['default']['anchor'] = 1; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['default']['hr'] = 1; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['advhr']['advhr'] = 1; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['default']['styleselect'] = 1; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['table'] = array(
      'tablecontrols' => 1,
    ); /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['template'] = array(
      'template' => 1,
    ); /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['theme_advanced_styles'] = 'Element Maroon=ws2-element-style ws2-element-maroon
  Element Gold=ws2-element-style ws2-element-gold
  Element Gray=ws2-element-style ws2-element-gray
  WS2 Alt White container=ws2-element-alt ws2-element-alt-white
  WS2 Alt Gray container=ws2-element-alt ws2-element-alt-gray
  WS2 Alt Black container=ws2-element-alt ws2-element-alt-black
  Lead paragraph=ws2-element-style lead-paragraph
  OL Stepped=ws2-element-style ws2-list-stepped
  Blockquote Image=ws2-element-style ws2-bq ws2-bq-image
  Signature=ws2-element-style ws2-sig-title
  Signature Byline=ws2-element-style ws2-sig-byline
  Table Bordered=ws2-element-style bordered
  Image align left=pull-left
  Image align right=pull-right
  Image caption text=ws2-element-style ws2-img-caption
  Image drop shadow=ws2-element-style ws2-drop-shadow
  Image with rounded corners=img-rounded
  Image with double-border=img-thumbnail
  Alert text success=alert alert-block alert-success
  Alert text warning=alert alert-block alert-warning
  Alert text danger=alert alert-block alert-danger
  Alert text info=alert alert-block alert-info
  Button Col-wide=ws2-element-style btn btn-block
  Button Large=ws2-element-style btn btn-lg
  Button Medium=ws2-element-style btn btn-sm
  Button Small=ws2-element-style btn btn-xs
  Button Tag=ws2-element-style btn btn-xs btn-tag
  Button Disabled=ws2-element-style btn btn-disabled
  Button Default=ws2-element-style btn btn-default
  Maroon button=ws2-element-style btn btn-primary
  Gray button=ws2-element-style btn btn-secondary
  Black button=ws2-element-style btn btn-black
  Gold button=ws2-element-style btn btn-gold
  DEPRECATED STYLES BELOW=do-not-use-following-styles
  DONOTUSE FOR WS2=do-not-use-following-styles
  Bordered table=bordered
  Oval image=img-circle
  Primary button=btn btn-primary
  Primary button large=btn btn-primary btn-lg
  Primary button full-col-wide=btn btn-primary btn-block
  Primary button large col-wide=btn btn-primary btn-lg btn-block
  Secondary button=btn btn-secondary
  Secondary button large=btn btn-secondary btn-lg
  Secondary button full-col-wide=btn btn-secondary btn-block
  Secondary button large col-wide=btn btn-secondary btn-lg btn-block
  RFI/Visit/Apply (RVA) button=btn btn-gold
  RVA button large=btn btn-gold btn-lg
  RVA button full-col-wide=btn btn-gold btn-block
  RVA button large col-wide=btn btn-gold btn-lg btn-block
  Explore Our Programs (EOP) button=btn btn-blue
  EOP button large=btn btn-blue btn-lg
  EOP button full-col-wide=btn btn-blue btn-block
  EOP button large col-wide=btn btn-blue btn-lg btn-block'; /* WAS: '' */
    $theme = variable_get('theme_default', '');
    if ($theme === 'college') {
      $data['panopoly_wysiwyg_text']['settings']['css_path'] = '%bprofiles/openasu/libraries/fontawesome/css/font-awesome.min.css,%bprofiles/openasu/modules/webspark_featurescustom/webspark_wysiwyg/css/webspark-wysiwyg.css,%bprofiles/openasu/themes/college/css/admin.css,%bprofiles/openasu/themes/college/css/nav.css,%bprofiles/openasu/themes/college/css/college.custom.css,%bprofiles/openasu/themes/college/css/college.media-rules.css';
    } else {
      $data['panopoly_wysiwyg_text']['settings']['css_path'] = '%bprofiles/openasu/libraries/innovation_bootstrap/css/bootstrap.min.css,%bprofiles/openasu/themes/innovation/css/innovation-main.css,%bprofiles/openasu/themes/innovation/css/buttons.css,%bprofiles/openasu/themes/innovation/css/forms.css,%bprofiles/openasu/themes/innovation/css/nav.css,%bprofiles/openasu/themes/innovation/fonts/roboto/css/roboto.css,%bprofiles/openasu/modules/webspark_featurescustom/webspark_wysiwyg/css/webspark-wysiwyg.css';
    }
    $data['panopoly_wysiwyg_text']['settings']['css_setting'] = 'self'; /* WAS: 'theme' */
    unset($data['panopoly_wysiwyg_text']['settings']['buttons']['default']['forecolor']);
    unset($data['panopoly_wysiwyg_text']['settings']['buttons']['default']['underline']);
    unset($data['panopoly_wysiwyg_text']['settings']['buttons']['paste']['pastetext']);
    unset($data['panopoly_wysiwyg_text']['settings']['buttons']['pdw']);
  }
}
