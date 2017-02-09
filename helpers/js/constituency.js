var county_name_and_region_by_id = {}; // Set this value in PHP before using these functions

function county_changed() {
	var county_id = $("#county_id").val();
	var region_id = (county_id in county_name_and_region_by_id) 
		? county_name_and_region_by_id[county_id].region_id 
		: 0;
	$("#region_id").val(region_id);
}

function region_changed() {
	var region_id = $("#region_id").val();
	var county_id = $("#county_id").val();
	var counties = filter_counties_by_region(region_id);
	var optionsAsString = "";
	for(var i = 0; i < counties.length; i++) {
		var county = counties[i];
		optionsAsString += "<option value=\'" + county['id'] + "\'>" + county['name'] + "</option>";
	}
	$("#county_id").find("option")
		.remove()
		.end()
		.append(optionsAsString);
}

function filter_counties_by_region(region_id) {
	if (region_id == 0)
		return Object.keys(county_name_and_region_by_id).map(function(key){
		    return county_name_and_region_by_id[key];
		});
	var counties = [];
	for (var county_id in county_name_and_region_by_id) {
		var county = county_name_and_region_by_id[county_id];
		if (county['region_id'] == region_id)
			counties.push(county);
	}
	return counties;
}

function set_default_county_if_region_set() {
	var selected_region = $("#region_id").val();
	if (selected_region && selected_region != 0)
		$("#county_id").val(0);
}
