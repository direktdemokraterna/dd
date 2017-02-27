<script>
	document.getElementById("user_vote_box").innerHTML = support_hint;
	if (acting_as_delegate ? false : true)
		ballots_to_count.map(function (ballot){
			if(ballot.user_code == sessionStorage.user_code) {
				support = ballot.support;
				document.getElementById("user_vote_box").innerHTML = support
					? (ballot.delegate_id 
						? "<br>" + delegate_supporting + " <a href='index.php?type=vote&action=view_delegate&id=" + 
						ballot.delegate_id + "'>" + ballot.delegate_name + "</a>." 
						: supporting) 
						+ stop_supporting_hint
					: support_withdrawn;
			}
		});
	$("#green_vote").css('display', (support ? 'none' : 'inline'));
	$("#yellow_vote").css('display', (support ? 'inline' : 'none'));
</script>