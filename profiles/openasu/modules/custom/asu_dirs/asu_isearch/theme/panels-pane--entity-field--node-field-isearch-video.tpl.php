<?php

/**
 * @file field.tpl.php
 * Default template implementation to display the value of a field.
 *
 * This file is not used and is here as a starting point for customization only.
 * @see theme_field()
 *
 * Available variables:
 * - $items: An array of field values. Use render() to output them.
 * - $label: The item label.
 * - $label_hidden: Whether the label display is set to 'hidden'.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - field: The current template type, i.e., "theming hook".
 *   - field-name-[field_name]: The current field name. For example, if the
 *     field name is "field_description" it would result in
 *     "field-name-field-description".
 *   - field-type-[field_type]: The current field type. For example, if the
 *     field type is "text" it would result in "field-type-text".
 *   - field-label-[label_display]: The current label position. For example, if
 *     the label position is "above" it would result in "field-label-above".
 *
 * Other variables:
 * - $element['#object']: The entity to which the field is attached.
 * - $element['#view_mode']: View mode, e.g. 'full', 'teaser'...
 * - $element['#field_name']: The field name.
 * - $element['#field_type']: The field type.
 * - $element['#field_language']: The field language.
 * - $element['#field_translatable']: Whether the field is translatable or not.
 * - $element['#label_display']: Position of label display, inline, above, or
 *   hidden.
 * - $field_name_css: The css-compatible field name.
 * - $field_type_css: The css-compatible field type.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 *
 * @see template_preprocess_field()
 * @see theme_field()
 *
 * @ingroup themeable
 */
?>

<?php if (count($items) == 1) { ?>

    <div class="<?php print $classes; ?>"<?php print $attributes; ?>>
        <?php if (!$label_hidden): ?>
            <h2 class="pane-title"<?php print $title_attributes; ?>><?php print $title ?></h2>
        <?php endif; ?>
        <div class="field-items"<?php print $content_attributes; ?>>
            <?php foreach ($items as $delta => $item): ?>
                <div class="field-item <?php print $delta % 2 ? 'odd' : 'even'; ?>"><?php print render($item); ?></div>
            <?php endforeach; ?>
        </div>
    </div>

<?php } else { ?>

    <div class="<?php print $classes; ?>"<?php print $attributes; ?>>
      <?php if (!$label_hidden): ?>
          <h2 class="pane-title"<?php print $title_attributes; ?>><?php print $title ?></h2>
      <?php endif; ?>
        <div class="field-items"<?php print $content_attributes; ?>>
            <div id="carouselHomepage" class="carousel slide row" data-ride="carousel">
                <div class="carousel-inner">
                    <?php $i = -1; ?>
                    <?php foreach ($items as $item): ?>
                        <?php $i++; ?>
                        <div class="item <?php if ($i == 0) {print "active";} ?>">
                            <div class="col-sm-6 car-vid-wrap">
                                <?php print theme('video_embed_field_embed_code', array('url' => $item[0]['#url'], 'style' => 'normal')); ?>
                            </div>
                            <div class="col-sm-6">
                                <a href="<?php print render($item[0]['#url']); ?>"><?php if ($item[0]['#video_data']['handler'] == 'vimeo') {print render($item[0]['#video_data']['title']);} else {print render($item[0]['#video_data'][0]['snippet']['title']);} ?></a>
                                <?php print render($item['#suffix']); ?>
                            </div>
                        </div><!-- /.item -->
                    <?php endforeach; ?>
                </div><!-- /.carousel-inner -->
                <!-- Controls -->
                <div class='col-md-12 carousel-nav'>
                    <ul class='pager carousel-nav'>
                        <li class='previous'><a data-slide='prev' href='#carouselHomepage'><i class='fa fa-angle-left' aria-hidden='true'></i> Previous Video</a></li>
                        <li class='next'><a data-slide='next' href='#carouselHomepage'>Next Video <i class='fa fa-angle-right' aria-hidden='true'></i></a></li>
                    </ul>
                </div>
            </div>
        </div>
    </div>
<?php } ?>