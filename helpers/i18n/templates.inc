<?php
namespace I18n;

class templates 
{
	public static function create_templates() {
		return array(
		'PNDNIVV' => '0162345'
		,'VDNPQN' => ''
		,'RXprVQAN' => ''
		,'VQNPON' => ''
		,'ONVBQN' => ''
//		,'VANPON' => ''
		,'DNVQN' => ''
		,'NdeXprXpeVpes' => ''
		,'DNXprXpeVpes' => ''
		,'ONXprXpeVpes' => ''
		,'DNXBXVprs' => ''
		,'DNXptBVpts' => '01243'
//		,'DNXVA' => ''
		,'DNSBA' => ''
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
		,'OSQAN' => ''
		,'VimDN' => ''
		,'VIVVpp' => ''
		,'BPDN' => ''
//		,'DNVA' => ''
		,'DNSA' => ''
		,'VQAN' => ''
		,'ANPN' => ''
//		,'ONVA' => ''
		,'ONSA' => ''
		,'VPON' => ''
		,'VNPN' => ''
		,'RVBQN' => ''
		,'RVprON' => ''
		,'NdeAPN' => ''
		,'DNXVpts' => ''
		,'NPAN' => ''
		,'NPON' => ''
		,'NPDN' => ''
		,'QNSA' => ''
		,'XONV' => ''
		,'DAGN' => ''
		,'RXprBV' => ''
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
		,'DAN' => ''
		,'IVimVpp' => ''
		,'NdeAP' => ''
		,'RVB' => ''
		,'VNP' => ''
		,'QAN' => ''
		,'JPN' => ''
		,'DGN' => ''
		,'OGN' => ''
		,'RBVpr' => '021'
		,'SBA' => ''
		,'XBV' => ''
		,'RSprVprsP' => '023'
		,'XVifVprs' => '02'
		,'XXpeVpes' => '02'
//		,'NdeVA' => ''
		,'NdeSA' => ''
		,'ON' => ''
		,'AN' => ''
		,'BN' => ''
		,'VR' => ''
		,'AP' => ''
		,'IVifR' => ''
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
		,'RVN' => ''
		,'PN' => ''
		,'VQ' => ''
		,'NBA' => ''
		,'XXVprs' => ''
		,'NidVs' => ''
		,'XptVpts' => ''
		,'XpeVpes' => ''
		,'SA' => ''
		,'XprVpe' => ''
		,'VA' => ''
		,'VV' => ''
		,'DN' => ''
		,'OS' => ''
		,'NF' => ''
		,'RVpr' => ''
		,'RV' => ''
		,'XVif' => ''
		,'BA' => ''
		,'BV' => '10'
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
			case 'G': return 'noun_gen';
			case 'I': return 'indefinite';
			case 'J': return 'interjection';
			case 'N': return 'noun';
			case 'O': return 'pron-poss';
			case 'P': return 'prep';
			case 'Q': return 'quant';
			case 'R': return 'pron';
			case 'S': return 'verb_state';
			case 'V': return 'verb';
			case 'X': return 'verb_aux';
			case 'W': return null;
			default: throw new \Exception("Unknown class_code: " . $class_code);
		}
	}

	public static function expand_modifiers($mod_str) 
	{
		switch($mod_str) {
			case 'pl': return array('numerus' => 'plural');
			case 'im': return array('tempus' => 'imperative');
			case 'if': return array('tempus' => 'infinitive');
			case 'pr': return array('tempus' => 'present');
			case 'prs': return array('tempus' => 'present', 'passive' => true);
			case 'pt': return array('tempus' => 'preteritum');
			case 'pts': return array('tempus' => 'preteritum', 'passive' => true);
			case 'pe': return array('tempus' => 'perfect');
			case 'pes': return array('tempus' => 'perfect', 'passive' => true);
			case 'de': return array('definite' => true);
			case 'id': return array('definite' => false);
			case 'pp': return array('tempus' => 'present_participle');
			case 's': return array('passive' => true);
			case '': return array();
			default: throw new \Exception("Unknown class_code: " . $class_code);
		}
	}
}
?>
