$(document).ready(function() {
	$("input#checkout").click(function() {
		var form = $(this).parents("form").get(0);
		var checked = $(form).find("input[name=accept_terms]").is(":checked");
		var newpage = ($(form).find("input[name=new-page]").val() == "true");
		if (checked) {
			if (newpage) {
				$(form).attr("target", "_blank");
				setTimeout("location.reload(true);", 2000);
			}
			return true;
		} else {
			alert('You must accept the terms of the ACE Cancellation Policy.');
			return false;
		}
	});
	$("input#updatecart").click(function() {
		var form = $(this).parents("form").get(0);
		$(form).attr("method", "POST");
	});
	$(".two-carts-info a").simpletip({
		content: 'Loading...',
		onBeforeShow: function() {
			this.load('/ajax-description?path=page/why-two-carts');
		}
	});
});