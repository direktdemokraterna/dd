<ul>
	<li class="members">
		<?php
			__h2("Medlemmar");
			\View\controls::output_link_list("member", array(
				"list" => "Visa alla medlemmar"
				,"settings" => "Ändra inställningar"
				,"calendar" => "Kalender"
				));
		?>
	</li>
	<li class="search-members">
		<?php \View\controls::output_search_box("medlemmar", "member", "search", 101); ?>
	</li>
</ul>