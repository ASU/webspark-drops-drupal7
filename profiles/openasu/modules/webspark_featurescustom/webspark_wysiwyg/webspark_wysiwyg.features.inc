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
    $data['panopoly_html_text']['settings']['block_formats'] = 'p,h2,h3,h4,h5,h6'; /* WAS: 'h1,h2,h3,h4,h5,h6' */
    $data['panopoly_html_text']['settings']['buttons']['linkit'] = array(
      'linkit' => 1,
    ); /* WAS: '' */
    $data['panopoly_html_text']['settings']['show_toggle'] = 1; /* WAS: 0 */
    $data['panopoly_html_text']['settings']['user_choose'] = 1; /* WAS: 0 */
    unset($data['panopoly_html_text']['settings']['buttons']['default']['link']);
    unset($data['panopoly_html_text']['settings']['buttons']['default']['stroke']);
  }
  if (isset($data['panopoly_wysiwyg_text'])) {
    $data['panopoly_wysiwyg_text']['settings']['block_formats'] = 'p,h2,h3,h4,h5,h6'; /* WAS: 'h1,h2,h3,h4,h5,h6' */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['default']['anchor'] = 1; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['default']['hr'] = 1; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['default']['styleselect'] = 1; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['table'] = array(
      'tablecontrols' => 1,
    ); /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['template'] = array(
      'template' => 1,
    ); /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['css_classes'] = 'Lead paragraph=lead-paragraph
        Bordered table=bordered
        Image align left=pull-left
        Image align right=pull-right
        Oval image=img-circle
        Image with rounded corners=img-rounded
        Image with double-border=img-thumbnail
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
    $data['panopoly_wysiwyg_text']['settings']['css_path'] = '%b%t/css/innovation-main.css,%b%t/css/buttons.css,%b%t/css/forms.css,%b%t/css/nav.css,%b%t/fonts/roboto/css/roboto.css'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['css_setting'] = 'self'; /* WAS: 'theme' */
    $data['panopoly_wysiwyg_text']['settings']['show_toggle'] = 1; /* WAS: 0 */
    $data['panopoly_wysiwyg_text']['settings']['user_choose'] = 1; /* WAS: 0 */
    unset($data['panopoly_wysiwyg_text']['settings']['buttons']['default']['forecolor']);
    unset($data['panopoly_wysiwyg_text']['settings']['buttons']['default']['underline']);
    unset($data['panopoly_wysiwyg_text']['settings']['buttons']['paste']['pastetext']);
    unset($data['panopoly_wysiwyg_text']['settings']['buttons']['pdw']);
    unset($data['panopoly_wysiwyg_text']['settings']['buttons']['spellchecker']);
  }
}
