<?php 
	db_user::update_last_activity_time($_SESSION['id']);
	include("menubar.inc");
	preg_match('/[\?|&]lang=(\w+)$/', $_SERVER['REQUEST_URI'], $lang_param_match);
	if ($lang_param_match) {
		$param = $lang_param_match[0];
		$lang = $lang_param_match[1];
		\I18n\controller::update_language($lang);
		$redirect = str_replace($param, '', $_SERVER['REQUEST_URI']);
		header("Location: $redirect");
		exit();
	}
?>
<div id="wrap">
	<div class="header">
		<div id="header-logo">
			<a href="index.php"><img id="dd-logo" src="images/direktdemokraterna-logotyp.png"></a>
		</div>
		<div id="header-lang">
			<a href="javascript:set_language('en')">En</a>
			<a href="javascript:set_language('sv')">Sv</a>
		</div>
	</div>
	<div class="main">
		<?php 
			include("primary_content.inc");
			include("sidebar.inc"); 
		?>
	</div>
</div>
<script>
	function set_language(lang) {
		var qsign = window.location.href.indexOf('?') >= 0
			? '&'
			: '?';
		window.location.href=window.location.href + qsign + 'lang=' + lang;
	}
</script>
