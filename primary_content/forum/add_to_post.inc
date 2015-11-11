<?php 
	$post_id = $_GET['id'];
	$post_info = db_forum::get_full_post_info($post_id, $_SESSION['id']);
	echo '<h1>Gör ett tillägg till ditt inlägg</h1>';
	\View\forum::output_post($post_info, false);
	\View\forum::output_text_editor('add_to_post', 'Tillägg till ovanstående inlägg', $post_id, '', "Lägg till");
?>
