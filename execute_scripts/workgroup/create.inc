<?php
	if(isset($_GET['new'])){
		$workgroup_id = db_workgroup::create(htmlspecialchars($_POST['title']), htmlspecialchars($_POST['description']), $_SESSION['id']);
		if($workgroup_id){
			if($ok){
				$message = "Arbetsgruppen skapad";
				db_helpers::insert_error_message($_SESSION['id'], $message);
				$redirect = "index.php?type=workgroup&action=view&id=" . $workgroup_id;
			}
		}
	}
?>