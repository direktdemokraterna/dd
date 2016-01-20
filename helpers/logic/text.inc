<?php

namespace Logic;

class text 
{
	public static function make_plaintext_from_wiki_text($wiki_text) {
		try {
			return self::remove_bbcode_tags($wiki_text);
		}
		catch (\Exception $ex) {
			return "ERROR WHEN PARSING TEXT: " . $ex;
		}
	}

	public static function make_html_from_wiki_text($wiki_text) {
		try {
			$html_text = self::replace_brackets_with_html_tags($wiki_text);
			$html_text = nl2br($html_text);
		}
		catch (\Exception $ex) {
			return "ERROR WHEN PARSING TEXT: " . $ex;
		}
		return $html_text;
	}

	public static function process_text ($text)
	{
		$processed_text = \general_helpers::clean($text, ENT_QUOTES & ENT_COMPAT,'ISO-8859-1', true);
		$processed_text = self::urls_to_links($processed_text);
		$processed_text = self::closetags($processed_text);
		$processed_text = self::replace_format_tags_with_brackets($processed_text);
		return $processed_text;
	}

	private static function replace_brackets_with_html_tags($wiki_text)
	{
		$html_text = $wiki_text;
		foreach (self::$html_tags_by_bbc_tag as $bbc_tag => $html_tag)
			$html_text = str_replace($bbc_tag, $html_tag, $html_text);	
		$html_text = self::replace_links_with_a_tags($html_text);
		return $html_text;
	}
	
	private static $html_tags_by_bbc_tag = array(
		"[b]" => "<b>"
		,"[/b]" => "</b>"
		,"[i]" => "<i>"
		,"[/i]" => "</i>"
		,"[u]" => "<u>"
		,"[/u]" => "</u>"
		);

	private static function replace_format_tags_with_brackets($text)
	{
		$text = str_replace("<b>", "[b]", $text);
		$text = str_replace("</b>", "[/b]", $text);
		$text = str_replace("<i>", "[i]", $text);
		$text = str_replace("</i>", "[/i]", $text);
		$text = str_replace("<u>", "[u]", $text);
		$text = str_replace("</u>", "[/u]", $text);
		return $text;
	}

	private static function urls_to_links ($text)
	{
		$rexProtocol = '(https?://)?';
		$rexDomain   = '((?:[-a-zA-Z0-9]{1,63}\.)+[-a-zA-Z0-9]{2,63}|(?:[0-9]{1,3}\.){3}[0-9]{1,3})';
		$rexPort     = '(:[0-9]{1,5})?';
		$rexPath     = '(/[!$-/0-9:;=@_\':;!a-zA-Z\x7f-\xff]*?)?';
		$rexQuery    = '(\?[!$-/0-9:;=@_\':;!a-zA-Z\x7f-\xff]+?)?';
		$rexFragment = '(#[!$-/0-9:;=@_\':;!a-zA-Z\x7f-\xff]+?)?';

		$validTlds = array_fill_keys(explode(" ", ".aero .asia .biz .cat .com .coop .edu .gov .info .int .jobs .mil .mobi .museum .name .net .org .pro .tel .travel .ac .ad .ae .af .ag .ai .al .am .an .ao .aq .ar .as .at .au .aw .ax .az .ba .bb .bd .be .bf .bg .bh .bi .bj .bm .bn .bo .br .bs .bt .bv .bw .by .bz .ca .cc .cd .cf .cg .ch .ci .ck .cl .cm .cn .co .cr .cu .cv .cx .cy .cz .de .dj .dk .dm .do .dz .ec .ee .eg .er .es .et .eu .fi .fj .fk .fm .fo .fr .ga .gb .gd .ge .gf .gg .gh .gi .gl .gm .gn .gp .gq .gr .gs .gt .gu .gw .gy .hk .hm .hn .hr .ht .hu .id .ie .il .im .in .io .iq .ir .is .it .je .jm .jo .jp .ke .kg .kh .ki .km .kn .kp .kr .kw .ky .kz .la .lb .lc .li .lk .lr .ls .lt .lu .lv .ly .ma .mc .md .me .mg .mh .mk .ml .mm .mn .mo .mp .mq .mr .ms .mt .mu .mv .mw .mx .my .mz .na .nc .ne .nf .ng .ni .nl .no .np .nr .nu .nz .om .pa .pe .pf .pg .ph .pk .pl .pm .pn .pr .ps .pt .pw .py .qa .re .ro .rs .ru .rw .sa .sb .sc .sd .se .sg .sh .si .sj .sk .sl .sm .sn .so .sr .st .su .sv .sy .sz .tc .td .tf .tg .th .tj .tk .tl .tm .tn .to .tp .tr .tt .tv .tw .tz .ua .ug .uk .us .uy .uz .va .vc .ve .vg .vi .vn .vu .wf .ws .ye .yt .yu .za .zm .zw .xn--0zwm56d .xn--11b5bs3a9aj6g .xn--80akhbyknj4f .xn--9t4b11yi5a .xn--deba0ad .xn--g6w251d .xn--hgbk6aj7f53bba .xn--hlcj6aya9esc7a .xn--jxalpdlp .xn--kgbechtv .xn--zckzah .arpa"), true);

		$position = 0;
		$return_value = "";
		while (preg_match("{\\b$rexProtocol$rexDomain$rexPort$rexPath$rexQuery$rexFragment(?=[?.!,;:\"]?(\s|$))}", $text, $match, PREG_OFFSET_CAPTURE, $position))
		{
	    	list($url, $urlPosition) = $match[0];

	    	// Print the text leading up to the URL.
	    	$return_value = substr($text, $position, $urlPosition - $position);

		    $domain = $match[2][0];
	    	$port   = $match[3][0];
	    	$path   = $match[4][0];

		    // Check if the TLD is valid - or that $domain is an IP address.
	    	$tld = strtolower(strrchr($domain, '.'));
	    	$return_value .= preg_match('{\.[0-9]{1,3}}', $tld) || isset($validTlds[$tld])
	    		? "[link]" . "$domain$port$path" . "[/link]"
				: $url;
	    	// Continue text parsing from after the URL.
	    	$position = $urlPosition + strlen($url);
		}

		// Print the remainder of the text.
		$return_value .= substr($text, $position);
		return $return_value;
	}

