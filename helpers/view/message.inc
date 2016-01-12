<?php
namespace View;

class message 
{
	public static function output_inbox($messages, $page, $message_count) 
	{
		\View\controls::output_paging_row($page, $message_count);
		self::output_inbox_grid($messages);
		\View\controls::output_paging_row($page, $message_count);
	}

	public static function output_inbox_grid($messages) 
	{
		$columns = array("", _t("Sender"), _t("Subject"), _t("Date"));
		$rows = array_map(function($message) {
			return array('<input type="checkbox" name="check_list[]" class="delete_checkbox" value="' . $message['id'] . '">'
				, _link($message['full_name'], 'member', 'view', 'id=' . $message['sender_id'])
				, _link($message['title'], 'message', 'view', 'id=' . $message['id'])
				, \general_helpers::show_date($message['sent_time']));
		}, $messages);
		$row_styles = array_map(function($message) {
			return $message['read_time'] ? null : 'unread';
		}, $messages);
		\View\controls::output_grid_view($columns, $rows, $row_styles);
	}

	public static function output_outbox($messages, $page, $message_count) 
	{
		\View\controls::output_paging_row($page, $message_count);
		self::output_outbox_grid($messages);
		\View\controls::output_paging_row($page, $message_count);
	}

	private static function output_outbox_grid($messages) 
	{
		$columns = array("", _t("Recipient"), _t("Subject"), _t("Date"));
		$rows = array_map(function($message) {
			return array('<input type="checkbox" name="check_list[]" class="delete_checkbox" value="' . $message['id'] . '">'
				, _link($message['full_name'], 'member', 'view', 'id=' . $message['recipient_id'])
				, _link($message['title'], 'message', 'view', 'id=' . $message['id'])
				, \general_helpers::show_date($message['sent_time']));
		}, $messages);
		$row_styles = array_map(function($message) {
			return $message['read_time'] ? null : 'unread';
		}, $messages);
		\View\controls::output_grid_view($columns, $rows, $row_styles);
	}

	public static function output_message($message, $user_is_sender, $user_is_recipient, $title_prefix = "", $include_reply_link = false) 
	{
		__h1($title_prefix . $message['title']);
		echo '<p>';
		echo '<table class="message">';
		echo '<tr>';
		echo '<td class="message_box_left">';
		if($user_is_sender) {
			__strong(_t("Recipient: "));
			__link($message['recipient_name'], 'member', 'view', 'id=' . $message['recipient_id']);
			__br();
		}
		if($user_is_recipient) {
			__strong(_t("Sender: "));
			__link($message['sender_name'], 'member', 'view', 'id=' . $message['sender_id']);
			__br();
		}
		__strong(_t("Sent: "));
		echo \general_helpers::show_date($message['sent_time']);
		__br();
		__strong(_t("Read: ", array('class' => 'adj')));
		if($message['read_time']) 
			echo \general_helpers::show_date($message['read_time']);
		else 
			__t("Unread"); 
		__br(2);
		if ($user_is_recipient && $include_reply_link) {
			__link(_t("Reply"), 'message', 'write', 'reply=' . $message['id']);
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
