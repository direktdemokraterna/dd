<ul>
	<li>
		<?php
			_h2(_t("Alternatives"));
			\View\general::output_link_list("forum_admin", array(
				"list_categories" => "List categories"
				,"new_category" => "Create new category"
				,"list_forums" => "List forums"
				,"new_forum" => "Create new forum"
				));
		?>
	</li>
</ul>