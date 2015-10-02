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


		var dd_anon_message = {user_id: user_id, user_code: sessionStorage.active_user_code, rsa: dd_rsa_message_encrypted, aes: dd_aes_message};
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
	var dd_message = {vote_id: vote_id, ballot: alternative};

	encrypt_ballot(dd_message);

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

	encrypt_ballot(dd_message);

	return true;
}

function encrypt_prio_abstain (){
	var prio_ranking = '{}';

	encrypt_prio_ballot(prio_ranking);

	var already_encrypted = true;

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

	encrypt_ballot(dd_message);

	return true;
}

function encrypt_single_delegation (constituency_id){
	var dd_message = {delegate_id: delegate_id, constituency_id: constituency_id};

	encrypt_ballot(dd_message);

	return true;
}

function encrypt_delegation_get_delegate_from_form (constituency_id){
	var select_element = document.getElementById("select" + constituency_id);
	var delegate_id_from_form = select_element.options[select_element.selectedIndex].value;
	var dd_message = {delegate_id: delegate_id_from_form, constituency_id: constituency_id};

	encrypt_ballot(dd_message);

	return true;
}

function show_delegate_votes (is_prop){
	document.getElementById("delegate_votes_box").className = "vote_result_box";

	var delegate_votes_box_content = "Delegatröster:<table><tr><th>Delegat</th><th>Röst</th><Rösten lagd av</th></tr>";

	list_of_votes.map(function (vote){
		if(vote.user_code == null){
			delegate_votes_box_content += "<tr><td><a href=\"index.php?type=vote&action=view_delegate&id=" + vote.voter_is_delegate_id + "\">" + vote.voter_is_delegate_name + "</a></td><td>";

			if(vote.hasOwnProperty('support_type')){
				if(vote.support_type == "support"){
					delegate_votes_box_content += "Stöder";
				}
				else if(vote.support_type == "abstain"){
					delegate_votes_box_content += "Avstår";
				}
			}
			else if(vote.hasOwnProperty('alternative')){
				if(vote.alternative == "yes"){
					delegate_votes_box_content += "Ja";
				}
				else if(vote.alternative == "no"){
					delegate_votes_box_content += "Nej";
				}
				else if(vote.alternative == "abstain"){
					delegate_votes_box_content += "Avstår";
				}
			}
			else if(vote.hasOwnProperty('value')){
				if(vote.value == "abstain"){
					delegate_votes_box_content += "Avstår";
				}
				else{
					delegate_votes_box_content += vote.value;
				}
			}

			delegate_votes_box_content += "</td><td>";
			if(vote.delegate_id != null){
				delegate_votes_box_content += "<a href=\"index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "\">" + vote.delegate_name + "</a>";
			}
			delegate_votes_box_content += "</td></tr>";
		}
	});

	if(is_prop == "prop"){
		delegate_votes_box_content += "</table><p><a href=\"index.php?type=vote&action=view_prop_ballots&id=" + prop_id + "\">Se alla röster för denna omröstning</a></p>";
	}
	else{
		delegate_votes_box_content += "</table><p><a href=\"index.php?type=vote&action=view_ballots&id=" + vote_id + "\">Se alla röster för denna omröstning</a></p>";
	}

	document.getElementById("delegate_votes_box").innerHTML = delegate_votes_box_content;
}