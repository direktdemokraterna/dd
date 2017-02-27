<?php 
	$workgroup = db_workgroup::get_info($_GET['id']);
	$is_member = db_workgroup::is_member($workgroup['id'], $_SESSION['id']);
	if($is_member) {
		__h1("Redigera arbetsgruppen " . _link($workgroup['title'], 'workgroup', 'view', 'id=' . $_GET['id']));
		\View\controls::output_text_editor(array(
			'name' => 'edit_description'
			,'legend' => "Ändra beskrivning"
			,'target_id' => $_GET['id']
			,'submit_text' => "Ändra"
			,'content' => $workgroup['description']));
	}
	else
		__p("Du är inte medlem i denna arbetsgrupp.");
?>