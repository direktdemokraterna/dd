<?php
namespace Thesaurus; 

class adjectives 
{
	public static function create_translations() {
		return array(
			//ADVERBS
			"temporarily:adverb" => array(
				"sv" => "tillf�lligt"
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
				"sv" => "p�g�ende"
				,"en" => "ongoing"
				)
			,"open:adj" => array(
				"sv" => "�ppen|_t:__na"
				,"en" => "open"
				)
			,"public:adj" => array(
				"sv" => "offentlig|t:a"
				,"en" => "public"
				)
			,"sufficient:adj" => array(
				"sv" => "tillr�cklig|t:a"
				,"en" => "sufficient"
				)
			,"time limited:adj" => array(
				"sv" => "tidsbegr�nsad|_t:e"
				,"en" => "time limited"
				)
		);
	}	
} 
?>