<?php
	$user_id = isset($_GET['id']) ? $_GET['id'] : $_SESSION['id']; 
	$userinfo = db_user::get_user_data($user_id); 
	_h1($userinfo['full_name']);
	echo '<div class="user_presentation_left">';
	echo '<img class="image150" src="' . USERIMG_PATH . $userinfo['image'] . '">';
	_br();
	_p(\View\controls::generate_internal_link(_t("Thread starts (") 
		. $userinfo['number_of_topics'] . ")", 'forum', 'topics_by_user', 'id=' 
		. $userinfo['id']));
	_p(\View\controls::generate_internal_link(_t("Posts (") 
		. $userinfo['number_of_posts'] . ")", 'forum', 'posts_by_user', 'id=' 
		. $userinfo['id']));
	if(!$userinfo['deletion_time'])
		_p(\View\controls::generate_internal_link(_t("Send message"), 'message', 'write', 'id=' . $userinfo['id']));
	echo '</div>';
	echo '<div class="user_presentation_right">';
	if($userinfo['deletion_time']) {
		_p(_t("This member's membership was terminated ") . strtolower(general_helpers::show_date($userinfo['deletion_time'])) . '.');
		if(isset($_SESSION['is_member_admin'])) {
			_open_form();
			_hidden("restore_user", 1);
			_submit_and_close(_t("Restore member"));
		}
	}
	else {
		$admin_roles = db_admin::get_admin_roles_for_user($user_id);
		foreach($admin_roles as $row)
			_p(_t("Is ") . \View\controls::generate_internal_link(_t(strtolower($row['title'])), 'member', 'admin_description', 'id=' . $row['id']));
		_p(_t("Last login: ") . general_helpers::show_date($userinfo['last_activity_time']));
		if($userinfo['show_email'])
			_p(_t("Email address: ") . $userinfo['email']);
		if($userinfo['show_telephone']) {
			if(!empty($userinfo['telephone1']))
				_p(_t("Telephone number: ") . $userinfo['telephone1']);
			if(!empty($userinfo['telephone2']))
				_p(_t("Telephone number: ") . $userinfo['telephone2']);
		}
		if($userinfo['show_skype'] && !empty($userinfo['skype_name']))
			_p(_t("Skype name: ") . $userinfo['skype_name']);
		_p(_t("Municipality: ") . $userinfo['county_name']);
		_p(_t("Region: ") . $userinfo['region_name']);
		_p(_t("Presentation:") . '<br>' . \View\general::make_html_from_wiki_text($userinfo['description']));
		_br();
		if ($user_id == $_SESSION['id'])
			_p(\View\controls::generate_internal_link(_t("Change my information"), 
				"member", "settings"));
		elseif(isset($_SESSION['is_member_admin']))
			_p(\View\controls::generate_internal_link(_t("Change information for this user"), 
				"member_admin", "edit", "id=" . $user_id));
		if(isset($_SESSION['is_forum_admin']))
			_p(\View\controls::generate_internal_link(_t("Set forum permissions for this user"), 
				"forum_admin", "edit_user", "id=" . $user_id));
		if(isset($_SESSION['is_vote_admin']))
			_p(\View\controls::generate_internal_link(_t("Set constituency permissions for this user"), 
				"vote_admin", "edit_user", "id=" . $user_id));
		if(isset($_SESSION['is_superadmin']))
			_p(\View\controls::generate_internal_link(_t("Set administrator roles for this user"), 
				"superadmin", "edit_admin", "id=" . $user_id));
		if(isset($_SESSION['is_member_admin'])) {
			_open_form();
			_hidden("delete_user", 1);
			_submit_and_close(_t("Remove this user"), null, _t("Do you really want to remove this user?"));
		}
	}
	echo '</div>';
?>
