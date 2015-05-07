var dd_public_key = "-----BEGIN PUBLIC KEY----- MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAsIpWVPRtuUJci9JuZEQY ExLoWrWqCO7KImTVRRryZKCQ8ywgi9bfS7inDpOvrmiMORomHjj7SDRySIzB8hpy C+DLVQEKz3vVs5bafzGxQcBdvdI3bXmCEd3mkmwaWhPcwTbARS71VbOTMezz7EQM jsSO4L6B74vblIJV+t+Q5D4v+FU1EgVCR22o3niM8MaqGAQTDpwC08cYQ2K4Iog5 Wh8Qv53JeJv0h6qQC7iB1Pf5oLrXtXxF/ozzBapFzRPFCj/Yvfx/7NPj1qFD/z4L kJAgWWnrpUEgwj55Lm6YHZPJThulx5IkvUdPjjtaMx4ktVaV1pj1g0ulB59It2E5 4wIDAQAB -----END PUBLIC KEY-----";
var dd_anon_public_key = "-----BEGIN PUBLIC KEY----- MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAix8NoW5Csdq2DCb8+LxC pqwXIVb123jPuhYvqm7tfFGtwRvxWUa8jWhscAipZQ+zdHXpYgchR3lgp3GGp1f3 DWF/+nr2oEosSmAupeF2WmzbpAlfGSFzCh+lmzlimYKntartYcWg1uuSeKqVj54u 5MHY66iG3LkNT0WQmqXfRMWV+6SSH9PLjWIsaAs/x0VLuHUe/lSxLhxMIPIPqtFc y324GTJWYVYiRK/eDiiBSbKBB11VmgVeIf1x3cDosTeMntXy1PBPzxiBzkMo2COe QJKZQT2912sOeURYTTGTvwxGb/nNDeqLXLI9Wpwm3UZO6/yYK5/z8dgwYgK6cvu1 LSkY7RzggKnGAHAxawjTRjgpWLIcnHYe/mE/BaDVLE/113piXbuUbqC3BBJ5JjzI XVMDQdN08ptZpSAXgXLTY9+L0aGzupb1AHwfr201FdtbBUEtfBl0AdrEu9r+ls5v QqIvkNbu5wwLllY5/5u6D2I2adXauBkqCq/Z2ksyw+LOc4py3G5zxfhcBfMqILl0 Nk5u4wNhTKxjOmdrOEW4oWrqj5NW6G1va/6PCNR2cIL8v0bpr0JABzYzXEzXSJO4 J9QJOxnyVUgaqC6dw3myRKX0MFe1kaHfWN4FPdNGaG52nkXMp5IzRg2NbP5P1GEw 3febVTI/8Gx40Mw04e5wJIkCAwEAAQ== -----END PUBLIC KEY-----";

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
