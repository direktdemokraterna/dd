<?php if($voteinfo['status'] == "active" || $voteinfo['status'] == "continouos" || ($voteinfo['status'] == "del_ended" && !$_SESSION['delegate_id'])) : ?>

	Lägg din röst:<br>
	
	<form method="post" action="" class="yes-no">
		<input type="hidden" name="vote_id" value="<?php echo $voteinfo['vote_id']; ?>">
		<input type="hidden" name="ballot" id="ballot" value="">

		<label for "median_value">Ditt önskade värde</label>
		<input type="text" name="median_value" id="median_value">
		<input type="submit" value="Rösta" onmousedown="return encrypt_median_ballot()">
		<input type="submit" class="vote_button" id="yellow_vote" value="Avstår" onmousedown="return encrypt_median_ballot('abstain')">
		<input type="submit" class="vote_button" id="white_vote" value="Ångra röst" style="display: none;" onmousedown="return encrypt_median_ballot('cancel')">
	</form>

<?php endif; ?>