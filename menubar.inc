<nav id="menubar">

	<div id="alt-menu-row">
		<a href="index.php"><span class="fa fa-home" id="alt-home-button"></span></a>
		<?php if(db_message::check_unread($_SESSION['id']) > 0) : ?>
			<a href="index.php?type=message&action=inbox"><span class="fa fa-envelope-o" id="alt-mail-button"></span></a>
		<?php endif; ?>
		<a onClick="expand_mobile_menu()"><span class="fa fa-bars" id="alt-menu-button"></span></a>
	</div>

<ul id="hide_menu">
	<li><a href="index.php?type=member">Användare</a>
		<ul>
			<li><a href="index.php?type=member&action=calendar">Kalender</a></li>
			<li><a href="index.php?type=member&action=settings">Inställningar</a></li>
			<li><a href="index.php?type=member&action=memberlist">Medlemslista</a></li>
		</ul>
	</li>

	<?php if(db_message::check_unread($_SESSION['id']) > 0) : ?>
		<li id="unread-mail"><a href="index.php?type=message&action=inbox" style="min-width: 10px; padding: 0 0 0 0;"><span style="font: 400 13px/32px FontAwesome;" class="fa fa-envelope-o" id="fa-envelope-o"></span></a>
		</li>
	<?php endif; ?>

	<li><a href="index.php?type=message">Meddelanden</a>
		<ul>
			<li><a href="index.php?type=message&action=inbox">Inbox</a></li>
			<li><a href="index.php?type=message&action=outbox">Skickade</a></li>
			<li><a href="index.php?type=message&action=write">Skriv meddelande</a></li>
		</ul>
	</li>

	<li><a href="index.php?type=workgroup">Arbetsgrupper</a>
		<ul>
			<?php $workgroups = db_workgroup::list_workgroups_where_user_is_member($_SESSION['id']); ?>
			<?php foreach($workgroups as $row) : ?>
				<li><a href="index.php?type=workgroup&action=view&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a></li>
			<?php endforeach; ?>
		</ul>
	</li>

	<li><a href="index.php?type=vote">Omröstningar</a>
		<ul>
			<li><a href="index.php?type=vote&action=list_props">Propositioner</a></li>
			<li><a href="index.php?type=vote&action=list_active_votes">Omröstningar</a></li>
			<li><a href="index.php?type=vote&action=delegations">Delegater</a></li>
		</ul>
	</li>

	<li><a href="index.php?type=forum">Forum</a>
		<ul>
			<li></li>
		</ul>
	</li>

	<?php if(isset($_SESSION['admin'])) : ?>
	<li><a href="#">Admin</a>
		<ul>
			<?php if(isset($_SESSION['is_member_admin'])) : ?>
			<li><a href="index.php?type=member_admin">Medlemsansvarig</a></li>
			<?php endif; ?>
			<?php if(isset($_SESSION['is_forum_admin'])) : ?>
			<li><a href="index.php?type=forum_admin">Forumadministratör</a></li>
			<?php endif; ?>
			<?php if(isset($_SESSION['is_vote_admin'])) : ?>
			<li><a href="index.php?type=vote_admin">Valadministratör</a></li>
			<?php endif; ?>
			<?php if(isset($_SESSION['is_treasurer'])) : ?>
			<li><a href="index.php?type=treasurer">Kassör</a></li>
			<?php endif; ?>
			<?php if(isset($_SESSION['is_superadmin'])) : ?>
			<li><a href="index.php?type=superadmin">Superadmin</a></li>
			<?php endif; ?>
		</ul>
	</li>
	<?php endif; ?>

</ul>

<ul id="logout-link">
<li><a href="#">Hej, <?php echo db_user::get_user_full_name($_SESSION['id']); ?></a>
	<ul>
		<li><a href="index.php?logout=1">Logga ut</a></li>
	</ul>
</li>
</ul>
</nav>

<div id="pseudo_menubar"></div>

<div style="clear: both;"></div>