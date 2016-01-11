<?php
namespace View;

class delegate 
{
	public static function output_delegate_list_header ($page, $result_counter, $sort_alternatives = null)
	{
		$show_other_constituencies_control = self::generate_show_other_constituencies_control();
		\general_helpers::make_list_header_with_region_county_filter($page, $result_counter, $sort_alternatives, $show_other_constituencies_control);
	}

	public static function output_delegate_list($delegates) 
	{
		$columns = array(_t("Title"), _t("Description"), _t("Delegands"));
		$rows = array_map(function($delegate) {
			return array(\View\general::generate_internal_link($delegate['title'], 'vote', 'view_delegate', 'id=' . $delegate['id'])
				, _limit_with_ellipsis(\View\general::make_plaintext_from_wiki_text($delegate['description']), 30)
				, $delegate['delegand_count']);
		}, $delegates);
		\View\general::output_grid_view($columns, $rows);
	}

	// makes the top links for choosing page and sorting alternatives for a list_of_links
	private static function generate_show_other_constituencies_control (){
		$show_outside = isset($_GET['show_outside']) ? $_GET['show_outside'] : 0;
		$html = '<input type="checkbox" name="show_outside"' .
			($show_outside ? ' checked' : '') 
			. ' id="show_outside" onchange="this.form.submit()"><label for "show_outside">' 
			. _t("Show delegates outside your constituencies") . '</label>';
		return _span($html, "list_sort_alternative");
	}
}
?>
