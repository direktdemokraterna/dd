<?php 
  $votes_alternatives = db_vote::get_alternatives_for_vote($voteinfo['id']);
  if (\Logic\vote::is_active_vote($voteinfo['status'])) {
    __t("Order the alternatives");
    __br();
    __open_form("prio-vote");
    __hidden("vote_id", $voteinfo['id']);
    __hidden("ballot");
	echo '<div class="vote-buttons"><div class="drop-boxes-prio-vote-wrapper">';
    echo '<ul class="prio-vote-box support-box" id="support-list"></ul>';
    echo '<ul class="prio-vote-box unsorted-box">';
    foreach($votes_alternatives as $row)
      echo '<li class="sortable" id="' . $row['id'] . '"><span title="' 
        . $row['description'] . '">' . $row['title'] . '</span></li>';
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
    __p(_link(_t("Add alternative to this vote"), 'vote', 'add_alternative', 'id=' . $voteinfo['id']));
    if(isset($_SESSION['is_vote_admin']))
      __p(_link(_t("Vote admin: Edit alternatives for this vote"), 'vote_admin', 'edit_alternatives', 'id=' . $voteinfo['id']));
  }
  else { // output alternative titles in hidden fields so user's vote can be presented
    foreach($votes_alternatives as $row)
      __hidden($row['id'], $row['title']);
  }
?>
