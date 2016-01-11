<ul>
	<li>
		<?php
			__h2(_t("Messages"));
			\View\controls::output_link_list("message", array(
				"inbox" => _t("Inbox")
				,"outbox" => _t("Sent", array("form" => "plural"))
				,"write" => _t("Write message")
				));
		?>
	</li>
</ul>