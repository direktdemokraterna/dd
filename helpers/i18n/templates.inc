<?php
namespace I18n;

class templates 
{
	public static function create_templates() {
		return array(
		'PNDNIVV' => '0162345'
		,'XRBXVif' => '3142'
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
		,'DNXVprsPN' => ''
		,'DNXptBVpts' => '01243'
		,'RXprVQN' => ''
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
		,'RSBAP' => ''
		,'NXBXVprs' => ''
		,'VimDN' => ''
		,'VIVVpp' => ''
		,'BPDN' => ''
		,'DNSA' => ''
		,'VQAN' => ''
		,'ANPN' => ''
		,'ONSA' => ''
		,'VPON' => ''
		,'VNPN' => ''
		,'RVBQN' => ''
		,'DNPQN' => ''
		,'RVprON' => ''
		,'NdeAPN' => ''
		,'DNXVpts' => ''
		,'NPAN' => ''
		,'NPON' => ''
		,'NPDN' => ''
		,'QNSA' => ''
		,'XONV' => ''
		,'DAGN' => ''
		,'BPQN' => ''
		,'RXBVif' => ''
		,'RXprBV' => ''
		,'ONXVpts' => ''
		,'ONVprA' => ''
		,'VAN' => ''
		,'APR' => ''
		,'VPApl' => ''
		,'VimON' => ''
		,'DNV' => ''
		,'OAN' => ''
		,'SAP' => ''
		,'XVP' => ''
		,'QNA' => ''
		,'QNPN' => ''
		,'PRVpr' => '021'
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
		,'SprBA' => ''
		,'XBVprs' => '021'
		,'XBV' => ''
		,'BXVif' => ''
		,'XXVif' => ''
		,'PRN' => ''
		,'RSprVprsP' => '023'
		,'XVifVprs' => '02'
		,'XXpeVpes' => '02'
//		,'NdeVA' => ''
		,'NdeSA' => ''
		,'PDN' => ''
		,'PON' => ''
		,'IBV' => ''
		,'ON' => ''
		,'AN' => ''
		,'BN' => ''
		,'VR' => ''
		,'AP' => ''
		,'IVifR' => ''
		,'NplP' => ''
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
		,'VprOAN' => ''
		,'RVN' => ''
		,'IVif' => ''
		,'PN' => ''
		,'VQ' => ''
		,'NBA' => ''
		,'CQN' => ''
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
		,'PR' => ''
		,'VC' => ''
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
