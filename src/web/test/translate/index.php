<?php
	include("../../init.inc");
	include("xml_parser.inc");
	include("testcase_helper.inc");
	include("testcase.inc");
	$testcases = array();
	$testcase = testcase_helper::empty_testcase();
	$testcase->from_text = isset($_POST['phrase']) ? $_POST['phrase'] : '';
	$testcase->to_text = isset($_POST['expected']) ? $_POST['expected'] : '';
	$testcase->hints = isset($_POST['hints']) ? $_POST['hints'] : '';
	if (isset($_POST['translate']))
		$testcase->test();
	else if (isset($_POST['remove'])) {
		$index = testcase_helper::extract_test_index($_POST['remove']);
		testcase_helper::remove_at_index($index);
		$testcases = testcase_helper::load();
	}
	else if (isset($_POST['test'])) {
		$index = testcase_helper::extract_test_index($_POST['test']);
		$testcases = testcase_helper::load();
		$testcase = $testcases[$index];
		$testcase->test();
	}
	else if (isset($_POST['save']))
		die('save');
	else if (isset($_POST['extract']))
		$testcases = testcase_helper::extract();
	else if (isset($_POST['run'])) {
		$testcases = testcase_helper::load();
		testcase_helper::run_tests($testcases);
		testcase_helper::save($testcases);
	}
	else if (isset($_GET['page']) || isset($_POST['showing_testcases']))
		$testcases = testcase_helper::load();
?><!DOCTYPE html>
<html>
<head>
	<link href="../../css/index.css" rel="stylesheet" type="text/css">
    <meta charset="UTF-8" />
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
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
			<input type="text" class="<?php echo $testcase->get_output_class(); ?>" name="actual" id="actual" tabindex="4" readonly value="<?php 
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
		testcase_helper::output($testcases, false, $page);
	}
?>
	</p></form>
	</div>
	<script type="text/javascript" language="JavaScript">
	window.setTimeout(function() { document.forms["translate-form"]["phrase"].focus(); },0);
	</script>
</body>
</html>