	// close opened html tags
	private static function closetags ($html) {
		// put all opened tags into an array
		preg_match_all ( "#<([a-z]+)( .*)?(?!/)>#iU", $html, $result );
		$openedtags = $result[1];
		// put all closed tags into an array
		preg_match_all ( "#</([a-z]+)>#iU", $html, $result );
		$closedtags = $result[1];
		$len_opened = count ( $openedtags );
		// all tags are closed
		if(count($closedtags ) == $len_opened)
			return $html;
		$openedtags = array_reverse ( $openedtags );
		// close tags
		for( $i = 0; $i < $len_opened; $i++ ){
			if ( !in_array ( $openedtags[$i], $closedtags ) )
				$html .= "</" . $openedtags[$i] . ">";
			else
				unset ( $closedtags[array_search ( $openedtags[$i], $closedtags)] );
		}
		return $html;
	}

	private static function remove_bbcode_tags($wiki_text)
	{
		$plaintext = $wiki_text;
		foreach (array_keys(self::$html_tags_by_bbc_tag) as $bbc_tag)
			$plaintext = str_replace($bbc_tag, "", $plaintext);	
		$plaintext = self::remove_links($plaintext);
		return $plaintext;
	}

	private static function replace_links_with_a_tags($text) {
		return self::transform_links($text, function ($link_text) 
			{
				$completeUrl = \Logic\util::starts_With($link_text, "http") 
					? $link_text 
					: "http://$url";
				return "<a href=\"$completeUrl\" target=\"_blank\">$url</a>";
			});
	}

	private static function remove_links($text) {
		return self::transform_links($text, function ($link_text) {return "";});
	}

	private static function transform_links($text, $transform_function) {
		$pos = 0;
		$open_link = "[link]";
		$close_link = "[/link]";
		while (true) {
			$start_link_index = strpos($text, $open_link, $pos);
			if ($start_link_index === false) break;
			$end_link_index = strpos($text, $close_link, $pos);
			if ($end_link_index === false) break;
			$start_url_index = $start_link_index + strlen($open_link);
			$link_text = substr($text, $start_url_index, $end_link_index - $start_url_index);
			$bbcode_link = $open_link . $link_text . $close_link;
			$html_link = $transform_function($link_text);
			$text = str_replace($bbcode_link, $html_link, $text);
			$pos = $start_link_index + strlen($html_link);
		}
		return $text;
	}
}