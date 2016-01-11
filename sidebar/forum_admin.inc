<ul>
	<li>
		<?php
			_h2(_t("Alternatives"));
			\View\controls::output_link_list("forum_admin", array(
				"list_categories" => _t("List categories")
				,"new_category" => _t("Create new category")
				,"list_forums" => _t("List forums")
				,"new_forum" => _t("Create new forum")
				));
		?>
	</li>
</ul>