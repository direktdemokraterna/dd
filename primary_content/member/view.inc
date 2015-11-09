<?php
	$user_id = isset($_GET['id']) ? $_GET['id'] : $_SESSION['id']; 
	$userinfo = db_user::get_user_data($user_id); ?>

<h1><?php echo $userinfo['first_name'] . " " . $userinfo['last_name']; ?></h1>

<?php if($userinfo['deletion_time']) : ?>

	<div class="user_presentation_left">

	<p><a href="index.php?type=forum&action=topics_by_user&id=<?php echo $userinfo['id']; ?>">Trådstarter (<?php echo $userinfo['number_of_topics']; ?>)</a></p>
	<p><a href="index.php?type=forum&action=posts_by_user&id=<?php echo $userinfo['id']; ?>">Postade inlägg (<?php echo $userinfo['number_of_posts']; ?>)</a></p>

	</div>

	<div class="user_presentation_right">

	<p>Den här medlemmens medlemskap avslutades <?php echo general_helpers::show_date($userinfo['deletion_time']); ?>.</p>

	<?php if(isset($_SESSION['is_member_admin'])) : ?>
		<p><form method="post" action="" class="standard-form">
			<input type="hidden" name="restore_user" value="1">
			<input type="submit" value="Återställ användare" style="width: auto;">
		</form></p>
	<?php endif; ?>

<?php else : ?>

	<div class="user_presentation_left">
	<img class="image150" src="<?php echo USERIMG_PATH . $userinfo['image']; ?>">

	<p><a href="index.php?type=message&action=write&id=<?php echo $userinfo['id']; ?>">Skicka meddelande</a></p>
	<p><a href="index.php?type=forum&action=topics_by_user&id=<?php echo $userinfo['id']; ?>">Trådstarter (<?php echo $userinfo['number_of_topics']; ?>)</a></p>
	<p><a href="index.php?type=forum&action=posts_by_user&id=<?php echo $userinfo['id']; ?>">Postade inlägg (<?php echo $userinfo['number_of_posts']; ?>)</a></p>

	</div>

	<div class="user_presentation_right">

	<?php
		$admin_roles = db_admin::get_admin_roles_for_user($user_id);
		foreach($admin_roles as $row){
			echo "<p>Är <a href=\"index.php?type=member&action=admin_description&id=" . $row['id'] . "\">" . strtolower($row['title']) . "</a></p>";
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
	<?php echo \forum_helpers::bbcode_to_html($userinfo['description']); ?>
	</p>

	<br>

	<?php
		if ($user_id == $_SESSION['id']) {
			echo "<p>";
			\View\general::output_internal_link("Ändra mina uppgifter", "member", "settings");
			echo "</p>";
		} 
		elseif(isset($_SESSION['is_member_admin'])) {
			echo "<p>";
			\View\general::output_internal_link("Ändra uppgifter för denna användare", "member_admin", "edit", 
				"id=" . $user_id);
			echo "</p>";
		}
	?>

	<?php if(isset($_SESSION['is_forum_admin'])) : ?>
		<p><a href="index.php?type=forum_admin&action=edit_user&id=<?php echo $user_id; ?>">Ställ in forumbehörigheter för denna användare</a></p>
	<?php endif; ?>

	<?php if(isset($_SESSION['is_vote_admin'])) : ?>
		<p><a href="index.php?type=vote_admin&action=edit_user&id=<?php echo $user_id; ?>">Ställ in valkretsbehörigheter för denna användare</a></p>
	<?php endif; ?>

	<?php if(isset($_SESSION['is_superadmin'])) : ?>
		<p><a href="index.php?type=superadmin&action=edit_admin&id=<?php echo $user_id; ?>">Ställ in administratörsrättigheter för denna användare</a></p>
	<?php endif; ?>

	<?php if(isset($_SESSION['is_member_admin'])) : ?>
		<form method="post" action="" class="standard-form" onsubmit="confirm('Vill du verkligen ta bort denna användare?');">
			<input type="hidden" name="delete_user" value="1">
			<input type="submit" value="Ta bort användare" style="width: auto;">
		</form>
	<?php endif; ?>

<?php endif; ?>

</div>