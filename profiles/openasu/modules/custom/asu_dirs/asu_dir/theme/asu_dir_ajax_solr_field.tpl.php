<?php
/**
 * Theme template for new Ajax-Solr enabled search
 *
 * @author Colton Testamarck
 */
?>

<div class="field-type-asu-directory" id="asu_dir<?php echo $id; ?>">

  <?php if ($items[0]['directory_config']['show_breadcrumbs']): ?>
      <div class="row">
          <div
                  class="asu-dir-breadcrumb<?php echo $id; ?> dir-breadcrumb col-md-12 <?php echo $dir_classes['dir_row_full']; ?>"></div>
      </div>
  <?php endif; ?>

    <div class="row asu-dir-selections">
        <div class="col-md-12 <?php echo $dir_classes['dir_row_full']; ?>">

            <div id="asu-dir-selection-wrapper<?php echo $id; ?>">
                <span class="breadcrumb">People</span>
                <span id="asu-dir-ajax-solr-selections<?php echo $id; ?>"></span>
            </div>
        </div>
    </div>

    <div class="row">
      <?php if ($configs['show_tree']): ?>
        <div class="col-md-4">
            <div class="asu-directory-tree-hierarchy">
                <div id="treediv<?php echo $id; ?>" class="treediv">
                </div>
            </div>
        </div>
        <div class="col-md-8">
          <?php else: ?>
            <div class="col-md-12">
              <?php endif; ?>

                <!--FILTER CONTAINER-->
              <?php if ($configs['show_filters']): ?>
                  <div class="asu-dir-search row">
                      <!--<div class="col-md-4"><select id="primaryTitleFacet"><option value="0">Primary Title</option></select></div> // Comment this out for now -->

                      <!-- DROPDOWN FILTER CONTAINER -->
                      <div
                              class="<?php echo $dir_classes['dir_dropdown']; ?> dir-dropdowns">
                          <div class="row">
                              <div class="col-md-6">
                                <?php if ($configs['show_filter_expertise']): ?>
                                    <div class="form-type-select">
                                        <select
                                                title="Expertise Areas"
                                                id="expertiseAreasFacet<?php echo $id; ?>"
                                                class="facet-widget">
                                            <option value="0">Expertise Areas
                                            </option>
                                        </select>
                                    </div>
                                <?php endif; ?>
                              </div>
                              <div class="col-md-6">
                                <?php if ($configs['show_filter_faculty_titles']): ?>
                                    <div class="form-type-select">
                                        <select
                                                title="Faculty Titles"
                                                id="facultyTitlesFacet<?php echo $id; ?>"
                                                class="facet-widget">
                                            <option value="0">Faculty Titles
                                            </option>
                                        </select>
                                    </div>
                                <?php endif; ?>
                              </div>
                          </div>
                      </div>
                      <!-- END DROPDOWN FILTER CONTAINER -->


                      <div id="asu-dir-ajax-solr-search<?php echo $id; ?>"
                           class="<?php echo $dir_classes['search']; ?> dir-search">
                        <?php if ($configs['show_filter_omni']): ?>
                            <input title="Search"
                                   class="input-main-search form-control form-text required"
                                   placeholder="Search" type="text"
                                   id="edit-keys<?php echo $id; ?>" name="keys"
                                   size="15" maxlength="128"/>
                            <button class="asu_dir_people_search_btn btn-main-search btn"
                                    value="
                <i class=&quot;fa fa-search&quot; aria-hidden=&quot;true&quot;></i>"
                                    type="submit">
                                <i class="fa fa-search"
                                   aria-hidden="true"></i><span
                                        class="asu-dir-hidden">Search</span>
                            </button>
                        <?php endif; ?>

                          <div id="asu-dir-ajax-solr-sort<?php echo $id; ?>">
                              Sort: &nbsp;<span class="asu-dir-sort-item"
                                                id="dir-firstNameSort<?php echo $id; ?>">First Name </span>
                              &nbsp; | &nbsp;
                              <span class="asu-dir-sort-item"
                                    id="dir-lastNameSort<?php echo $id; ?>">Last Name </span>

                            <?php if (!$configs['hide_filter_rank_sort']): ?>
                                &nbsp; | &nbsp;
                                <span class="asu-dir-sort-item"
                                      id="dir-rankSort<?php echo $id; ?>">Rank </span>
                            <?php endif; ?>
                          </div>
                      </div>
                  </div>
              <?php endif; ?>

              <?php if ($items[0]['directory_config']['show_az_index']): ?>
                  <div id="ajax-solr-alpha-bar<?php echo $id; ?>"
                       class="asu-dir-alpha-bar row">
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
                          <li>ALL</li>
                      </ul>
                  </div>
              <?php endif; ?>

              <?php print theme('asu_dir_ajax_solr_people', array(
                'items' => $items,
                'settings' => $settings
              )); ?>

            </div>

        </div>
    </div>