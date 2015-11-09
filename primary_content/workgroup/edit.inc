<?php 
	$workgroup = db_workgroup::get_info($_GET['id']);
	$is_member = db_workgroup::is_member($workgroup['id'], $_SESSION['id']);
	if($is_member) {
		echo '<h1>Redigera arbetsgruppen ' . \View\general::generate_internal_link($workgroup['title'], 'workgroup', 'view', 'id=' . $_GET['id']) . '</h1>';
		\View\forum::output_text_editor('edit_description', 'Ändra beskrivning', $_GET['id'], $workgroup['description'], "Ändra");
	}
	else 
		echo '<p>Du är inte medlem i den här arbetsgruppen.</p>';
?>