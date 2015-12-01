<h1>Skapa ny proposition</h1>
<form method="post" action="" class="standard-form">
<?php
	\View\vote::make_vote_type_selector(isset($_POST["type_of_vote"]) ? $_POST["type_of_vote"] : null);
	\View\vote::make_constituency_selector(
		isset($_POST["constituency_id"]) ? $_POST["constituency_id"] : null
		, $_SESSION['id']); 
	\View\vote::make_title_input(); 
	\View\vote::make_description_input(); 
?>
<br><input type="submit" name="" id="submit" value="Skicka in" tabindex="5">
</form>
