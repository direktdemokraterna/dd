<script>
  var you_voted = "<?php __('You have voted: '); ?>";
  var you_voted_abstain = "<?php __('You have voted abstain.'); ?>";
  var you_voted_yourself = "<?php __('You have cast this ballot.'); ?>";
  var your_delegate = "<?php __('Your delegate'); ?>";
  var voted_for_you = "<?php __('has voted for you.'); ?>";
list_of_votes.map(function (vote){
	if(vote.user_code == sessionStorage.user_code && acting_as_delegate == false){
		if(vote.value === null || vote.value === "abstain")
			document.getElementById("user_vote_box").innerHTML = you_voted_abstain;
		else {
			document.getElementById("user_vote_box").innerHTML = you_voted + vote.value + ".";
			document.getElementById("median_value").value = vote.value;
		}

		if(vote.delegate_id == null){
			document.getElementById("user_vote_box").innerHTML += "<br>" + you_voted_yourself;
			document.getElementById("white_vote").style.display = "inline-block";
		}
		else
			document.getElementById("user_vote_box").innerHTML += "<br>" + your_delegate + " <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a> " + voted_for_you;
	}
});
</script>