<?php 
	__h1(_t("Affirmed propositions"));
	$status = 'affirmed';
	$prop_count = db_prop::list_props_count($status, $_SESSION['id']);
	if ($prop_count) {
		$prop_groups = \Logic\vote::get_prop_groups($status);
		\View\vote::make_proposition_list($prop_groups, $prop_count, "vote", "view_prop");
	}
	else 
		__t("There are no affirmed propositions in your constituencies");?>
