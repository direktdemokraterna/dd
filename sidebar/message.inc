<ul>
	<li>
		<?php
			_h2(_t("Messages"));
			\View\general::output_link_list("message", array(
				"inbox" => _t("Inbox")
				,"outbox" => _t("Sent", array("form" => "plural"))
				,"write" => _t("Write message")
				));
		?>
	</li>
</ul>