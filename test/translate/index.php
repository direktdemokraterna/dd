<?php
	include("../../init.inc");
	include("xml_parser.inc");
	include("testcases.inc");
	$testcases = array();
	$testcase = testcases::empty_testcase();
	$testcase->from_text = isset($_POST['phrase']) ? $_POST['phrase'] : '';
	$testcase->to_text = isset($_POST['expected']) ? $_POST['expected'] : '';
	$testcase->hints = isset($_POST['hints']) ? $_POST['hints'] : '';
	if (isset($_POST['translate']))
		$testcase->test();
	else if (isset($_POST['remove'])) {
		$index = testcases::extract_test_index($_POST['remove']);
		testcases::remove_at_index($index);
		$testcases = testcases::load();
	}
	else if (isset($_POST['test'])) {
		$index = testcases::extract_test_index($_POST['test']);
		$testcases = testcases::load();
		$testcase = $testcases[$index];
		$testcase->test();
	}
	else if (isset($_POST['save']))
		die('save');
	else if (isset($_POST['extract']))
		$testcases = testcases::extract();
	else if (isset($_POST['run']))
		$testcases = testcases::load();
	else if (isset($_GET['page']) || isset($_POST['showing_testcases']))
		$testcases = testcases::load();
?>
<html>
<head>
	<link href="../../helpers/css/index.css" rel="stylesheet" type="text/css">
	<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
	<link rel="shortcut icon" href="images/favicon.ico">
	<title>DD Test - Translation</title>
	<style>
		label { display: block; width: 150px; }
		input[type="text"] { display: block; width: 500px; }
		.correct {color:green;}
		.incorrect {color:red;}
	</style>
</head>
<body>
	<div style="margin:20px;">
		<h1 style="font-size: 24px; font-family: Lato, sans-serif; font-weight: 700; margin-bottom: 30px; ">Test translation</h1><br>
		<form method="post" id="translate-form" action=""><p>
			<label for "phrase">Fras</label>
			<input type="text" name="phrase" id="phrase" tabindex="1" value="<?php 
				echo $testcase->from_text; ?>">
			<br>
			<label for "hints">Direktiv</label>
			<input type="text" name="hints" id="hints" tabindex="2" value="<?php 
				echo $testcase->hints; ?>">
			<br>
			<label for "expected">Förväntad översättning</label>
			<input type="text" name="expected" id="expected" tabindex="3" value="<?php 
				echo $testcase->to_text; ?>">
			<br>
			<label for "actual">Översättning</label>
			<input type="text" class="<?php echo $testcase->output_class(); ?>" name="actual" id="actual" tabindex="4" readonly value="<?php 
				echo $testcase->actual; ?>">
			<br>
			<input type="submit" name="translate" value="Översätt">
			<input type="submit" name="save" value="Spara testfall">
			<input type="submit" name="run" value="Kör testfall">
			<br>
			<input type="submit" name="extract" value="Extrahera från applikationen">
<?php
	if ($testcases) {
		$page = isset($_GET['page']) ? $_GET['page'] : 1;
		testcases::output($testcases, false, $page);
	}
?>
	</p></form>
	</div>
	<script type="text/javascript" language="JavaScript">
	window.setTimeout(function() { document.forms["translate-form"]["phrase"].focus(); },0);
	</script>
</body>
</html>