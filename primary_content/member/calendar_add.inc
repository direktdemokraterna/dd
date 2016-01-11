<?php
	__h1(_t("Add activity"));
	__open_form("calendar_form");
	$calendar_info = array("year" => date("Y"), "month" => date("n"), "day" => date("j"));
	\View\calendar::output_time_fields($calendar_info);
	\View\calendar::output_location_field();
	\View\calendar::output_description_fields();
	__br(2);
	__p(_t("Check if you want the activity to be repeated several days in a row, once every week for several weeks or once every month for several months."));
?>
<div class="checkbox_div">
	<label for "repeat_per_day"><?php __t("Every day"); ?></label>
	<div class="checkbox_inner_div">
		<input type="radio" name="repeat_type" value="day" id="repeat_per_day">
	</div>
</div>
<div class="checkbox_div">
	<label for "repeat_per_week"><?php __t("Every week"); ?></label>
	<div class="checkbox_inner_div">
		<input type="radio" name="repeat_type" value="week" id="repeat_per_week">
	</div>
</div>
<div class="checkbox_div">
	<label for "repeat_per_month"><?php __t("Every month"); ?></label>
	<div class="checkbox_inner_div">
		<input type="radio" name="repeat_type" value="month" id="repeat_per_month">
	</div>
</div>
<?php
	$options = array();
	for($i=2; $i<53; $i++) $options[$i] = $i;
	\View\controls::output_labeled_selector("repeat_number", _t("Number of repetitions"), $options);
	__br();
	__submit_and_close(_t("Add"));
?>
