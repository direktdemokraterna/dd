<script>
list_of_votes.map(function (vote){
	if(vote.user_code == sessionStorage.active_user_code){
		if(vote.alternative == "yes"){
			document.getElementById("user_vote_box").innerHTML = "Du har r�stat ja.";
		}
		else if(vote.alternative == "no"){
			document.getElementById("user_vote_box").innerHTML = "Du har r�stat nej.";
		}
		else if(vote.alternative == "abstain"){
			document.getElementById("user_vote_box").innerHTML = "Du har r�stat avst�r.";
		}
		
		if(vote.delegate_id == null){
			document.getElementById("user_vote_box").innerHTML += "<br>Du har sj�lv lagt denna r�st.";
		}
		else{
			document.getElementById("user_vote_box").innerHTML += "<br>Din delegat <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a> har r�stat �t dig.";
		}
	}
});
</script>