<?php
namespace View;

class workgroup 
{
	public static function list_workgroups($workgroups) {
		$columns = array("Namn", "Stängd", "Antal medlemmar");
		$rows = array_map(function($workgroup) {
			return array(_link($workgroup['title'], 'workgroup', 'view'
				, 'id=' . $workgroup['id'] . \View\general::get_from_action_for_url(array('search')))
			, ($workgroup['membership_vote_id'] ? "Ja": "Nej")
			, $workgroup['number_of_members']);
		}, $workgroups);
		\View\controls::output_grid_view($columns, $rows);
	}

	public static function output_workgroup_membership_vote_button($label, $action, $workgroup_id, $user_id) {
		__action($label, $action, array("id" => $workgroup_id, "user" => $user_id));
	}

	public static function output_workgroup_info($workgroup, $is_member, $is_candidate) {
		\View\controls::output_search_back_link();
		__h1($workgroup['title']);
		if($workgroup['is_active']==0)
			__p("Den här arbetsgruppen är föreslagen. Den behöver at least tre medlemmar till var aktiverade. För närvarande antalet medlemmar är " . $workgroup['number_of_members'] . ".");
		if($is_member)
			__p("Du är medlem i denna arbetsgrupp.");
		else if($is_candidate)
			__p("Du har ansökt om medlemskap i denna arbetsgrupp.");
		echo '<p>';
		__strong("Antal medlemmar: ");
		echo $workgroup['number_of_members'];
		__br();
		$is_active = $workgroup['is_active'];
		__strong($is_active ? "Skapad: " : "Föreslagen: ");
		echo \general_helpers::show_date($workgroup[$is_active ? 'create_time' : 'propose_time']);
		__br();				
		__strong("Beskrivning: ");
		__br();
		echo \Logic\text::make_html_from_wiki_text($workgroup['description']);
		echo '</p>';
		if($is_member) {
			__link("Ändra beskrivning", 'workgroup', 'edit', 'id=' . $_GET['id']);
			__br(2);
		}		
	}

	public static function output_active_group_membership($workgroup, $is_member) {
		\View\workgroup::output_workgroup_members($workgroup, $is_member);
		if($workgroup['membership_vote_id'])
			\View\workgroup::output_membship_changes($workgroup);
		elseif($is_member)
			\View\workgroup::output_open_workgroup_membership_support_form($workgroup);
		elseif($is_candidate)
			\View\workgroup::output_open_workgroup_candidacy_form($workgroup);
		else
			\View\workgroup::output_open_workgroup_application_form($workgroup);
	}

	public static function output_inactive_workgroup_form($workgroup, $is_member)
	{
		echo '<p>';
		__open_form();
		__hidden("id", $workgroup['id']);
		if($is_member) {
			echo "Du stödjer att denna arbetsgrupp aktiveras.";
			__space(3);
			__submit_and_close("Sluta stödja denna arbetsgrupp", "cancel_support_workgroup");
		}
		else {
			__space(3);
			__submit_and_close("Stöd denna arbetsgrupp", "support_workgroup");
			echo "Arbetsgruppen kommer att aktiveras när tre medlemmar stöder dess bildande. De tre stödjarna kommer automatiskt att bli medlemmar i den nybildade arbetsgruppen.";
		}
		echo '</p>';
	}

	private static function output_workgroup_members($workgroup, $is_member)
	{
		$workgroup_members = \db_workgroup::list_members($workgroup['id']); 
		__p(__strong("Medlemmar i denna arbetsgrupp:"));
		foreach($workgroup_members as $row) {
			$user_id = $row['user_id'];
			__link($row['full_name'], 'member', 'view', 'id=' . $user_id);
			__space(3);
			if($is_member && $workgroup['membership_vote_id']==0) {
				$exclude_info = \db_workgroup::exclude_info($workgroup['id'], $row['user_id'], $_SESSION['id']);
				if($exclude_info['number_of_excluders']) {
					__space(3);
					echo $exclude_info['number_of_excluders'] . " gruppmedlemmar vill utesluta den här medlemmen.";
				}
				$is_excluder = $exclude_info['is_excluder'] > 0;
				if($is_excluder)
				 	echo " (Du stöder uteslutning av den här gruppmedlemmen)";
			 	__space(3);						
				\View\workgroup::output_workgroup_membership_vote_button(
					$is_excluder ? "Undo" : "Rösta för uteslutning av denna gruppmedlem"
					,$is_excluder ? "cancel_exclude" : "support_exclude", $workgroup['id'], $row['user_id']);
			}
			__br();
		}
	}

