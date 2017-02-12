<?php
	if(isset($_POST['new_post_content'])){
		$post_id = \Logic\forum::insert_post($_POST['target_id'], $_POST['new_post_content']);
		if(!\Logic\util::page_has_error())
			$redirect = "index.php?type=forum&action=show_posts&post_id=" . $post_id . "#post" . $post_id;
	}
?>