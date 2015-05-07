<?php $userinfo = db_user::get_user_data($_GET['id']); ?>

<h1><?php echo $userinfo['first_name'] . " " . $userinfo['last_name']; ?></h1>

<div class="user_presentation_left">
<img class="image150" src="<?php echo USERIMG_PATH . $userinfo['image']; ?>">

<p><a href="index.php?type=message&action=write&id=<?php echo $userinfo['id']; ?>">Skicka meddelande</a></p>
<p><a href="index.php?type=forum&action=topics_by_user&id=<?php echo $userinfo['id']; ?>">Trådstarter (<?php echo $userinfo['number_of_topics']; ?>)</a></p>
<p><a href="index.php?type=forum&action=posts_by_user&id=<?php echo $userinfo['id']; ?>">Postade inlägg (<?php echo $userinfo['number_of_posts']; ?>)</a></p>

</div>

<div class="user_presentation_right">

<?php
	$admin_roles = db_admin::get_admin_roles_for_user($_GET['id']);
	foreach($admin_roles as $row){
		echo "<p>Är <a href=\"index.php?type=admin_roles&action=description&id=" . $row['id'] . "\">" . strtolower($row['title']) . "</a></p>";
	}
?>

<p>Senast inloggad: <?php echo general_helpers::show_date($userinfo['last_activity_time']); ?></p>
<?php if($userinfo['show_email']==1) : ?>
	<p>Mejladress: <?php echo $userinfo['email']; ?></p>
<?php endif; ?>
<?php if($userinfo['show_telephone']==1) : ?>
	<?php if(!empty($userinfo['telephone1'])) : ?>
		<p>Telefonnummer: <?php echo $userinfo['telephone1']; ?></p>
	<?php endif; ?>
	<?php if(!empty($userinfo['telephone2'])) : ?>
		<p>Telefonnummer: <?php echo $userinfo['telephone2']; ?></p>
	<?php endif; ?>
<?php endif; ?>
<?php if($userinfo['show_skype']==1 && !empty($userinfo['skype_name'])) : ?>
	<p>Skype användarnamn: <?php echo $userinfo['skype_name']; ?></p>
<?php endif; ?>
<p>Kommun: <?php echo $userinfo['county']; ?></p>
<p>Län: <?php echo $userinfo['region']; ?></p>

<p>Presentation:<br>
<?php echo nl2br($userinfo['description']); ?>
</p>

</div>