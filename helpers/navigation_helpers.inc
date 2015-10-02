<?php

class navigation_helpers {
public static $DIVISIONS = Array(
	"member" => array("pages" => Array(
		"list" => array("actions" => array(), "page" => "memberlist.inc")
		,"view" => array("actions" => array(), "page" => "view.inc")
		,"notices" => array("actions" => array(), "page" => "notices.inc")
		,"settings" => array("actions" => array(), "page" => "settings.inc")
		,"calendar" => array("actions" => array(), "page" => "calendar.inc")
		,"calendar_add" => array("actions" => array(), "page" => "calendar_add.inc")
		,"calendar_edit" => array("actions" => array(), "page" => "calendar_edit.inc")
		,"admin_description" => array("actions" => array(), "page" => "admin_description.inc")
		,"admin_list" => array("actions" => array(), "page" => "admin_list.inc")
		,"search" => array("actions" => array(), "page" => "search.inc"))
	,"default_page" => "memberlist.inc", "role" => null)

	,"message" => array("pages" => Array(
		"inbox" => array("actions" => array(), "page" => "inbox.inc")
		,"outbox" => array("actions" => array(), "page" => "outbox.inc")
		,"write" => array("actions" => array(), "page" => "write.inc")
		,"view" => array("actions" => array(), "page" => "view.inc"))
	, "default_page" => "inbox.inc", "role" => null)

	,"workgroup" => array("pages" => Array(
		"listall" => array("actions" => array(), "page" => "listall.inc")
		,"listproposed" => array("actions" => array(), "page" => "listproposed.inc")
		,"create" => array("actions" => array(), "page" => "create.inc")
		,"edit" => array("actions" => array(), "page" => "edit.inc")
		,"edit" => array("actions" => array(), "page" => "edit.inc")
		,"view" => array("actions" => array(), "page" => "view.inc")
		,"cancel_exclude" => array("actions" => array(), "page" => "view.inc")
		,"support_exclude" => array("actions" => array(), "page" => "view.inc")
		,"support_candidate" => array("actions" => array(), "page" => "view.inc")
		,"cancel_support_candidate" => array("actions" => array(), "page" => "view.inc")
		,"submit_candidacy" => array("actions" => array(), "page" => "view.inc")
		,"cancel_candidacy" => array("actions" => array(), "page" => "view.inc")
		,"support_workgroup" => array("actions" => array(), "page" => "view.inc")
		,"cancel_support_workgroup" => array("actions" => array(), "page" => "view.inc")
		,"search" => array("actions" => array(), "page" => "search.inc"))
, "default_page" => "listall.inc", "role" => null)

,"admin_role" => array("pages" => 
	Array("description" => array("actions" => array(), "page" => "description.inc"))
	, "default_page" => null, "role" => null)

,"forum" => array("pages" => Array(
	"show_forums" => array("actions" => array(), "page" => "show_forums.inc")
	,"show_topics" => array("actions" => array(), "page" => "show_topics.inc")
	,"show_posts" => array("actions" => array(), "page" => "show_posts.inc")
	,"new_topic" => array("actions" => array(), "page" => "new_topic.inc")
	,"new_post" => array("actions" => array(), "page" => "new_post.inc")
	,"report" => array("actions" => array(), "page" => "report_post.inc")
	,"edit" => array("actions" => array(), "page" => "edit_post.inc")
	,"add" => array("actions" => array(), "page" => "add_to_post.inc")
	,"topics_by_user" => array("actions" => array(), "page" => "topics_by_user.inc")
	,"posts_by_user" => array("actions" => array(), "page" => "posts_by_user.inc")
	,"search" => array("actions" => array(), "page" => "search.inc"))
, "default_page" => "show_forums.inc", "role" => null)

,"vote" => array("pages" => Array(
	"add_prop" => array("actions" => array(), "page" => "add_prop.inc")
	,"list_props" => array("actions" => array(), "page" => "list_props.inc")
	,"list_old_props" => array("actions" => array(), "page" => "list_old_props.inc")
	,"view_prop" => array("actions" => array(), "page" => "view_prop.inc")
	,"delegate_settings" => array("actions" => array(), "page" => "delegate_settings.inc")
	,"view_delegate" => array("actions" => array(), "page" => "view_delegate.inc")
	,"list_delegates" => array("actions" => array(), "page" => "list_delegates.inc")
	,"delegations" => array("actions" => array(), "page" => "delegations.inc")
	,"list_active_votes" => array("actions" => array(), "page" => "list_active_votes.inc")
	,"list_old_votes" => array("actions" => array(), "page" => "list_old_votes.inc")
	,"view_vote" => array("actions" => array(), "page" => "view_vote.inc")
	,"delegate_votes" => array("actions" => array(), "page" => "delegate_votes.inc")
	,"add_alternative" => array("actions" => array(), "page" => "add_alternative.inc")
	,"view_ballots" => array("actions" => array(), "page" => "view_ballots.inc")
	,"view_prop_ballots" => array("actions" => array(), "page" => "view_prop_ballots.inc")
	,"search" => array("actions" => array(), "page" => "search.inc"))
, "default_page" => "list_active_votes.inc", "role" => null)

,"member_admin" => array("pages" => Array(
	"create_new" => array("actions" => array(), "page" => "create_new.inc")
	,"edit" => array("actions" => array(), "page" => "edit.inc")
	,"memberlist" => array("actions" => array(), "page" => "memberlist.inc")
	,"list_applications" => array("actions" => array(), "page" => "list_applications.inc")
	,"process_application" => array("actions" => array(), "page" => "process_application.inc")
	,"view_delegate" => array("actions" => array(), "page" => "view_delegate.inc")
	,"list_delegates" => array("actions" => array(), "page" => "list_delegates.inc")
	,"create_workgroup" => array("actions" => array(), "page" => "create_workgroup.inc")
	,"edit_workgroup" => array("actions" => array(), "page" => "edit_workgroup.inc"))
, "default_page" => "memberlist.inc", "role" => "is_member_admin")

,"forum_admin" => array("pages" => Array(
	"new_category" => array("actions" => array(), "page" => "new_category.inc")
	,"list_categories" => array("actions" => array(), "page" => "list_categories.inc")
	,"edit_category" => array("actions" => array(), "page" => "edit_category.inc")
	,"new_forum" => array("actions" => array(), "page" => "new_forum.inc")
	,"list_forums" => array("actions" => array(), "page" => "list_forums.inc")
	,"edit_forum" => array("actions" => array(), "page" => "edit_forum.inc")
	,"edit_topic" => array("actions" => array(), "page" => "edit_topic.inc")
	,"edit_post" => array("actions" => array(), "page" => "edit_post.inc")
	,"edit_user" => array("actions" => array(), "page" => "edit_user.inc"))
, "default_page" => "list_categories.inc", "role" => "is_forum_admin")

,"vote_admin" => array("pages" => Array(
	"create_new_vote" => array("actions" => array(), "page" => "create_new_vote.inc")
	,"edit_vote" => array("actions" => array(), "page" => "edit_vote.inc")
	,"edit_alternatives" => array("actions" => array(), "page" => "edit_alternatives.inc")
	,"edit_alternative" => array("actions" => array(), "page" => "edit_alternative.inc")
	,"edit_user" => array("actions" => array(), "page" => "edit_user.inc")
	,"edit_constituency" => array("actions" => array(), "page" => "edit_constituency.inc")
	,"constituencylist" => array("actions" => array(), "page" => "constituencylist.inc")
	,"edit_post" => array("actions" => array(), "page" => "edit_post.inc")
	,"edit_user" => array("actions" => array(), "page" => "edit_user.inc"))
, "default_page" => "votelist.inc", "role" => "is_vote_admin")

,"treasurer" => array("pages" => 
	Array("treasurer" => array("actions" => array(), "page" => "treasurer.inc"))
	, "default_page" => "treasurer.inc", "role" => "is_treasurer")

,"superadmin" => array("pages" => 
	Array("edit_admin" => array("actions" => array(), "page" => "edit_admin.inc"))
	, "default_page" => "memberlist.inc", "role" => "is_superadmin")
);

public static function execute_action_script() {
}

public static function get_subpage() {
	$path = self::get_specific_path();
	return $path != null 
	? $path
	: "primary_content/first_page.inc";
}

private static function get_specific_path() {
	$divisionName = $_GET['type'];
	$division = isset(self::$DIVISIONS[$divisionName]) 
	? self::$DIVISIONS[$divisionName] 
	: null;
	if($division == null || !self::user_has_access($division)) return null;

	$actionName = $_GET['action'];
	$pages = $division["pages"];
	$pageName = isset($pages[$actionName])
	? $pages[$actionName]["page"] 
	: $division["default_page"];
	return $pageName != null ? "primary_content/" . $divisionName . "/" . $pageName : null;
}

private static function user_has_access($division) {
	return $division["role"] == null || isset($_SESSION[$division["role"]]);
}
} //End of class