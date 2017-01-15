<script>
	var you_voted_yes = "<?php __t('You have voted yes.'); ?>";
	var you_voted_no = "<?php __t('You have voted no.'); ?>";
	var you_voted_abstain = "<?php __t('You have voted abstain.'); ?>";
	var you_voted = "<?php __t('You have personally cast this ballot.'); ?>";
	var your_delegate = "<?php __t('Your delegate'); ?>";
	var voted_for_you = "<?php __t('has voted for you.'); ?>";
	if (acting_as_delegate ? false : true)
		ballots_to_count.map(function (ballot){
			if(ballot.user_code == sessionStorage.user_code){
				if(ballot.ballot == "yes")
					document.getElementById("user_vote_box").innerHTML = you_voted_yes;
				else if(ballot.ballot == "no")
					document.getElementById("user_vote_box").innerHTML = you_voted_no;
				else if(ballot.ballot == "abstain")
					document.getElementById("user_vote_box").innerHTML = you_voted_abstain;
				if(ballot.delegate_id == null){
					document.getElementById("user_vote_box").innerHTML += "<br>" + you_voted;
					document.getElementById("white_vote").style.display = "inline-block";
				}
				else
					document.getElementById("user_vote_box").innerHTML += "<br>" + your_delegate + " <a href='index.php?type=vote&action=view_delegate&id=" + ballot.delegate_id + "'>" + ballot.delegate_name + "</a> " + voted_for_you;
			}
		});
</script>