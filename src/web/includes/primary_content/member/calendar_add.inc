<?php
	__h1("Lägg till aktivitet");
	__open_form("calendar_form");
	$calendar_info = array("year" => date("Y"), "month" => date("n"), "day" => date("j"));
	\View\calendar::output_time_fields($calendar_info);
	\View\calendar::output_location_field();
	\View\calendar::output_description_fields();
	__br(2);
	__p("Markera om du vill att aktiviteten ska upprepas flera dagar i rad, en gång i veckan under flera veckor eller en gång i månaden under flera månader.");
?>
<div class="checkbox_div">
	<label for "repeat_per_day">Varje dag</label>
	<div class="checkbox_inner_div">
		<input type="radio" name="repeat_type" value="day" id="repeat_per_day">
	</div>
</div>
<div class="checkbox_div">
	<label for "repeat_per_week">Varje vecka</label>
	<div class="checkbox_inner_div">
		<input type="radio" name="repeat_type" value="week" id="repeat_per_week">
	</div>
</div>
<div class="checkbox_div">
	<label for "repeat_per_month">Varje månad</label>
	<div class="checkbox_inner_div">
		<input type="radio" name="repeat_type" value="month" id="repeat_per_month">
	</div>
</div>
<?php
	$options = array();
	for($i=2; $i<53; $i++) $options[$i] = $i;
	\View\controls::output_labeled_selector("repeat_number", "Antal upprepningar", $options);
	__br();
	__submit_and_close("Lägg till");
?>
