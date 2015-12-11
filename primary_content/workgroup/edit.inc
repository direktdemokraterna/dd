<?php 
	$workgroup = db_workgroup::get_info($_GET['id']);
	$is_member = db_workgroup::is_member($workgroup['id'], $_SESSION['id']);
	if($is_member) {
		_h1(_t("Edit the workgroup ") . \View\general::generate_internal_link($workgroup['title'], 'workgroup', 'view', 'id=' . $_GET['id']));
		\View\forum::output_text_editor(array(
			'name' => 'edit_description'
			,'legend' => _t('Change description')
			,'target_id' => $_GET['id']
			,'submit_text' => _t("Change")
			,'content' => $workgroup['description']));
	}
	else
		_p(_t("You are not a member of this workgroup."));
?>