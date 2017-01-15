<?php
	$constituencies = db_constituency::get_constituencies_for_voter($_SESSION['delegate_id'] 
			? $_SESSION['delegate_id'] : $_SESSION['id']);
	$list_of_delegations_from_db = db_delegate::get_delegations_for_multiple_constituencies($constituencies);
	$list_of_delegations = Array();
	foreach($list_of_delegations_from_db as $row)
		$list_of_delegations[] = Array("user_code" => $row['user_code'], "constituency_id" => $row['constituency_id'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
?>
<script>
	var user_id = <?php echo json_encode($_SESSION['id']); ?>;
	var list_of_delegations = <?php echo json_encode($list_of_delegations); ?>;
	var acting_as_delegate = <?php if($_SESSION['delegate_id']) echo "true"; else echo "false"; ?>;
</script>

<?php 
	__h1(_t("Your current delegations" . ($_SESSION['delegate_id'] ? " as delegate" : '')));
	__open_form("prio-vote");
	__hidden("ballot");
	foreach($constituencies as $row) {
		echo '<div class="delegation_box">';
		echo _t("Constituency: ");
		__strong($row['name']);
		__br();
		if($_SESSION['delegate_id']) {
			echo '<span>';
			$delegate_delegate_for_constituency = db_delegate::get_delegates_delegate_for_constituency($_SESSION['delegate_id'], $row['id']);
			if($delegate_delegate_for_constituency) {
				__t("You have delegated your vote in this constituency to ");
				__link($delegate_delegate_for_constituency['delegate_title'], 'vote', 'view_delegate', 'id=' 
					. $delegate_delegate_for_constituency['delegate_id']);
			}
			else
				__t("You have no delegate in this constituency");
			echo '</span>';
		}
		else 
			echo '<span id="constituency' . $row['id'] . '">' . _t("You have no delegate in this constituency") . '</span>';
		__br(2);
		$delegates_for_constituency = db_delegate::get_available_delegates($row['id']
			, $_SESSION['delegate_id']);
		$delegate_options = array("null" => _t("Remove delegate"));
		foreach ($delegates_for_constituency as $delegate)
			$delegate_options[$delegate['id']] = $delegate['title'];
			echo '<div class="styled-select slate">';
		\View\controls::output_selector('select' . $row['id'], $delegate_options);
		echo '</div>';
		echo '<button type="submit" value="' . _t("Delegate") . '" onmousedown="return encrypt_delegation_get_delegate_from_form(' 
			. $row['id'] . ')">' . _t("Delegate") . '</button>';
		echo '</div>';
	}
	echo '</form>';
	echo '<script>';
	echo 'var dynamic_delegation_info_text = "' . _t("You have delegated your vote in this constituency to") . '";';
	echo '</script>';
?>
<script>
list_of_delegations.map(function (vote){
	if(vote.user_code == sessionStorage.user_code){
		var constituency_element = "constituency" + vote.constituency_id;
		document.getElementById(constituency_element).innerHTML = dynamic_delegation_info_text + " <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a>";
	}
});
</script>