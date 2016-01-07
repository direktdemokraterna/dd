<?php
namespace Logic;

class delegate 
{
	public static function delete_delegate_for_user ($user_id)
	{
		$delegate_id = \db_delegate::get_delegate_id_from_user_id($user_id);
		return self::delete_delegate($delegate_id);
	}

	public static function delete_delegate ($delegate_id)
	{
		\Logic\vote::remove_delegate_ballots($delegate_id);
		\Logic\vote::remove_delegate_delegations($delegate_id);
		\db_constituency::remove_constituency_access($delegate_id);
		return \db_delegate::delete_delegate($delegate_id);
	}

	public static function register_delegation_from_post() 
	{
		if(isset($_POST['ballot'])){
			if($_SESSION['delegate_id']){
				$delegand_id = $_SESSION['delegate_id'];
				$ballot = json_decode($_POST['ballot'], true);
				$constituency_id = $ballot['constituency_id'];
				$delegate_id = $ballot['delegate_id'];
				\db_constituency::check_voter_constituency_access($delegand_id, $constituency_id);
				$ok = \db_delegate::register_delegation(null, $delegand_id, $delegate_id, $constituency_id);
				if($ok)
					$_SESSION['report_message'] = _t("Your delegate's delegation is registered.");
				else
					\Logic\util::report_error(_t("Something went wrong. No delegation registered."));
			}
			else{
				$user_constituencies = \db_constituency::get_constituencies_for_voter($_SESSION['id']);
				$user_constituencies_array = Array();
				foreach($user_constituencies as $row)
					$user_constituencies_array[] = $row['id'];
				$user_constituencies_serialized = serialize($user_constituencies_array);
				$post_vars = Array("user_id" => $_SESSION['id'], "user_constituencies" => $user_constituencies_serialized, "ballot" => $_POST['ballot']);
				$reply = \crypt_helpers::curl_to_anon_server("anonymise_delegation_ballot.php", $post_vars);
				if($reply == "success")
					$_SESSION['report_message'] = _t("Your delegation is registered.");
				else
					\Logic\util::report_error(_t("Something went wrong. No delegation registered."));
			}
		}		
	}
}
