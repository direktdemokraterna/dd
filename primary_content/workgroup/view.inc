<?php 
	$workgroup = db_workgroup::get_info($_GET['id']);
?>

<?php if(!empty($workgroup)) : ?>

	<h1><?php echo $workgroup['title']; ?></h1>

	<?php 
		if($workgroup['is_active']==0)
			_p(_t("This workgroup is proposed. It needs at least three members to be activated. Currently the number of members is " . $workgroup['number_of_members'] . "."));
		$is_member = db_workgroup::is_member($workgroup['id'], $_SESSION['id']);
		$is_candidate = db_workgroup::is_candidate($workgroup['id'], $_SESSION['id']);
		if($is_member)
			_p(_t("You are a member of this workgroup."));
		else if($is_candidate)
			_p(_t("You have applied for membership in this workgroup."));
	?>

	<?php
		echo '<p>';
		_strong(_t("Number of members: "));
		echo $workgroup['number_of_members'];
		_br();
		$is_active = $workgroup['is_active'];
		_strong(_t($is_active ? "Created: " : "Proposed: "));
		echo general_helpers::show_date($workgroup[$is_active ? 'create_time' : 'propose_time']);
		_br();				
		_strong(_t("Description: "));
		echo \View\general::make_html_from_wiki_text($workgroup['description']);
		echo '</p>';
		if($is_member) {
			\View\general::output_internal_link(_t("Edit description"), 'workgroup', 'edit', 'id=' . $_GET['id']);
			_br();
		}
	?>

	<?php if($workgroup['is_active']==1) : ?>

		<?php 
			$workgroup_members = db_workgroup::list_members($workgroup['id']); 
			_p(_strong(_t("Members of this workgroup:")));
		?>
		<?php foreach($workgroup_members as $row) : ?>
			<a href="index.php?type=member&action=view&id=<?php echo $row['user_id']; ?>"><?php echo $row['full_name']; ?></a>
			<?php if($is_member && $workgroup['is_restricted']==0) : ?>
				<?php $exclude_info = db_workgroup::exclude_info($workgroup['id'], $row['user_id'], $_SESSION['id']); ?>
				<?php if($exclude_info['number_of_excluders'] > 0) : ?>
					(<?php echo $exclude_info['number_of_excluders']; ?> gruppmedlem<?php if($exclude_info['number_of_excluders'] != 1) echo "mar"; ?> vill utesluta denna medlem) 
				<?php endif; ?>
				<?php if($exclude_info['is_excluder'] > 0) : ?>
					 (Du stödjer en uteslutning av denna gruppmedlem.)
					 &nbsp;&nbsp;&nbsp;<form method="post" action="" class="standard-form" style="display: inline;"><input type="hidden" name="type" value="cancel_exclude"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="hidden" name="user" value="<?php echo $row['user_id']; ?>"><input type="submit" style="width: auto;" value="Ångra"></form>
				<?php else : ?>
					&nbsp;&nbsp;&nbsp;<form method="post" action="" class="standard-form" style="display: inline;"><input type="hidden" name="type" value="support_exclude"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="hidden" name="user" value="<?php echo $row['user_id']; ?>"><input type="submit" style="width: auto;" value="Rösta för uteslutning av denna gruppmedlem"></form>
				<?php endif; ?>
			<?php endif; ?>
			<br>
		<?php endforeach; ?>

		<?php if($workgroup['is_restricted']>0) : ?>
			<br><p>Den här arbetsgruppen är stängd och medlemmarna väljs via personval. Det går inte att ansöka om medlemskap på samma sätt som i öppna grupper. Omröstningen där medlemmarna i denna arbetsgrupp utses finns <a href="index.php?type=vote&action=view_vote&id=<?php echo $workgroup['is_restricted']; ?>">här</a>.</p>

			<?php
				$workgroup_membership_changes = db_workgroup::get_workgroup_election_changes($_GET['id']);
			?>
			<?php if(!empty($workgroup_membership_changes)) : ?>
				<p>
				<strong>Kommande förändringar i medlemskap</strong><br>
				<table>
				<tr><th>Tidpunkt</th><th>Medlem ut</th><th>Kandidat in</th></tr>
				<?php foreach($workgroup_membership_changes as $row) : ?>
					<?php
						$name_of_user_in = db_user::get_user_full_name($row['user_id_in']);
						$name_of_user_out = db_user::get_user_full_name($row['user_id_out']);
						$time_of_transfer = general_helpers::show_date($row['timestamp']+BUFFER_TIME_FOR_CONTINUOUS_ELECTIONS);
					?>
					<tr><td><?php echo $time_of_transfer; ?></td><td><a href="index.php?type=member&action=view&id=<?php echo $row['user_id_out']; ?>"><?php echo $name_of_user_out; ?></a></td><td><a href="index.php?type=member&action=view&id=<?php echo $row['user_id_in']; ?>"><?php echo $name_of_user_in; ?></a></td></tr>
				<?php endforeach; ?>
				</table></p>
			<?php endif; ?>
		<?php else : ?>
			<?php if($is_member) : ?>
				<?php $workgroup_candidates = db_workgroup::list_candidates($workgroup['id']); ?>
				<p>
				<strong>Kandidater till medlemskap: </strong><br>
				<?php if(empty($workgroup_candidates)) : ?>
					Inga kandidater
				<?php else : ?>
					<?php foreach($workgroup_candidates as $row) : ?>
						<a href="index.php?type=member&action=view&id=<?php echo $row['user_id']; ?>"><?php echo $row['full_name']; ?></a>
						<?php $candidate_info = db_workgroup::candidate_info($workgroup['id'], $row['user_id'], $_SESSION['id']); ?>
						 (<?php echo $candidate_info['number_of_supporters']; ?> gruppmedlem<?php if($candidate_info['number_of_supporters'] != 1) echo "mar"; ?> stödjer att denna kandidat upptas. 
						<?php if($candidate_info['is_supporter'] > 0) : ?>
						 	&nbsp;&nbsp;&nbsp;<form method="post" action="" class="standard-form" style="display: inline;"><input type="hidden" name="type" value="cancel_support_candidate"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="hidden" name="user" value="<?php echo $row['user_id']; ?>"><input type="submit" style="width: auto;" value="Dra tillbaka ditt stöd för denna kandidat"></form>
						<?php else : ?>
						 	&nbsp;&nbsp;&nbsp;<form method="post" action="" class="standard-form" style="display: inline;"><input type="hidden" name="type" value="support_candidate"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="hidden" name="user" value="<?php echo $row['user_id']; ?>"><input type="submit" style="width: auto;" value="Stöd denna kandidat"></form>
						<?php endif; ?>
					<?php endforeach; ?>
				<?php endif; ?>

				<p><strong>Avsluta ditt medlemskap</strong>
				<form method="post" action="" class="standard-form"><input type="hidden" name="type" value="cancel_membership"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="submit" style="width: auto;" value="Gå ur den här arbetsgruppen" onclick="return confirm('Vill du verkligen gå ur den här arbetsgruppen?');"></form>
				</p>

			<?php elseif($is_candidate) : ?>
				<?php $candidate_info = db_workgroup::candidate_info($workgroup['id'], $_SESSION['id'], $_SESSION['id']); ?>
				<?php $needed_member_count_for_candidate = ceil(db_workgroup::get_member_count($workgroup['id']) / 1.999); ?>
				<p>Du har ansökt om medlemskap i denna arbetsgrupp. För närvarande har du stöd av <?php echo $candidate_info['number_of_supporters']; ?> medlem<?php if($candidate_info['number_of_supporters'] != 1) echo "mar"; ?>, <?php echo $needed_member_count_for_candidate; ?> behövs för att upphöjas till medlem.
				<br>
				<form method="post" action="" class="standard-form"><input type="hidden" name="type" value="cancel_candidacy"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="submit" style="width: auto;" value="Ta tillbaka medlemsansökan"></form>
				</p>
			<?php else : ?>
				<p>
				<form method="post" action="" class="standard-form"><input type="hidden" name="type" value="submit_candidacy"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="submit" style="width: auto;" value="Ansök om medlemskap"></form>
				</p>
			<?php endif; ?>
		<?php endif; ?>

	<?php else : ?>
		<?php if($is_member) : ?>
			<p>Du stödjer att denna arbetsgrupp aktiveras. 
			<form method="post" action="" class="standard-form"><input type="hidden" name="type" value="cancel_support_workgroup"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="submit" style="width: auto;" value="Ta tillbaka ditt stöd till denna arbetsgrupp"></form>
		<?php else : ?>
			<p>
			<form method="post" action="" class="standard-form"><input type="hidden" name="type" value="support_workgroup"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="submit" style="width: auto;" value="Stöd denna arbetsgrupp"></form> 
			(Arbetsgruppen kommer aktiveras när 3 medlemmar stödjer den. De tre stödjarna kommer automatiskt omvandlas till medlemmar.)</p>
		<?php endif; ?>
	<?php endif; ?>
<?php endif; ?>

<?php if(isset($_SESSION['is_member_admin'])) : ?>
	<a href="index.php?type=member_admin&action=edit_workgroup&id=<?php echo $workgroup['id']; ?>">Administrera denna arbetsgrupp som medlemsadministratör</a>
<?php endif; ?>