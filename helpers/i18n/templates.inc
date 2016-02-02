<?php
namespace I18n;

class templates 
{
	public static function create_templates() {
		return array(
		'VDNPQN' => 'VDNPQN'
		,'DNVQN' => 'DNVQN'
		,'DNXVA' => 'DNXVA'
		,'QNPON' => 'QNPON'
		,'DNVBA' => 'DNVBA'
		,'DNAPN' => 'DNAPN'
		,'VimDN' => 'VimDN'
		,'BPDN' => 'BPDN'
		,'DNVA' => 'DNVA'
		,'VQAN' => 'VQAN'
		,'ANPN' => 'ANPN'
		,'ONVA' => 'ONVA'
		,'VPON' => 'VPON'
		,'VNPN' => 'VNPN'
		,'RVprON' => 'RVprON'
		,'NdeAPN' => 'NdeAPN'
		,'VAN' => 'VAN'
		,'APR' => 'APR'
		,'VPApl' => 'VPApl'
		,'VimON' => 'VimON'
		,'DNV' => 'DNV'
		,'OAN' => 'OAN'
		,'XVP' => 'XVP'
		,'QN' => 'QN'
		,'QNA' => 'QNA'
		,'QNV' => 'QNV'
		,'VQN' => 'VQN'
		,'APN' => 'APN'
		,'VPN' => 'VPN'
		,'NPN' => 'NPN'
		,'NAN' => 'NAN'
		,'NdeAP' => 'NdeAP'
		,'RVB' => 'RVB'
		,'VNP' => 'VNP'
		,'ON' => 'ON'
		,'AN' => 'AN'
		,'BN' => 'BN'
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
		,'NdeA' => 'NdeA'
		,'NBA' => 'NBA'
		,'NdeV' => 'NdeV'
		,'NinS' => 'NinS'
		,'VA' => 'VA'
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
			case 'S': return 'verb-pass';
			case 'V': return 'verb';
			case 'X': return 'verb-aux';
			case 'W': return null;
			default: throw new \Exception("Unknown class_code: " . $class_code);
		}
	}

	public static function expand_modifiers($mod_str) 
	{
		switch($mod_str) {
			case 'pl': return array('numerus' => 'plural');
			case 'im': return array('tempus' => 'imperative');
			case 'pr': return array('tempus' => 'present');
			case 'in': return array('definite' => false);
			case 'de': return array('definite' => true);
			case '': return array();
			default: throw new \Exception("Unknown class_code: " . $class_code);
		}
	}
}
?>
