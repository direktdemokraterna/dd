<?php
namespace I18n;

class templates 
{
	public static function create_templates() {
		return array(
		'VimDN' => 'VimDN'
		,'BPDN' => 'BPDN'
		,'VAN' => 'VAN'
		,'APR' => 'APR'
		,'VPApl' => 'VPApl'
		,'VON' => 'VON'
		,'QNA' => 'QNA'
		,'QNV' => 'QNV'
		,'VQN' => 'VQN'
		,'VPN' => 'VPN'
		,'NPN' => 'NPN'
		,'NAP' => 'NAP'
		,'ON' => 'ON'
		,'AN' => 'AN'
		,'QN' => 'QN'
		,'VR' => 'VR'
		,'AP' => 'AP'
		,'VP' => 'VP'
		,'NP' => 'NP'
		,'VimN' => 'VimN'
		,'Npl' => 'Npl'
		,'V' => 'V'
		,'N' => 'N'		
		,'VN' => 'VN'
		,'PN' => 'PN'
		,'VQ' => 'VQ'
		,'NA' => 'NA'
		,'NBA' => 'NBA'
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
			case 'B': return 'adverb';
			case 'C': return '%d';
			case 'D': return 'definite';
			case 'N': return 'noun';
			case 'O': return 'pron-poss';
			case 'P': return 'prep';
			case 'Q': return 'quant';
			case 'R': return 'pron';
			case 'V': return 'verb';
			case 'W': return null;
			default: throw new \Exception("Unknown class_code: " . $class_code);
		}
	}

	public static function expand_modifiers($mod_str) 
	{
		switch($mod_str) {
			case 'pl': return array('numerus' => 'plural');
			case 'im': return array('tempus' => 'imperative');
			case '': return array();
			default: throw new \Exception("Unknown class_code: " . $class_code);
		}
	}
}
?>
