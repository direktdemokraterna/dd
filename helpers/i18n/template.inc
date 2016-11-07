<?php
namespace I18n;

class template
{
	public static $template_partial_counter = 0;
	public static $template_complete_counter = 0;

	public $priority;
	public $from_sequence;
	public $translation_indices;
	public $compact_form;

	public function __construct($priority, $from_pattern, $to_order) 
	{
		$this->priority = $priority;
		$this->from_sequence = self::expand_pattern($from_pattern);
		$this->translation_indices = self::expand_order($this->from_sequence, $to_order);
		$this->compact_form = $from_pattern;
	}

	public function __toString() {
        return $this->compact_form;
    }

    public function filter_translator_matches($translator_matches, $double_noun_indices
    	, &$translator_index) 
    {
    	$filtered_translator_matches = array();
    	foreach ($this->from_sequence as $word_form) {
    		if (in_array($translator_index, $double_noun_indices)){
	    		$translator_match = $translator_matches[$translator_index++];
	    		$filtered_match = self::filter_translator_match($translator_match
	    			, function($translator) {
	    				return $translator instanceof noun 
	    					&& $translator->is_potentially_first_of_double_noun();
	    			});
	    		if (!$filtered_match) return null;
				$filtered_translator_matches[] = $filtered_match;
    		}
    		$translator_match = $translator_matches[$translator_index++];
    		$filtered_match = self::filter_translator_match($translator_match
    			, function($translator) use ($word_form) {return $word_form->matches($translator);});
    		if (!$filtered_match) return null;
			$filtered_translator_matches[] = $filtered_match;
    	}
    	return $filtered_translator_matches;
    }

    public function filter_translator_match($translator_match, $predicate) 
    {
    	$filtered_translators = array();
    	foreach ($translator_match->translators as $translator)
			if ($predicate($translator))
    			$filtered_translators[] = $translator;
		return $filtered_translators
			? new translator_match($translator_match->phrase, $filtered_translators)
			: null;
    }

	public function get_translated_parts($translator_matches, $translation_hints = null
		, $double_noun_indices, &$translator_index, &$translators_before, &$translators_after) 
	{
		$translated_parts = $this->translate_parts($translator_matches, $translation_hints
			, $double_noun_indices, $translator_index, $translators_before, $translators_after);
		$ordered_translated_parts = (controller::get_language() == BASE_LANG)
			? $translated_parts
			: $this->order_translated_parts($translated_parts);
		return array_filter($ordered_translated_parts, function($word) {return $word;});
	}

	private static function expand_pattern($pattern) 
	{
		$word_parts = self::split_word_patterns($pattern);
		$word_forms = array_map('self::expand_word_form', $word_parts);
		return $word_forms;
	}

	private static function split_word_patterns($pattern) 
	{
		$word_parts = array();
		$word_part = '';
		foreach (str_split($pattern) as $char) {
			if (ctype_upper($char) && $word_part) {
				$word_parts[] = $word_part;
				$word_part = '';
			}
			$word_part .= $char;
		}
		$word_parts[] = $word_part;
		return $word_parts;
	}

	private static function expand_word_form($word_part) 
	{
		$class = templates::expand_class($word_part[0]);
		$modifiers = templates::expand_modifiers(mb_substr($word_part, 1));
		return new word_form($class, $modifiers, $word_part);
	}

	private static function expand_order($from_sequence, $order) 
	{
		$indices = array();
		if ($order) 
			self::extract_indices($indices, $order);
		else 
			self::generate_natural_order($indices, $from_sequence);
		return $indices;	
	}

	private static function extract_indices(&$indices, $order) 
	{
		foreach (str_split($order) as $index)
			$indices[] = (int)$index;
	}

	private static function generate_natural_order(&$indices, $from_sequence) 
	{
		for ($index = 0; $index < count($from_sequence); $index++)
			$indices[] = $index;
	}

	private function translate_parts($translator_matches, $translation_hints = null
		, $double_noun_indices, &$translator_index, &$translators_before, &$translators_after) 
	{
		$localized_strings = array();
		$word_index = 0;
    	$noun_prefix = null;
    	do {
    		$match = $translator_matches[$translator_index];
			$is_double_noun = in_array($translator_index++, $double_noun_indices);
			$translator = array_shift($translators_after);
			$hints = $is_double_noun
				? null
				: self::merge_hints($translation_hints, $word_index++);
			if ($is_double_noun)
				$noun_prefix = $match->make_noun_prefix();
			else {
				$localized_strings[] = $noun_prefix . $match->translate($translators_before, $translators_after, $hints);
				$noun_prefix = null;
			}
			$translators_before[] = $translator;
		}
		while ($word_index < count($this->from_sequence));
		return $localized_strings;
	}

	private function order_translated_parts($translated_parts) 
	{
		$ordered_translated_parts = array();
		foreach ($this->translation_indices as $from_index)
			$ordered_translated_parts[] = $translated_parts[$from_index];
		return $ordered_translated_parts;
	}

	private function merge_hints($translation_hints, $word_index) 
	{
		$word_form = $this->from_sequence[$word_index];
		return $word_form->merge_hints($translation_hints);
	}
}

class word_form_match 
{
	public $word_form;
	public $word;

	public function __construct($word_form, $word) 
	{
		$this->word_form = $word_form;
		$this->word = $word;
	}
}
