<ul>
	<li>
		<?php
			_h2("Alternatives");
			$links = array(
				"list" => "See all members"
				,"create_new" => "Create new member"
				);
			if (db_user::get_all_user_applications())
				$links['list_applications'] = "Handle applications";
			$links['create_workgroup'] = "Create workgroup";
			\View\general::output_link_list("member", $links);
		?>
	</li>
</ul>