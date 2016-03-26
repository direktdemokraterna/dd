<?php
namespace Thesaurus; 

class pronouns
{
	public static function create_translations() {
		return array(
			//PRONOUN
			"all:pron" => array(
				"sv" => "alla"
				,"en" => "all"
				)
			,"i:pron" => array(
				"sv" => "jag"
				,"en" => "I"
				)
			,"[]it:pron[verb_state]" => array(
				"sv" => "det"
				,"en" => "it"
				)
			,"it:pron" => array(
				"sv" => "den"
				,"en" => "it"
				)
			,"own:pron" => array(
				"sv" => "egen"
				,"en" => "own"
				)
			,"me:pron" => array(
				"sv" => "mig"
				,"en" => "me"
				)
			,"something:pron" => array(
				"sv" => "något"
				,"en" => "something"
				)
			,"there:pron" => array(
				"sv" => "det"
				,"en" => "there"
				)
			,"they:pron" => array(
				"sv" => "de"
				,"en" => "they"
				)
			,"[all]those:pron" => array(
				"sv" => ""
				,"en" => "those"
				)
			,"those:pron" => array(
				"sv" => "de"
				,"en" => "those"
				)
			,"where:pron" => array(
				"sv" => "där"
				,"en" => "where"
				)
			,"which:pron" => array(
				"sv" => "vilka"
				,"en" => "which"
				)
			,"who:pron" => array(
				"sv" => "som"
				,"en" => "who"
				)
			,"[to]you:pron" => array(
				"sv" => "dig"
				,"en" => "you"
				)
			,"you:pron" => array(
				"sv" => "du"
				,"en" => "you"
				)

			//POSSESSIVE PRONOUN
			,"its:pron-poss" => array(
				"sv" => "dess"
				,"en" => "its"
				)
			,"[]this:pron-poss[verb|verb_state]" => array(
				"sv" => "det här"
				,"en" => "this"
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
