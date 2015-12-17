<?php
namespace Thesaurus; 

class quantifiers
{
	public static function create_translations() {
		return array(
			"%d:quant" => array(
				"sv" => "%d"
				,"en" => "%d"
				)
			,"more:quant" => array(
				"sv" => "fler"
				,"en" => "more"
				)
			,"no:quant" => array(
				"sv" => "ingen|_t:__a"
				,"en" => "no"
				)
			,"one:quant" => array(
				"sv" => "en|_tt"
				,"en" => "one"
				)
			,"other:quant[noun-plural]" => array(
				"sv" => "andra"
				,"en" => "other"
				)
			,"three:quant" => array(
				"sv" => "tre"
				,"en" => "three"
				)
			,"several:quant" => array(
				"sv" => "flera"
				,"en" => "several"
				)
			,"a:quant" => array(
				"sv" => "en|_tt"
				,"en" => "a"
				)
			,"an:quant" => array(
				"sv" => "en|_tt"
				,"en" => "an"
				)
		);
	}	
} 
?>
