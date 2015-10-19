function ensureUserCodes(url, user_id, temp_code) {
	if (sessionStorage.active_user_code ? false : true)
		updateUserCodes(url, user_id, temp_code);
}

function updateUserCodes(url, user_id, temp_code) {
	make_ajax_call(url + "receive_temp_code.php?user_id=" + user_id + "&temp_code=" + temp_code,
		function(response) {
			if(response == 'success')
				retrieveUserCodes(url, user_id, temp_code);
			else 
				alert('failed to retrieve user codes from anonymization server. Try to logout and login again. Server responded: '
					+ response);
		});
}

function retrieveUserCodes(url, user_id, temp_code) {
	make_ajax_call(url + "give_out_user_codes.php?user_id=" + user_id + "&temp_code=" + temp_code,
		function(response) {
        	var user_codes = JSON.parse(response);
        	sessionStorage.active_user_code = user_codes.active_user_code;
			sessionStorage.passive_user_code1 = user_codes.passive_user_code1;
			sessionStorage.passive_user_code2 = user_codes.passive_user_code2;
			sessionStorage.passive_user_code3 = user_codes.passive_user_code3;
			//alert('set user_code: ' + sessionStorage.active_user_code);
	    });
}

function make_ajax_call(url, callback) {
	var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function() {
    		if (xmlhttp.readyState == 4 && xmlhttp.status == 200)
    			callback(xmlhttp.responseText);
    	}
    xmlhttp.open("GET", url);
    xmlhttp.send();
}
