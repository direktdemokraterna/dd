<?

class crypt_helpers {


public static function curl_to_anon_server ($anon_server_script, $post_vars = null){

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

// Function for calling up anon server and ordering it to hand out user codes to user, it also prints out the JS code for the user to fetch said user codes
public static function send_user_codes_to_user ($user_id){

	$temp_code = general_helpers::GenerateRandomString(20);

	$post_vars = Array("user_id" => $user_id, "temp_code" => $temp_code);
	$reply = crypt_helpers::curl_to_anon_server("receive_temp_code.php", $post_vars);

	if($reply == "success"){

		echo "<script>\n";
		echo "function JSONP (json) {\n";
		echo "sessionStorage.active_user_code = json.active_user_code;\n";
		echo "sessionStorage.passive_user_code1 = json.passive_user_code1;\n";
		echo "sessionStorage.passive_user_code2 = json.passive_user_code2;\n";
		echo "sessionStorage.passive_user_code3 = json.passive_user_code3;\n";
		echo "};\n";
		echo "</script>\n";
		echo "\n";
		echo "<script src='" . ANON_SERVER_URL . "give_out_user_codes.php?callback=JSONP&user_id=" . $user_id . "&temp_code=" . $temp_code . "'></script>\n";

	}

}

public static function decrypt_ballot ($rsa_message, $aes_message){

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


} //End of class