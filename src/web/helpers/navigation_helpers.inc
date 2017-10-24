<?php
class navigation_helpers {
	private static $divisions = null;

	public static function get_subpage() {
		$path = self::get_specific_path();
		return $path
			? $path
			: "./includes/primary_content/first_page.inc";
	}

	public static function get_sidebar_page() {
		$page = self::get_sidebar_page_name();
		return "./includes/sidebar/$page.inc";
	}

	public static function handle_action_request() 
	{
		if (self::restore_post())
			return;
		$divisionName = $_GET['type'];
		$execute_page = self::get_execute_page($divisionName);
		if ($execute_page && !self::is_view_request($execute_page))
			self::execute_action($divisionName, $execute_page);
	}

	private static function get_sidebar_page_name() {
		$divisionName = $_GET['type'];
		$division = self::get_division($divisionName);
		return $division ? $divisionName : "forum";
	}

	private static function get_execute_page($divisionName) 
	{
		$division = self::get_division($divisionName);
		return $division 
			? $division->get_page($_GET['action'], Page_info::EXECUTE)
			: null;
	}

	private static function restore_post() {
		if (empty($_SESSION['previous_post'])) return false;
		foreach ($_SESSION['previous_post'] as $key => $value)
			$_POST[$key] = $value;
		unset($_SESSION['previous_post']);
		return true;
	}

	private static function is_view_request($pageInfo) {
		return empty($_POST) && $pageInfo->is_applicable(Page_info::VIEW);
	}

	private static function execute_action($divisionName, $pageInfo) 
	{
		if($_SESSION['csrf_token'] != $_POST['csrf_token'])
			\Logic\util::report_error("CSRF-fel, ladda om sidan och försök igen.");
		else{
			$path = "./includes/execute_scripts/" . $divisionName . "/" . $pageInfo->name;
			require($path);
			$_SESSION['csrf_token'] = null;
		}
		if (empty($redirect)) {
			$redirect = $_SERVER['REQUEST_URI'];
			if (\Logic\util::page_has_error())
				$_SESSION['previous_post'] = $_POST;
		}
		header("Location: $redirect");
		exit();
	}

	private static function get_specific_path() {
		$divisionName = $_GET['type'];
		$division = self::get_division($divisionName);
		if ($division == null) return null;
		$pageName = $division->get_page_name($_GET['action']);
		return $pageName != null 
			? self::get_page_path($divisionName, $pageName)
			: null;
	}

	private static function get_page_path($divisionName, $pageName) {
		$parts = explode('/', $pageName);
		$is_qualified_page_name = count($parts) == 2;
		return "./includes/primary_content/" . ($is_qualified_page_name ? '' : $divisionName . "/") . $pageName;
	}

	private static function get_division($divisionName) {
		$divisions = self::get_divisions();
		$division = isset($divisions[$divisionName]) 
			? $divisions[$divisionName] 
			: null;
		return $division != null && $division->user_has_access() 
			? $division 
			: null;
	}

	private static function get_divisions() {
		if (self::$divisions == null) {
			self::$divisions = self::create_divisions();
		}
		return self::$divisions;
	}	

