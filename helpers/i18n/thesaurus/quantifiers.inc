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
			,"no[noun-singular]:quant" => array(
				"sv" => "ingen"
				,"en" => "no"
				)
			,"no[noun-plural]:quant" => array(
				"sv" => "inga"
				,"en" => "no"
				)
			,"other[noun-plural]:quant" => array(
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
