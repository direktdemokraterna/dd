<?php 
	__h1("Inkorg");
	$message_count = db_message::get_inbox_count($_SESSION['id']);
	if($message_count) {
		$page = isset($_GET['page']) ? $_GET['page'] : 1;
		$sort = isset($_GET['sort']) ? $_GET['sort'] : 0;
		$inbox = db_message::get_inbox($_SESSION['id'], $page, $sort);
		__open_form();
		__hidden("delete", 1);
		\View\message::output_inbox($inbox, $page, $message_count);
		__br();
		echo '<input type="checkbox" name="checkall" onclick="checkAll(this, \'delete_checkbox\');">' . "Markera alla";
		__br();
		__submit_and_close("Ta bort markerade");
	}
	else
		echo "Inga meddelanden.";
?>
