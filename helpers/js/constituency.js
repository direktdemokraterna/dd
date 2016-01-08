var regions_by_county = {}; // Set this value in PHP before using these functions

function county_changed() {
	var county_id = $("#county").val();
	var region_id = (county_id in regions_by_county ? regions_by_county[county_id] : 0);
	$("#region").val(region_id);
}

function region_changed() {
	var region_id = $("#region").val();
	var counties = filter_counties_by_region(region_id);
	var optionsAsString = "";
	for(var i = 0; i < counties.length; i++) {
		optionsAsString += "<option value=\'" + counties[i] + "\'>" + counties[i] + "</option>";
	}
	$("#county").find("option")
		.remove()
		.end()
		.append(optionsAsString);
}

function set_default_county_if_region_set() {
	var selected_region = $("#region").val();
	if (selected_region && selected_region != 0)
		$("#county").val(0);			
}

function filter_counties_by_region(region_id) {
	if (region_id == 0)
		return Object.keys(regions_by_county);
	var counties = [];
	for (var county_id in regions_by_county)
		if (regions_by_county[county_id] == region_id)
			counties.push(county_id);
	return counties;
}
