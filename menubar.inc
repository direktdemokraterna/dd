<nav id="menubar">
	<div id="alt-menu-row">
		<a onClick="toggle_mobile_main_menu()"><span class="fa fa-bars alt-header-button left" id="alt-top-menu"></span></a>
		<a href="index.php"><span class="fa fa-home alt-header-button left" id="alt-home-button"></span></a>
		<?php if(db_message::check_unread($_SESSION['id']) > 0) : ?>
			<a href="index.php?type=message&action=inbox"><span class="fa fa-envelope-o alt-header-button left" id ="alt-mail-button"></span></a>
		<?php endif; ?>
		<a onClick="toggle_mobile_user_menu()"><span class="fa fa-user alt-header-button right" id="alt-user-menu"></span></a>
	</div>
	<ul id="hide_menu" class="clearfix">
		<li><?php
			__link(_t("User"), "member");
			\View\controls::output_link_list("member", array(
				"calendar" => _t("Calendar")
				,"settings" => _t("My profile")
				,"memberlist" => _t("Members")
				,"admin_list" => _t("Administrators")
				));
			?>
		</li>
		<?php if(db_message::check_unread($_SESSION['id']) > 0) : ?>
			<li id="unread-mail"><a href="index.php?type=message&action=inbox" style="min-width: 15px; padding: 0 5px 0 5px;"><span style="font: 400 13px/32px FontAwesome;" class="fa fa-envelope-o" id="fa-envelope-o"></span></a>
			</li>
		<?php endif; ?>
		<li><?php
			__link(_t("Messages"), "message");
			\View\controls::output_link_list("message", array(
				"inbox" => _t("Inbox")
				,"outbox" => _t("Outbox")
				,"write" => _t("Write message")
				));
			?>
		</li>
		<li><?php
			__link(_t("Workgroups"), "workgroup");
			echo '<ul>';
				$workgroups = db_workgroup::list_workgroups_where_user_is_member($_SESSION['id']);
				foreach($workgroups as $row)
					__li(_link($row['title'], "workgroup", "view", "id=" .
						$row['id']));
			echo '</ul>';
			?>
		</li>
		<li><?php
			__link(_t("Votes"), "vote");
			\View\controls::output_link_list("vote", array(
				"list_props" => _t("Propositions")
				,"list_active_votes" => _t("Votes")
				,"delegations" => _t("Delegates")
				));
			?>
		</li>
		<li class="forum"><?php __link(_t("Forum"), "forum"); ?></li>
		<?php if(isset($_SESSION['admin'])) : ?>
		<li><a href="#"><?php __t("Admin"); ?></a>
			<ul>
				<?php
					if(isset($_SESSION['is_member_admin']))
						__li(_link(_t("Member admin"), "member_admin"));
					if(isset($_SESSION['is_forum_admin']))
						__li(_link(_t("Forum admin"), "forum_admin"));
					if(isset($_SESSION['is_vote_admin']))
						__li(_link(_t("Vote admin"), "vote_admin"));
					if(isset($_SESSION['is_treasurer']))
						__li(_link(_t("Treasurer"), "treasurer"));
					if(isset($_SESSION['is_superadmin']))
						__li(_link(_t("Superadmin"), "superadmin"));
				?>
			</ul>
		</li>
		<?php endif; ?>
	</ul>
	<ul id="logout-link">
		<li><?php
				$is_delegate = db_delegate::is_user_delegate($_SESSION['id']);
				$user_label = db_user::get_user_full_name($_SESSION['id']);
				$hello = _span(_t("Hello, "), "large_screen");
				$user_label = $hello . $user_label;
				if ($_SESSION['delegate_id']) $user_label .=
					_t(" (delegate)", array('class' => 'noun'));
				__link($user_label, "member", "view");
			?>
			<ul>
				<?php if ($_SESSION['delegate_id']) : ?>
					<li><a onClick="set_acting_as_delegate(0)">
						<?php __t("Act as individual"); ?></a></li>
				<?php elseif (db_delegate::is_user_delegate($_SESSION['id'])) : ?>
					<li><a onClick="set_acting_as_delegate(1)">
						<?php __t("Act as delegate"); ?></a></li>
				<?php endif; ?>
				<li><a href="index.php?logout=1"><?php __t("Logout"); ?></a></li>
			</ul>
		</li>
	</ul>
</nav>
<div id="pseudo_menubar"></div>
<div style="clear: both;"></div>
