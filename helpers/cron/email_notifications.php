<?php
require(dirname(__FILE__)."./../../init.inc");
$users_to_send_emails_to = db_notice::get_users_to_send_emails_to();
foreach ($users_to_send_emails_to as $user) {
	$email_address = db_user::get_user_email($user['user_id']);
	$notices = db_notice::get_email_notices_for_user($user['user_id']);
	$title = "Nya händelser i Direktdemokreternas system";
	$message = "";
	foreach ($notices as $notice) {
		echo "ADSF";
		if($notice['type_of_notification'] == "quoting_post"){
			$post_info = db_forum::get_post_info($notice['action_id']);
			$message .= _link($post_info['full_name'] . " har citerat ditt inlägg i " . $post_info['title'], 'forum', 'show_posts', 'post_id=' . $post_info['post_id'] . '#post' . $post_info['post_id']) . "\n<br>";
		}
		elseif($notice['type_of_notification'] == "vote_started"){
			$vote_info = db_vote::get_vote_info($notice['action_id']);
			$message .= _link("Omröstningen " . $vote_info['title'] . " har startat", 'vote', 'view_vote', 'id=' . $vote_info['id']) . "\n<br>";
		}
		elseif($notice['type_of_notification'] == "vote_finished"){
			$vote_info = db_vote::get_vote_info($notice['action_id']);
			$message .= _link("Omröstningen " . $vote_info['title'] . " har avslutats", 'vote', 'view_vote', 'id=' . $vote_info['id']) . "\n<br>";
		}
		elseif($notice['type_of_notification'] == "proposition_created"){
			$prop_info = db_prop::get_prop_info($notice['action_id']);
			$message .= _link($prop_info['user_full_name'] . " har skapat propositionen " . $prop_info['title'], 'vote', 'view_prop', 'id=' . $prop_info['prop_id']) . "\n<br>";
		}
	}
	$ok = general_helpers::admin_mail($email_address, $title, $message);
	if($ok){
		db_notice::delete_email_notices_for_user($user['user_id']);
		db_notice::update_last_email_notification($user['user_id'], time());
	}
}