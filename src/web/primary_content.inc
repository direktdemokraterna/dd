<div id="main-content">
	<?php
		general_helpers::show_report_messages();
		$subpage = navigation_helpers::get_subpage();
		require($subpage);
	?>
</div>

	