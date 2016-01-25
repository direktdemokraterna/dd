<?php
namespace I18n;

class template_match
{
	public $templates;
	public $translator_matches;
	private $matched_word_form_count;

	public static function start($translator_match) 
	{
		return new self(array($translator_match)
			, self::match_last_translator($translator_match->translator)
			, 1);
	}
	
	public function __construct($translator_matches, $templates, $matched_word_form_count) 
	{
		$this->templates = $templates;
		$this->translator_matches = $translator_matches;
		$this->matched_word_form_count = $matched_word_form_count;
	}

	public function translate($translation_hints = null) {
		$translated_words = $this->get_translated_parts($translation_hints);
		return implode('', $translated_words);
	}

	public function prepend($translator_match) {
		$matching_templates = array();
		$new_translator_matches = array_merge(array($translator_match), $this->translator_matches);
		foreach ($this->templates as $template) {
			$offset = count($template->from_sequence) - $this->matched_word_form_count;
			if ($offset >= 0 && $template->partially_matches($new_translator_matches, $offset))
				$matching_templates[] = $template;
		}
		return $matching_templates
			? new template_match($new_translator_matches, $matching_templates
				, $this->matched_word_form_count + 1)
			: null;
	}

	public function match_complete() {
		$matching_templates = array();
		foreach ($this->templates as $template) {
			if ($template->matches($this->translator_matches))
				$matching_templates[] = $template;
		}
		$this->templates = $matching_templates;
		$matched_word_form_count = 0;
	}

	private static function match_last_translator($translator) {
		$all_templates = template_storage::get_templates();
		$matched_templates = array();
		foreach ($all_templates as $template) {
			if ($template->matches_last_translator($translator))
				$matched_templates[] = $template;		
		}
		return $matched_templates;
	}

	private function get_translated_parts($translation_hints = null) 
	{
		$translators_after = array_map(function($match) {return $match->translator;}, $this->translator_matches);
		$translators_before = array();
		$localized_strings = array();
		foreach ($this->translator_matches as $match) {
			$translator = array_shift($translators_after);
			$localized_strings[] = $match->translate($translators_before, $translators_after, $translation_hints);
			$translators_before[] = $translator;
		}
		return $localized_strings;
	}	
}
?>
