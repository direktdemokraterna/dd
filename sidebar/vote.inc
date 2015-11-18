<ul>
	<li>
		<?php 
			_h2("Propositions");
			\View\general::output_link_list("vote", array(
			"list_props" => "List active propositions"
			,"list_affirmed_props" => "List affirmed propositions"
			,"add_prop" => "Create proposition"
			));
		?>
	</li>
	<li>
		<?php 
			\View\general::output_search_box("propositions", "proposition", "search_prop", 101);
		?>
	</li>
	<li>
		<?php 
			_h2("Votes");
			\View\general::output_link_list("vote", array(
			"list_active_votes" => "List active votes"
			,"list_old_votes" => "List old votes"
			));
		?>
	</li>
	<li>
		<?php 
			\View\general::output_search_box("votes", "vote", "search", 103);
		?>
	</li>
	<li>
		<?php
			_h2("Delegates");
			$is_delegate = db_delegate::is_user_delegate($_SESSION['id']);
			\View\general::output_link_list("vote", array(
			"list_delegates" => "List delegates"
			,"delegations" => "Handle delegations"
			,"delegate_settings" => ($is_delegate ? "Handle" : "Become a") . " delegate"
			));
		?>
	</li>
</ul>