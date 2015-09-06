<?php

class navigation_helpers {
	private static $MEMBER_PAGES = Array(
		"list" => "memberlist.inc"
		,"view" => "view.inc"
		,"notices" => "notices.inc"
		,"settings" => "settings.inc"
		,"calendar" => "calendar.inc"
		,"calendar_add" => "calendar_add.inc"
		,"calendar_edit" => "calendar_edit.inc"
		,"admin_description" => "admin_description.inc"
		,"admin_list" => "admin_list.inc"
		,"search" => "search.inc"
		);
	
	private static $MESSAGE_PAGES = Array(
		"inbox" => "inbox.inc"
		,"outbox" => "outbox.inc"
		,"write" => "write.inc"
		,"view" => "view.inc"
		);
	
	private static $WORKGROUP_PAGES = Array(
		"listall" => "listall.inc"
		,"listproposed" => "listproposed.inc"
		,"create" => "create.inc"
		,"edit" => "edit.inc"
		,"edit" => "edit.inc"
		,"view" => "view.inc"
		,"cancel_exclude" => "view.inc"
		,"support_exclude" => "view.inc"
		,"support_candidate" => "view.inc"
		,"cancel_support_candidate" => "view.inc"
		,"submit_candidacy" => "view.inc"
		,"cancel_candidacy" => "view.inc"
		,"support_workgroup" => "view.inc"
		,"cancel_support_workgroup" => "view.inc"
		,"search" => "search.inc"
		);

	private static $FORUM_PAGES = Array(
		"show_forums" => "show_forums.inc"
		,"show_topics" => "show_topics.inc"
		,"show_posts" => "show_posts.inc"
		,"new_topic" => "new_topic.inc"
		,"new_post" => "new_post.inc"
		,"report" => "report_post.inc"
		,"edit" => "edit_post.inc"
		,"add" => "add_to_post.inc"
		,"topics_by_user" => "topics_by_user.inc"
		,"posts_by_user" => "posts_by_user.inc"
		,"search" => "search.inc"
		);

	private static $VOTE_PAGES = Array(
		"add_prop" => "add_prop.inc"
		,"list_props" => "list_props.inc"
		,"list_old_props" => "list_old_props.inc"
		,"view_prop" => "view_prop.inc"
		,"delegate_settings" => "delegate_settings.inc"
		,"view_delegate" => "view_delegate.inc"
		,"list_delegates" => "list_delegates.inc"
		,"delegations" => "delegations.inc"
		,"list_active_votes" => "list_active_votes.inc"
		,"list_old_votes" => "list_old_votes.inc"
		,"view_vote" => "view_vote.inc"
		,"delegate_votes" => "delegate_votes.inc"
		,"add_alternative" => "add_alternative.inc"
		,"search" => "search.inc"
		);
	
	private static $ADMIN_ROLE_PAGES = Array(
		"description" => "description.inc"
		);

	private static $MEMBER_ADMIN_PAGES = Array(
		"create_new" => "create_new.inc"
		,"edit" => "edit.inc"
		,"memberlist" => "memberlist.inc"
		,"list_applications" => "list_applications.inc"
		,"process_application" => "process_application.inc"
		,"view_delegate" => "view_delegate.inc"
		,"list_delegates" => "list_delegates.inc"
		,"create_workgroup" => "create_workgroup.inc"
		,"edit_workgroup" => "edit_workgroup.inc"
		);

	private static $FORUM_ADMIN_PAGES = Array(
		"new_category" => "new_category.inc"
		,"list_categories" => "list_categories.inc"
		,"edit_category" => "edit_category.inc"
		,"new_forum" => "new_forum.inc"
		,"list_forums" => "list_forums.inc"
		,"edit_forum" => "edit_forum.inc"
		,"edit_topic" => "edit_topic.inc"
		,"edit_post" => "edit_post.inc"
		,"edit_user" => "edit_user.inc"
		);

	private static $VOTE_ADMIN_PAGES = Array(
		"create_new_vote" => "create_new_vote.inc"
		,"edit_vote" => "edit_vote.inc"
		,"edit_alternatives" => "edit_alternatives.inc"
		,"edit_alternative" => "edit_alternative.inc"
		,"edit_user" => "edit_user.inc"
		,"edit_constituency" => "edit_constituency.inc"
		,"constituencylist" => "constituencylist.inc"
		,"edit_post" => "edit_post.inc"
		,"edit_user" => "edit_user.inc"
		);

	private static $SUPER_ADMIN_PAGES = Array(
		"edit_admin" => "edit_admin.inc"
		);

	public static function get_subpage() {
		$page = self::get_specific_page();
		return $page != null 
			? $page
			: "primary_content/first_page.inc";
	}
	
	private static function get_specific_page() {
		switch ($_GET['type']) {
			case "member":
				return self::get_page("member", self::$MEMBER_PAGES, "memberlist.inc");
			case "message":
				return self::get_page("message", self::$MESSAGE_PAGES, "inbox.inc");
			case "workgroup":
				return self::get_page("workgroup", self::$WORKGROUP_PAGES, "listall.inc");
			case "admin_role":
				return self::get_page("admin_role", self::$ADMIN_ROLE_PAGES);
			case "forum":
				return self::get_page("forum", self::$FORUM_PAGES, "show_forums.inc");
			case "vote":
				return self::get_page("vote", self::$VOTE_PAGES, "list_active_votes.inc");
			case "member_admin":
				return self::get_page("member_admin", self::$MEMBER_ADMIN_PAGES, "memberlist.inc", 'is_member_admin');
			case "forum_admin":
				return self::get_page("forum_admin", self::$FORUM_ADMIN_PAGES, "list_categories.inc", 'is_forum_admin');
			case "vote_admin":
				return self::get_page("vote_admin", self::$VOTE_ADMIN_PAGES, "votelist.inc", 'is_vote_admin');
			case "treasurer":
				return isset($_SESSION['is_treasurer']) ? "primary_content/treasurer.inc" : null;
			case "superadmin":
				return self::get_page("superadmin", self::$SUPER_ADMIN_PAGES, "memberlist.inc", 'is_superadmin');
			default: return null;
		}
	}

	private static function get_page($folder, $pages, $default_page = null, $role = null) {
		if($role != null && !isset($_SESSION[$role])) return null;
		$pageName = isset($pages[$_GET['action']]) 
			? $pages[$_GET['action']] 
			: $default_page;
		return $pageName != null ? "primary_content/" . $folder . "/" . $pageName : null;
	}
} //End of class