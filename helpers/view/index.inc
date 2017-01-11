<?php
namespace View;

class index
{
	public static function output_language_buttons() {
		echo '<a onClick="set_language(\'sv\')" class="lang-flag"><img title="Svenska" class="language-button" src="' 
			. BASE_URL . 'images/swe32.png"></a>';
		echo '<a onClick="set_language(\'en\')" class="lang-flag"><img title="English" src="' . BASE_URL 
			. 'images/eng32.png"></a>';
	}
}
?>