<?php
	if(isset($_POST['title']) && isset($_POST['number_of_members'])){

		$already_exists = db_workgroup::get_id_from_name($_POST['title']);

		if(!$already_exists){
			$workgroup_id = db_workgroup::create_restricted(general_helpers::clean($_POST['title']), forum_helpers::process_text($_POST['description']), (int)$_POST['number_of_members']);
			if($workgroup_id){
				$_SESSION['report_message'] = "Arbetsgruppen skapad";
				$redirect = "index.php?type=workgroup&action=view&id=" . $workgroup_id;
			}
			else{
				$_SESSION['report_message'] = "Något gick fel, ingen arbetsgrupp skapad";
				$_SESSION['red_report_message'] = 1;
			}
		}
		else{
			$_SESSION['report_message'] = "Det finns redan en arbetsgrupp med den namnet";
			$_SESSION['red_report_message'] = 1;
		}
	}
?>