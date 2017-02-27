<?php 
	__h1("Medlemsansökningar");
	$result = db_user::get_all_user_applications();
	echo '<div class="list_of_links">';
	foreach($result as $row) {
		__link($row['full_name'], 'member_admin', 'process_application', 'id=' . $row['id']);
		echo ' (Mottagen ' . strtolower(general_helpers::show_date($row['application_filed_time'])) . ')';
		__br();
	}
	echo '</div>';
?>
