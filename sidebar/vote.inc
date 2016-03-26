<ul>
	<li>
		<?php 
			__h2(_t("Propositions"));
			\View\controls::output_link_list("vote", array(
			"list_props" => _t("List active propositions")
			,"list_affirmed_props" => _t("List affirmed propositions")
			,"add_prop" => _t("Create proposition")
			));
		?>
	</li>
	<li>
		<?php 
			\View\controls::output_search_box("propositions", "vote", "search_prop", 101);
		?>
	</li>
	<li>
		<?php 
			__h2(_t("Votes"));
			\View\controls::output_link_list("vote", array(
			"list_active_votes" => _t("List active votes")
			,"list_old_votes" => _t("List old votes")
			));
		?>
	</li>
	<li>
		<?php 
			\View\controls::output_search_box("votes", "vote", "search", 103);
		?>
	</li>
	<li>
		<?php
			__h2(_t("Delegates"));
			$is_delegate = db_delegate::is_user_delegate($_SESSION['id']);
			\View\controls::output_link_list("vote", array(
			"list_delegates" => _t("List delegates")
			,"delegations" => _t("Handle delegations")
			,"delegate_settings" => _t(($is_delegate ? "Handle" : "Become a") . " delegate")
			));
		?>
	</li>
</ul>