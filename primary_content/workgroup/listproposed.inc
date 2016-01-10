
<?php 
	_h1(_t("Proposed workgroups", array('class' => 'adj')));
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$workgroups = db_workgroup::list_proposed($page);
	\View\workgroup::list_workgroups($workgroups);
?>

