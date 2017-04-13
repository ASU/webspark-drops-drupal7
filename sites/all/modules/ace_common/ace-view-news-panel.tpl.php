<?php
/**
 * @file ace-view-news-panel.tpl.php
 * The news panel view style plugin.
 *
 * @ingroup views_templates
 */
?>

<div class="news-panel clearfix">
	<div class="title clearfix">
		<img src="sites/all/modules/ace/ace_common/images/planet.png" />
	 	<div class="inner">
	 		<h1>ACE BROADCASTING:</h1>
	 		<span>Fulfilling our mission to enrich AEC Professionals</span>
	 	</div>
	</div>
	
	<?php foreach ($rows as $id => $row): ?>
		<?php print theme('ace_news_item', node_load($row->nid)); ?>
    <?php endforeach; ?>
</div>