<?php
namespace View;

class workgroup 
{
	public static function list_workgroups($workgroups) {
		$columns = array(_t("Name"), _t("Restricted"), _t("Number of members"));
		$rows = array_map(function($workgroup) {
			return array(\View\controls::generate_internal_link($workgroup['title'], 'workgroup', 'view'
				, 'id=' . $workgroup['id'] . \View\general::get_from_action_for_url(array('search')))
			, ($workgroup['membership_vote_id'] ? _t("Yes"): _t("No"))
			, $workgroup['number_of_members']);
		}, $workgroups);
		\View\controls::output_grid_view($columns, $rows);
	}

	public static function output_workgroup_membership_vote_button($label, $action, $workgroup_id, $user_id) {
		_action(_t($label), $action, array("id" => $workgroup_id, "user" => $user_id));
	}

	public static function output_workgroup_info($workgroup, $is_member, $is_candidate) {
		if (isset($_GET['from_action']))
			\View\controls::output_search_back_link();
		_h1($workgroup['title']);
		if($workgroup['is_active']==0)
			_p(_t("This workgroup is proposed. It needs at least three members to be activated. Currently the number of members is " . $workgroup['number_of_members'] . "."));
		if($is_member)
			_p(_t("You are a member of this workgroup."));
		else if($is_candidate)
			_p(_t("You have applied for membership in this workgroup."));
		echo '<p>';
		_strong(_t("Number of members:   "));
		echo $workgroup['number_of_members'];
		_br();
		$is_active = $workgroup['is_active'];
		_strong(_t($is_active ? "Created: " : "Proposed: ", array('class' => 'adj')));
		echo \general_helpers::show_date($workgroup[$is_active ? 'create_time' : 'propose_time']);
		_br();				
		_strong(_t("Description: "));
		_br();
		echo \Logic\text::make_html_from_wiki_text($workgroup['description']);
		echo '</p>';
		if($is_member) {
			_link(_t("Edit description"), 'workgroup', 'edit', 'id=' . $_GET['id']);
			_br(2);
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
		_open_form();
		_hidden("id", $workgroup['id']);
		if($is_member) {
			__('You support that this workgroup is activated.');
			_space(3);
			_submit_and_close(_t("Stop supporting this workgroup"), "cancel_support_workgroup");
		}
		else {
			_space(3);
			_submit_and_close(_t("Support this workgroup"), "support_workgroup");
			__('(The workgroup will be activated when 3 members support it. The three supporters will automatically be given membership.)');
		}
		echo '</p>';
	}

	private static function output_workgroup_members($workgroup, $is_member)
	{
		$workgroup_members = \db_workgroup::list_members($workgroup['id']); 
		_p(_strong(_t("Members of this workgroup:")));
		foreach($workgroup_members as $row) {
			$user_id = $row['user_id'];
			_link($row['full_name'], 'member', 'view', 'id=' . $user_id);
			_space(3);
			if($is_member && $workgroup['membership_vote_id']==0) {
				$exclude_info = \db_workgroup::exclude_info($workgroup['id'], $row['user_id'], $_SESSION['id']);
				if($exclude_info['number_of_excluders']) {
					_space(3);
					__($exclude_info['number_of_excluders'] . " group member want to exclude this member.");
				}
				$is_excluder = $exclude_info['is_excluder'] > 0;
				if($is_excluder)
				 	__(" (You support the exclusion of this group member)");
			 	_space(3);						
				\View\workgroup::output_workgroup_membership_vote_button(
					$is_excluder ? "Undo" : "Vote for the exclusion of this group member"
					,$is_excluder ? "cancel_exclude" : "support_exclude", $workgroup['id'], $row['user_id']);
			}
			_br();
		}
	}

	private static function output_membship_changes($workgroup)
	{
		_br();
		_p(_t("This workgroup is closed and the members are appointed through candidate election. It is not possible to apply for membership in the same way as in open groups. The election of the members of this workgroup can be found ") . 
			\View\controls::generate_internal_link(_t("here"), 'vote','view_vote', 'id=' . $workgroup['membership_vote_id']));
		$workgroup_membership_changes = \db_workgroup::get_workgroup_election_changes($_GET['id']);
		if(!empty($workgroup_membership_changes)) {
			echo '<p>';
			_strong(_t("Upcoming changes in membership", array('class' => 'noun')));
			_br();
			echo '<table>';
			echo '<tr><th>' . _t("Time") . '</th><th>' . _t("Member out") . '</th><th>' 
			. _t("Candidate in") . '</th></tr>';
			foreach($workgroup_membership_changes as $row) {
				$name_of_user_in = \db_user::get_user_full_name($row['user_id_in']);
				$name_of_user_out = \db_user::get_user_full_name($row['user_id_out']);
				$time_of_transfer = \general_helpers::show_date($row['timestamp']+BUFFER_TIME_FOR_CONTINUOUS_ELECTIONS);
				echo '<tr><td>' . $time_of_transfer . '</td><td>';
				_link($name_of_user_out, 'member', 'view', 'id=' . $row['user_id_out']);
				echo '</td><td>';
				_link($name_of_user_in, 'member', 'view', 'id=' . $row['user_id_in']);
				echo '</td></tr>';
			}
			echo '</table></p>';
		}		
	}

	private static function output_open_workgroup_membership_support_form($workgroup) 
	{
		$workgroup_candidates = \db_workgroup::list_candidates($workgroup['id']);
		echo '<p>';
		_strong(_t("Candidates for membership: "));
		_br(2);
		if(empty($workgroup_candidates))
			__("No candidates");
		else foreach($workgroup_candidates as $row) {
			\View\controls::output_internal_link($row['full_name'], 'member', 'view', 'id=' . $row['user_id']);
			$candidate_info = \db_workgroup::candidate_info($workgroup['id'], $row['user_id'], $_SESSION['id']);
		 	$is_supporter = $candidate_info['is_supporter'];
		 	_space(3);
			__($candidate_info['number_of_supporters'] . 
				" group member support the admittance of this candidate."); 
		 	_space(3);
		 	_open_form();
		 	_hidden("id", $workgroup['id']);
		 	_hidden("user", $row['user_id']);
		 	if ($is_supporter)
				_submit_and_close("Revoke your support for this candidate", "cancel_support_candidate");
			else 
				_submit_and_close("Support this candidate", "support_candidate");
		}
		echo '</p>';
		echo '<p>';
		_strong(_t("Discontinue your membership"));
		_action(_t("Leave this workgroup"), "cancel_membership"
			, array("id" => $workgroup['id'])
			, _t("Do you really want to leave this workgroup?"));
		echo '</p>';
	}

	private static function output_open_workgroup_candidacy_form($workgroup)
	{
		\View\workgroup::output_open_workgroup_candidacy_form($workgroup);
		$candidate_info = \db_workgroup::candidate_info($workgroup['id'], $_SESSION['id'], $_SESSION['id']);
		$needed_member_count_for_candidate = ceil(\db_workgroup::get_member_count($workgroup['id']) / 1.999);
		echo '<p>';
		__('You have applied for membership in this workgroup. At present you are supported by ' . $candidate_info['number_of_supporters'] . ' member, ' . $needed_member_count_for_candidate . ' is needed to become a member.');
		_br();
		_open_form();
		_hidden("id", $workgroup['id']);
		_submit_and_close("Cancel your membership application", "cancel_candidacy");
		echo '</p>';
	}

	private static function output_open_workgroup_application_form($workgroup)
	{
		/*
		__p(
			_form(
				_hidden("id", $workgroup['id'])
				. _submit("Apply for membership")
				)
			);
		*/
		echo '<p>';
		_open_form();
		_hidden("id", $workgroup['id']);
		_submit_and_close("Apply for membership", "submit_candidacy");
		echo '</p>';
	}
}
?>