	private static function output_membship_changes($workgroup)
	{
		__br();
		__p("Den här arbetsgruppen är stängd och medlemmarna utses via personval. Det går inte att ansöka om medlemskap på samma sätt som i öppna grupper. Personvalet av medlemmarna i denna arbetsgrupp finns " . 
			_link("här", 'vote','view_vote', 'id=' . $workgroup['membership_vote_id']));
		$workgroup_membership_changes = \db_workgroup::get_workgroup_election_changes($_GET['id']);
		if(!empty($workgroup_membership_changes)) {
			echo '<p>';
			__strong("Kommande förändringar i medlemskap");
			__br();
			echo '<table>';
			echo '<tr><th>Tidpunkt</th><th>Medlem ut</th><th>Medlem in</th></tr>';
			foreach($workgroup_membership_changes as $row) {
				$name_of_user_in = \db_user::get_user_full_name($row['user_id_in']);
				$name_of_user_out = \db_user::get_user_full_name($row['user_id_out']);
				$time_of_transfer = \general_helpers::show_date($row['timestamp']+BUFFER_TIME_FOR_CONTINUOUS_ELECTIONS);
				echo '<tr><td>' . $time_of_transfer . '</td><td>';
				__link($name_of_user_out, 'member', 'view', 'id=' . $row['user_id_out']);
				echo '</td><td>';
				__link($name_of_user_in, 'member', 'view', 'id=' . $row['user_id_in']);
				echo '</td></tr>';
			}
			echo '</table></p>';
		}		
	}

	private static function output_open_workgroup_membership_support_form($workgroup) 
	{
		$workgroup_candidates = \db_workgroup::list_candidates($workgroup['id']);
		echo '<p>';
		__strong("Kandidater till medlemskap: ");
		__br(2);
		if(empty($workgroup_candidates))
			echo "Inga kandidater";
		else foreach($workgroup_candidates as $row) {
			__link($row['full_name'], 'member', 'view', 'id=' . $row['user_id']);
			$candidate_info = \db_workgroup::candidate_info($workgroup['id'], $row['user_id'], $_SESSION['id']);
		 	$is_supporter = $candidate_info['is_supporter'];
		 	__space(3);
			echo $candidate_info['number_of_supporters'] . " medlemmar stöder denna kandidatur."; 
		 	__space(3);
		 	__action(($is_supporter ? "Ta tillbaka ditt stöd för" : "Stöd denna") . " kandidat"
		 		, ($is_supporter ? "ångra stöd" : "stöd") . "_candidate"
		 		, array("id" => $workgroup['id'], "user" => $row['user_id']));

		}
		echo '</p>';
		echo '<p>';
		__strong("Gå ur denna arbetsgrupp");
		__action("Gå ur denna arbetsgrupp", "cancel_membership"
			, array("id" => $workgroup['id'])
			, "Vill du verkligen lämna den här arbetsgruppen?");
		echo '</p>';
	}

	private static function output_open_workgroup_candidacy_form($workgroup)
	{
		\View\workgroup::output_open_workgroup_candidacy_form($workgroup);
		$candidate_info = \db_workgroup::candidate_info($workgroup['id'], $_SESSION['id'], $_SESSION['id']);
		$needed_member_count_for_candidate = ceil(\db_workgroup::get_member_count($workgroup['id']) / 1.999);
		echo '<p>';
		echo 'Du har ansökt om medlemskap i denna arbetsgrupp. För närvarande är det ' . $candidate_info['number_of_supporters'] . ' medlemmar som stödjer dig, ' . $needed_member_count_for_candidate . ' behövs för att göra dig till medlem.';
		__br();
		action("Dra tillbaka din medlemsansökan", "cancel_candidacy"
			, array("id" => $workgroup['id']));
		echo '</p>';
	}

	private static function output_open_workgroup_application_form($workgroup)
	{
		echo '<p>';
		__action("Ansök om medlemskap", "submit_candidacy", array("id" => $workgroup['id']));
		echo '</p>';
	}
}
?>
