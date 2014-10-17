<?php
/**
 * @file
 * webspark_wysiwyg.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function webspark_wysiwyg_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: filter
  $overrides["filter.panopoly_wysiwyg_text.filters|wysiwyg|settings|valid_elements"] = 'a[!href|target<_blank|title|style|class],
      div[style|class|align<center?justify?left?right],
      br,em,i,strong,cite,code,blockquote,ul,ol,li,dl,dt,dd,
      table[style|class],thead,th,tbody,tr,td,
      span[style],p[style|class],
      h1[style|class],h2[style|class],h3[style|class],h4[style|class],h5[style|class],h6[style|class],
      img[!src|title|alt|style|width|height|class|hspace|vspace],
      @[style|class],#p,
      buttton[style|class]';

  // Exported overrides for: image
  $overrides["image.wysiwyg_template_thumbnail.label"] = 'wysiwyg_template_thumbnail';

  // Exported overrides for: wysiwyg
  $overrides["wysiwyg.panopoly_wysiwyg_text.settings|buttons|default|styleselect"] = 1;
  $overrides["wysiwyg.panopoly_wysiwyg_text.settings|buttons|default|underline"]["DELETED"] = TRUE;
  $overrides["wysiwyg.panopoly_wysiwyg_text.settings|buttons|table"] = array(
    'tablecontrols' => 1,
  );
  $overrides["wysiwyg.panopoly_wysiwyg_text.settings|buttons|template"] = array(
    'template' => 1,
  );
  $overrides["wysiwyg.panopoly_wysiwyg_text.settings|css_classes"] = 'Image align left=pull-left
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
  EOP button large col-wide=btn btn-blue btn-lg btn-block';

 return $overrides;
}
