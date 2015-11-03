<nav id="menubar">
	<div id="alt-menu-row">
		<a onClick="toggle_mobile_main_menu()"><span class="fa fa-bars alt-header-button left" id="alt-top-menu"></span></a>
		<a href="index.php"><span class="fa fa-home alt-header-button left" id="alt-home-button"></span></a>
		<?php if(db_message::check_unread($_SESSION['id']) > 0) : ?>
			<a href="index.php?type=message&action=inbox"><span class="fa fa-envelope-o alt-header-button left" id ="alt-mail-button"></span></a>
		<?php endif; ?>
		<a onClick="toggle_mobile_user_menu()"><span class="fa fa-user alt-header-button right" id="alt-user-menu"></span></a>
	</div>
	<ul id="hide_menu">
		<li><a href="index.php?type=member">Användare</a>
			<ul>
				<li><a href="index.php?type=member&action=calendar">Kalender</a></li>
				<li><a href="index.php?type=member&action=settings">Inställningar</a></li>
				<li><a href="index.php?type=member&action=memberlist">Medlemslista</a></li>
				<li><a href="index.php?type=member&action=admin_list">Adminlista</a></li>
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
		<li><?php
				$welcome_text = "Hej, " . db_user::get_user_full_name($_SESSION['id']);
				\View\general::output_internal_link($welcome_text, "member", "view");
			?>
			<ul>
				<li><a href="index.php?logout=1">Logga ut</a></li>
			</ul>
		</li>
	</ul>
</nav>
<div id="pseudo_menubar"></div>
<div style="clear: both;"></div>