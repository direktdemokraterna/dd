<?php

if($_GET['type']=="member") {
	if($_GET['action']=="settings") {
		require("execute_scripts/member/settings.inc");
	}
	elseif($_GET['action']=="calendar") {
		require("execute_scripts/member/calendar.inc");
	}
	elseif($_GET['action']=="calendar_add") {
		require("execute_scripts/member/calendar_add.inc");
	}
	elseif($_GET['action']=="calendar_edit") {
		require("execute_scripts/member/calendar_edit.inc");
	}
}

elseif($_GET['type']=="message") {
	if($_GET['action']=="inbox"){
		require("execute_scripts/message/inbox.inc");
	}
	elseif($_GET['action']=="outbox"){
		require("execute_scripts/message/outbox.inc");
	}
	elseif($_GET['action']=="write"){
		require("execute_scripts/message/write.inc");
	}
	elseif($_GET['action']=="view"){
		require("execute_scripts/message/view.inc");
	}
}

elseif($_GET['type']=="workgroup") {
	if($_GET['action']=="create"){
		require("execute_scripts/workgroup/create.inc");
	}
	elseif($_GET['action']=="view"){
		require("execute_scripts/workgroup/view.inc");
	}
	elseif($_GET['action']=="edit"){
		require("execute_scripts/workgroup/edit.inc");
	}
}

elseif($_GET['type']=="admin_role") {
	if($_GET['action']=="description"){
		require("execute_scripts/admin_role/description.inc");
	}
}

elseif($_GET['type']=="forum") {
	if($_GET['action']=="show_forums"){
		require("execute_scripts/forum/show_forums.inc");
	}
	elseif($_GET['action']=="show_topics"){
		require("execute_scripts/forum/show_topics.inc");
	}
	elseif($_GET['action']=="show_posts"){
 		require("execute_scripts/forum/sort_posts_and_topics.inc");
		require("execute_scripts/forum/show_posts.inc");
	}
	elseif($_GET['action']=="report"){
		require("execute_scripts/forum/report_post.inc");
	}
	elseif($_GET['action']=="edit"){
		require("execute_scripts/forum/edit_post.inc");
	}
	elseif($_GET['action']=="add"){
		require("execute_scripts/forum/add_to_post.inc");
	}
	elseif($_GET['action']=="delete"){
		require("execute_scripts/forum/delete_post.inc");
	}
}

elseif($_GET['type']=="vote") {
	if($_GET['action']=="add_prop"){
		require("execute_scripts/vote/add_prop.inc");
	}
	elseif($_GET['action']=="delegate_settings"){
		require("execute_scripts/vote/delegate_settings.inc");
	}
	elseif($_GET['action']=="view_prop"){
		require("execute_scripts/vote/view_prop.inc");
	}
	elseif($_GET['action']=="view_vote"){
		require("execute_scripts/vote/view_vote.inc");
	}
	elseif($_GET['action']=="view_delegate"){
		require("execute_scripts/vote/view_delegate.inc");
	}
	elseif($_GET['action']=="delegations"){
		require("execute_scripts/vote/delegations.inc");
	}
	elseif($_GET['action']=="add_alternative"){
		require("execute_scripts/vote/add_alternative.inc");
	}
}

elseif($_GET['type']=="member_admin" && isset($_SESSION['is_member_admin'])) {
	if($_GET['action']=="create_new"){
		require("execute_scripts/member_admin/create_new.inc");
	}
	elseif($_GET['action']=="edit"){
		require("execute_scripts/member_admin/edit.inc");
	}
	elseif($_GET['action']=="process_application"){
		require("execute_scripts/member_admin/process_application.inc");
	}
	elseif($_GET['action']=="create_workgroup"){
		require("execute_scripts/member_admin/create_workgroup.inc");
	}
	elseif($_GET['action']=="edit_workgroup"){
		require("execute_scripts/member_admin/edit_workgroup.inc");
	}

}

elseif($_GET['type']=="forum_admin" && isset($_SESSION['is_forum_admin'])) {
	if($_GET['action']=="new_category"){
		require("execute_scripts/forum_admin/new_category.inc");
	}
	elseif($_GET['action']=="edit_category"){
		require("execute_scripts/forum_admin/edit_category.inc");
	}
	elseif($_GET['action']=="new_forum"){
		require("execute_scripts/forum_admin/new_forum.inc");
	}
	elseif($_GET['action']=="edit_forum"){
		require("execute_scripts/forum_admin/edit_forum.inc");
	}
	elseif($_GET['action']=="edit_topic"){
		require("execute_scripts/forum_admin/edit_topic.inc");
	}
	elseif($_GET['action']=="edit_post"){
		require("execute_scripts/forum_admin/edit_post.inc");
	}
	elseif($_GET['action']=="edit_user"){
		require("execute_scripts/forum_admin/edit_user.inc");
	}
}

elseif($_GET['type']=="vote_admin" && isset($_SESSION['is_vote_admin'])) {
	if($_GET['action']=="edit_vote"){
		require("execute_scripts/vote_admin/edit_vote.inc");
	}
	elseif($_GET['action']=="create_new_vote"){
		require("execute_scripts/vote_admin/create_new_vote.inc");
	}
	elseif($_GET['action']=="edit_alternatives"){
		require("execute_scripts/vote_admin/edit_alternatives.inc");
	}
	elseif($_GET['action']=="edit_alternative"){
		require("execute_scripts/vote_admin/edit_alternative.inc");
	}
	elseif($_GET['action']=="edit_user"){
		require("execute_scripts/vote_admin/edit_user.inc");
	}
}

elseif($_GET['type']=="treasurer" && isset($_SESSION['is_treasurer'])) {

}

elseif($_GET['type']=="superadmin" && isset($_SESSION['is_superadmin'])) {
	if($_GET['action']=="edit_admin"){
		require("execute_scripts/superadmin/edit_admin.inc");
	}
}


// Execute redirect if data processed above
if(isset($redirect)){
	header("Location: $redirect");
	exit();
}

?>