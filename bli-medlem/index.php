<?php 
include("../init.inc");
session::update_language();

// Processing data if form has been posted
$mandatory_fields = array('first_name', 'last_name', 'street_address', 'zip_code', 'city_address', 'county_id', 'email', 'social_security_number');
$is_all_mandatory_set = true;
foreach ($mandatory_fields as $mandatory) 
	$is_all_mandatory_set &= isset($_POST[$mandatory]);
if($is_all_mandatory_set){
	$telephone1 = str_replace(" ", "", str_replace("-", "", $_POST['telephone1']));
	$telephone2 = str_replace(" ", "", str_replace("-", "", $_POST['telephone2']));
	$personnummer = general_helpers::clean_personnummer($_POST['social_security_number']);
	$error = \Logic\user::validate_user($personnummer, $_POST['email']);
	if ($error)
		die($error);
	$region_id = db_constituency::get_region_id_from_county_id($_POST['county']);
	if(!$region_id)
		die(_t("Select your municipality."));
	$form_data_has_been_processed = db_user::enter_user_application(
		general_helpers::clean($_POST['first_name'])
		, general_helpers::clean($_POST['last_name'])
		, general_helpers::clean($_POST['street_address'])
		, (int)$_POST['zip_code']
		, general_helpers::clean($_POST['city_address'])
		, $_POST['county_id']
		, $region_id
		, $personnummer
		, $_POST['email']
		, general_helpers::clean($telephone1)
		, general_helpers::clean($telephone2));
}

?><!DOCTYPE html>
<html>
<head>
	<link href="../helpers/css/index.css" rel="stylesheet" type="text/css">
	<link href="../helpers/css/login.css" rel="stylesheet" type="text/css">
	<meta charset="UTF-8" />
	<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<link rel="shortcut icon" href="../images/favicon.ico">
	<title>DD Medlemssystem ver <?php echo VERSION ?></title>
</head>

<body>

<div class="wrap">
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
		__h1(_t("Thank you for your application."));		
		echo '</p>';
		die();
	}
	if ($_POST) {
		echo '<p>';
		__t("One or more mandatory fields are not filled in.");		
		echo '</p>';
	}
?>
<h1 style="font-size: 24px; font-family: Lato, sans-serif; font-weight: 700; margin-bottom: 30px; "><?php __t("Membership application"); ?>
</h1>
<script src="//code.jquery.com/jquery-1.11.3.min.js"></script>
<script src="../helpers/js/constituency.js"></script>
<script src="../helpers/js/session.js"></script>

<?php
	__t("* mandatory");
	__br();
	__open_form("login-form");
	$tab_index = 1;
	__textfield('first_name', _t("Given name"), $tab_index++);
	__textfield('last_name', _t("Last name*"), $tab_index++);
	__textfield('street_address', _t("Street address*"), $tab_index++);
	__textfield('zip_code', _t("Zip code*"), $tab_index++);
	__textfield('city_address', _t("City*"), $tab_index++);
	\View\member::output_county_selectors();
	__textfield("telephone1", _t("Telephone 1"), $tab_index++);
	__textfield("telephone2", _t("Telephone 2"), $tab_index++);
	__textfield("email*", _t("Email"), $tab_index++);
	__textfield("skype_name", _t("Skype name"), $tab_index++);
?>
<input type="checkbox" name="news_letter" value="1" id="news_letter">
	<label for "news_letter"><?php __t("I want to subscribe to the news letter"); ?></label>
<button type="submit" value="<?php __t("Send"); ?>"><?php __t("Send"); ?></button>
</form>

<script type="text/javascript" language="JavaScript">
window.setTimeout(function() { document.forms["login-form"]["first_name"].focus(); },0);
</script>

</div>
</div>

</body>
</html>