<?php 
	_h1(_t("Submitted applications"));
	$result = db_user::get_all_user_applications();
	echo '<div class="list_of_links">';
	foreach($result as $row) {
		_link($row['full_name'], 'member_admin', 'process_application', 'id=' . $row['id']);
		echo _t(' (Received ', array('class' => 'adj')) . strtolower(general_helpers::show_date($row['application_filed_time'])) . ')';
		_br();
	}
	echo '</div>';
?>
