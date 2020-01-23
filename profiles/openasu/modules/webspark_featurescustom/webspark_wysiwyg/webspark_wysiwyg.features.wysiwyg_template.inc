<?php
/**
 * @file
 * webspark_wysiwyg.features.wysiwyg_template.inc
 */

/**
 * Implements hook_wysiwyg_template_default_templates().
 */
function webspark_wysiwyg_wysiwyg_template_default_templates() {
  $templates = array();
  $templates['explore_programs_box'] = array(
    'title' => 'Explore Our Programs Box',
    'description' => 'Replace the button links and text with your own.',
    'weight' => 0,
    'fid' => 0,
    'format' => 'wysiwyg',
    'body' => '<div class="panel explore-programs"><div class="panel-body"><h3>Explore Our Programs</h3><p><a href="https://webapp4.asu.edu/programs/t5/undergrad" class="btn btn-blue btn-block">Undergraduate programs</a> <a href="https://webapp4.asu.edu/programs/t5/graduate/false" class="btn btn-blue btn-block">Graduate programs</a></p></div></div>',
    'name' => 'explore_programs_box',
    'content_types' => array(),
  );
  $templates['inline_columns_2'] = array(
    'title' => 'Two inline columns',
    'description' => 'Inserts a single row of TWO (2) self-contained columns, built on Bootstrap + HTML DIV tags. Replace the sample title and text in each column.',
    'weight' => 1,
    'fid' => 0,
    'body' => '<div class="row row-full wysiwyg-cols">
      <div class="column col-sm-12 col-md-6 col-lg-6 wysiwyg-cols-first">
        <h3>Sample column title</h3>
        <p>Delete this sample text and create your own content for this column. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent vel odio purus. Aenean ut leo bibendum, cursus ligula bibendum, lobortis erat. </p>
      </div>
      <div class="column col-sm-12 col-md-6 col-lg-6 wysiwyg-cols-last">
        <h3>Use the WYSIWYG if you want.</h3>
        <p>Delete this same text and create your own content. Quisque tempus viverra neque in auctor. Aliquam feugiat venenatis ullamcorper. Sed ac rhoncus enim, ac luctus justo. Etiam elementum, neque id commodo tristique, quam est mattis tellus, non semper turpis libero vehicula massa. Sed lobortis metus non orci rutrum varius. Quisque imperdiet bibendum dictum. Suspendisse vestibulum in elit vitae finibus. Donec quis vulputate augue. Fusce quis iaculis libero. Curabitur consectetur fermentum egestas. </p>
      </div>
    </div>',
    'name' => 'inline_columns_2',
    'content_types' => array(),
  );
  $templates['inline_columns_3'] = array(
    'title' => 'Three inline columns',
    'description' => 'Inserts a single row of THREE (3) self-contained columns, built on Bootstrap + HTML DIV tags. Replace the sample title and text in each column.',
    'weight' => 2,
    'fid' => 0,
    'body' => '<div class="row row-full wysiwyg-cols wysiwyg-cols-first">
      <div class="column col-sm-12 col-md-6 col-lg-4">
        <h3>Sample Column title</h3>
        <p>Sample text to replace with your own content for this column. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent vel odio purus. Aenean ut leo bibendum, cursus ligula bibendum, lobortis erat. </p>
      </div>
      <div class="column col-sm-12 col-md-6 col-lg-4">
        <h3>This uses Bootstrap + HTML DIV tags.</h3>
        <p>Take care to not delete any of the HTML tags while editing. Only edit the content. Phasellus ac lorem est. Ut enim orci, vehicula et enim nec, mollis porta tellus.</p>
      </div>
      <div class="column col-sm-12 col-md-6 col-lg-4 wysiwyg-cols-last">
        <h3>Use the WYSIWYG if you want.</h3>
        <p>>You should be able to use the WYSIWYG to replace this content with whatever is available in the WYSIWYG.</p>
      </div>
    </div>',
    'name' => 'inline_columns_3',
    'content_types' => array(),
  );
  $templates['inline_columns_4'] = array(
    'title' => 'Four inline columns',
    'description' => 'Inserts a single row of FOUR (4) self-contained columns, built on Bootstrap + HTML DIV tags. Replace the sample title and text in each column.',
    'weight' => 3,
    'fid' => 0,
    'body' => '
      <div class="row row-full wysiwyg-cols">
        <div class="column col-sm-12 col-md-6 col-lg-3 wysiwyg-cols-first">
          <h3>Sample Column title</h3>
          <p>Sample text to replace with your own content for this column. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent vel odio purus. Aenean ut leo bibendum, cursus ligula bibendum, lobortis erat. </p>
        </div>
        <div class="column col-sm-12 col-md-6 col-lg-3">
          <h3>This uses Bootstrap + HTML DIV tags.</h3>
          <p>Take care to not delete any of the HTML tags while editing. Only edit the content. Phasellus ac lorem est. Ut enim orci, vehicula et enim nec, mollis porta tellus.</p>
        </div>
        <div class="column col-sm-12 col-md-6 col-lg-3">
          <h3>Use the WYSIWYG if you want.</h3>
          <p>>You should be able to use the WYSIWYG to replace this content with whatever is available in the WYSIWYG.</p>
        </div>
        <div class="column col-sm-12 col-md-6 col-lg-3 wysiwyg-cols-last">
          <p><strong>IMPORTANT: </strong>Take care to not delete any of the HTML tags while editing. Only edit the content. Phasellus ac lorem est. Ut enim orci, vehicula et enim nec, mollis porta tellus.</p>
        </div>
      </div>',
    'name' => 'inline_columns_4',
    'content_types' => array(),
  );
  $templates['inline_columns_6'] = array(
    'title' => 'Six inline columns',
    'description' => 'Inserts a single row of FOUR (4) self-contained columns, built on Bootstrap + HTML DIV tags. Replace the sample title and text in each column.',
    'weight' => 4,
    'fid' => 0,
    'body' => '
      <div class="row row-full wysiwyg-cols">
        <div class="column col-sm-12 col-md-4 col-lg-2 wysiwyg-cols-first">
          <h3>Sample column title</h3>
          <p>Sample text to replace with your own content for this column. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent vel odio purus. Aenean ut leo bibendum, cursus ligula bibendum, lobortis erat. </p>
        </div>
        <div class="column col-sm-12 col-md-4 col-lg-2">
          <h3>This uses Bootstrap + HTML DIV tags.</h3>
          <p>Take care to not delete any of the HTML tags while editing. Only edit the content. Phasellus ac lorem est. Ut enim orci, vehicula et enim nec, mollis porta tellus.</p>
        </div>
        <div class="column col-sm-12 col-md-4 col-lg-2">
          <h3>Use the WYSIWYG if you want.</h3>
          <p>>You should be able to use the WYSIWYG to replace this content with whatever is available in the WYSIWYG.</p>
        </div>
        <div class="column col-sm-12 col-md-4 col-lg-2">
          <p>Take care to not delete any of the HTML tags while editing. Only edit the content. Phasellus ac lorem est. Ut enim orci, vehicula et enim nec, mollis porta tellus.</p>
        </div>
        <div class="column col-sm-12 col-md-4 col-lg-2">
          <p><strong>OPTIONAL:</strong> Use "Full HTML" to edit the layout.</p>
          <p>Only do this if you know what you are doing. If you screw up the HTML, you will have to know how to manually fix it or you will be starting over with your edits.</p>
        </div>
        <div class="column col-sm-12 col-md-4 col-lg-2 wysiwyg-cols-last">
          <h3>Optional title - Delete me</h3>
          <p>Delete this same text and create your own content. Quisque tempus viverra neque in auctor. Aliquam feugiat venenatis ullamcorper. Sed ac rhoncus enim, ac luctus justo. Etiam elementum, neque id commodo tristique, quam est mattis tellus, non semper.</p>
        </div>
      </div>',
    'name' => 'inline_columns_6',
    'content_types' => array(),
  );
  return $templates;
}
