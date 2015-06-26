<?php
	if($_SESSION['delegate_id']){
		$constituencies = db_constituency::get_constituencies_for_delegate($_SESSION['delegate_id']);
	}
	else{
		$constituencies = db_constituency::get_constituencies_for_user($_SESSION['id']);
	}

	$list_of_delegations_from_db = db_delegate::get_delegations_for_multiple_constituencies($constituencies);
	$list_of_delegations = Array();
	foreach($list_of_delegations_from_db as $row){
		$list_of_delegations[] = Array("user_code" => $row['user_code'], "constituency_id" => $row['constituency_id'], "delegate_id" => $row['delegate_id'], "delegate_name" => $row['delegate_name']);
	}
?>


<script>
	var user_id = <?php echo json_encode($_SESSION['id']); ?>;
	var list_of_delegations = <?php echo json_encode($list_of_delegations); ?>;
	var acting_as_delegate = <?php if($_SESSION['delegate_id']) echo "true"; else echo "false"; ?>;
</script>

<?php if($_SESSION['delegate_id']) : ?>
	<h1>Dina nuvarande delegeringar som delegat</h1>
<?php else : ?>
	<h1>Dina nuvarande delegeringar</h1>	
<?php endif; ?>


<form method="post" action="" class="prio-vote">
	<input type="hidden" name="ballot" id="ballot" value="">

<?php foreach($constituencies as $row) : ?>

	<div class="delegation_box">
		<h2>Valkrets: <?php echo $row['name']; ?></h2>

		<?php if($_SESSION['delegate_id']) : ?>
			<span>
				<?php
					$delegate_delegate_for_constituency = db_delegate::get_delegates_delegate_for_constituency($_SESSION['delegate_id'], $row['id']);
				?>
				<?php if($delegate_delegate_for_constituency) : ?>
					Du har delegerat din röst i denna valkrets till <a href="index.php?type=vote&action=view_delegate&id=<?php echo $delegate_delegate_for_constituency['delegate_id']; ?>"><?php echo $delegate_delegate_for_constituency['delegate_title']; ?></a>
				<?php else : ?>
					Du har ingen delegat i denna valkrets
				<?php endif; ?>
			</span><br>
		<?php else : ?>
			<span id="constituency<?php echo $row['id']; ?>">Du har ingen delegat i denna valkrets</span><br>
		<?php endif; ?>

		<br>
		<?php
			$delegates_for_constituency = db_delegate::get_delegates_for_constituency($row['id']);
		?>
		<select id="select<?php echo $row['id']; ?>">
			<option value="null">Ta bort delegat</option>
			<?php foreach ($delegates_for_constituency as $delegate): ?>
				<option value="<?php echo $delegate['id']; ?>"><?php echo $delegate['title']; ?></option>
			<?php endforeach ?>
		</select>
		<input type="submit" value="Delegera" onmousedown="return encrypt_delegation_get_delegate_from_form(<?php echo $row['id']; ?>)">
	</div>

<?php endforeach; ?>

</form>



<script>
list_of_delegations.map(function (vote){
	if(vote.user_code == sessionStorage.active_user_code){
		var constituency_element = "constituency" + vote.constituency_id;
		document.getElementById(constituency_element).innerHTML = "Du har delegerat din röst i denna valkrets till <a href='index.php?type=vote&action=view_delegate&id=" + vote.delegate_id + "'>" + vote.delegate_name + "</a>";
	}
});
</script>