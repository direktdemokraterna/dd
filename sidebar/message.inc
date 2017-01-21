<ul>
	<li>
		<?php
			__h2("Meddelanden");
			\View\controls::output_link_list("message", array(
				"inbox" => "Inkorg"
				,"outbox" => "Skickade"
				,"write" => "Skriv meddelande"
				));
		?>
	</li>
</ul>