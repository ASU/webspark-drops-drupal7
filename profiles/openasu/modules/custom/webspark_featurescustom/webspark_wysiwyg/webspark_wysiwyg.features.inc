<?php
/**
 * @file
 * webspark_wysiwyg.features.inc
 */

/**
 * Implements hook_filter_default_formats_alter().
 */
function webspark_wysiwyg_filter_default_formats_alter(&$data) {
  if (isset($data['panopoly_wysiwyg_text'])) {
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['valid_elements'] = 'a[!href|target<_blank|title|style|class],
    
            div[style|class|align<center?justify?left?right],
    
            br,em,i,strong,cite,code,blockquote,ul,ol,li,dl,dt,dd,
    
            table[style|class],thead,th,tbody,tr,td,
    
            span[style],p[style|class],
    
            h1[style|class],h2[style|class],h3[style|class],h4[style|class],h5[style|class],h6[style|class],
    
            img[!src|title|alt|style|width|height|class|hspace|vspace],
    
            @[style|class],#p,
    
            buttton[style|class]'; /* WAS: 'a[!href|target<_blank|title|style|class],
    div[style|class|align<center?justify?left?right],
    br,em,i,strong,cite,code,blockquote,ul,ol,li,dl,dt,dd,
    span[style],p[style|class],
    h1[style|class],h2[style|class],h3[style|class],h4[style|class],h5[style|class],h6[style|class],
    img[!src|title|alt|style|width|height|class|hspace|vspace],
    @[style|class]' */
  }
}

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
  if (isset($data['panopoly_wysiwyg_text'])) {
    $data['panopoly_wysiwyg_text']['settings']['buttons']['default']['styleselect'] = 1; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['table'] = array(
      'tablecontrols' => 1,
    ); /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['buttons']['template'] = array(
      'template' => 1,
    ); /* WAS: '' */
    $data['panopoly_wysiwyg_text']['settings']['css_classes'] = 'Image align left=pull-left
        Image align right=pull-right
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
    unset($data['panopoly_wysiwyg_text']['settings']['buttons']['default']['underline']);
    unset($data['panopoly_wysiwyg_text']['settings']['buttons']['pdw']);
    unset($data['panopoly_wysiwyg_text']['settings']['buttons']['spellchecker']);
  }
}
