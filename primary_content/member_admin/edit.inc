
<h1>Redigera medlem</h1>
	
<?php $result = db_user::get_user_data($_GET['id']); ?>

<?php if($result['deletion_time']) : ?>
	<p>Denna användare ströks från medlemslistan <?php echo general_helpers::show_date($result['deletion_time']); ?>.</p>
<?php endif; ?>

<form method="post" class="standard-form" action="">
<input type="hidden" name="edit_user" value="1">
<?php
	\View\member::output_edit_fields($result);
?>
<br><input type="submit" name="" id="submit" value="Uppdatera">
</form>

<form method="post" action="" class="standard-form">
	<input type="hidden" name="change_password" value="1">
	<input type="submit" value="Byt lösenord för denna användare" style="width: auto;">
</form>

<?php if($result['deletion_time']) : ?>
	<form method="post" action="" class="standard-form">
		<input type="hidden" name="restore_user" value="1">
		<input type="submit" value="Återställ denna borttagna användare" style="width: auto;">
	</form>
<?php else : ?>
	<form method="post" action="" class="standard-form">
		<input type="hidden" name="delete_user" value="1">
		<input type="submit" value="Ta bort denna användare från medlemslistan" style="width: auto;" onclick="return confirm('Vill du verkligen ta bort denna användare?');">
	</form>
<?php endif; ?>

<?php if(isset($_SESSION['is_forum_admin'])) : ?>
	<p><a href="index.php?type=forum_admin&action=edit_user&id=<?php echo $_GET['id']; ?>">Ställ in forumbehörigheter för denna användare</a></p>
<?php endif; ?>

<?php if(isset($_SESSION['is_vote_admin'])) : ?>
	<p><a href="index.php?type=vote_admin&action=edit_user&id=<?php echo $_GET['id']; ?>">Ställ in valkretsbehörigheter för denna användare</a></p>
<?php endif; ?>

<?php if(isset($_SESSION['is_superadmin'])) : ?>
	<p><a href="index.php?type=superadmin&action=edit_admin&id=<?php echo $_GET['id']; ?>">Ställ in administratörsrättigheter för denna användare</a></p>
<?php endif; ?>