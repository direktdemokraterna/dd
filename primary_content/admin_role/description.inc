<?php $admin_role_info = db_admin::get_admin_role_info($_GET['id']); ?>

<h1><?php echo $admin_role_info['title']; ?></h1>

<p><strong>Beskrivning:</strong><br>
<?php echo \View\general::make_html_from_wiki_text($admin_role_info['description']); ?>
</p>
<br>
<br>
<strong>Nuvarande innehavare: </strong>

<?php 
	$admin_role_users = db_admin::get_admin_role_users($_GET['id']);
	foreach($admin_role_users as $row){
		echo "<p><a href=\"index.php?type=member&action=view&id=" . $row['id'] . "\">" . $row['first_name'] . " " . $row['last_name'] . "</a></p>\n";
	}
?>