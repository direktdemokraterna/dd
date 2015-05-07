<?php db_user::update_last_activity_time($_SESSION['id']); ?>
<?php include("menubar.inc"); ?>


<div id="wrap">

<div class="header">

	<div id="header-logo">
		<a href="index.php"><img id="dd-logo" src="images/direktdemokraterna-logotyp.png"></a>
	</div>

</div>


<div class="main">

	<?php include("primary_content.inc"); ?>

	<?php include("sidebar.inc"); ?>

</div>


</div>