<?php
/**
 * @file ace-view-accordion.tpl.php
 * Basic accordion style plugin for views.
 *
 * @ingroup views_templates
 */
  $nodes = array();
  foreach ($view->result as $resultNode) {
    $nodeObj = node_load($resultNode->nid);
    $nodes[] = array(
      'title' => ace_labelfy($nodeObj->title),
      'content' => '',
      'selected' => false,
      'type' => $nodeObj->type,
    );
  }
  
  foreach ($rows as $i => $row) { 
    $nodes[$i]['content'] = theme('ace_accordion_content', node_load($row->nid));
  }
  
  $nodes[0]['selected'] = true;
?>

<script type="text/javascript">
  $(document).ready(function() {
  	$(".tabs .tab[id^=tab_menu]").click(function() {
  	    var curMenu=$(this);
  	    $(".tabs .tab[id^=tab_menu]").removeClass("selected");	    
  	    curMenu.addClass("selected");
  		
  	    var index = curMenu.attr("id").split("tab_menu_")[1];
  	    $(".curvedContainer .tabcontent").css("display", "none");
  	  	var $tabContent = $(".curvedContainer #tab_content_"+index);
		$tabContent.css("display", "block");
		
		var $livestreamVid = $tabContent.find("iframe.livestream");
		$livestreamVid.attr('src', $livestreamVid.attr('src')); // Force livestream vid to reload on tab switch.
  	});
  });
</script>

<?php print theme('ace_accordion', $nodes); ?>
