<?php 
	_h1(_t("Inbox"));
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$inbox = db_message::get_inbox($_SESSION['id'], $page);
	$number_of_messages = count($inbox);
	$start_message = ($page - 1) * 20 + 1;
	$stop_message = $start_message + $number_of_messages - 1;
	$i = 0;
	if($number_of_messages) {
		_open_form();
		_hidden("delete", 1);
		echo _t("Showing messages ") . "$start_message - $stop_message";
		echo '<table class="message"><tr><td></td><td>' . _t("Sender") . '</td><td>' . _t("Subject") . '</td><td>' . _t("Date") . '</td></tr>';
		foreach($inbox as $row) {
			echo '<tr class="' . ($i++ % 2 ? "even_row" : "odd_row") . '">';
			echo '<td><input type="checkbox" name="check_list[]" class="delete_checkbox" value="' . $row['id'] . '"></td>';
			echo '<td>';
			_link($row['full_name'], 'member', 'view', 'id=' . $row['sender_id']);
			echo '</td><td>';
			_link($row['title'], 'message', 'view', 'id=' . $row['id']);
			echo '</td><td>' . general_helpers::show_date($row['sent_time']) . '</td>';
			echo '</tr>';			
		}
		echo '</table>';
		_br();
		echo '<input type="checkbox" name="checkall" onclick="checkAll(this, \'delete_checkbox\');">' . _t("Check all");
		_br();
		_submit_and_close(_t("Delete checked", array('form' => 'plural')));
	}
	else
		__("No messages.");
?>
