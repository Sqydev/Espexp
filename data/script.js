function updateSliderValR(val) {
	document.getElementById("valueR").innerText = val;
}

function updateSliderValG(val) {
	document.getElementById("valueG").innerText = val;
}

function updateSliderValB(val) {
	document.getElementById("valueB").innerText = val;
}

function sendValueR() {
	// Update val to slider val
	const val = document.getElementById("sliderR").value;
	// Oh, so that chainges your url to /slider?value=${val} and than cpp catches that
	fetch(`/sliderR?value=${val}`);
}

function sendValueG() {
	// Update val to slider val
	const val = document.getElementById("sliderG").value;
	// Oh, so that chainges your url to /slider?value=${val} and than cpp catches that
	fetch(`/sliderG?value=${val}`);
}

function sendValueB() {
	// Update val to slider val
	const val = document.getElementById("sliderB").value;
	// Oh, so that chainges your url to /slider?value=${val} and than cpp catches that
	fetch(`/sliderB?value=${val}`);
}
