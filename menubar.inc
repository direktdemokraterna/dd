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
		<li><?php 
			\View\general::output_internal_link("User", "member"); 
			\View\general::output_link_list("member", array(
				"calendar" => "Calendar"
				,"settings" => "My profile"
				,"memberlist" => "Members"
				,"admin_list" => "Administrators"
				)); 
			?>
		</li>
		<?php if(db_message::check_unread($_SESSION['id']) > 0) : ?>
			<li id="unread-mail"><a href="index.php?type=message&action=inbox" style="min-width: 10px; padding: 0 0 0 0;"><span style="font: 400 13px/32px FontAwesome;" class="fa fa-envelope-o" id="fa-envelope-o"></span></a>
			</li>
		<?php endif; ?>
		<li><?php 
			\View\general::output_internal_link("Messages", "message"); 
			\View\general::output_link_list("message", array(
				"inbox" => "Inbox"
				,"outbox" => "Outbox"
				,"write" => "Write message"
				)); 
			?>
		</li>
		<li><a href="index.php?type=workgroup">Arbetsgrupper</a>
			<ul>
				<?php $workgroups = db_workgroup::list_workgroups_where_user_is_member($_SESSION['id']); ?>
				<?php foreach($workgroups as $row) : ?>
					<li><a href="index.php?type=workgroup&action=view&id=<?php echo $row['id']; ?>"><?php echo $row['title']; ?></a></li>
				<?php endforeach; ?>
			</ul>
		</li>
		<li><?php 
			\View\general::output_internal_link("Votes", "vote");
			\View\general::output_link_list("vote", array(
				"list_props" => "Propositions"
				,"list_active_votes" => "Votes"
				,"delegations" => "Delegates"
				)); 
			?>
		</li>
		<li><?php \View\general::output_internal_link("Forum", "forum"); ?>
			<ul>
				<li></li>
			</ul>
		</li>
		<?php if(isset($_SESSION['admin'])) : ?>
		<li><a href="#"><?php __("Admin"); ?></a>
			<ul>
				<?php 
					if(isset($_SESSION['is_member_admin']))
						echo '<li>' . \View\general::generate_internal_link("Member admin", "member_admin") . 
					'</li>';
					if(isset($_SESSION['is_forum_admin']))
						echo '<li>' . \View\general::generate_internal_link("Forum admin", "forum_admin") . 
					'</li>';
					if(isset($_SESSION['is_vote_admin']))
						echo '<li>' . \View\general::generate_internal_link("Vote admin", "vote_admin") . 
					'</li>';
					if(isset($_SESSION['is_treasurer']))
						echo '<li>' . \View\general::generate_internal_link("Treasurer", "treasurer") . 
					'</li>';
					if(isset($_SESSION['is_superadmin']))
						echo '<li>' . \View\general::generate_internal_link("Superadmin", "superadmin") . 
					'</li>';
				?>
			</ul>
		</li>
		<?php endif; ?>
	</ul>
	<ul id="logout-link">
		<li><?php
				$welcome_text = _t("Hello") . ", " . db_user::get_user_full_name($_SESSION['id']);
				\View\general::output_internal_link($welcome_text, "member", "view");
			?>
			<ul>
				<li><a href="index.php?logout=1"><?php __("Logout"); ?></a></li>
			</ul>
		</li>
	</ul>
</nav>
<div id="pseudo_menubar"></div>
<div style="clear: both;"></div>