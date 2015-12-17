<?php 

include("../helpers/init.inc");

// Processing data if form has been posted
if(isset($_POST['first_name']) && isset($_POST['last_name']) && isset($_POST['street_address']) && isset($_POST['zip_code']) && isset($_POST['city_address']) && isset($_POST['county']) && isset($_POST['email']) && isset($_POST['social_security_number'])){
	$telephone = str_replace(" ", "", str_replace("-", "", $_POST['telephone']));
	$personnummer = general_helpers::clean_personnummer($_POST['social_security_number']);
	$error = \Logic\user::validate_user($personnummer, $_POST['email']);
	if ($error)
		die($error);
	$region = db_constituency::get_region_from_county($_POST['county']);
	if(!$region){
		die(_t("Select your municipality."));
	}
	$form_data_has_been_processed = db_user::enter_user_application(general_helpers::clean($_POST['first_name']), general_helpers::clean($_POST['last_name']), general_helpers::clean($_POST['street_address']), (int)$_POST['zip_code'], general_helpers::clean($_POST['city_address']), $_POST['county'], $region, $personnummer, $_POST['email'], general_helpers::clean($telephone));
}

?>
<html><head>

<link href="../helpers/css/index.css" rel="stylesheet" type="text/css">
<link href="../helpers/css/login.css" rel="stylesheet" type="text/css">

<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<link rel="shortcut icon" href="images/favicon.ico">

<title>DD - Nya versionen</title>

</head>

<body>

<div id="wrap">

<div id="login-column">

<div id="login_image">
	<img src="../images/dd120.png">
</div>

<br>

<?php if(isset($form_data_has_been_processed)) : ?>
	<p>
	<h1><?php __("Thank you for your application."); ?></h1>
	</p>
<?php else : ?>

<h1 style="font-size: 24px; font-family: Lato, sans-serif; font-weight: 700; margin-bottom: 30px; "><?php __("Membership application"); ?>
</h1><?php __("* mandatory"); ?><br>
<form method="post" id="login-form" action="">
<p>
	<?php
		\View\general::make_textfield('first_name', _t("Given name"), 1);
		\View\general::make_textfield('last_name', _t("Last name*"), 2);
		\View\general::make_textfield('street_address', _t("Street address*"), 3);
		\View\general::make_textfield('zip_code', _t("Zip code*"), 4);
		\View\general::make_textfield('city_address', _t("City*"), 5);
		self::output_county_selectors();
		\View\general::make_textfield("telephone", _t("Telephone"), $tab_index++, $result);
		\View\general::make_textfield("email*", _t("Email"), $tab_index++, $result);
		\View\general::make_textfield("skype_name", _t("Skype name"), $tab_index++, $result);
	?>
<input type="checkbox" name="news_letter" value="1" id="news_letter">
	<label for "news_letter"><?php __("I want to subscribe to the news letter"); ?></label>
<input type="submit" value="<?php __("Send"); ?>">
</p>
</form>

<script type="text/javascript" language="JavaScript">
window.setTimeout(function() { document.forms["login-form"]["first_name"].focus(); },0);
</script>

<?php endif; ?>

</div>
</div>

</body>
</html>