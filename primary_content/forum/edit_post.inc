<?php 
	$post_info = db_forum::get_full_post_info($_GET['id'], $_SESSION['id']);
	__h1(_t("Edit post"));
	\View\forum::output_post($post_info, false);
	\View\controls::output_text_editor(array(
		'name' => 'edit_post'
		,'legend' => _t('Edit post')
		,'target_id' => $_GET['id']
		,'submit_text' => _t("Change")
		,'content' => $post_info['content']));
?>
