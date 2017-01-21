<ul>
	<li class="sidebar-propositions">
		<?php 
			__h2("Propositioner");
			\View\controls::output_link_list("vote", array(
			"list_props" => "Visa aktiva propositioner"
			,"list_affirmed_props" => "Visa beviljade propositioner"
			,"add_prop" => "Skapa proposition"
			));
		?>
	</li>
	<li class="">
		<?php 
			\View\controls::output_search_box("propositioner", "vote", "search_prop", 101);
		?>
	</li>
	<li>
		<?php 
			__h2("Omröstningar");
			\View\controls::output_link_list("vote", array(
			"list_active_votes" => "Visa pågående omröstningar"
			,"list_old_votes" => "Visa avslutade omröstningar"
			));
		?>
	</li>
	<li>
		<?php 
			\View\controls::output_search_box("omröstningar", "vote", "search", 103);
		?>
	</li>
	<li>
		<?php
			__h2("Delegater");
			$is_delegate = db_delegate::is_user_delegate($_SESSION['id']);
			\View\controls::output_link_list("vote", array(
			"list_delegates" => "Visa delegater"
			,"delegations" => "Hantera delegeringar"
			,"delegate_settings" => ($is_delegate ? "Hantera" : "Bli") . " delegat")
			);
		?>
	</li>
</ul>