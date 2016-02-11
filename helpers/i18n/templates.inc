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
		,'VANPON' => ''
		,'DNVQN' => ''
		,'DNXprXpeVpes' => ''
		,'ONXprXpeVpes' => ''
		,'DNXBXVprs' => ''
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
		,'VNPON' => ''
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
		,'DNXVpts' => ''
		,'NPAN' => ''
		,'NPON' => ''
		,'NPDN' => ''
		,'ONXVpts' => ''
		,'VAN' => ''
		,'APR' => ''
		,'VPApl' => ''
		,'VimON' => ''
		,'DNV' => ''
		,'OAN' => ''
		,'XVP' => ''
		,'QNA' => ''
		,'QN' => ''
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
		,'Npl' => ''
		,'NplA' => ''
		,'NdeA' => ''
		,'VimN' => ''
		,'NVs' => ''
		,'NdeV' => ''
		,'VN' => ''
		,'PNCN' => ''
		,'PN' => ''
		,'VQ' => ''
		,'NBA' => ''
		,'NinVs' => ''
		,'XpeVpes' => ''
		,'VA' => ''
		,'VV' => ''
		,'DN' => ''
		,'NF' => ''
		,'RVpr' => ''
		,'RV' => ''
		,'V' => ''
		,'N' => ''		
		,'W' => ''
		);
	}

	public static function expand_class($class_code) 
	{
		switch($class_code) {
			case 'A': return 'adj';
			case 'B': return 'adverb';
			case 'C': return 'conj';
			case 'D': return 'definite';
			case 'F': return '%d';
			case 'G': return 'noun-gen';
			case 'I': return 'indefinite';
			case 'J': return 'interjection';
			case 'N': return 'noun';
			case 'O': return 'pron-poss';
			case 'P': return 'prep';
			case 'Q': return 'quant';
			case 'R': return 'pron';
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
			case 'prs': return array('tempus' => 'present', 'passive' => true);
			case 'pt': return array('tempus' => 'preteritum');
			case 'pts': return array('tempus' => 'preteritum', 'passive' => true);
			case 'pe': return array('tempus' => 'perfect');
			case 'pes': return array('tempus' => 'perfect', 'passive' => true);
			case 'in': return array('definite' => false);
			case 'de': return array('definite' => true);
			case 'pp': return array('tempus' => 'present_participle');
			case 's': return array('passive' => true);
			case '': return array();
			default: throw new \Exception("Unknown class_code: " . $class_code);
		}
	}
}
?>
