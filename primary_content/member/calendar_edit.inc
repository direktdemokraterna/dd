<?php
	$calendar_info = db_calendar::get_event($_GET['id']);
	if($calendar_info['user_id'] == $_SESSION['id'] && $calendar_info['timestamp'] > time()) {
		__h1(_t("Edit activity"));
		__open_form("calendar_form");
		\View\calendar::output_time_fields($calendar_info);
		\View\calendar::output_location_field($calendar_info);
		\View\calendar::output_description_fields($calendar_info);
		__br();
		__submit_and_close(_t("Change"));
	}
	else
		__t("You cannot change this activity.");
?>
