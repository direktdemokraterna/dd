<ul>
	<li>
		<?php
			_h2(_t("Members"));
			\View\general::output_link_list("member", array(
				"list" => _t("See all members")
				,"settings" => _t("Change settings")
				,"calendar" => _t("Calendar")
				));
		?>
	</li>
	<li>
		<?php \View\general::output_search_box("member", "member", "search", 101); ?>
	</li>
</ul>