<?php
namespace I18n;

class templates 
{
	public static function create_templates() {
		return array(
		'VDNPQN' => ''
		,'RXprVQAN' => ''
		,'VQNPON' => ''
		,'ONVBQN' => ''
		,'DNVQN' => ''
		,'DNXVA' => ''
		,'QNPON' => ''
		,'DNVBA' => ''
		,'DNAPN' => ''
		,'QNPDN' => ''
		,'RBVprPN' => '12034'
		,'NRVDN' => ''
		,'NPOGN' => ''
		,'DNXBV' => ''
		,'ANPDN' => ''
		,'VimDN' => ''
		,'VIVVpp' => ''
		,'BPDN' => ''
		,'DNVA' => ''
		,'VQAN' => ''
		,'ANPN' => ''
		,'ONVA' => ''
		,'VPON' => ''
		,'VNPN' => ''
		,'RVprON' => ''
		,'NdeAPN' => ''
		,'DNXVps' => ''
		,'NPAN' => ''
		,'NPON' => ''
		,'NPDN' => ''
		,'ONXVps' => ''
		,'VAN' => ''
		,'APR' => ''
		,'VPApl' => ''
		,'VimON' => ''
		,'DNV' => ''
		,'OAN' => ''
		,'XVP' => ''
		,'QN' => ''
		,'QNA' => ''
		,'QNV' => ''
		,'VQN' => ''
		,'APN' => ''
		,'VPN' => ''
		,'NPN' => ''
		,'NAN' => ''
		,'NdeAP' => ''
		,'RVB' => ''
		,'VNP' => ''
		,'QAN' => ''
		,'JPN' => ''
		,'ON' => ''
		,'AN' => ''
		,'BN' => ''
		,'VR' => ''
		,'AP' => ''
		,'VP' => ''
		,'NP' => ''
		,'VimN' => ''
		,'Npl' => ''
		,'V' => ''
		,'N' => ''		
		,'VN' => ''
		,'PN' => ''
		,'VQ' => ''
		//,'NA' => ''
		,'NplA' => ''
		,'NdeA' => ''
		,'NBA' => ''
		,'NdeV' => ''
		,'NinS' => ''
		,'VA' => ''
		,'VV' => ''
		,'DN' => ''
		,'NC' => ''
		,'RVpr' => ''
		,'W' => ''
		);
	}

	public static function expand_class($class_code) 
	{
		switch($class_code) {
			case 'A': return 'adj';
			case 'B': return 'adverb';
			case 'C': return '%d';
			case 'D': return 'definite';
			case 'G': return 'noun-gen';
			case 'I': return 'indefinite';
			case 'J': return 'interjection';
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
			case 'ps': return array('tempus' => 'supinum', 'passive' => true);
			case 'pp': return array('tempus' => 'present_participle');
			case '': return array();
			default: throw new \Exception("Unknown class_code: " . $class_code);
		}
	}
}
?>
