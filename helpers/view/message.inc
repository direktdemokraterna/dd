<?php
namespace View;

class message 
{
	public static function output_inbox($messages) 
	{
		$columns = array("", _t("Sender"), _t("Subject"), _t("Date"));
		$rows = array_map(function($message) {
			return array('<input type="checkbox" name="check_list[]" class="delete_checkbox" value="' . $message['id'] . '">'
				, \View\controls::generate_internal_link($message['full_name'], 'member', 'view', 'id=' . $message['sender_id'])
				, \View\controls::generate_internal_link($message['title'], 'message', 'view', 'id=' . $message['id'])
				, \general_helpers::show_date($message['sent_time']));
		}, $messages);
		$row_styles = array_map(function($message) {
			return $message['read_time'] ? null : 'unread';
		}, $messages);
		\View\controls::output_grid_view($columns, $rows, $row_styles);
	}

	public static function output_outbox($messages) 
	{
		$columns = array("", _t("Recipient"), _t("Subject"), _t("Date"));
		$rows = array_map(function($message) {
			return array('<input type="checkbox" name="check_list[]" class="delete_checkbox" value="' . $message['id'] . '">'
				, \View\controls::generate_internal_link($message['full_name'], 'member', 'view', 'id=' . $message['recipient_id'])
				, \View\controls::generate_internal_link($message['title'], 'message', 'view', 'id=' . $message['id'])
				, \general_helpers::show_date($message['sent_time']));
		}, $messages);
		$row_styles = array_map(function($message) {
			return $message['read_time'] ? null : 'unread';
		}, $messages);
		\View\controls::output_grid_view($columns, $rows, $row_styles);
	}

	public static function output_message($message, $user_is_sender, $user_is_recipient, $title_prefix = "", $include_reply_link = false) 
	{
		_h1($title_prefix . $message['title']);
		echo '<p>';
		echo '<table class="message">';
		echo '<tr>';
		echo '<td class="message_box_left">';
		if($user_is_sender) {
			_strong(_t("Recipient: "));
			_link($message['recipient_name'], 'member', 'view', 'id=' . $message['recipient_id']);
			_br();
		}
		if($user_is_recipient) {
			_strong(_t("Sender: "));
			_link($message['sender_name'], 'member', 'view', 'id=' . $message['sender_id']);
			_br();
		}
		_strong(_t("Sent: "));
		echo \general_helpers::show_date($message['sent_time']);
		_br();
		_strong(_t("Read: ", array('class' => 'adj')));
		if($message['read_time']) 
			echo \general_helpers::show_date($message['read_time']);
		else 
			__("Unread"); 
		_br(2);
		if ($user_is_recipient && $include_reply_link) {
			_link(_t("Reply"), 'message', 'write', 'reply=' . $message['id']);
		}
		echo '</td>';
		echo '<td>';
		echo \Logic\text::make_html_from_wiki_text($message['content']);
		echo '</td>';
		echo '</tr>';
		echo '</table>';		
	}
}
?>
