<ul>
	<li>
		<?php
			__h2(_t("Alternatives"));
			$links = array(
				"overview" => _t("Overview")
				,"ny_inbetalning" => _t("Incoming payment")
				,"ny_utbetalning" => _t("Outgoing payment")
				,"medlemsavgifter" => _t("Member fees")
				);
			\View\controls::output_link_list("treasurer", $links);
		?>
	</li>
</ul>