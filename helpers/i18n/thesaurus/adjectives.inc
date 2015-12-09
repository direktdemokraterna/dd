<?php
namespace Thesaurus; 

class adjectives 
{
	public static function create_translations() {
		return array(
			//ADVERBS
			"temporarily:adverb" => array(
				"sv" => "tillfälligt"
				,"en" => "temporarily"
				)

			//ADJECTIVES
			//singular_indefinite|non_type2:plural_indefinite:definite
			,"active:adj" => array(
				"sv" => "aktiv|t:a"
				,"en" => "active"
				)
			,"affirmed:adj" => array(
				"sv" => "beviljad|_t:e"
				,"en" => "affirmed"
				)
			,"auto-generated:adj" => array(
				"sv" => "automatgenererad|_t:e"
				,"en" => "auto-generated"
				)
			,"continous:adj" => array(
				"sv" => "kontinuerlig|t:a"
				,"en" => "continous"
				)
			,"current:adj" => array(
				"sv" => "aktuell|t:a"
				,"en" => "current"
				)
			,"finished:adj" => array(
				"sv" => "avslutad|_t:e"
				,"en" => "finished"
				)
			,"late:adj" => array(
				"sv" => "sen|t:a:aste"
				,"en" => "late::st"
				)
			,"my:adj" => array(
				"sv" => "min|_tt:a"
				,"en" => "my"
				)
			,"new:adj" => array(
				"sv" => "ny|tt:a"
				,"en" => "new"
				)
			,"old:adj" => array(
				"sv" => "gammal|t:___la"
				,"en" => "old"
				)
			,"ongoing:adj" => array(
				"sv" => "pågående"
				,"en" => "ongoing"
				)
			,"open:adj" => array(
				"sv" => "öppen|_t:__na"
				,"en" => "open"
				)
			,"public:adj" => array(
				"sv" => "offentlig|t:a"
				,"en" => "public"
				)
			,"restricted:adj" => array(
				"sv" => "stängd|_t:a"
				,"en" => "restricted"
				)
			,"submitted:adj" => array(
				"sv" => "inskickad|_t:e"
				,"en" => "submitted"
				)
			,"sufficient:adj" => array(
				"sv" => "tillräcklig|t:a"
				,"en" => "sufficient"
				)
			,"time limited:adj" => array(
				"sv" => "tidsbegränsad|_t:e"
				,"en" => "time limited"
				)
		);
	}	
} 
?>
