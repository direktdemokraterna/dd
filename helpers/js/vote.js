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
	var encrypted_ballot = encrypt_message(ballot_json, dd_public_key);
	encrypted_ballot["user_id"] = user_id;
	encrypted_ballot["user_code"] = sessionStorage.user_code;
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
	document.getElementById("delegate_votes_box").className = "vote_result_box";
	var delegate_votes_box_content = delegate_vote_box_header;
	list_of_votes.map(function (vote){
		if(vote.user_code == null){
			delegate_votes_box_content += "<tr><td><a href=\"index.php?type=vote&action=view_delegate&id=" + vote.voter_id + "\">" + vote.voter_is_delegate_name + "</a></td><td style='color: white'>";
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
	document.getElementById("delegate_votes_box").innerHTML = delegate_votes_box_content;
}

////////////////////////////////////////////
/// UI helper methods
////////////////////////////////////////////

function output_prio_vote(user_vote_box, vote) {
	user_vote_box.innerHTML = "";
	if(vote.prio_ranking == "abstain")
		user_vote_box.innerHTML += you_voted_abstain + "<br>";        
	else{
		var promoting = [];
		var demoting = [];
		populate_promoting_demoting_lists(promoting, demoting, vote.prio_ranking);
		if (promoting.length) 
		 	user_vote_box.innerHTML += you_promoted + promoting.join() + '<br>';
		if (demoting.length) 
		 	user_vote_box.innerHTML += you_demoted + demoting.join() + '<br>';
	}	
}

function populate_promoting_demoting_lists(promoting, demoting, prio_ranking) {
	var prio_ranking_object = JSON.parse(prio_ranking);
	var ul_support = document.getElementById("support-list");
	var ul_reject = document.getElementById("reject-list");
	var sorted_alternative_rank_pairs = get_sorted_alternative_rank_pairs(prio_ranking_object);
	for (var i = 0; i < sorted_alternative_rank_pairs.length; i++) {
		var pair = sorted_alternative_rank_pairs[i];
	    var li_element = document.getElementById(pair.key);
	    if(li_element != null){
	      var li_content = li_element.innerHTML;
	      li_element.parentNode.removeChild(li_element);
	      var li = document.createElement("li");
	      li.setAttribute("id", pair.key);
	      li.className = "sortable";
	      if(pair.rank > 0) {
	        promoting.push(li_content);
	        ul_support.appendChild(li);                
	      }
	      else {
	        demoting.push(li_content);
	        ul_reject.appendChild(li);                
	      }
	      document.getElementById(pair.key).innerHTML = li_content;
	    }
	  }
}

function get_sorted_alternative_rank_pairs(prio_ranking_object) {
	var pairs = [];
	for (var key in prio_ranking_object)
	  	if (prio_ranking_object.hasOwnProperty(key))
	  		pairs.push({key: key, rank: prio_ranking_object[key]});
	pairs.sort(function (a, b) {
		return b.rank - a.rank;
	});
	return pairs;
}
