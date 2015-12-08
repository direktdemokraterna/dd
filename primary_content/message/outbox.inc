<?php 
	_h1(_t("Outbox"));
	$page = isset($_GET['page']) ? $_GET['page'] : 1;
	$outbox = db_message::get_outbox($_SESSION['id'], $page);
	$number_of_messages = count($outbox);
	$start_message = ($page - 1) * 20 + 1;
	$stop_message = $start_message + $number_of_messages - 1;
	$i = 0;
?>

<?php if($number_of_messages>0) : ?>
	<?php
		_open_form("");
		_hidden("delete", 1);
		echo _t("Showing messages ") . "$start_message - $stop_message";
	?>
	<table class="message"><tr><td></td><td><?php __("Recipient"); ?></td><td><?php __("Subject"); ?></td><td><?php __("Date"); ?></td></tr>

	<?php foreach($outbox as $row) : ?>
		<tr class="<?php if($i++ % 2) echo "even_row"; else echo "odd_row"; ?>">
		<td><input type="checkbox" name="check_list[]" class="delete_checkbox" value="<?php echo $row['id']; ?>"></td>
		<td><a href="index.php?type=member&action=view&id=<?php echo $row['sender_id']; ?>"><?php echo $row['full_name']; ?></a></td>
		<td><a href="index.php?type=message&action=view&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a></td>
		<td><?php echo general_helpers::show_date($row['sent_time']); ?></td>
		</tr>
	<?php endforeach; ?>

	</table>
	<br><input type="checkbox" name="checkall" onclick="checkAll(this, 'delete_checkbox');">Markera alla
	<br>
	<?php
		_submit_and_close(_t("Delete checked", array('form' => 'plural')));
	?>
	</form>

<?php else : ?>
	<?php __("No messages."); ?>
<?php endif; ?>