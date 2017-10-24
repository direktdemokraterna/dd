<?php 
	$workgroup = db_workgroup::get_info($_GET['id']);
	$is_restricted = $workgroup['membership_vote_id'] ? true : false;
	if($is_restricted)
		$constituency_id = db_vote::get_constituency_id_for_vote($workgroup['membership_vote_id']);
	__h1("Administrera arbetsgruppen " . _link($workgroup['title'], 'workgroup', 'view', 'id=' . $_GET['id']));
	__open_form();
	__label("Typ av arbetsgrupp", "workgroup_type");
	echo '<input type="radio" name="is_restricted" id="is_restricted" value="0" tabindex="1"' . ($is_restricted ? '>' : ' checked>') . "Öppen";
	echo '<input type="radio" name="is_restricted" id="is_restricted" value="1" tabindex="2"' . ($is_restricted ? ' checked>' : '>') . "Stängd";
	__textfield("title", "Arbetsgruppens namn", 4, $workgroup);
	if($is_restricted)
		__textfield("number_of_members", "Antal medlemmar", 5, $workgroup);
	__br();
	__submit_and_close("Ändra", null, null, 7);
	\View\controls::output_text_editor(array(
		'name' => 'edit_description'
		,'legend' => "Beskrivning av arbetsgruppen"
		,'target_id' => $_GET['id']
		,'submit_text' => "Ändra"
		,'content' => $workgroup['description']));
	__open_form();
	__hidden("delete", 1);
	__p("Borttagning av arbetsgruppen kan inte ångras.");
	__submit_and_close("Ta bort", null, "Vill du verkligen ta bort den här arbetsgruppen?", 8);
?>
