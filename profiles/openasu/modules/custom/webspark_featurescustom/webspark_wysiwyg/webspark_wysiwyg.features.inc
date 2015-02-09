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
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][0] = 'a*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][10] = 'f*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][100] = 'Y*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][102] = 'Z*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][12] = 'g*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][14] = 'h*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][16] = 'i*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][18] = 'j*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][2] = 'b*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][20] = 'k*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][22] = 'l*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][24] = 'm*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][26] = 'n*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][28] = 'o*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][30] = 'p*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][32] = 'q*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][34] = 'r*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][36] = 's*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][38] = 't*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][4] = 'c*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][40] = 'u*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][42] = 'v*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][44] = 'w*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][46] = 'x*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][48] = 'y*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][50] = 'z*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][52] = 'A*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][54] = 'B*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][56] = 'C*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][58] = 'D*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][6] = 'd*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][60] = 'E*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][62] = 'F*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][64] = 'G*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][66] = 'H*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][68] = 'I*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][70] = 'J*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][72] = 'K*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][74] = 'L*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][76] = 'M*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][78] = 'N*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][8] = 'e*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][80] = 'O*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][82] = 'P*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][84] = 'Q*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][86] = 'R*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][88] = 'S*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][90] = 'T*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][92] = 'U*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][94] = 'V*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][96] = 'W*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['rule_valid_ids'][98] = 'X*'; /* WAS: '' */
    $data['panopoly_wysiwyg_text']['filters']['wysiwyg']['settings']['valid_elements'] = 'a[href|target<_blank|title|style|class|id],
    div[style|class|align<center?justify?left?right],
    br,em,i,strong,cite,code,blockquote,ul,ol,li,dl,dt,dd,
    table[style|class],thead,th,tbody,tr,td,
    span[style],p[style|class],
    h1[style|class],h2[style|class],h3[style|class],h4[style|class],h5[style|class],h6[style|class],
    img[!src|title|alt|style|width|height|class|hspace|vspace],
    @[style|class],#p,&nbsp;
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
    $data['panopoly_wysiwyg_text']['settings']['css_classes'] = 'Image align left=pull-left
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
    $data['panopoly_wysiwyg_text']['settings']['css_path'] = '%b%t/css/innovation-main.css,%b%t/css/grid.css,%b%t/css/buttons.css,%b%t/css/forms.css,%b%t/css/nav.css,%b%t/fonts/roboto/css/roboto.css'; /* WAS: '' */
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
