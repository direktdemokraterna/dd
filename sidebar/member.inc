<ul>
	<li>
		<?php
			__h2("Medlemmar");
			\View\controls::output_link_list("member", array(
				"list" => "Visa alla medlemmar"
				,"settings" => "Ändra inställningar"
				,"calendar" => "Kalender"
				));
		?>
	</li>
	<li>
		<?php \View\controls::output_search_box("medlemmar", "member", "search", 101); ?>
	</li>
</ul>