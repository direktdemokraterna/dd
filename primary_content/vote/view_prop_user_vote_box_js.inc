<script>
	document.getElementById("user_vote_box").innerHTML = support_hint;
	list_of_votes.map(function (vote){
		if(vote.user_code == sessionStorage.user_code && !acting_as_delegate) {
			support = vote.support;
			document.getElementById("user_vote_box").innerHTML = support
				? (vote.delegate_id 
					? "<br>" + delegate_supporting + " <a href='index.php?type=vote&action=view_delegate&id=" + 
					vote.delegate_id + "'>" + vote.delegate_name + "</a>." 
					: supporting) 
					+ stop_supporting_hint
				: support_withdrawn;
		}
	});
	$("#green_vote").css('display', (support ? 'none' : 'inline'));
	$("#yellow_vote").css('display', (support ? 'inline' : 'none'));
</script>