<?php
namespace View;

class workgroup 
{
	public static function output_workgroup_membership_vote_button($label, $action, $workgroup_id, $user_id) {
		echo '<form method="post" action="" class="standard-form" style="display: inline;">';
		echo '<input type="hidden" name="type" value="' 
		. $action . '"><input type="hidden" name="id" value="' . $workgroup_id . '">';
		echo '<input type="hidden" name="user" value="' . $user_id . '">';
		echo '<input type="submit" style="width: auto;" value="' . _t($label) . '">';
		echo '</form>';
	}
}
?>
