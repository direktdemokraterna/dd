<?php 
	__h1("Arbetsgrupper");
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	$workgroups = db_workgroup::list_all($page);
	\View\workgroup::list_workgroups($workgroups);
?>

