<?php
if(isset($_POST['prop_id']) && isset($_POST['ballot'])){
	if($_POST['prop_id'] == $_GET['id'])
		\Logic\vote::update_proposition_support($_POST['prop_id'], $_POST['ballot']);
	else
		die("mismatch prop_id");
}