<div id="main-content">

<?php

echo general_helpers::check_report_messages();


if($_GET['type']=="member") {
	if($_GET['action']=="list"){
		require("primary_content/member/memberlist.inc");
	}
	elseif($_GET['action']=="view") {
		require("primary_content/member/view.inc");
	}
	elseif($_GET['action']=="notices") {
		require("primary_content/member/notices.inc");
	}
	elseif($_GET['action']=="settings") {
		require("primary_content/member/settings.inc");
	}
	elseif($_GET['action']=="calendar") {
		require("primary_content/member/calendar.inc");
	}
	elseif($_GET['action']=="calendar_add") {
		require("primary_content/member/calendar_add.inc");
	}
	elseif($_GET['action']=="calendar_edit") {
		require("primary_content/member/calendar_edit.inc");
	}
	elseif($_GET['action']=="admin_description") {
		require("primary_content/member/admin_description.inc");
	}
	elseif($_GET['action']=="admin_list") {
		require("primary_content/member/admin_list.inc");
	}
	elseif($_GET['action']=="search") {
		require("primary_content/member/search.inc");
	}
	else{
		require("primary_content/member/memberlist.inc");
	}
}

elseif($_GET['type']=="message") {
	if($_GET['action']=="inbox"){
		require("primary_content/message/inbox.inc");
	}
	elseif($_GET['action']=="outbox"){
		require("primary_content/message/outbox.inc");
	}
	elseif($_GET['action']=="write"){
		require("primary_content/message/write.inc");
	}
	elseif($_GET['action']=="view"){
		require("primary_content/message/view.inc");
	}
	else{
		require("primary_content/message/inbox.inc");
	}
}

elseif($_GET['type']=="workgroup") {
	if($_GET['action']=="listall"){
		require("primary_content/workgroup/listall.inc");
	}
	elseif($_GET['action']=="listproposed"){
		require("primary_content/workgroup/listproposed.inc");
	}
	elseif($_GET['action']=="create"){
		require("primary_content/workgroup/create.inc");
	}
	elseif($_GET['action']=="view" || $_GET['action']=="cancel_exclude" || $_GET['action']=="support_exclude" || $_GET['action']=="support_candidate" || $_GET['action']=="cancel_support_candidate" || $_GET['action']=="submit_candidacy" || $_GET['action']=="cancel_candidacy" || $_GET['action']=="support_workgroup" || $_GET['action']=="cancel_support_workgroup"){
		require("primary_content/workgroup/view.inc");
	}
	elseif($_GET['action']=="search"){
		require("primary_content/workgroup/search.inc");
	}
	else{
		require("primary_content/workgroup/listall.inc");
	}
}

elseif($_GET['type']=="admin_role") {
	if($_GET['action']=="description"){
		require("primary_content/admin_role/description.inc");
	}
}

elseif($_GET['type']=="forum") {
	if($_GET['action']=="show_forums"){
		require("primary_content/forum/show_forums.inc");
	}
	elseif($_GET['action']=="show_topics"){
		require("primary_content/forum/show_topics.inc");
	}
	elseif($_GET['action']=="show_posts"){
		require("primary_content/forum/show_posts.inc");
	}
	elseif($_GET['action']=="new_topic"){
		require("primary_content/forum/new_topic.inc");
	}
	elseif($_GET['action']=="new_post"){
		require("primary_content/forum/new_post.inc");
	}
	elseif($_GET['action']=="report"){
		require("primary_content/forum/report_post.inc");
	}
	elseif($_GET['action']=="edit"){
		require("primary_content/forum/edit_post.inc");
	}
	elseif($_GET['action']=="add"){
		require("primary_content/forum/add_to_post.inc");
	}
	elseif($_GET['action']=="topics_by_user"){
		require("primary_content/forum/topics_by_user.inc");
	}
	elseif($_GET['action']=="posts_by_user"){
		require("primary_content/forum/posts_by_user.inc");
	}
	elseif($_GET['action']=="search"){
		require("primary_content/forum/search.inc");
	}
	else{
		require("primary_content/forum/show_forums.inc");
	}
}

