<ul>
	<li class="alternatives">
		<?php
			__h2("Alternativ");
			$links = array(
				"overview" => "Översikt"
				,"ny_inbetalning" => "Inkommande betalningar"
				,"ny_utbetalning" => "Utgående betalningar"
//				,"medlemsavgifter" => "Medlemsavgifter"
				);
			\View\controls::output_link_list("treasurer", $links);
		?>
	</li>
</ul>