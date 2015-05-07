<?php 
	$workgroup = db_workgroup::get_info($_GET['id']);
?>

<?php if(!empty($workgroup)) : ?>

	<h1><?php echo $workgroup['title']; ?></h1>

	<?php if($workgroup['is_active']==0) : ?>

		<p>Denna arbetsgrupp är föreslagen. För att bli aktiv måste den ha minst tre medlemmar. Just nu är antalet medlemmar <?php echo $workgroup['number_of_members']; ?> st.</p>

	<?php endif; ?>

	<?php
		$is_member = db_workgroup::is_member($workgroup['id'], $_SESSION['id']);
		$is_candidate = db_workgroup::is_candidate($workgroup['id'], $_SESSION['id']);
	?>

	<?php if($is_member) : ?>
		<p>Du är medlem i denna arbetsgrupp.</p>
	<?php elseif($is_candidate) : ?>
		<p>Du har ansökt om medlemskap i denna arbetsgrupp.</p>
	<?php endif; ?>

	<p>
	<strong>Antal medlemmar: </strong><?php echo $workgroup['number_of_members']; ?><br>
	<strong>Skapad: </strong><?php echo general_helpers::show_date($workgroup['create_time']); ?><br>
	<strong>Beskrivning:</strong><br>
	<?php echo nl2br($workgroup['description']); ?>
	</p>

	<?php if($workgroup['is_active']==1) : ?>

		<?php $workgroup_members = db_workgroup::list_members($workgroup['id']); ?>
		<p>
		<strong>Medlemmar i denna arbetsgrupp: </strong><br>
		</p>
		<?php foreach($workgroup_members as $row) : ?>
			<a href="index.php?type=member&action=view&id=<?php echo $row['user_id']; ?>"><?php echo $row['full_name']; ?></a>
			<?php if($is_member && $workgroup['is_restricted']==0) : ?>
				<?php $exclude_info = db_workgroup::exclude_info($workgroup['id'], $row['user_id'], $_SESSION['id']); ?>
				<?php if($exclude_info['number_of_excluders'] > 0) : ?>
					(<?php echo $exclude_info['number_of_excluders']; ?> gruppmedlem<?php if($exclude_info['number_of_excluders'] != 1) echo "mar"; ?> vill utesluta denna medlem) 
				<?php endif; ?>
				<?php if($exclude_info['is_excluder'] > 0) : ?>
					 (Du stödjer en uteslutning av denna gruppmedlem.)
					 <form method="post" action="" class="single_submit_button"><input type="hidden" name="type" value="cancel_exclude"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="hidden" name="user" value="<?php echo $row['user_id']; ?>"><input type="submit" value="Ångra"></form>
				<?php else : ?>
					<form method="post" action="" class="single_submit_button"><input type="hidden" name="type" value="support_exclude"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="hidden" name="user" value="<?php echo $row['user_id']; ?>"><input type="submit" value="Rösta för uteslutning av denna gruppmedlem"></form>
				<?php endif; ?>
			<?php endif; ?>
			<br>
		<?php endforeach; ?>

		<?php if($workgroup['is_restricted']==1) : ?>
			<p>Den här arbetsgruppen har restriktioner för medlemskap. Mest troligt beror detta på att arbetsgruppens medlemmar utses genom val bland medlemmarna.</p>
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
						 	<form method="post" action="" class="single_submit_button"><input type="hidden" name="type" value="cancel_support_candidate"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="hidden" name="user" value="<?php echo $row['user_id']; ?>"><input type="submit" value="Dra tillbaka ditt stöd för denna kandidat"></form>
						<?php else : ?>
						 	<form method="post" action="" class="single_submit_button"><input type="hidden" name="type" value="support_candidate"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="hidden" name="user" value="<?php echo $row['user_id']; ?>"><input type="submit" value="Stöd denna kandidat"></form>
						<?php endif; ?>
					<?php endforeach; ?>
				<?php endif; ?>
			<?php elseif($is_candidate) : ?>
				<?php $candidate_info = db_workgroup::candidate_info($workgroup['id'], $_SESSION['id'], $_SESSION['id']); ?>
				<?php $needed_member_count_for_candidate = ceil(db_workgroup::get_member_count($workgroup['id']) / 1.999); ?>
				<p>Du har ansökt om medlemskap i denna arbetsgrupp. För närvarande har du stöd av <?php echo $candidate_info['number_of_supporters']; ?> medlem<?php if($candidate_info['number_of_supporters'] != 1) echo "mar"; ?>, <?php echo $needed_member_count_for_candidate; ?> behövs för att upphöjas till medlem.
				<br>
				<form method="post" action="" class="single_submit_button"><input type="hidden" name="type" value="cancel_candidacy"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="submit" value="Ta tillbaka medlemsansökan"></form>
				</p>
			<?php else : ?>
				<p>
				<form method="post" action="" class="single_submit_button"><input type="hidden" name="type" value="submit_candidacy"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="submit" value="Ansök om medlemskap"></form>
				</p>
			<?php endif; ?>
		<?php endif; ?>

	<?php else : ?>
		<?php if($is_member) : ?>
			<p>Du stödjer att denna arbetsgrupp aktiveras. 
			<form method="post" action="" class="single_submit_button"><input type="hidden" name="type" value="cancel_support_workgroup"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="submit" value="Ta tillbaka ditt stöd till denna arbetsgrupp"></form>
		<?php else : ?>
			<p>
			<form method="post" action="" class="single_submit_button"><input type="hidden" name="type" value="support_workgroup"><input type="hidden" name="id" value="<?php echo $workgroup['id']; ?>"><input type="submit" value="Stöd denna arbetsgrupp"></form> 
			(Arbetsgruppen kommer aktiveras när 3 medlemmar stödjer den. De tre stödjarna kommer automatiskt omvandlas till medlemmar.)</p>
		<?php endif; ?>
	<?php endif; ?>
<?php endif; ?>