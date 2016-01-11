<ul>
	<li>
		<?php
			_h2(_t("Alternatives"));
			$links = array(
				"list" => _t("See all members")
				,"create_new" => _t("Create new member")
				);
			if (db_user::get_all_user_applications())
				$links['list_applications'] = _t("Handle applications");
			$links['create_workgroup'] = _t("Create workgroup");
			\View\controls::output_link_list("member_admin", $links);
		?>
	</li>
</ul>