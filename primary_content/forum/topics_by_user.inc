<?php
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	$i = 0;

	$user_full_name = db_user::get_user_full_name($_GET['id']);
?>

<h1>Trådstarter av <?php echo $user_full_name; ?></h1>

<?php $topics = db_forum::get_topics_by_user($_GET['id'], $_SESSION['id'], $page); ?>
<?php if(empty($topics)) : ?>
	<p>Inga trådstarter.</p>
<?php else : ?>

	<div class="topic_list">
	<div class="topic_list_top_row">
		<span class="subject_column">Ämne</span><span class="numerical_column">Deltagare</span><span class="numerical_column">Inlägg</span><span class="last_post_column">Senaste inlägg</span>
		<div style="clear: both;"></div>
	</div>

	<?php foreach($topics as $row) : ?>
		<?php 
			$number_of_pages = ceil( $row['number_of_posts'] / POSTS_PER_PAGE );
		?>
		<div class="topic_list_row">
			<span class="subject_column">
				<a href="index.php?type=forum&action=show_posts&id=<?php echo $row['topic_id']; ?>"><?php echo $row['topic_title']; ?></a>
				<?php if($number_of_pages > 1) : ?>
					 <a href="index.php?type=forum&action=show_posts&id=<?php echo $row['topic_id']; ?>&page=<?php echo $number_of_pages; ?>">(<?php echo $number_of_pages; ?>)</a>
				<?php endif; ?>
				<br><span class="list_sub_text">Startat av: <a href="index.php?type=member&action=view&id=<?php echo $row['topic_user_id']; ?>"><?php echo $row['topic_user_full_name']; ?></a></span>
			</span>
			<span class="numerical_column"><?php echo $row['number_of_participants']; ?></span>
			<span class="numerical_column"><?php echo $row['number_of_posts']; ?></span>
			<span class="last_post_column">
				<?php echo general_helpers::show_date($row['last_posted_time']); ?><br>
				<span class="list_sub_text">Av: <a href="index.php?type=member&action=view&id=<?php echo $row['last_user_id']; ?>"><?php echo $row['last_user_full_name']; ?></a></span>
			</span>
			<div style="clear: both;"></div>
		</div>
	<?php endforeach; ?>

	</div>
<?php endif; ?>