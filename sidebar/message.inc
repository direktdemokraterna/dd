<ul>
	<li>
		<?php
			_h2(_t("Messages"));
			\View\general::output_link_list("message", array(
				"inbox" => "Inbox"
				,"outbox" => "Sent"
				,"write" => "Write message"
				));
		?>
	</li>
</ul>