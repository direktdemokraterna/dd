<?php
namespace Thesaurus; 

class pronouns
{
	public static function create_translations() {
		return array(
			//PRONOUN
			"i:pron" => array(
				"sv" => "jag"
				,"en" => "I"
				)
			,"something:pron" => array(
				"sv" => "något"
				,"en" => "something"
				)
			,"[to]you:pron" => array(
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
			,"this:pron-poss" => array(
				"sv" => "denna|___tta"
				,"en" => "this"
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
