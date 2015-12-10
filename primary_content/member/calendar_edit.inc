<?php
	$calendar_info = db_calendar::get_event($_GET['id']);
	if($calendar_info['user_id'] == $_SESSION['id'] && $calendar_info['timestamp'] > time()) {
		_h1(_t("Change activity"));
		_open_form("calendar_form");
		\View\calendar::output_time_fields($calendar_info);
		\View\calendar::output_location_field($calendar_info);
		\View\calendar::output_description_fields();
		_br();
		_submit_and_close(_t("Change"));
	}
	else
		__("You cannot change this activity.");
?>
