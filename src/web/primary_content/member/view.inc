<?php
	$user_id = isset($_GET['id']) ? $_GET['id'] : $_SESSION['id']; 
	$userinfo = db_user::get_user_data($user_id); 
	if($userinfo['full_name'] == "Inte aktiverad" && !$_SESSION['is_member_admin']){
		echo "Den här medlemmen är inte aktiverad ännu.";
	}
	else{
		__h1($userinfo['full_name']);
		echo '<div class="user_presentation_left">';
		echo '<img class="image150" src="' . USERIMG_PATH . 'userimg_150_width/' . $userinfo['image'] . '">';
		__br();
		__p(_link("Startade trådar (" 
			. $userinfo['number_of_topics'] . ")", 'forum', 'topics_by_user', 'id=' 
			. $userinfo['id']));
		__p(_link("Inlägg (" 
			. $userinfo['number_of_posts'] . ")", 'forum', 'posts_by_user', 'id=' 
			. $userinfo['id']));
		if(!$userinfo['deletion_time'])
			__p(_link("Skicka meddelande", 'message', 'write', 'id=' . $userinfo['id']));
		echo '</div>';
		echo '<div class="user_presentation_right">';
		if($userinfo['deletion_time']) {
			__p("Den här användarens medlemskap avslutades " . strtolower(general_helpers::show_date($userinfo['deletion_time'])) . '.');
			if(isset($_SESSION['is_member_admin'])) {
				__open_form();
				__hidden("restore_user", 1);
				__submit_and_close("Återställ medlem");
			}
		}
		else {
			echo '<div class="user-info-details">';
			__p('<strong>Roll i Direktdemokraterna:</strong>');
			$admin_roles = db_admin::get_admin_roles_for_user($user_id);			
			foreach($admin_roles as $row)
				__p(_link($row['title'], 'member', 'admin_description', 'id=' . $row['id']));
			__p('&nbsp;');
			__p("<strong>Senaste<br>inloggning:</strong> " . (empty($userinfo['last_activity_time']) ? "Aldrig" : general_helpers::show_date($userinfo['last_activity_time'])));
			if($userinfo['show_email'])
				__p("<strong>Mejladress:</strong> " . $userinfo['email']);
			if($userinfo['show_telephone']) {
				if(!empty($userinfo['telephone1']))
					__p("<strong>Telefonnummer:</strong> " . $userinfo['telephone1']);
				if(!empty($userinfo['telephone2']))
					__p("<strong>Telefonnummer:</strong> " . $userinfo['telephone2']);
			}
			if($userinfo['show_skype'] && !empty($userinfo['skype_name']))
				__p("<strong>Skype-namn:</strong> " . $userinfo['skype_name']);
			__p("<strong>Kommun:</strong> " . $userinfo['county_name']);
			__p("<strong>Län:</strong> " . $userinfo['region_name']);
			__p("<strong>Presentation:</strong>" . '<br>' . \Logic\text::make_html_from_wiki_text($userinfo['description']));
			echo '</div>';
			__br();
			if ($user_id == $_SESSION['id'])
				__p(_link("Ändra mina uppgifter", 
					"member", "settings"));
			elseif(isset($_SESSION['is_member_admin']))
				__p(_link("Ändra uppgifter för denna användare", 
					"member_admin", "edit", "id=" . $user_id));
			if(isset($_SESSION['is_forum_admin']))
				__p(_link("Ställ in forumbehörigheter för denna användare", 
					"forum_admin", "edit_user", "id=" . $user_id));
			if(isset($_SESSION['is_vote_admin']))
				__p(_link("Ställ in valkretsbehörigheter för denna användare", 
					"vote_admin", "edit_user", "id=" . $user_id));
			if(isset($_SESSION['is_superadmin']))
				__p(_link("Ställ in admin-rättigheter för denna användare", 
					"superadmin", "edit_admin", "id=" . $user_id));
			if(isset($_SESSION['is_member_admin'])) {
				__open_form();
				__hidden("delete_user", 1);
				__submit_and_close("Ta bort den här användaren", null, "Vill du verkligen ta bort den här användaren?");
			}
		}
	}
	echo '</div>';
?>
