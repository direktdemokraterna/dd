<?php 
  if (\Logic\vote::is_active_vote($voteinfo['status'])) {
    $vote_id = $voteinfo['id'];
    echo "Rangordna kandidaterna";
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
    echo '<button type="submit" class="vote_button blue-button" id="green_vote" value="Rösta">Rösta</button>';    
	echo '<button type="submit" class="vote_button" id="yellow_vote" value="Avstår" onmousedown="return prio_abstain()">Avstår</button>';
	echo '<button type="submit" class="vote_button" id="white_vote" value="Ångra röst" style="display: ' . ($_SESSION['delegate_id'] && !empty($delegate_ballot) ? "inline-block" : "none") 
      	. ';" onmousedown="return prio_cancel()">Ångra röst</button>';
    echo '</div><span id="if_delegate_vote" class="p"></span>';
    echo '</div></form>';
    echo '</div>';
	echo '<div>';
    __p(general_helpers::in_multiarray($votes_alternatives, "user_id", $_SESSION['id'])
      ? _link("Dra tillbaka din kandidatur i denna omröstning", 'vote', 'add_alternative', 'id=' . $vote_id)
      : _link("Kandidera i denna omröstning", 'vote', 'add_alternative', 'id=' . $vote_id));
    if(isset($_SESSION['is_vote_admin']))
      __p(_link("Valadministratör: Redigera alternativen i denna omröstning.", 'vote_admin', 'edit_alternatives', 'id=' . $vote_id));
  }
?>
