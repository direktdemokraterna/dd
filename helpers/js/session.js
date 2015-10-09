function retrieveUserCodes(url, user_id, temp_code) {
	//alert('retrieveUserCodes: ' + user_id);
	var xmlhttp = new XMLHttpRequest();
    xmlhttp.onreadystatechange = function() {
		//alert('onreadystatechange: ' + xmlhttp.readyState + ', ' + xmlhttp.status);
        if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
			//alert('received user codes: ' + xmlhttp.responseText);
        	var user_codes = JSON.parse(xmlhttp.responseText);
        	sessionStorage.active_user_code = user_codes.active_user_code;
			sessionStorage.passive_user_code1 = user_codes.passive_user_code1;
			sessionStorage.passive_user_code2 = user_codes.passive_user_code2;
			sessionStorage.passive_user_code3 = user_codes.passive_user_code3;
			//alert('successfully retreived user codes: ' + xmlhttp.responseText);
        }
    }
    xmlhttp.open("GET", url + "give_out_user_codes.php?user_id=" + user_id + "&temp_code=" + temp_code);
    xmlhttp.send();
}