	private static function create_divisions() {
		return array(
			"member" => Division_info::create(array(
				"list" => Page_info::create("memberlist.inc")
				,"view" => Page_info::create("view.inc", Page_info::VIEW_AND_EXECUTE)
				,"notices" => Page_info::create("notices.inc")
				,"settings" => Page_info::create("settings.inc", Page_info::VIEW_AND_EXECUTE)
				,"calendar" => Page_info::create("calendar.inc", Page_info::VIEW_AND_EXECUTE)
				,"calendar_add" => Page_info::create("calendar_add.inc", Page_info::VIEW_AND_EXECUTE)
				,"calendar_edit" => Page_info::create("calendar_edit.inc", Page_info::VIEW_AND_EXECUTE)
				,"admin_description" => Page_info::create("admin_description.inc")
				,"admin_list" => Page_info::create("admin_list.inc")
				,"search" => Page_info::create("search.inc"))
			,"memberlist.inc")

			,"message" => Division_info::create(array(
				"inbox" => Page_info::create("inbox.inc", Page_info::VIEW_AND_EXECUTE)
				,"outbox" => Page_info::create("outbox.inc", Page_info::VIEW_AND_EXECUTE)
				,"write" => Page_info::create("write.inc", Page_info::VIEW_AND_EXECUTE)
				,"view" => Page_info::create("view.inc", Page_info::VIEW_AND_EXECUTE))
			, "inbox.inc")

			,"workgroup" => Division_info::create(array(
				"listall" => Page_info::create("listall.inc")
				,"listproposed" => Page_info::create("listproposed.inc")
				,"create" => Page_info::create("create.inc", Page_info::VIEW_AND_EXECUTE)
				,"edit" => Page_info::create("edit.inc", Page_info::VIEW_AND_EXECUTE)
				,"view" => Page_info::create("view.inc", Page_info::VIEW_AND_EXECUTE)
				,"cancel_exclude" => Page_info::create("view.inc")
				,"support_exclude" => Page_info::create("view.inc")
				,"support_candidate" => Page_info::create("view.inc")
				,"cancel_support_candidate" => Page_info::create("view.inc")
				,"submit_candidacy" => Page_info::create("view.inc")
				,"cancel_candidacy" => Page_info::create("view.inc")
				,"support_workgroup" => Page_info::create("view.inc")
				,"cancel_support_workgroup" => Page_info::create("view.inc")
				,"search" => Page_info::create("search.inc"))
			,"listall.inc")

			,"forum" => Division_info::create(array(
				"show_forums" => Page_info::create("show_forums.inc", Page_info::VIEW_AND_EXECUTE)
				,"show_topics" => Page_info::create("show_topics.inc", Page_info::VIEW_AND_EXECUTE)
				,"show_posts" => Page_info::create("show_posts.inc", Page_info::VIEW_AND_EXECUTE)
				,"new_topic" => Page_info::create("new_topic.inc")
				,"new_post" => Page_info::create("new_post.inc")
				,"report" => Page_info::create("report_post.inc", Page_info::VIEW_AND_EXECUTE)
				,"edit" => Page_info::create("edit_post.inc", Page_info::VIEW_AND_EXECUTE)
				,"add" => Page_info::create("add_to_post.inc", Page_info::VIEW_AND_EXECUTE)
				,"delete" => Page_info::create("delete_post.inc", Page_info::EXECUTE)
				,"topics_by_user" => Page_info::create("topics_by_user.inc")
				,"posts_by_user" => Page_info::create("posts_by_user.inc")
				,"search" => Page_info::create("search.inc"))
			, "show_forums.inc")

			,"vote" => Division_info::create(array(
				"add_prop" => Page_info::create("add_prop.inc", Page_info::VIEW_AND_EXECUTE)
				,"list_props" => Page_info::create("list_props.inc")
				,"list_affirmed_props" => Page_info::create("list_affirmed_props.inc")
				,"view_prop" => Page_info::create("view_prop.inc", Page_info::VIEW_AND_EXECUTE)
				,"delegate_settings" => Page_info::create("delegate_settings.inc", Page_info::VIEW_AND_EXECUTE)
				,"view_delegate" => Page_info::create("view_delegate.inc", Page_info::VIEW_AND_EXECUTE)
				,"list_delegates" => Page_info::create("list_delegates.inc")
				,"delegations" => Page_info::create("delegations.inc", Page_info::VIEW_AND_EXECUTE)
				,"list_active_votes" => Page_info::create("list_active_votes.inc")
				,"list_old_votes" => Page_info::create("list_old_votes.inc")
				,"view_vote" => Page_info::create("view_vote.inc", Page_info::VIEW_AND_EXECUTE)
				,"add_alternative" => Page_info::create("add_alternative.inc", Page_info::VIEW_AND_EXECUTE)
				,"view_ballots" => Page_info::create("view_ballots.inc")
				,"view_prop_ballots" => Page_info::create("view_prop_ballots.inc")
				,"search" => Page_info::create("search.inc")
				,"search_prop" => Page_info::create("search_prop.inc"))
			, "list_active_votes.inc")

			,"member_admin" => Division_info::create(array(
				"create_new" => Page_info::create("create_new.inc", Page_info::VIEW_AND_EXECUTE)
				,"edit" => Page_info::create("edit.inc", Page_info::VIEW_AND_EXECUTE)
				,"list_applications" => Page_info::create("list_applications.inc")
				,"process_application" => Page_info::create("process_application.inc", Page_info::VIEW_AND_EXECUTE)
				,"view_delegate" => Page_info::create("view_delegate.inc")
				,"list_delegates" => Page_info::create("list_delegates.inc")
				,"create_workgroup" => Page_info::create("create_workgroup.inc", Page_info::VIEW_AND_EXECUTE)
				,"edit_workgroup" => Page_info::create("edit_workgroup.inc", Page_info::VIEW_AND_EXECUTE))
			, "member/memberlist.inc", "is_member_admin")

			,"forum_admin" => Division_info::create(array(
				"new_category" => Page_info::create("new_category.inc", Page_info::VIEW_AND_EXECUTE)
				,"list_categories" => Page_info::create("list_categories.inc")
				,"edit_category" => Page_info::create("edit_category.inc", Page_info::VIEW_AND_EXECUTE)
				,"new_forum" => Page_info::create("new_forum.inc", Page_info::VIEW_AND_EXECUTE)
				,"list_forums" => Page_info::create("list_forums.inc")
				,"edit_forum" => Page_info::create("edit_forum.inc", Page_info::VIEW_AND_EXECUTE)
				,"edit_topic" => Page_info::create("edit_topic.inc", Page_info::VIEW_AND_EXECUTE)
				,"edit_post" => Page_info::create("edit_post.inc", Page_info::VIEW_AND_EXECUTE)
				,"edit_user" => Page_info::create("edit_user.inc", Page_info::VIEW_AND_EXECUTE))
			, "list_categories.inc", "is_forum_admin")

			,"vote_admin" => Division_info::create(array(
				"constituencylist" => Page_info::create("constituencylist.inc")
				,"create_constituency" => Page_info::create("create_constituency.inc")
				,"create_new_vote" => Page_info::create("create_new_vote.inc", Page_info::VIEW_AND_EXECUTE)
				,"edit_alternative" => Page_info::create("edit_alternative.inc", Page_info::VIEW_AND_EXECUTE)
				,"edit_alternatives" => Page_info::create("edit_alternatives.inc", Page_info::VIEW_AND_EXECUTE)
				,"edit_constituency" => Page_info::create("edit_constituency.inc")
				,"edit_post" => Page_info::create("edit_post.inc")
				,"edit_user" => Page_info::create("edit_user.inc", Page_info::VIEW_AND_EXECUTE)
				,"edit_vote" => Page_info::create("edit_vote.inc", Page_info::VIEW_AND_EXECUTE)
				,"votelist" => Page_info::create("votelist.inc"))
			, "votelist.inc", "is_vote_admin")

			,"treasurer" => Division_info::create(array(
				"overview" => Page_info::create("treasurer.inc")
				,"ny_inbetalning" => Page_info::create("ny_inbetalning.inc", Page_info::VIEW_AND_EXECUTE)
				,"ny_utbetalning" => Page_info::create("ny_utbetalning.inc", Page_info::VIEW_AND_EXECUTE)
				,"medlemsavgifter" => Page_info::create("medlemsavgifter.inc")
				,"transaktion" => Page_info::create("transaktion.inc"))
			, "treasurer.inc", "is_treasurer")

			,"superadmin" => Division_info::create(array(
				"edit_admin" => Page_info::create("edit_admin.inc", Page_info::VIEW_AND_EXECUTE))
			, "member/memberlist.inc", "is_superadmin")
		);
	}
}