elseif($_GET['type']=="vote") {
	if($_GET['action']=="add_prop"){
		require("primary_content/vote/add_prop.inc");
	}
	elseif($_GET['action']=="list_props"){
		require("primary_content/vote/list_props.inc");
	}
	elseif($_GET['action']=="list_old_props"){
		require("primary_content/vote/list_old_props.inc");
	}
	elseif($_GET['action']=="view_prop"){
		require("primary_content/vote/view_prop.inc");
	}
	elseif($_GET['action']=="delegate_settings"){
		require("primary_content/vote/delegate_settings.inc");
	}
	elseif($_GET['action']=="view_delegate"){
		require("primary_content/vote/view_delegate.inc");
	}
	elseif($_GET['action']=="list_delegates"){
		require("primary_content/vote/list_delegates.inc");
	}
	elseif($_GET['action']=="delegations"){
		require("primary_content/vote/delegations.inc");
	}
	elseif($_GET['action']=="list_active_votes"){
		require("primary_content/vote/list_active_votes.inc");
	}
	elseif($_GET['action']=="list_old_votes"){
		require("primary_content/vote/list_old_votes.inc");
	}
	elseif($_GET['action']=="view_vote"){
		require("primary_content/vote/view_vote.inc");
	}
	elseif($_GET['action']=="delegate_votes"){
		require("primary_content/vote/delegate_votes.inc");
	}
	elseif($_GET['action']=="add_alternative"){
		require("primary_content/vote/add_alternative.inc");
	}
	elseif($_GET['action']=="search"){
		require("primary_content/vote/search.inc");
	}
else {
	require("primary_content/vote/list_active_votes.inc");
}
}


elseif($_GET['type']=="member_admin" && isset($_SESSION['is_member_admin'])) {
	if($_GET['action']=="create_new"){
		require("primary_content/member_admin/create_new.inc");
	}
	elseif($_GET['action']=="edit"){
		require("primary_content/member_admin/edit.inc");
	}
	elseif($_GET['action']=="memberlist"){
		require("primary_content/member_admin/memberlist.inc");
	}
	elseif($_GET['action']=="list_applications"){
		require("primary_content/member_admin/list_applications.inc");
	}
	elseif($_GET['action']=="process_application"){
		require("primary_content/member_admin/process_application.inc");
	}
	else{
		require("primary_content/member_admin/memberlist.inc");
	}
}

elseif($_GET['type']=="forum_admin" && isset($_SESSION['is_forum_admin'])) {
	if($_GET['action']=="new_category"){
		require("primary_content/forum_admin/new_category.inc");
	}
	elseif($_GET['action']=="list_categories"){
		require("primary_content/forum_admin/list_categories.inc");
	}
	elseif($_GET['action']=="edit_category"){
		require("primary_content/forum_admin/edit_category.inc");
	}
	elseif($_GET['action']=="new_forum"){
		require("primary_content/forum_admin/new_forum.inc");
	}
	elseif($_GET['action']=="list_forums"){
		require("primary_content/forum_admin/list_forums.inc");
	}
	elseif($_GET['action']=="edit_forum"){
		require("primary_content/forum_admin/edit_forum.inc");
	}
	elseif($_GET['action']=="edit_topic"){
		require("primary_content/forum_admin/edit_topic.inc");
	}
	elseif($_GET['action']=="edit_post"){
		require("primary_content/forum_admin/edit_post.inc");
	}
	elseif($_GET['action']=="edit_user"){
		require("primary_content/forum_admin/edit_user.inc");
	}
	else{
		require("primary_content/forum_admin/list_categories.inc");
	}
}

elseif($_GET['type']=="vote_admin" && isset($_SESSION['is_vote_admin'])) {
	if($_GET['action']=="create_new_vote"){
		require("primary_content/vote_admin/create_new_vote.inc");
	}
	elseif($_GET['action']=="edit_vote"){
		require("primary_content/vote_admin/edit_vote.inc");
	}
	elseif($_GET['action']=="edit_alternatives"){
		require("primary_content/vote_admin/edit_alternatives.inc");
	}
	elseif($_GET['action']=="edit_alternative"){
		require("primary_content/vote_admin/edit_alternative.inc");
	}
	elseif($_GET['action']=="edit_user"){
		require("primary_content/vote_admin/edit_user.inc");
	}
	elseif($_GET['action']=="edit_constituency"){
		require("primary_content/vote_admin/edit_constituency.inc");
	}
	elseif($_GET['action']=="constituencylist"){
		require("primary_content/vote_admin/constituencylist.inc");
	}
	else{
		require("primary_content/vote_admin/votelist.inc");
	}
}

elseif($_GET['type']=="treasurer" && isset($_SESSION['is_treasurer'])) {
	require("primary_content/treasurer.inc");
}

elseif($_GET['type']=="superadmin" && isset($_SESSION['is_superadmin'])) {
	if($_GET['action']=="edit_admin"){
		require("primary_content/superadmin/edit_admin.inc");
	}
	else{
		require("primary_content/superadmin/memberlist.inc");
	}
}

else {
	require("primary_content/first_page.inc");
}

?>

</div>

	