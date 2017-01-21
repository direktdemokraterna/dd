<?php 
	$post_id = $_GET['id'];
	$post_info = db_forum::get_full_post_info($post_id, $_SESSION['id']);
	__h1("Gör ett tillägg till ditt inlägg");
	\View\forum::output_post($post_info, false);
	\View\controls::output_text_editor(array(
		'name' => 'add_to_post'
		,'legend' => "Tillägg till inlägg"
		,'target_id' => $post_id
		,'submit_text' => "Lägg till"));
?>
