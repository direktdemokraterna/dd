<?php
namespace I18n;

class util
{
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
			: array_merge($retval, self::split_word_forms(substr($parts[1], 1)));
	}
}
?>
