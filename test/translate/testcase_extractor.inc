<?php

class testcase_extractor 
{
	public static function extract($base_dir) 
	{
		$cases = array();
		$files = scandir($base_dir);
		foreach ($files as $file) {
			if ($file && substr($file, 0, 1) != '.') {
				$abs_path = $base_dir . "/" . $file;
				if (is_dir($abs_path)) {
					$new_cases = self::extract($abs_path);
					$cases = array_merge($cases, $new_cases);
				}
				else if (in_array(substr($file, strlen($file) - 4), array(".php", ".inc"))){
					$new_cases = self::parse($abs_path);
					$cases = array_merge($cases, $new_cases);
				}
			}
		}
		return $cases;
	}

	public static function parse($file_path) 
	{
		$text = file_get_contents($file_path);
		$translation_pattern = '/_t\(["\']([^\'"]+)["\']\)/';
		$translation_pattern = '/_t\((?:"([^"]+)"|\'([^\']+)\')\)/';
		preg_match_all($translation_pattern, $text, $matches);
		$phrases = $matches[1];
		$cases = array();
		foreach ($phrases as $phrase) {
			$phrase = trim($phrase);
			if ($phrase && substr($phrase, 0, 1) != '$') {
				$case = new Testcase();
				$case->from_language = 'en';
				$case->to_language = 'sv';
				$case->from_text = $phrase;
				$case->to_text =_t("$phrase");
				$cases[] = $case;
			}			
		}
		return $cases;
	}
}
?>