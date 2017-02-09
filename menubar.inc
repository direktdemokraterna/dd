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
		<li class="mb-members"><?php
			__link("Användare", "member");
			\View\controls::output_link_list("member", array(
				"settings" => "Profil"
				,"memberlist" => "Medlemmar"
				,"admin_list" => "Administratörer"
				));
			?>
		</li>
		<?php if(db_message::check_unread($_SESSION['id']) > 0) : ?>
			<li id="unread-mail"><a href="index.php?type=message&action=inbox" style="min-width: 15px; padding: 0 5px 0 5px;"><span style="font: 400 13px/32px FontAwesome;" class="fa fa-envelope-o" id="fa-envelope-o"></span></a>
			</li>
		<?php endif; ?>
		<li class="mb-messages"><?php
			__link("Meddelanden", "message");
			\View\controls::output_link_list("message", array(
				"inbox" => "Inkorg"
				,"outbox" => "Utkorg"
				,"write" => "Skriv meddelande"
				));
			?>
		</li>
		<li class="mb-votes"><?php
			__link("Omröstningar", "vote");
			\View\controls::output_link_list("vote", array(
				"list_props" => "Propositioner"
				,"list_active_votes" => "Omröstningar"
				,"delegations" => "Delegater"
				));
			?>
		</li>
		<li class="mb-forum"><?php __link("Forum", "forum"); ?></li>
		<?php if(isset($_SESSION['admin'])) : ?>
		<li class="mb-admin"><a href="#">Admin</a>
			<ul>
				<?php
					if(isset($_SESSION['is_member_admin']))
						__li(_link("Medlemsadministratör", "member_admin"));
					if(isset($_SESSION['is_forum_admin']))
						__li(_link("Forumadministratör", "forum_admin"));
					if(isset($_SESSION['is_vote_admin']))
						__li(_link("Valadministratör", "vote_admin"));
					if(isset($_SESSION['is_treasurer']))
						__li(_link("Kassör", "treasurer"));
					if(isset($_SESSION['is_superadmin']))
						__li(_link("Superadmin", "superadmin"));
				?>
			</ul>
		</li>
		<?php endif; ?>
		<?php
			$notices = db_notice::get_view_notices_for_user($_SESSION['id']);
			if(!empty($notices)){
				echo '<li id="unread-mail"><a href="index.php?type=member&action=notice" style="min-width: 15px; padding: 0 5px 0 5px;"><span style="font: 400 13px/32px FontAwesome;" class="fa fa-bell-o" id="fa-bell-o"></span></a><ul>';
				foreach ($notices as $notice) {
					echo "<li>";
					echo general_helpers::output_notice_link($notice['id']);
					echo "</li>";
				}
				if(count($notices) > 1)
					echo "<li style=\"border-top: dotted;\"><a href=\"" . $_SERVER['REQUEST_URI'] . "&remove_all_notices=1\">Ta bort alla notifieringar</a></li>";
				echo "</ul></li>";
			}
		 ?>
	</ul>
	<ul id="logout-link">
		<li><?php
				$is_delegate = db_delegate::is_user_delegate($_SESSION['id']);
				$user_label = db_user::get_user_full_name($_SESSION['id']);
				$hello = _span("Hallå ", "large_screen");
				$user_label = $hello . $user_label;
				if ($_SESSION['delegate_id']) $user_label .=
					" (delegat)";
				__link($user_label, "member", "view");
			?>
			<ul>
				<?php if ($_SESSION['delegate_id']) : ?>
					<li class="mb-individual"><a onClick="set_acting_as_delegate(0)">
						Agera som individ</a></li>
				<?php elseif (db_delegate::is_user_delegate($_SESSION['id'])) : ?>
					<li class="mb-delegate"><a onClick="set_acting_as_delegate(1)">
						Agera som delegat</a></li>
				<?php endif; ?>
				<li class="mb-logout"><a href="index.php?logout=1">Logga ut</a></li>
			</ul>
		</li>
	</ul>
</nav>
<div id="pseudo_menubar"></div>
<div style="clear: both;"></div>
