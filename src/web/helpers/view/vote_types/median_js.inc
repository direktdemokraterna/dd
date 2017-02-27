<script>
  var you_voted = "Du har röstat: ";
  var you_voted_abstain = "Du har röstat avstår.";
  var you_voted_yourself = "Du har personligen lagt denna röst";
  var your_delegate = "Din delegat";
  var voted_for_you = "har röstat åt dig.";
  if (acting_as_delegate ? false : true)
	ballots_to_count.map(function (ballot){
	if(ballot.user_code == sessionStorage.user_code){
		if(ballot.ballot === null || ballot.ballot === "abstain")
			document.getElementById("user_vote_box").innerHTML = you_voted_abstain;
		else {
			document.getElementById("user_vote_box").innerHTML = you_voted + ballot.ballot + ".";
			document.getElementById("median_value").value = ballot.ballot;
		}

		if(ballot.delegate_id == null){
			document.getElementById("user_vote_box").innerHTML += "<br>" + you_voted_yourself;
			document.getElementById("white_vote").style.display = "inline-block";
		}
		else
			document.getElementById("user_vote_box").innerHTML += "<br>" + your_delegate + " <a href='index.php?type=vote&action=view_delegate&id=" + ballot.delegate_id + "'>" + ballot.delegate_name + "</a> " + voted_for_you;
	}
});
</script>