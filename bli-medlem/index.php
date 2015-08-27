<?php 

include("../helpers/init.inc");

// Processing data if form has been posted
if(isset($_POST['first_name']) && isset($_POST['last_name']) && isset($_POST['street_address']) && isset($_POST['zip_code']) && isset($_POST['city_address']) && isset($_POST['county']) && isset($_POST['email']) && isset($_POST['social_security_number'])){

	$telephone = str_replace("-", "", $_POST['telephone']);
	$telephone = str_replace(" ", "", $_POST['telephone']);

	$personnummer = general_helpers::clean_personnummer($_POST['social_security_number']);
	
	if(db_user::check_if_personnummer_exists($personnummer)){
		die("Det finns redan en användare med det personnumret");
	}

	if(!general_helpers::check_personnummer($personnummer)){
		die("Ogiltigt personnummer");
	}

	if(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
		die("Ogiltig mejladress");
	}

	if(db_user::check_if_email_exists($_POST['email'])){
		die("Det finns redan en användare med den mejladressen");
	}

	$region = db_helpers::get_region_from_county($_POST['county']);

	if(!$region){
		die("Välj din kommun.");
	}

	$form_data_has_been_processed = db_user::enter_user_application(htmlspecialchars($_POST['first_name'], ENT_COMPAT,'ISO-8859-1', true), htmlspecialchars($_POST['last_name'], ENT_COMPAT,'ISO-8859-1', true), htmlspecialchars($_POST['street_address'], ENT_COMPAT,'ISO-8859-1', true), (int)$_POST['zip_code'], htmlspecialchars($_POST['city_address'], ENT_COMPAT,'ISO-8859-1', true), $_POST['county'], $region, $personnummer, $_POST['email'], general_helpers::clean($telephone));

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
	<h1>Tack för din anmälan.</h1>
	</p>
<?php else : ?>

<h1 style="font-size: 24px; font-family: Lato, sans-serif; font-weight: 700; margin-bottom: 30px; ">Medlemsanmälan</h1>
* obligatoriskt<br>
<form method="post" id="login-form" action="">
<p>
<label for "first_name">Förnamn*</label>
<input type="text" name="first_name" id="first_name" tabindex="1">

<label for "last_name">Efternamn*</label>
<input type="text" name="last_name" id="last_name" tabindex="2">

<label for "street_address">Adress*</label>
<input type="text" name="street_address" id="street_address" tabindex="3">

<label for "zip_code">Postnummer*</label>
<input type="text" name="zip_code" id="zip_code" tabindex="4">

<label for "city_address">Postort*</label>
<input type="text" name="city_address" id="city_address" tabindex="5">

<label for "county">Kommun*</label><br>
<select name="county" id="county" tabindex="6">
	<option value="">Välj din kommun</option>
	<?php 
		$counties = db_helpers::get_counties();
		foreach($counties as $row){
			echo "<option value=\"" . $row['kommun'] . "\">" . $row['kommun'] . "</option>";
		}
	?>
</select><br><br>

<label for "telephone">Telefon</label>
<input type="text" name="telephone" id="telephone" tabindex="7">

<label for "email">E-post*</label>
<input type="text" name="email" id="email" tabindex="8">

<label for "social_security_number">Personnummer*</label>
<input type="text" name="social_security_number" id="social_security_number" tabindex="9">

<input type="checkbox" name="news_letter" value="1" id="news_letter"><label for "news_letter">Jag vill prenumerera på nyhetsbrevet</label>

<input type="submit" value="Skicka">
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