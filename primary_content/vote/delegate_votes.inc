<?php
	$voteinfo = db_vote::get_vote_info($_GET['id']); 

	$delegate_votes = db_delegate::get_delegate_ballots_for_vote($_GET['id']); 
?>

<h1>Delegatr�ster i omr�stningen <?php echo $voteinfo['title']; ?></h1>

<?php if(empty($delegate_votes)) : ?>
	Inga delegatr�ster lagda.
<?php else : ?>

	<table class="responsive">
		<tr><td>Delegat</td><td>R�st</td></tr>

		<?php foreach ($delegate_votes as $row): ?>
			
		<?php endforeach ?>


<?php endif; ?>
