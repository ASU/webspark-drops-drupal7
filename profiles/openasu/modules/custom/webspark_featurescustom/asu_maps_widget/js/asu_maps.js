//https://maps.googleapis.com/maps/api/js?v=3.12&sensor=true&libraries=places,drawing&key=AIzaSyCM63RtfDMkEhFpz6TfXLmW1QKzRF3cBz8
function initialize() {
	//static lat,lng
	var myLatLng = new google.maps.LatLng(33.42184849843031, -111.9283177883301);
	//custom map options
	var mapOptions = {
		center: myLatLng,
		zoom: 17,
		panControl: false,
		zoomControl: true,
		zoomControlOptions: {
			style: google.maps.ZoomControlStyle.SMALL,
			position: google.maps.ControlPosition.RIGHT_BOTTOM
		},
		mapTypeControl: false,
		scaleControl: false,
		streetViewControl: false,
		overviewMapControl: false
	};
	//add map to div asu_map
	var map = new google.maps.Map(document.getElementById("asu_map"), mapOptions);
	//overlay options | DO NOT EDIT
	var overlay = new google.maps.ImageMapType({
		getTileUrl: function(coord, zoom) {
			// Define locals
			var ymax, y, overlayName, path, url;
			// Our tiles use the TMS coordinate system, which has the y coord flipped from default Google
			// This flips the y coord value that Google passes us
			ymax = 1 << zoom;
			y = ymax - coord.y - 1;
			// Create the tile URL
			// Sample URL: http://assets.concept3dinc.netdna-cdn.com/assets/120/MasterOverlay7/16/12393/39230.png
			overlayName = 'MasterOverlay7';
			path = 'assets/120/' + overlayName + '/' +
				zoom + '/' + coord.x + '/' + y + '.png';
			url = 'http://assets.concept3dinc.netdna-cdn.com/' + path;
			return url;
		},
		tileSize: new google.maps.Size(256, 256)
	});
	//add overlay to map
	map.overlayMapTypes.push(overlay);
	//marker options + add marker to map
	var marker = new google.maps.Marker({
		position: myLatlng,
		map: map,
		title: 'Hello World!'
	});
}
google.maps.event.addDomListener(window, 'load', initialize);