<div id="main-content">

<?php

echo general_helpers::check_report_messages();

$subpage = navigation_helpers::get_subpage();
require($subpage);

?>

</div>

	