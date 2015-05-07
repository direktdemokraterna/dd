<div id="sidebar">

<?php

if($_GET['type']=="member") {
	require("sidebar/member.inc");
}

elseif($_GET['type']=="message") {
	require("sidebar/message.inc");
}

elseif($_GET['type']=="workgroup") {
	require("sidebar/workgroup.inc");
}

elseif($_GET['type']=="forum") {
	require("sidebar/forum.inc");
}

elseif($_GET['type']=="vote") {
	require("sidebar/vote.inc");
}

elseif($_GET['type']=="admin_roles") {
	require("sidebar/admin_roles.inc");
}

elseif($_GET['type']=="member_admin") {
	require("sidebar/member_admin.inc");
}

elseif($_GET['type']=="forum_admin") {
	require("sidebar/forum_admin.inc");
}

elseif($_GET['type']=="treasurer") {
	require("sidebar/treasurer.inc");
}

elseif($_GET['type']=="superadmin") {
	require("sidebar/superadmin.inc");
}



require("sidebar/default.inc");

?>
