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
			,"that[noun]:definite" => array(
				"sv" => "den|_t"
				,"en" => "that"
				)
			,"the:definite" => array(
				"sv" => ""
				,"en" => "the"
				)
			,"the[adj|quant]:definite" => array(
				"sv" => "den|_t:_"
				,"en" => "the"
				)
			,"[]this:definite" => array(
				"sv" => "den|_t:_ här"
				,"en" => "this:__ese"
				)

			//INDEFINITE MODIFIERS
			,"[]to:indefinite" => array(
				"sv" => "för att"
				,"en" => "to"
				)
			,"to[verb|adverb]:indefinite" => array(
				"sv" => "att"
				,"en" => "to"
				)
		);
	}	
} 
?>
