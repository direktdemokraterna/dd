<?php 
	$workgroup = db_workgroup::get_info($_GET['id']);
	if($workgroup['is_restricted'] > 0){
		$constituency_id = db_vote::get_constituency_id_for_vote($workgroup['is_restricted']);
	}
	_h1(_t("Administrate the workgroup ") . \View\general::generate_internal_link($workgroup['title'], 'workgroup', 'view', 'id=' . $_GET['id']));
	_open_form();
	_label(_t("Type of workgroup"), "workgroup_type");
	echo '<input type="radio" name="is_restricted" id="is_restricted" value="0" tabindex="1"' . ($workgroup['is_restricted'] ? '>' : ' checked>') . _t('Open');
	echo '<input type="radio" name="is_restricted" id="is_restricted" value="1" tabindex="2"' . ($workgroup['is_restricted'] ? ' checked>' : '>') . _t('Closed', array('class' => 'adj'));
	\View\general::make_textfield("title", _t('Name of workgroup'), 4, $workgroup);
	if($workgroup['is_restricted'])
		\View\general::make_textfield("number_of_members", _t('Number of members'), 5, $workgroup);
	_br();
	_submit_and_close(_t("Change"), 7);
	\View\forum::output_text_editor('edit_description', 'Beskrivning av arbetsgruppen', $_GET['id'], $workgroup['description'], "Ändra");
	_open_form();
	_hidden("delete", 1);
	_p(_t("Removal of the workgroup cannot be undone."));
	_submit_and_close(_t("Remove"), _t("Do you really want to remove this workgroup?"), 8);
?>
