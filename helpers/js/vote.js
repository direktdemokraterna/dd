////////////////////////////////////////////
/// Encryption
////////////////////////////////////////////

function Generate_Random_String(len){
    var text = "";
    var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for( var i=0; i < len; i++ )
        text += possible.charAt(Math.floor(Math.random() * possible.length));
    return text;
}

function rsa_encrypt_string (strMessage, public_key){
	var rsa = new JSEncrypt();
	rsa.setPublicKey(public_key);
	return rsa.encrypt(strMessage);
}

function encrypt_password (password, public_key){
	var password_message_json = JSON.stringify({password: password});
	return rsa_encrypt_string(password_message_json, public_key);
}

function encrypt_message (message_json, public_key){
	var password = Generate_Random_String(20);
	var encrypted_password = encrypt_password(password, public_key);
	var aes_message = GibberishAES.enc(message_json, password);
	return {rsa: encrypted_password, aes: aes_message, password: password};
}

////////////////////////////////////////////
/// Ballot encryption
////////////////////////////////////////////

function package_encrypted_ballot (encrypted_ballot_json){
	var packaged_ballot = encrypt_message(encrypted_ballot_json, dd_anon_public_key);
	packaged_ballot["anon_password"] = packaged_ballot["password"];
	return packaged_ballot;
}

function encrypt_ballot (ballot_json){
	//alert("active_user_code: " + sessionStorage.active_user_code);
	var encrypted_ballot = encrypt_message(ballot_json, dd_public_key);
	encrypted_ballot["user_id"] = user_id;
	encrypted_ballot["user_code"] = sessionStorage.active_user_code;
	return encrypted_ballot;
}

function encrypt_and_package_ballot (ballot_json){
	var encrypted_ballot = encrypt_ballot(ballot_json);
	var encrypted_ballot_json = JSON.stringify(encrypted_ballot);
	var packaged_ballot = package_encrypted_ballot(encrypted_ballot_json);
	return JSON.stringify(packaged_ballot);
}

function prepare_ballot_for_submit (ballot){
	var ballot_json = JSON.stringify(ballot);
	packaged_ballot_json = acting_as_delegate 
		? ballot_json 
		: encrypt_and_package_ballot(ballot_json);
	document.getElementById("ballot").value = packaged_ballot_json;
}

////////////////////////////////////////////
/// Public API - specific ballot encryption methods
////////////////////////////////////////////

function encrypt_yes_no_ballot (alternative){
	var dd_message = {vote_id: vote_id, ballot: alternative};
	prepare_ballot_for_submit(dd_message);
	return true;
}

function encrypt_prio_ballot (prio_ranking){
	if(prio_type == "abstain"){
		prio_ranking = "abstain";
	}
	else if(prio_type == "cancel"){
		prio_ranking = "cancel";
	}
	var dd_message = {vote_id: vote_id, ballot: prio_ranking};
	prepare_ballot_for_submit(dd_message);
	return true;
}

function encrypt_prio_abstain (){
	var prio_ranking = '{}';
	encrypt_prio_ballot(prio_ranking);
	return true;
}

function encrypt_prop_ballot (support){
	var dd_message = {prop_id: prop_id, support: support};
	prepare_ballot_for_submit(dd_message);
	return true;
}

function encrypt_median_ballot (abstain_or_cancel){
	if(abstain_or_cancel === "abstain"){
		var value = "abstain";
	}
	else if(abstain_or_cancel === "cancel"){
		var value = "cancel";
	}
	else{
		var value = document.getElementById("median_value").value;
		value = value.replace("'", ".");
	}
	var dd_message = {vote_id: vote_id, ballot: value};
	prepare_ballot_for_submit(dd_message);
	return true;
}

function encrypt_single_delegation (constituency_id){
	var dd_message = {delegate_id: delegate_id, constituency_id: constituency_id};
	prepare_ballot_for_submit(dd_message);
	return true;
}

function encrypt_delegation_get_delegate_from_form (constituency_id){
	var select_element = document.getElementById("select" + constituency_id);
	var delegate_id_from_form = select_element.options[select_element.selectedIndex].value;
	var dd_message = {delegate_id: delegate_id_from_form, constituency_id: constituency_id};
	prepare_ballot_for_submit(dd_message);
	return true;
}

function show_delegate_votes (is_prop)
{
	var delegate_vote_box_header = "Delegatröster:<table><tr style='color: white'><th>Delegat</th><th>Röst</th><Rösten lagd av</th></tr>";
	var support_text = "Stöder";
	var not_support_text = "Stöder ej";
	var abstain_text = "Avstår";
	var yes_text = "Ja";
	var no_text = "Nej";
	document.getElementById("delegate_votes_box").className = "vote_result_box";
	var delegate_votes_box_content = delegate_vote_box_header;
	list_of_votes.map(function (vote){
		if(vote.user_code == null){
			delegate_votes_box_content += "<tr><td><a href=\"index.php?type=vote&action=view_delegate&id=" + vote.voter_is_delegate_id + "\">" + vote.voter_is_delegate_name + "</a></td><td style='color: white'>";
			if(vote.hasOwnProperty('support'))
				delegate_votes_box_content += vote.support ? support_text : not_support_text;
			else if(vote.hasOwnProperty('alternative'))
				delegate_votes_box_content += vote.alternative == "abstain"
					? abstain_text
					: (vote.alternative == "yes" ? yes_text : no_text);
			else if(vote.hasOwnProperty('value'))
				delegate_votes_box_content += vote.value == "abstain"
					? abstain_text
					: vote.value;
			delegate_votes_box_content += "</td><td>";
			if(vote.delegate_id)
				delegate_votes_box_content += "<a href=\"index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "\">" + vote.delegate_name + "</a>";
			delegate_votes_box_content += "</td></tr>";
		}
	});
	/*
	delegate_votes_box_content += is_prop == "prop" 
		? "</table><p><a href=\"index.php?type=vote&action=view_prop_ballots&id=" + prop_id + "\">Se alla röster för denna proposition</a></p>"
		: "</table><p><a href=\"index.php?type=vote&action=view_ballots&id=" + vote_id + "\">Se alla röster för denna omröstning</a></p>";
		*/
	document.getElementById("delegate_votes_box").innerHTML = delegate_votes_box_content;
}
