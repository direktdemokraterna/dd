var session_too_old_message = '';
var is_session_active = false;

function set_user_code(json) {
	sessionStorage.user_code = json.user_code;
}

function failed_to_set_user_code() {
	alert(session_too_old_message);
}

function set_language(lang) {
	var qsign = window.location.href.indexOf('?') >= 0
		? '&'
		: '?';
	window.location.href=window.location.href + qsign + 'lang=' + lang;
}
