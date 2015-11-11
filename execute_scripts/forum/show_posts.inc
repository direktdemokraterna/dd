<?php
	if(isset($_POST['new_post_content']))
		\Logic\forum::insert_post($_POST['target_id'], $_POST['new_post_content'])
?>