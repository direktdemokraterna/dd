<?php
namespace Thesaurus; 

class modifiers 
{
	public static function create_translations() {
		return array(
			// GENITIVE
			"'s:genitive" => array(
				"sv" => "s"
				,"en" => "'s"
				)
			,"':genitive" => array(
				"sv" => ""
				,"en" => "'"
				)

			// DEFINITE MARKERS
			,"once every:definite" => array(
				"sv" => "en gång i"
				,"en" => "once every"
				)
			,"that:definite[noun]" => array(
				"sv" => "den|_t"
				,"en" => "that"
				)
			,"the:definite[adj|quant]" => array(
				"sv" => "den|_t:_"
				,"en" => "the"
				)
			,"the:definite" => array(
				"sv" => ""
				,"en" => "the"
				)
			,"[verb|]this:definite[adj|noun|noun_gen]" => array(
				"sv" => "den|_t:_ här"
				,"en" => "this:__ese"
				)

			//INDEFINITE MODIFIERS
			,"[verb-imperative|]to:indefinite" => array(
				"sv" => "för att"
				,"en" => "to"
				)
			,"to:indefinite[verb|adverb]" => array(
				"sv" => "att"
				,"en" => "to"
				)
		);
	}	
} 
?>
