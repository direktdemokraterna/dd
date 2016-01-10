<script>
  var you_voted = "<?php __('You have voted: '); ?>";
  var you_voted_abstain = "<?php __('You have voted abstain.'); ?>";
  var you_voted_yourself = "<?php __('You have personally cast this ballot.'); ?>";
  var your_delegate = "<?php __('Your delegate'); ?>";
  var voted_for_you = "<?php __('has voted for you.'); ?>";
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