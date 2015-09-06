<?php 
	$post_info = db_forum::get_full_post_info($_GET['id'], $_SESSION['id']);
?>

<h1>Modereringsalternativ f�r �mne: <?php echo $post_info['title']; ?></h1>

<h2>Flytta �mnet till annat forum</h2>
<form method="post" action="" class="standard-form">
	<input type="hidden" name="move_topic" value="1">
	<select name="forum_id" id="forum_id">
		<?php 
			$forums = db_forum_admin::get_all_forums();
			foreach($forums as $row){
				echo "<option value=\"" . $row['id'] . "\">" . $row['title'] . "</option>";
			}
		?>
	</select>
	<br><input type="submit" value="Flytta">
</form>

<h2>Radera �mnet och alla dess inl�gg</h2>
<form method="post" action="" class="standard-form">
	<input type="hidden" name="delete_topic" value="1">
	<input type="submit" value="Radera">
</form>
