<script>
list_of_votes.map(function (vote){
	if(vote.user_code == sessionStorage.active_user_code && acting_as_delegate == false){
		if(vote.value === null){
			document.getElementById("user_vote_box").innerHTML = "Du har röstat avstår";
		}
		else{
			if(vote.value === "abstain"){
				document.getElementById("user_vote_box").innerHTML = "Du har röstat avstår.";
			}
			else{
				document.getElementById("user_vote_box").innerHTML = "Du har röstat " + vote.value + ".";
				document.getElementById("median_value").value = vote.value;
			}
		}

		if(vote.delegate_id == null){
			document.getElementById("user_vote_box").innerHTML += "<br>Du har själv lagt denna röst.";
			document.getElementById("white_vote").style.display = "inline-block";
		}
		else{
			document.getElementById("user_vote_box").innerHTML += "<br>Din delegat <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a> har röstat åt dig.";
		}
	}
});
</script>