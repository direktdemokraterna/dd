<?php
	$workgroup = isset($_GET['id'])
		? db_workgroup::get_info($_GET['id'])
		: null;
	if($workgroup)
	{
		$is_member = \db_workgroup::is_member($workgroup['id'], $_SESSION['id']);
		$is_candidate = \db_workgroup::is_candidate($workgroup['id'], $_SESSION['id']);
		\View\workgroup::output_workgroup_info($workgroup, $is_member, $is_candidate);
		if($workgroup['is_active'])
			\View\workgroup::output_active_group_membership($workgroup, $is_member);
		else 
			\View\workgroup::output_inactive_workgroup_form($workgroup, $is_member);
		if(isset($_SESSION['is_member_admin']))
			__link("Administrera denna arbetsgrupp som medlemsadministratör", "member_admin", 
				"edit_workgroup", "id=" . $workgroup['id']);
	}
	else {
		__p("Inga arbetsgrupper.");
	}
?>	