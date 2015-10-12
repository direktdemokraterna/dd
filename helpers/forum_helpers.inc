<?php

class forum_helpers 
{
	public static function process_text ($text)
	{
		$processed_text = general_helpers::clean($text, ENT_QUOTES & ENT_COMPAT,'ISO-8859-1', true);
		$processed_text = forum_helpers::urls_to_links($processed_text);
		$processed_text = forum_helpers::closetags($processed_text);
		$processed_text = self::replace_format_tags_with_brackets($processed_text);
		return $processed_text;
	}

	public static function process_post_text ($posted_post_id, $text)
	{
		$processed_text = forum_helpers::process_text($text);
		$processed_text = str_replace("[/quote]\r\n\r\n", "[/quote]\r\n", $processed_text);
		$number_of_quotes_in_post = substr_count($processed_text, "[quote=");

		// Iterating through post text to find all quotes, check validity of quote and transforming into HTML
		for($i=0; $i<$number_of_quotes_in_post; $i++){
			$quote_start = strpos($processed_text, "[quote=");
			$text_starting_at_post_id = substr($processed_text, $quote_start+7);
			$end_pos_of_post_id = strpos($text_starting_at_post_id, "]");
			$post_id = substr($text_starting_at_post_id, 0, $end_pos_of_post_id);
			$quote_stop = strpos($processed_text, "[/quote]");

			$old_full_quote_text = substr($processed_text, $quote_start, $quote_stop-$quote_start+8); 

			$quote_text_with_end_bracket = substr($old_full_quote_text, 8 + strlen((string)$post_id));
			$quote_text = substr($quote_text_with_end_bracket, 0, -8);

			// Checking quote validity in db.
			$valid_quote = db_forum::check_quote_validity($post_id, $quote_text);
			if($valid_quote){
				$post_info = db_forum::get_post_info($post_id);
				$new_full_quote_text = "<div class=\"quote_in_post\"><a class=\"quote_in_post_link\" href=\"index.php?type=forum&action=show_posts&id=" . $post_id . "\">" . $post_info['full_name'] . " skrev:</a>\n" . $quote_text . "</div>";
				$processed_text = str_replace($old_full_quote_text, $new_full_quote_text, $processed_text);
			}
			else{
				$_SESSION['report_message'] = "Ett citat i ditt inlägg är inte korrekt.";
				db_helpers::insert_error_message($_SESSION['id'], $message , "red");
				$redirect = $_SERVER['REQUEST_URI'];
				header("Location: $redirect");
				exit();
			}
		}
		return $processed_text;
	}

	public static function output_page_links ($number_of_pages, $current_page, $link_without_page_number)
	{
		echo "<span class=\"float-right\">";
		if($current_page > 1){
			$previous_page = $current_page - 1;
			echo "<a href=\"" . $link_without_page_number . $previous_page . "\"><</a> ";
		}
		for($i=1; $i<($number_of_pages+1); $i++){
			echo "&nbsp;&nbsp;&nbsp;";
			if($i != $current_page)
				echo "<a href=\"" . $link_without_page_number . $i . "\">" . $i . "</a> ";
			else
				echo "<strong>" . $i . "</strong> ";
		}
		if($current_page < $number_of_pages){
			echo "&nbsp;&nbsp;&nbsp;";
			$next_page = $current_page + 1;
			echo "<a href=\"" . $link_without_page_number . $next_page . "\">></a> ";
		}
		echo "</span>";
	}

	public static function urls_to_links ($text)
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
	    	if (preg_match('{\.[0-9]{1,3}}', $tld) || isset($validTlds[$tld]))
		    {
	    	    // Prepend http:// if no protocol specified
	        	$completeUrl = $match[1][0] ? $url : "http://$url";

	        	// Print the hyperlink.
		        $return_value .= sprintf('<a href="%s" target="_blank">%s</a>', $completeUrl, "$domain$port$path");
	    	}
		    else
	    	{
	        	// Not a valid URL.
	        	$return_value .= $url;
		    }

	    	// Continue text parsing from after the URL.
	    	$position = $urlPosition + strlen($url);
		}

		// Print the remainder of the text.
		$return_value .= substr($text, $position);
		return $return_value;
	}

	// close opened html tags
	public static function closetags ($html) {
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
	// close opened html tags

	public static function de_process_text ($deprocessed_text)
	{
		$deprocessed_text = self::replace_format_tags_with_brackets($deprocessed_text);
		$deprocessed_text = strip_tags($deprocessed_text);
		return $deprocessed_text;
	}

	public static function de_process_post_text ($deprocessed_text)
	{
		$deprocessed_text = self::replace_format_tags_with_brackets($deprocessed_text);
		$deprocessed_text = preg_replace("~<div class=\"quote_in_post\"><a class=\"quote_in_post_link\" href=\"index.php\?type=forum&action=show_posts&id=([0-9]+)\">.+</a>\n~", "[quote=$1]", $deprocessed_text);
		$deprocessed_text = str_replace("</div>", "[/quote]", $deprocessed_text);
		$deprocessed_text = str_replace("[/quote]\r\n", "[/quote]\r\n\r\n", $deprocessed_text);
		$deprocessed_text = strip_tags($deprocessed_text);
		return $deprocessed_text;
	}

	public static function update_county_region_forum_access ($user_id, $county)
	{
		$county_forum_id = db_helpers::get_local_county_forum($county);
		$region = db_helpers::get_region_from_county($_POST['county']);
		$region_forum_id = db_helpers::get_local_region_forum($region);
		db_forum_admin::drop_local_forums_for_user($user_id);
		db_forum_admin::add_forum_access($user_id, $county_forum_id);
		db_forum_admin::add_forum_access($user_id, $region_forum_id);
	}

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
}