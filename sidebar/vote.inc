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
		<?php _h2("Search propositions"); ?>
		<form method="post" class="sidebar_search_form" action="index.php?type=vote&action=search_prop">
			<input tabindex="101" type="text" value="" name="prop_search_input" class="sidebar_search_input">
			<input tabindex="102" type="submit" class="sidebar_search_submit" value="<?php __('Search'); ?>">
		</form>
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
		<?php _h2("Search votes"); ?>
		<form method="post" class="sidebar_search_form" action="index.php?type=vote&action=search">
			<input tabindex="101" type="text" value="" name="vote_search_input" class="sidebar_search_input">
			<input tabindex="102" type="submit" class="sidebar_search_submit" value="<?php __('Search'); ?>">
		</form>
	</li>
	<li>
		<?php
			_h2("Delegates");
			$is_delegate = db_delegate::is_user_delegate($_SESSION['id']);
			\View\general::output_link_list("vote", array(
			"list_delegates" => "List delegates"
			,"delegations" => "Handle delegations"
			,"delegate_settings" => $is_delegate ? "Handle delegate" : "Become a delegate"
			));
		?>
	</li>
</ul>