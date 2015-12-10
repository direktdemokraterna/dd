<?php
namespace Thesaurus; 

class pronouns
{
	public static function create_translations() {
		return array(
			//PRONOUN
			"[to]you:pron" => array(
				"sv" => "dig"
				,"en" => "you"
				)
			,"you:pron" => array(
				"sv" => "du"
				,"en" => "you"
				)

			//PRONOUN: it
			,"it:pron-it" => array(
				"sv" => "den|det"
				,"en" => "it"
				)

			//POSSESSIVE PRONOUN
			,"its:pron-poss" => array(
				"sv" => "dess"
				,"en" => "its"
				)
			,"whose:pron-poss" => array(
				"sv" => "vars"
				,"en" => "whose"
				)
			,"your:pron-poss" => array(
				"sv" => "din|_tt:a"
				,"en" => "your"
				)
		);
	}	
} 
?>
