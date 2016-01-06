var session_too_old_message = '';
var is_session_active = false;

function set_user_codes(user_codes) {
	sessionStorage.active_user_code = user_codes.active_user_code;
	sessionStorage.passive_user_code1 = user_codes.passive_user_code1;
	sessionStorage.passive_user_code2 = user_codes.passive_user_code2;
	sessionStorage.passive_user_code3 = user_codes.passive_user_code3;		
}

function failed_to_set_user_codes() {
	alert(session_too_old_message);
}

function set_language(lang) {
	var qsign = window.location.href.indexOf('?') >= 0
		? '&'
		: '?';
	window.location.href=window.location.href + qsign + 'lang=' + lang;
}
