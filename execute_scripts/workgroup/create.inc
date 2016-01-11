<?php
	if(isset($_POST['title'])){

		$already_exists = db_workgroup::get_id_from_name($_POST['title']);

		if(!$already_exists){
			$workgroup_id = db_workgroup::create(general_helpers::clean($_POST['title'])
				, \Logic\text::process_text($_POST['description']), $_SESSION['id']);
			if($workgroup_id){
				$_SESSION['report_message'] = _t("Workgroup created");
				$redirect = "index.php?type=workgroup&action=view&id=" . $workgroup_id;
			}
			else{
				$_SESSION['report_message'] = _t("Something went wrong. No workgroup created");
				$_SESSION['red_report_message'] = 1;
			}
		}
		else{
			$_SESSION['report_message'] = _t("There already exists a workgroup with that name");
			$_SESSION['red_report_message'] = 1;
		}
	}
?>