<ul>
	<li>
		<?php
			__h2("Alternativ");
			\View\controls::output_link_list("forum_admin", array(
				"list_categories" => "Visa kategorier"
				,"new_category" => "Skapa ny kategori"
				,"list_forums" => "Visa forum"
				,"new_forum" => "Skapa nytt forum"
				));
		?>
	</li>
</ul>