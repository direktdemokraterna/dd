<?php 
	__h1(_t("Inbox"));
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$inbox = db_message::get_inbox($_SESSION['id'], $page);
	$number_of_messages = count($inbox);
	$start_message = ($page - 1) * 20 + 1;
	$stop_message = $start_message + $number_of_messages - 1;
	if($number_of_messages) {
		__open_form();
		__hidden("delete", 1);
		echo _t("Showing messages ") . "$start_message - $stop_message";
		\View\message::output_inbox($inbox);
		__br();
		echo '<input type="checkbox" name="checkall" onclick="checkAll(this, \'delete_checkbox\');">' . _t("Check all");
		__br();
		__submit_and_close(_t("Delete selected", array('form' => 'plural')));
	}
	else
		__t("No messages.");
?>
