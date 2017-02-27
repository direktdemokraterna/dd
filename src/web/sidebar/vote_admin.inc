<ul>
	<li class="alternatives">
		<?php 
			__h2("Valadministratör");
			\View\controls::output_link_list("vote_admin", array(
			"constituencylist" => "Visa valkretsar"
			,"create_constituency" => "Skapa ny valkrets"
			,"votelist" => "Visa omröstningar"
			,"create_new_vote" => "Skapa ny omröstning"
			));
		?>
	</li>
</ul>