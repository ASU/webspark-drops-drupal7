/*
 * Functionality for the course listing tables.
 * This file allows users to click the title of the 
 * course to cause the course description to show
 * beneath that row.
 */
$(document).ready(function() {
	var productTables = $("table.products");
	
	// Remove title links
	productTables.find("tr td.title a").each(function() {
		var title = $(this).html();
		$(this).parent("td").html(title);
	});
	
	// Setup tablesorter
	if (productTables.find("th.category").length) {
		productTables.tablesorter({ 
			widgets: ['zebra'],
			headers: {
				3: { sorter: false },
				4: { sorter: false },
				5: { sorter: false },
			},
			sortList: [[0,0]],
		});
	} else {
		productTables.tablesorter({ 
			widgets: ['zebra'],
			headers: {
				2: { sorter: false },
				3: { sorter: false },
				4: { sorter: false },
			},
			sortList: [[0,0]],
		});
	}
	productTables.addClass("tablesorter");
	
	// Set up row highlighting and clicking to show/hide
	var i = 0;
	productTables.each(function() {
		var tableClass = "product-table-" + i;
		$(this)
			// Add a class to distinguish this table.
			.addClass(tableClass)
			// Set up row expansion and highlights for standard rows.
			.find("tbody tr")
				.hover(function() {
					$(this).addClass("highlighted");
					if ($(this).hasClass("expanded")) {
						$(this).next().addClass("highlighted");
					}
				}, function() {
					$(this).removeClass("highlighted");
					if ($(this).hasClass("expanded")) {
						$(this).next().removeClass("highlighted");
					}
				}).click(function() { 
					toggleDetails($(this), tableClass);
				}).addClass("expandable")
			.end()
			// When clicking a sort header, hide all details rows for this table.
			.find("thead th.header")
				.click(function() {
					hideDetails(null, tableClass);
				})
			.end()
			// Set up row expansion and highlights for details rows.
			.next("div.product-details-hidden")
				.find("tr.details")
					.addClass("highlighted")
					.hover(function() {
						$(this).addClass("highlighted").prev().addClass("highlighted");
					}, function() {
						$(this).removeClass("highlighted").prev().removeClass("highlighted");
					}).click(function() { 
						hideDetails($(this), tableClass); 
					});
		i++;
	});
	
	// Stop a click on in-table links from resulting in show/hide details.
	$("table.products a").add("div.product-details-hidden a")
		.click(function(event) { event.stopPropagation(); });
	
	// Do descending sort if that's the desired default.
	productTables.each(function() {
		if ($(this).hasClass("descendingSort")) {
			$(this).trigger("sorton", [[[0,1]]]);
		}
	});
});

function toggleDetails(row, tableClass) {
	if (row.hasClass("expanded")) {
		hideDetails(row, tableClass);
	} else {
		showDetails(row, tableClass);
	}
}

function showDetails(row, tableClass) {
	var cac = row.attr("id");
	var detailsRow = $("table." + tableClass + " + div").find("tr#details_" + cac).clone(true);
	if (row.hasClass("odd")) {
		detailsRow.addClass("odd").removeClass("even");
	} else {
		detailsRow.addClass("even").removeClass("odd");
	}
	detailsRow.find("a.file.jqModal").each(function() {
		$("#jqmFileTarget").jqmAddTrigger(this);
	});
	row.after(detailsRow);
	row.addClass("expanded");
}

function hideDetails(row, tableClass) {
	if (row != null && row.hasClass("details")) {
		row.prev().removeClass("expanded").removeClass("highlighted");
		row.remove();
	} else if (row != null) {
		row.removeClass("expanded");
		row.next().remove();
	} else {
		// Hide all
		$("table.products." + tableClass)
			.find("tbody tr.details").remove()
			.end()
			.find("tbody tr.expanded").removeClass("expanded");
	}
}