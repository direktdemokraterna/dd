<ul>
	<li>
		<?php
			_h2(_t("Members"));
			\View\general::output_link_list("member", array(
				"list" => "See all members"
				,"settings" => "Change settings"
				,"calendar" => "Calendar"
				));
		?>
	</li>
	<li>
		<?php \View\general::output_search_box("member", "member", "search", 101); ?>
	</li>
</ul>