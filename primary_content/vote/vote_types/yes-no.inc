<?php if($voteinfo['status'] == "active" || $voteinfo['status'] == "continuous" || ($voteinfo['status'] == "del_ended" && !$_SESSION['delegate_id'])) : ?>

	Lägg din röst:<br>
	
	<form method="post" action="" class="yes-no">
		<input type="hidden" name="vote_id" value="<?php echo $voteinfo['vote_id']; ?>">
		<input type="hidden" name="ballot" id="ballot" value="">

		<input type="submit" class="vote_button" id="green_vote" value="Ja" onmousedown="return encrypt_yes_no_ballot('yes')">
		<input type="submit" class="vote_button" id="red_vote" value="Nej" onmousedown="return encrypt_yes_no_ballot('no')">
		<input type="submit" class="vote_button" id="yellow_vote" value="Avstår" onmousedown="return encrypt_yes_no_ballot('abstain')">
	</form>

<?php endif; ?>