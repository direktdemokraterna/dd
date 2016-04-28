<ul>
	<li>
		<?php
			__h2(_t("Alternatives"));
			$links = array(
				"overview" => _t("Översikt")
				,"ny_inbetalning" => _t("Inbetalning")
				,"ny_utbetalning" => _t("Utbetalning")
				,"medlemsavgifter" => _t("Medlemsavgifter")
				);
			\View\controls::output_link_list("treasurer", $links);
		?>
	</li>
</ul>