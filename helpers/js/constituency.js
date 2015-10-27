var regions_by_county = {}; // Set this value in PHP before using these functions
var EMPTY = "EMPTY"; // Value representing an empty option

function county_changed() {
	var county = $("#county").val();
	var region = (county in regions_by_county ? regions_by_county[county] : EMPTY);
	$("#region").val(region);
}

function region_changed() {
	var region = $("#region").val();
	var counties = filter_counties_by_region(region);
	var optionsAsString = "";
	for(var i = 0; i < counties.length; i++) {
		optionsAsString += "<option value=\'" + counties[i] + "\'>" + counties[i] + "</option>";
	}
	$("#county").find("option")
		.remove()
		.end()
		.append(optionsAsString);
}

function filter_counties_by_region(region) {
	if (region == EMPTY) {
		return Object.keys(regions_by_county);
	}
	var counties = [];
	for (var county in regions_by_county) {
		if (regions_by_county[county] == region)
			counties.push(county);
	}
	return counties;
}
