<?php
namespace I18n;

class templates 
{
	public static function create_templates() {
		return array(
		'NPN' => 'NPN'
		,'QNA' => 'QNA'
		,'ON' => 'ON'
		,'AN' => 'AN'
		,'QN' => 'QN'
		,'VR' => 'VR'
		,'AP' => 'AP'
		,'VP' => 'VP'
		,'NP' => 'NP'
		,'Npl' => 'Npl'
		,'V' => 'V'
		,'N' => 'N'		
		,'VN' => 'VN'
		,'VQ' => 'VQ'
		,'NA' => 'NA'
		,'NV' => 'NV'
		,'VV' => 'VV'
		,'DN' => 'DN'
		,'NC' => 'NC'
		,'W' => 'W'
		);
	}

	public static function expand_class($class_code) 
	{
		switch($class_code) {
			case 'A': return 'adj';
			case 'C': return '%d';
			case 'Q': return 'quant';
			case 'N': return 'noun';
			case 'V': return 'verb';
			case 'P': return 'prep';
			case 'R': return 'pron';
			case 'D': return 'definite';
			case 'O': return 'pron-poss';
			case 'W': return null;
			default: throw new \Exception("Unknown class_code: " . $class_code);
		}
	}

	public static function expand_modifiers($mod_str) 
	{
		switch($mod_str) {
			case 'pl': return array('numerus' => 'plural');
			case '': return array();
			default: throw new \Exception("Unknown class_code: " . $class_code);
		}
	}
}
?>
