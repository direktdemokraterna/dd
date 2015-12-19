<?php
namespace View;

class index
{
	public static function output_language_buttons() {
		echo '<a onClick="set_language(\'en\')"><img title="English" src="images/eng32.png"></a>';
		echo '&nbsp;';
		echo '&nbsp;';
		echo '<a onClick="set_language(\'sv\')"><img title="Svenska" class="language-button" src="images/swe32.png"></a>';
	}
}
?>