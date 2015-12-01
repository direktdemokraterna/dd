<ul>
	<li>
		<?php 
			_h2(_t("Vote admin"));
			\View\general::output_link_list("vote_admin", array(
			"constituencylist" => _t("List constituencies")
			,"create_constituency" => _t("Create new constituency")
			,"votelist" => _t("List votes")
			,"create_new_vote" => _t("Create new vote")
			));
		?>
	</li>
</ul>