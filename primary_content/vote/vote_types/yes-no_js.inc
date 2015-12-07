<script>
	var you_voted_yes = "<?php __('You have voted yes.'); ?>";
	var you_voted_no = "<?php __('You have voted no.'); ?>";
	var you_voted_abstain = "<?php __('You have voted abstain.'); ?>";
	var you_voted = "<?php __('You have cast this ballot.'); ?>";
	var your_delegate = "<?php __('Your delegate'); ?>";
	var voted_for_you = "<?php __('has voted for you.'); ?>";
	list_of_votes.map(function (vote){
		if(vote.user_code == sessionStorage.active_user_code && acting_as_delegate == false){
			if(vote.alternative == "yes")
				document.getElementById("user_vote_box").innerHTML = you_voted_yes;
			else if(vote.alternative == "no")
				document.getElementById("user_vote_box").innerHTML = you_voted_no;
			else if(vote.alternative == "abstain")
				document.getElementById("user_vote_box").innerHTML = you_voted_abstain;
			if(vote.delegate_id == null){
				document.getElementById("user_vote_box").innerHTML += "<br>" + you_voted;
				document.getElementById("white_vote").style.display = "inline-block";
			}
			else{
				document.getElementById("user_vote_box").innerHTML += "<br>" + your_delegate + " <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a> " + voted_for_you;
			}
		}
	});
</script>