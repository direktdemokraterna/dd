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

elseif($_GET['type']=="member_admin") {
	if($_GET['action']=="create_new"){
		require("execute_scripts/member_admin/create_new.inc");
	}
	elseif($_GET['action']=="edit"){
		require("execute_scripts/member_admin/edit.inc");
	}
}

elseif($_GET['type']=="forum_admin") {
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
}

elseif($_GET['type']=="treasurer") {

}

elseif($_GET['type']=="superadmin") {
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