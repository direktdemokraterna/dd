<h1>Skapa ny proposition</h1>
<form method="post" action="" class="standard-form">
<?php
	\View\prop_helper::make_vote_type_selector();
	\View\prop_helper::make_constituency_selector(); 
	\View\prop_helper::make_title_input(); 
	\View\prop_helper::make_description_input(); 
?>
<br><input type="submit" name="" id="submit" value="Skicka in" tabindex="5">
</form>
