<?php 
  $votes_alternatives = db_vote::get_alternatives_for_vote($voteinfo['id']);
  if (\Logic\vote::is_active_vote($voteinfo['status'])) {
    __("Order the alternatives");
    _br();
    _open_form("prio-vote");
    _hidden("vote_id", $voteinfo['id']);
    _hidden("ballot");
    echo '<ul class="prio-vote-box support-box" id="support-list"></ul>';
    echo '<ul class="prio-vote-box unsorted-box">';
    foreach($votes_alternatives as $row)
      echo '<li class="sortable" id="' . $row['id'] . '"><span title="' 
        . $row['description'] . '">' . $row['title'] . '</span></li>';
    echo '</ul>';
    echo '<ul class="prio-vote-box reject-box" id="reject-list"></ul>';
    echo '<input type="submit" class="vote_button" id="green_vote" value="' . _t('Vote') . '"><br>';
    echo '<input type="submit" class="vote_button" id="yellow_vote" value="' . _t('Abstain') 
      . '" onmousedown="return prio_abstain()">';
    echo '<input type="submit" class="vote_button" id="white_vote" value="' . _t('Revoke ballot') 
      . '" style="display: ' . ($_SESSION['delegate_id'] && !empty($delegate_ballot) ? "inline-block" : "none") 
      . ';" onmousedown="return prio_cancel()">';
    echo '<br><span id="if_delegate_vote" class="p"></span>';
    echo '</form>';
    echo '</div>';
    echo '<div>';
    _p(\View\general::generate_internal_link(_t("Add alternative to this vote"), 'vote', 'add_alternative', 'id=' . $voteinfo['id']));
    if(isset($_SESSION['is_vote_admin']))
      _p(\View\general::generate_internal_link(_t("Vote admin: Edit alternatives for this vote"), 'vote_admin', 'edit_alternatives', 'id=' . $voteinfo['id']));
  }
  else { // output alternative titles in hidden fields so user's vote can be presented
    foreach($votes_alternatives as $row)
      _hidden($row['id'], $row['title']);
  }
?>
