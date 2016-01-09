<?php 
	_h1(_t("Outbox"));
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$outbox = db_message::get_outbox($_SESSION['id'], $page);
	$number_of_messages = count($outbox);
	$start_message = ($page - 1) * 20 + 1;
	$stop_message = $start_message + $number_of_messages - 1;
	$i = 0;
	if($number_of_messages) {
		_open_form();
		_hidden("delete", 1);
		echo _t("Showing messages ") . "$start_message - $stop_message";
		\View\message::output_outbox($outbox);
		_br();
		echo '<input type="checkbox" name="checkall" onclick="checkAll(this, \'delete_checkbox\');">' . _t("Check all");
		_br();
		_submit_and_close(_t("Delete selected", array('form' => 'plural')));
	}
	else
		__("No messages.");
?>