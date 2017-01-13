<?php 
  if (\Logic\vote::is_active_vote($voteinfo['status'])) {
    $vote_id = $voteinfo['id'];
    __t("Order the candidates");
    __br();
    __open_form("prio-vote");
    __hidden("vote_id", $vote_id);
    __hidden("ballot");
	echo '<div class="vote-buttons"><div class="drop-boxes-prio-vote-wrapper">';
    echo '<ul class="prio-vote-box support-box" id="support-list"></ul>';
    echo '<ul class="prio-vote-box unsorted-box">';
    $votes_alternatives = db_vote::get_candidates_for_vote($vote_id);
    foreach($votes_alternatives as $row)
      echo '<li class="sortable" id="' . $row['id'] . '"><span title="' 
        . $row['description'] . '">' . $row['user_name'] . '</span></li>';
    echo '</ul>';
    echo '<ul class="prio-vote-box reject-box" id="reject-list"></ul></div>';
	echo '<div class="prio-vote-buttons-wrapper">';
    echo '<button type="submit" class="vote_button blue-button" id="green_vote" value="' . _t('Vote') . '">' . _t('Vote') . '</button>';    
	echo '<button type="submit" class="vote_button" id="yellow_vote" value="' . _t('Abstain') 
      	. '" onmousedown="return prio_abstain()">' . _t('Abstain') . '</button>';
	echo '<button type="submit" class="vote_button" id="white_vote" value="' . _t('Revoke ballot') 
      	. '" style="display: ' . ($_SESSION['delegate_id'] && !empty($delegate_ballot) ? "inline-block" : "none") 
      	. ';" onmousedown="return prio_cancel()">' . _t('Revoke ballot') . '</button>';
    echo '</div><span id="if_delegate_vote" class="p"></span>';
    echo '</div></form>';
    echo '</div>';
	echo '<div>';
    __p(general_helpers::in_multiarray($votes_alternatives, "user_id", $_SESSION['id'])
      ? _link(_t("Revoke your candidacy for this vote"), 'vote', 'add_alternative', 'id=' . $vote_id)
      : _link(_t("Candidate for this vote"), 'vote', 'add_alternative', 'id=' . $vote_id));
    if(isset($_SESSION['is_vote_admin']))
      __p(_link(_t("Vote admin: Edit the alternatives for this vote"), 'vote_admin', 'edit_alternatives', 'id=' . $vote_id));
  }
?>
