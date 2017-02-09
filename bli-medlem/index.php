<?php 
include("../init.inc");

function getPostValueOrEmpty($name) {
    return isset($_POST[$name]) ? general_helpers::clean($_POST[$name]) : "";
}

$first_name = getPostValueOrEmpty('first_name');
$last_name = getPostValueOrEmpty('last_name');
$street_address = getPostValueOrEmpty('street_address');
$zip_code = str_replace(" ", "", getPostValueOrEmpty('zip_code'));
$city_address = getPostValueOrEmpty('city_address');
$county_id = getPostValueOrEmpty('county_id');
$user_data = [
    'county_id' => $county_id
];
$telephone1 = str_replace(" ", "", str_replace("-", "", getPostValueOrEmpty('telephone1')));
$telephone2 = str_replace(" ", "", str_replace("-", "", getPostValueOrEmpty('telephone2')));
$personal_identity_number = general_helpers::clean_personnummer(getPostValueOrEmpty('personal_identity_number'));
$email = getPostValueOrEmpty('email');

// Processing data if form has been posted
$mandatory_fields = array('first_name', 'last_name', 'street_address', 'zip_code', 'city_address', 'county_id', 'email', 'personal_identity_number');
$is_all_mandatory_set = true;
foreach ($mandatory_fields as $mandatory) {
    $is_all_mandatory_set &= !empty($_POST[$mandatory]);
}
$region_id = true;
if ($is_all_mandatory_set) {
    $error_message = \Logic\user::validate_user($personal_identity_number, $email);
    if (!$error_message)
        $region_id = db_constituency::get_region_id_from_county_id($county_id);
	if (!$region_id) {
        $error_message = "Välj kommun";
    } else {
	    $user_data['region_id'] = $region_id;
    }
    if (!$error_message) {
        $form_data_has_been_processed = db_user::enter_user_application(
            $first_name
            , $last_name
            , $street_address
            , (int)$zip_code
            , $city_address
            , $user_data['county_id']
            , $region_id
            , $personal_identity_number
            , $email
            , $telephone1
            , $telephone2);
    }
} else if ($_POST) {
    $error_message = "Ett eller flera fält är inte ifyllda";
}

?><!DOCTYPE html>
<html>
<head>
    <link href="../helpers/css/reset.css" rel="stylesheet" type="text/css">
    <link href="../helpers/css/index.css" rel="stylesheet" type="text/css">
	<link href="../helpers/css/login.css" rel="stylesheet" type="text/css">
    <link href="../helpers/font-awesome-4.3.0/css/font-awesome.min.css" rel="stylesheet" type="text/css">
	<meta charset="UTF-8" />
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="shortcut icon" href="../images/favicon.ico">
	<title>Direktdemokraterna Medlemssystem - Bli medlem. Version <?php echo VERSION ?></title>
</head>

<body>

<div id="wrap">
<div class="login-column">
<div>
	<?php \View\index::output_language_buttons(); ?>
</div>
<div class="login_image">
	<img src="../images/dd120.png">
</div>

<br>

<?php 
	if(isset($form_data_has_been_processed)) {
		echo '<p>';
		__h1("Tack för din ansökan");
		echo '</p>';
		die();
	}
	if (isset($error_message)) {
		echo '<p>' . $error_message .'</p>';
	}
?>
<h1 style="font-size: 24px; font-family: Lato, sans-serif; font-weight: 700; margin-bottom: 30px; ">Medlemsansökan
</h1>
<script src="//code.jquery.com/jquery-1.11.3.min.js"></script>
<script src="../helpers/js/constituency.js"></script>
<script src="../helpers/js/session.js"></script>

<?php
	echo "* obligatoriskt";
	__br();
	__open_form("login-form");
	$tab_index = 1;
	__textfield('first_name', "Förnamn*", $tab_index++, $first_name, ['autofocus' => null, 'required' => null]);
	__textfield('last_name', "Efternamn*", $tab_index++, $last_name, ['required' => null]);
	__textfield('street_address', "Gatuadress*", $tab_index++, $street_address, ['required' => null]);
	__textfield('zip_code', "Postnummer*", $tab_index++, $zip_code, ['required' => null]);
	__textfield('city_address', "Postort*", $tab_index++, $city_address, ['required' => null]);
	\View\member::output_county_selectors($user_data, $tab_index);
	__textfield("telephone1", "Telefonnummer", $tab_index++, $telephone1);
	__textfield("telephone2", "Alternativt telefonnummer", $tab_index++, $telephone2);
	__textfield("email", "Mejladress*", $tab_index++, $email, ['required' => null]);
	__textfield("personal_identity_number", "Personnummer*", $tab_index++, $personal_identity_number, ['required' => null]);
?>
<input type="checkbox" name="news_letter" value="1" id="news_letter">
	<label for "news_letter">Jag vill prenumerera på nyhetsbrevet</label>
<button type="submit" value="Skicka">Skicka</button>
</form>

</div>
</div>

</body>
</html>