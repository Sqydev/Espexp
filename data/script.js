function updateSliderVal(val) {
	document.getElementById("value").innerText = val;
}

function sendValue() {
	// Oh, so that chainges your url to /slider?value=${val} and than cpp catches that
	fetch(`/slider?value=${val}`);
}
