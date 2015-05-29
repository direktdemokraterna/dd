<?php
	if(isset($_GET['new'])){
		$workgroup_id = db_workgroup::create(htmlspecialchars($_POST['title']), htmlspecialchars($_POST['description']), $_SESSION['id']);
		if($workgroup_id){
			if($ok){
				$_SESSION['report_message'] = "Arbetsgruppen skapad";
				$redirect = "index.php?type=workgroup&action=view&id=" . $workgroup_id;
			}
		}
	}
?>