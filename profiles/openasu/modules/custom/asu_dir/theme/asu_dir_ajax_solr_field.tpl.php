<?php
/**
 * Theme template for new Ajax-Solr enabled search
 *
 * @author Colton Testamarck
 */
?>

<div class="field-type-asu-directory">

  <?php if ($items[0]['directory_config']['show_breadcrumbs']): ?>
    <div class="row">
      <div class="asu_directory_breadcrumb col-md-12"></div>
    </div>
  <?php endif; ?>

  <div class="row asu-dir-selections">
    <div class="col-md-12">

      <div id="asu-dir-selection-wrapper">
        <span class="breadcrumb">People ></span>
        <span id="asu-dir-ajax-solr-selections"></span>
      </div>
    </div>
  </div>


  <div class="row">
    <?php if ($items[0]['directory_config']['show_tree']): ?>
    <div class="col-md-4">
      <div class="asu-directory-tree-hierarchy">
        <div id="treediv">
        </div>
      </div>
    </div>
    <div class="col-md-8">
      <?php else: ?>
      <div class="col-md-12">
        <?php endif; ?>


        <div class="asu-dir-search row">
          <!--<div class="col-md-4"><select id="primaryTitleFacet"><option value="0">Primary Title</option></select></div> // Comment this out for now -->
          <div class="col-md-8 form-type-select">
            <select title="Expertise Areas" id="expertiseAreasFacet" class="facet-widget">
              <option value="0">Expertise Areas</option>
              asu
            </select></div>

          <div id="asu-dir-ajax-solr-search" class="col-md-4">
n-search form-control form-text required" placeholder="Search" type="text" id="edit-keys" name="keys" size="15" maxlength="128"/>
            <button class="asu_dir_people_search_btn btn-main-search btn"
                    value="
              <i class=&quot;fa fa-search&quot; aria-hidden=&quot;true&quot;></i>"
                    type="submit">
              <i class="fa fa-search" aria-hidden="true"></i><span
                class="asu-dir-hidden">Search</span></button>

            <div id="asu-dir-ajax-solr-sort">
              Sort By: &nbsp;<span class="asu-dir-sort-item" id="dir-lastNameSort">Last Name </span>
              &nbsp; | &nbsp;
              <span class="asu-dir-sort-item" id="dir-rankSort">Rank </span>
            </div>
          </div>
        </div>


        <div id="ajax-solr-alpha-bar" class="asu-dir-alpha-bar row">
          <ul class="alphabet">
            <li>A</li>
            <li>B</li>
            <li>C</li>
            <li>D</li>
            <li>E</li>
            <li>F</li>
            <li>G</li>
            <li>H</li>
            <li>I</li>
            <li>J</li>
            <li>K</li>
            <li>L</li>
            <li>M</li>
            <li>N</li>
            <li>O</li>
            <li>P</li>
            <li>Q</li>
            <li>R</li>
            <li>S</li>
            <li>T</li>
            <li>U</li>
            <li>V</li>
            <li>W</li>
            <li>X</li>
            <li>Y</li>
            <li>Z</li>
          </ul>
        </div>

        <?php print theme('asu_dir_ajax_solr_people', array(
          'items' => $items,
          'settings' => $settings
        )); ?>
      </div>

    </div>

  </div>

</div>