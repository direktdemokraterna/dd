var session_too_old_message = '';
var is_session_active = false;

function set_user_code(json) {
	sessionStorage.user_code = json.user_code;
}

function failed_to_set_user_code() {
	alert(session_too_old_message);
}

function set_control_parameter(param_name, value) {
	var qsign = window.location.href.indexOf('?') >= 0
		? '&'
		: '?';
	window.location.href=window.location.href + qsign + param_name + '=' + value;
}

function set_language(lang) {
	set_control_parameter('lang', lang);
}

function set_acting_as_delegate(value) {
	set_control_parameter('act_as_delegate', value);
}
