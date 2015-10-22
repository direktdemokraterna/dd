<?php
class crypt_helpers 
{
	public static function curl_to_anon_server ($anon_server_script, $post_vars = null)
	{
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, ANON_SERVER_URL . $anon_server_script);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		if($post_vars){
			$post_data = http_build_query($post_vars);
			curl_setopt($ch, CURLOPT_POST, 1);
			curl_setopt($ch, CURLOPT_POSTFIELDS, $post_data);
		}
		$reply = curl_exec($ch);
		curl_close($ch);
		return $reply;
	}

	public static function retrieve_user_codes_on_client ($user_id)
	{
		$_SESSION['temp_code'] = general_helpers::GenerateRandomString(20);
		$post_vars = Array("user_id" => $user_id, "temp_code" => $_SESSION['temp_code']);
		$reply = crypt_helpers::curl_to_anon_server("receive_temp_code.php", $post_vars);
		if($reply != "success") 
			die($reply);		
		echo "<script>retrieveUserCodes('" .  ANON_SERVER_BROWSER_URL . "', " . $user_id . 
			", '" . $_SESSION['temp_code'] . "');</script>\n";
	}

	public static function ensure_user_codes_on_client ($user_id)
	{
		echo "<script>ensureUserCodes('" .  ANON_SERVER_BROWSER_URL . "', " . $user_id . ", '" . $_SESSION['temp_code'] . "');</script>\n";
	}

	public static function decrypt_ballot ($rsa_message, $aes_message)
	{
		$private_key = RSA_PRIVATE_KEY;
		// decryption using phplibsec RSA library
		include('Crypt/RSA.php');
		$rsa = new Crypt_RSA();
		$rsa->loadKey($private_key);
		$rsa->setEncryptionMode(CRYPT_RSA_ENCRYPTION_PKCS1);

		$ballot_rsa_decrypted = $rsa->decrypt(base64_decode($rsa_message));
		$ballot_rsa_decrypted_decoded = json_decode($ballot_rsa_decrypted, true);

		// decryption using Giberish AES library
		include('Crypt/GibberishAES.php');
		$ballot_aes_decrypted = GibberishAES::dec($aes_message, $ballot_rsa_decrypted_decoded['password']);
		$ballot_aes_decrypted_decoded = json_decode($ballot_aes_decrypted, true);
		return $ballot_aes_decrypted_decoded;
	}
}
?>