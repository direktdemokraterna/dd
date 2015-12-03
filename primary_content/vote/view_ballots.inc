<?php
	$voteinfo = db_vote::get_vote_info($_GET['id']); 
	$ballots = db_vote::get_ballots($_GET['id']); 
?>

<h1>Alla röster i omröstningen <?php echo $voteinfo['title']; ?></h1>

<?php if(empty($ballots)) : ?>
	Inga röster lagda.
<?php else : ?>

	<table class="responsive">
		<tr><th>Röstande</th><th>Röst</th><th>Delegat</th><th>Röstningstidpunkt</th></tr>

		<?php foreach ($ballots as $ballot) : ?>
			<tr><td>
			<?php if($ballot['user_code']) : ?>
				Användare
			<?php else : ?>
				<a href="index.php?type=vote&action=view_delegate&id=<?php echo $ballot['voter_is_delegate_id']; ?>"><?php echo $ballot['voter_is_delegate_name']; ?></a>
			<?php endif; ?>
			</td>
			<td>
			<?php 
				echo \View\vote::get_ballot_content($voteinfo['type'], $ballot['ballot']);
			?>
			</td>
			<td>
			<?php if($ballot['delegate_id']) : ?>
				<a href="index.php?type=vote&action=view_delegate&id=<?php echo $ballot['delegate_id']; ?>"><?php echo $ballot['delegate_name']; ?></a>
			<?php endif; ?>
			</td>
			<td>
			<?php echo general_helpers::show_date($ballot['time_ballot_placed']); ?>
			</td></tr>
		<?php endforeach; ?>
	</table>

<?php endif; ?>