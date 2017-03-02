function validateMedianValue(valueFieldName, submitButtonName) {
	var valueField = $("#" + valueFieldName);
	var submitButton = $("#" + submitButtonName);
	var value = valueField[0].value;
	var isValid = $.isNumeric(value);
	submitButton[0].disabled = !isValid;
	if (isValid)
		valueField.removeClass("invalidInput");	
	else
		valueField.addClass("invalidInput");	
}