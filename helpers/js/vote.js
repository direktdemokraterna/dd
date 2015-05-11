function encrypt_ballot (dd_message){
	var dd_message_json = JSON.stringify(dd_message);

	if(acting_as_delegate == true){
		document.getElementById("ballot").value = dd_message_json;
	}

	else{
		var dd_password = Generate_Random_String(20);

		var dd_aes_message = GibberishAES.enc(dd_message_json, dd_password);

		var dd_rsa_message = {password: dd_password};
		var dd_rsa_message_json = JSON.stringify(dd_rsa_message);

		var dd_rsa = new JSEncrypt();
		dd_rsa.setPublicKey(dd_public_key);
		var dd_rsa_message_encrypted = dd_rsa.encrypt(dd_rsa_message_json);


		var dd_anon_message = {user_id: user_id, rsa: dd_rsa_message_encrypted, aes: dd_aes_message};
		var dd_anon_message_json = JSON.stringify(dd_anon_message);

		var dd_anon_password = Generate_Random_String(20);

		var dd_anon_aes_message = GibberishAES.enc(dd_anon_message_json, dd_anon_password);

		var dd_anon_rsa_message = {password: dd_anon_password};
		var dd_anon_rsa_message_json = JSON.stringify(dd_anon_rsa_message);

		var dd_anon_rsa = new JSEncrypt();
		dd_anon_rsa.setPublicKey(dd_anon_public_key);
		var dd_anon_rsa_message_encrypted = dd_anon_rsa.encrypt(dd_anon_rsa_message_json);

		var ballot = {rsa: dd_anon_rsa_message_encrypted, aes: dd_anon_aes_message, anon_password: dd_anon_password};
		var ballot_json = JSON.stringify(ballot);

		document.getElementById("ballot").value = ballot_json;
	}

	return true;

}

function encrypt_yes_no_ballot (alternative){
	var dd_message = {vote_id: vote_id, alternative: alternative};

	encrypt_ballot(dd_message);

	return true;
}

function encrypt_prio_ballot (prio_ranking){
	var dd_message = {vote_id: vote_id, prio_ranking: prio_ranking};

	encrypt_ballot(dd_message);

	return true;
}

function encrypt_prop_ballot (support_type){
	var dd_message = {prop_id: prop_id, support_type: support_type};

	encrypt_ballot(dd_message);

	return true;
}

function Generate_Random_String(len){
    var text = "";
    var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for( var i=0; i < len; i++ )
        text += possible.charAt(Math.floor(Math.random() * possible.length));

    return text;
}

function encrypt_median_ballot (){
	var value = document.getElementById("median_value").value;
	value = value.replace("'", ".");
	var dd_message = {vote_id: vote_id, value: value};

	encrypt_ballot(dd_message);

	return true;
}
