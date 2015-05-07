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

	$private_key = "-----BEGIN RSA PRIVATE KEY----- MIIEogIBAAKCAQEAsIpWVPRtuUJci9JuZEQYExLoWrWqCO7KImTVRRryZKCQ8ywg i9bfS7inDpOvrmiMORomHjj7SDRySIzB8hpyC+DLVQEKz3vVs5bafzGxQcBdvdI3 bXmCEd3mkmwaWhPcwTbARS71VbOTMezz7EQMjsSO4L6B74vblIJV+t+Q5D4v+FU1 EgVCR22o3niM8MaqGAQTDpwC08cYQ2K4Iog5Wh8Qv53JeJv0h6qQC7iB1Pf5oLrX tXxF/ozzBapFzRPFCj/Yvfx/7NPj1qFD/z4LkJAgWWnrpUEgwj55Lm6YHZPJThul x5IkvUdPjjtaMx4ktVaV1pj1g0ulB59It2E54wIDAQABAoIBAAOlPHNXpfzJdB8t Be6+TmyPNOR+oNeILfz4B3fJJSoGLy536E1XvArhWFqSmr7N70TuMQBQKk9k43Rz d6PLGQGWyQwYNlCitkuvLBOsg1EGXfxhkjE805gQp9/sXItX1dsL7693pBHhE4NY T12L6ch4iMzD3x7Pszj48gaSrEUr3KdiSY3qqx8cRRcQJDfTrRjOnx5JYWMPUAIU P+uoVrZIbKNWPPcdm5ErkcSJWPw48B8s47zrlEglNCdrRYp3n70cx+SuOd2rx2ND NV6EUVXTBz2gu6HOvYFChv4L9XmspCsaDnqNPgxbh0fJkXP3i/DHHJASxwKG1eY+ ybkuEDUCgYEAshohDFDmLe98MvuCCbjpB0A8m6To5mUqXBG0xnLqj+dVmZTiZTbr l/WwCRwEoDTLVOzTTovCtsFKM3Bcmj0mIdsc5bEMiV9w7kb+OTj28gHUVPxiOyqd KhIPJ5P3LKpT4Jk2gNgILuDKIMFq7hYt6ZWWlDwq6NGephtYuCJoRc0CgYEA/cFZ E9AUiR7V0rRnJXQ66POQeIItmhHACjB1NoDv5g2wanF8K+mUdnPWXry4HVUgmp4c N2JW3t/CE7OaZ2q08WEEJuPAgtuxfYbSiTWHigwe2VUNWmGjR78Q8pIYePgnyDft MATy2obRzx3EvjlQRQz5ixLr+zuu/vu7pXQAzm8CgYBX5b1ZrrNrCD5riuTql2+q PHGs/v5SdqspNTPanOxWiP0eBvSUrz4miQKP/FvsFSIkj5zZrvAx8cMFD/cjx/oB y3m/glmFkqzRbAgbhZmaZny8VLLGMInQMYl5JvVd/dHXjsXvYK7pM9eNwudbCWcv WLwv/GHQ9WMu52ApwBFmIQKBgCQ8y0rACV63j5OCfcRkf9EqjzQWawq4hDMwTlzV Nu0kgVACGthuh+wOiMuIqcZOlNRfxenG2l8Dl0SW/nLMU0CxORWQqrpFQ2iIq2I6 ybtWFcW1lq2UievCBlqNsH79+ThnfDDCVCgO3sF0H9eGeccSnkRVFGwRTuFM87Qi B8dzAoGAZgaDoRoVmGwy4xsTOlwISdUfmYvGjLEFujUHTC2ky4x7CjVoAGtSycJx U6wdMOfAZG/NeuRaop3Jz35H7+zFr2195pnKgJirdvAcwPO2hoKv8xF9yGU6Pp1Q 7dBfULUhppU0IT7hX9fONkaKk9TzpU4R/paFDTxPTuiA1v5rLlg= -----END RSA PRIVATE KEY-----";

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