<?php
namespace I18n;

class template_match
{
	public $template;
	public $templates;
	public $translator_matches;
	private $mapped_word_forms;
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
		$new_translator_matches = array_merge(array($translator_match), $this->translator_matches);
		if (template::is_compound_noun($translator_match->translator, $this->translator_matches))
			return new template_match($new_translator_matches, $this->templates
				, $this->matched_word_form_count);
		$new_matched_word_form_count = $this->matched_word_form_count + 1;
		$matching_templates = array();
		foreach ($this->templates as $template) {
			$offset = count($template->from_sequence) - $new_matched_word_form_count;
			if ($offset >= 0 && $template->partially_matches($new_translator_matches, $offset))
				$matching_templates[] = $template;
		}
		return $matching_templates
			? new template_match($new_translator_matches, $matching_templates
				, $new_matched_word_form_count)
			: null;
	}

	public function match_complete() {
		foreach ($this->templates as $template) {
			$mapped_word_forms = $template->map_to_word_forms($this->translator_matches);
			if ($mapped_word_forms) {
				$this->template = $template;
				$this->mapped_word_forms = $mapped_word_forms;
				$matched_word_form_count = 0;
				return;				
			}
		}
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
		$index = 0;
		foreach ($this->translator_matches as $match) {
			$translator = array_shift($translators_after);
			$word_form = $this->mapped_word_forms[$index++];
			$hints = $word_form 
				? $word_form->merge_hints($translation_hints)
				: $translation_hints;
			$localized_strings[] = $match->translate($translators_before, $translators_after, $hints);
			$translators_before[] = $translator;
		}
		return $localized_strings;
	}
}
?>
