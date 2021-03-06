<?php
class crypt_helpers 
{
	public static function curl_to_anon_server ($anon_server_script, $post_vars = null, $sign = true)
	{
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, ANON_SERVER_URL . $anon_server_script);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
		curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 2);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 1);
		curl_setopt($ch, CURLOPT_BINARYTRANSFER, 1);
		if ($sign)
			$post_vars = self::sign($post_vars);
		if ($post_vars) {
			$post_data = http_build_query($post_vars);
			curl_setopt($ch, CURLOPT_POST, 1);
			curl_setopt($ch, CURLOPT_POSTFIELDS, $post_data);			
		}
		$reply = curl_exec($ch);
		$info = curl_getinfo($ch);
		curl_close($ch);
		return $reply;
	}

	public static function get_signed_data_from_anon_server() {
		$serial_data = $_POST['data'];
		$signature = $_POST['sign'];
		self::verify($signature, $serial_data);
		$data = unserialize($serial_data);
		return $data;
	}

	private static function sign($post_vars) {
		include_once('Crypt/RSA.php');
		if (!$post_vars)
			$post_vars = array();
		$post_vars['salt'] = general_helpers::GenerateRandomString(20);
		$serial_data = serialize($post_vars);
		$hash = hash('sha256', $serial_data);
		$rsa = new Crypt_RSA();
		$rsa->loadKey(DD_PRIVATE_KEY);
		$rsa->setEncryptionMode(CRYPT_RSA_ENCRYPTION_PKCS1);
		$signature = $rsa->encrypt($hash);
		$post_vars = array('sign' => ($signature), 'data' => ($serial_data));
		return $post_vars;
	}

	private static function verify($signature, $plaintext) {
		include_once('Crypt/RSA.php');
		$computed_hash = hash('sha256', $plaintext);
		$rsa = new Crypt_RSA();
		$rsa->loadKey(DD_ANON_PUBLIC_KEY);
		$rsa->setEncryptionMode(CRYPT_RSA_ENCRYPTION_PKCS1);
		$hash = $rsa->decrypt($signature);
		if ($hash != $computed_hash)
			throw new \Exception('Invalid message: ' . $plaintext 
				. '. Hash missmatch, provided: ' . $hash 
				. ', computed: ' . $computed_hash);
	}

	public static function retrieve_user_code_on_client ($user_id)
	{
		$temp_code = general_helpers::GenerateRandomString(20);
		$_SESSION['temp_code'] = $temp_code;
		$post_vars = array("user_id" => $user_id, "temp_code" => $temp_code);
		$reply = crypt_helpers::curl_to_anon_server("receive_temp_code.php", $post_vars);
		if($reply != "success") 
			die($reply);
		echo '<script>' . PHP_EOL;
		echo 'is_session_active = 0;' . PHP_EOL;
 		self::output_get_user_code_cross_domain_call($user_id, $temp_code);
 		echo '</script>' . PHP_EOL;
	}

	public static function ensure_user_code_on_client ($user_id)
	{
		echo '<script>' . PHP_EOL;
		echo 'session_too_old_message = "' 
			. "Din session är för gammal. Logga ut och logga in igen" . '";' . PHP_EOL;
		echo 'is_session_active = sessionStorage.user_code ? 1 : 0;' . PHP_EOL;
 		self::output_get_user_code_cross_domain_call($user_id, $_SESSION['temp_code']);
 		echo '</script>' . PHP_EOL;
	}

	private static function output_get_user_code_cross_domain_call($user_id, $temp_code) 
	{
		echo 'var cross_domain_script = document.createElement("script");' . PHP_EOL;
		echo 'cross_domain_script.src = "' . ANON_SERVER_BROWSER_URL
 			. 'give_out_user_code.php?user_id=' . $user_id
 			. '&temp_code=' . $temp_code . '&ignore=" + is_session_active;' . PHP_EOL;
 		echo 'document.getElementsByTagName("head")[0].appendChild(cross_domain_script);' . PHP_EOL;
	}

	public static function decrypt_ballot ($rsa_message, $aes_message)
	{
		// decryption using phplibsec RSA library
		include_once('Crypt/RSA.php');
		$rsa = new Crypt_RSA();
		$rsa->loadKey(DD_PRIVATE_KEY);
		$rsa->setEncryptionMode(CRYPT_RSA_ENCRYPTION_PKCS1);

		$ballot_rsa_decrypted = $rsa->decrypt(base64_decode($rsa_message));
		$ballot_rsa_decrypted_decoded = json_decode($ballot_rsa_decrypted, true);

		// decryption using Giberish AES library
		include_once('Crypt/GibberishAES.php');
		$ballot_aes_decrypted = GibberishAES::dec($aes_message, $ballot_rsa_decrypted_decoded['password']);
		$ballot_aes_decrypted_decoded = json_decode($ballot_aes_decrypted, true);
		return $ballot_aes_decrypted_decoded;
	}
}
