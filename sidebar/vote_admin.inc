<ul>
	<li>
		<h2><?php __("vote admin"); ?></h2>
		<?php \View\general::output_link_list("vote_admin", array(
			"constituencylist" => "List constituencies"
			,"create_constituency" => "Create new constituency"
			,"votelist" => "List votes"
			,"create_new_vote" => "Create new vote"
			));
		?>
	</li>
</ul>