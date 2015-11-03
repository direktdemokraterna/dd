<?php
	$is_delegate = db_delegate::is_user_delegate($_SESSION['id']);
	if($is_delegate){
		$delegate_settings = db_delegate::get_delegate_settings($_SESSION['id']);
	}
?>

<h1>Delegatinställningar</h1>

<?php if(!$is_delegate) : ?>
	<p>Du är ännu inte registrerad som delegat. Vill du skapa en delegatprofil i databasen trycker du på knappen nedan. Även om du skapar en delegat i anslutning till din användare behöver du inte rösta med den (så att din röstning syns offentligt) eller låta andra användare delegera till den.</p>
	<form method="post" action="" class="standard-form">
	<input type="submit" name="register_delegate" value="Skapa delegat"></form>
<?php else : ?>
	<form method="post" action="" class="standard-form">
		<h2>Rösta som delegat</h2>
		<label for "acting_as_delegate">Rösta som delegat: </label>
		<input type="checkbox" id="acting_as_delegate" name="acting_as_delegate" <?php if($_SESSION['delegate_id']) echo "checked"; ?>>

		<p>Om ovanstående ruta är ikryssad röstar du i alla omröstningar och propositioner som delegat istället för som enskild användare. Det innebär att du röstar för alla som har delegerat sin röst till dig i den frågan. Den innebär också att din röst blir offentlig och kan ses av andra. Du kan bara rösta som delegat inom de valkretsar som du angivit för din delegat här under. Röstar du inom någon annan valkrets kommer du rösta som enskild användare även om rutan ovan är ikryssad. </p>

		<h2>Valkretsar för din delegat</h2>

		<?php
			$constituencies = db_delegate::get_constituencies_for_user_and_delegate_activity($_SESSION['id'], $delegate_settings['delegate_id']);
		?>

		<p>Här kan du välja inom vilka valkretsar andra användare ska kunna delegera till dig som delegat. Du väljer med andra ord inom vilka valkretsar du är aktiv som delegat. Har du inte kryssat för några valkretsar är du inte aktiv som delegat alls.</p>

		<ul class="checkbox-grid">

		<?php foreach($constituencies as $row) : ?>
			<li><input type="checkbox" name="constituencies[]" id="<?php echo $row['constituency_title']; ?>" value="<?php echo $row['constituency_id']; ?>" <?php if($row['delegate_active']>0) echo " checked"; ?>>
			<label for "<?php echo $row['constituency_title']; ?>"><?php echo $row['constituency_title']; ?></label></li>
		<?php endforeach; ?>

		</ul><div class="clear">
		</div><br><input type="submit" name="change_delegate" style="margin-left: 10%;" id="submit" value="Uppdatera">
	</form>
	<form method="post" action="" class="standard-form" onsubmit="return confirm('Din delegat kommer att raderas fullständigt. Du kan också välja att tillfälligt avaktivera din delegat. Vill du fortsätta ändå?');">
		<h2>Ta bort delegat</h2>
		<input type="submit" style="margin-left: 10%;" name="delete" id="delete" value="Ta bort delegat">
	</form>

<?php endif; ?>