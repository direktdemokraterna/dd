<?php 
	$workgroup = db_workgroup::get_info($_GET['id']);
	$is_restricted = $workgroup['membership_vote_id'] ? true : false;
	if($is_restricted)
		$constituency_id = db_vote::get_constituency_id_for_vote($workgroup['membership_vote_id']);
	_h1(_t("Administrate the workgroup ") . \View\general::generate_internal_link($workgroup['title'], 'workgroup', 'view', 'id=' . $_GET['id']));
	_open_form();
	_label(_t("Type of workgroup"), "workgroup_type");
	echo '<input type="radio" name="is_restricted" id="is_restricted" value="0" tabindex="1"' . ($is_restricted ? '>' : ' checked>') . _t('Open');
	echo '<input type="radio" name="is_restricted" id="is_restricted" value="1" tabindex="2"' . ($is_restricted ? ' checked>' : '>') . _t('Closed', array('class' => 'adj'));
	\View\general::make_textfield("title", _t('Name of workgroup'), 4, $workgroup);
	if($is_restricted)
		\View\general::make_textfield("number_of_members", _t('Number of members'), 5, $workgroup);
	_br();
	_submit_and_close(_t("Change"), null, 7);
	\View\forum::output_text_editor(array(
		'name' => 'edit_description'
		,'legend' => _t('Description of the workgroup')
		,'target_id' => $_GET['id']
		,'submit_text' => _t("Change")
		,'content' => $workgroup['description']));
	_open_form();
	_hidden("delete", 1);
	_p(_t("Removal of the workgroup cannot be undone."));
	_submit_and_close(_t("Remove"), _t("Do you really want to remove this workgroup?"), 8);
?>
