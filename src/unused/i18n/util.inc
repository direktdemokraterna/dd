<?php
namespace I18n;
class util
{
	public static function split_phrases($text) 
	{
		return preg_split('/\s*[.,;:!?&=()*]+\s*/', $text, -1, PREG_SPLIT_NO_EMPTY);
	}
	public static function split_words($phrase) 
	{
		return preg_split('/\s+/', $phrase, 0, PREG_SPLIT_NO_EMPTY);
	}
	public static function apply_translations($original, $phrases, $translations) 
	{
		$translation = $original;
		for ($i = 0; $i < count($phrases); $i++)
			$translation = str_replace($phrases[$i], $translations[$i], $translation);
		return $translation;
	}
	public static function extract_numbers(&$phrase)
	{
		preg_match_all('/\d+/', $phrase, $matches);
		$numbers = $matches[0];
		if ($numbers) 
			$phrase = preg_replace('/\d+/', '%d', $phrase);
		return $numbers;
	}		
	public static function restore_numbers($phrase, &$numbers) {
		while ($numbers) {
			$phrase = preg_replace('/%d/', $numbers[0], $phrase, 1, $replace_count);
			if ($replace_count == 0) break;
			array_shift($numbers);
		}
		return $phrase;
	}
    public static function preserve_case($target, $source)
    {
        return (self::starts_with_uppercase($source)
                ? mb_strtoupper(mb_substr($target, 0, 1))
                : mb_strtolower(mb_substr($target, 0, 1)))
            . mb_substr($target, 1);
    }
	public static function preserve_space($original, $translation) {
		preg_match('/^\s+/', $original, $leading_space_matches);
		preg_match('/\s+$/', $original, $trailing_space_mathes);
		$translation = ($leading_space_matches ? $leading_space_matches[0] : '') 
			. $translation 
			. ($trailing_space_mathes ? $trailing_space_mathes[0] : '');
		return $translation;
	}
	public static function split_word_forms($compact_representation) 
	{
		$parts = explode(':(', $compact_representation, 2);
		if (count($parts) == 1)
			return explode(':', $compact_representation);
		$retval = explode(':', $parts[0]);
		$parts = explode(')', $parts[1], 2);
		$retval[] = $parts[0];
		return count($parts) == 1
			? $retval
			: array_merge($retval, self::split_word_forms(mb_substr($parts[1], 1)));
	}

    private static function starts_with_uppercase($str) {
        $first_character = mb_substr($str, 0, 1);
        return mb_strtolower($first_character) !== $first_character;
    }
}
?>