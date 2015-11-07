<ul>
	<li>
		<h2>Propositioner</h2>
		<ul>
			<li><a href="index.php?type=vote&action=list_props">Lista aktiva propositioner</a></li>
			<li><a href="index.php?type=vote&action=list_affirmed_props">Lista beviljade propositioner</a></li>
			<li><a href="index.php?type=vote&action=add_prop">Skapa proposition</a></li>
		</ul>
	</li>
	<li>
		<h2>Omröstningar</h2>
		<ul>
			<li><a href="index.php?type=vote&action=list_active_votes">Lista pågående omröstningar</a></li>
			<li><a href="index.php?type=vote&action=list_old_votes">Lista gamla omröstningar</a></li>
		</ul>
	</li>
	<li>
		<h2>Delegater</h2>
		<?php
			$is_delegate = db_delegate::is_user_delegate($_SESSION['id']);
		?>
		<ul>
			<li><a href="index.php?type=vote&action=list_delegates">Lista delegater</a></li>
			<li><a href="index.php?type=vote&action=delegations">Se delegeringar</a></li>
			<li><a href="index.php?type=vote&action=delegate_settings">
				<?php echo $is_delegate ? "Hantera delegat" : "Bli delegat"; ?>
			</a></li>
		</ul>
	</li>
	<li>
		<h2>Sök propositioner och omröstningar</h2>
		<form method="post" class="sidebar_search_form" action="index.php?type=vote&action=search">
			<input tabindex="101" type="text" value="" name="vote_search_input" class="sidebar_search_input">
			<input tabindex="102" type="submit" class="sidebar_search_submit" value="Sök">
		</form>
	</li>
</ul>