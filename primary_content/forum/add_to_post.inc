<?php 
	$post_id = $_GET['id'];
	$post_info = db_forum::get_full_post_info($post_id, $_SESSION['id']);
	_h1(_t("Make an addition to your post"));
	\View\forum::output_post($post_info, false);
	\View\controls::output_text_editor(array(
		'name' => 'add_to_post'
		,'legend' => _t('Addition to post')
		,'target_id' => $post_id
		,'submit_text' => _t("Add")));
?>