class Division_info {
	public $pages;
	public $default_page;
	public $role;

	public static function create($pages, $default_page = null, $role = null) {
		$division_info = new Division_info;
		$division_info->pages = $pages;
		$division_info->default_page = $default_page;
		$division_info->role = $role;
		return $division_info;
	}

	public function get_page_name($actionName) {
		$pageInfo = $this->get_page($actionName);
		return $pageInfo != null
			? $pageInfo->name 
			: $this->default_page;
	}

	public function get_page($name, $page_type = Page_info::VIEW) {
		$page = isset($this->pages[$name])
			? $this->pages[$name]
			: null;
		return $page != null && $page->is_applicable($page_type) 
			? $page 
			: null;
	}

	public function user_has_access() {
		return $this->role == null || isset($_SESSION[$this->role]);
	}
}

class Page_info {
	const VIEW = 1;
	const EXECUTE = 2;
	const VIEW_AND_EXECUTE = 3;

	public $name;
	public $page_type;
	public $show;
	public $execute;

	public static function create($name, $page_type = self::VIEW) {
		$page_info = new Page_info();
		$page_info->name = $name;
		$page_info->page_type = $page_type;
		$page_info->show = $page_info->is_applicable(self::VIEW);
		$page_info->execute = $page_info->is_applicable(self::EXECUTE);
		return $page_info;
	}

	public function is_applicable($page_type) {
		return ($page_type & $this->page_type) === $page_type;
	}
}