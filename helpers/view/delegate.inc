<?php
namespace View;

class delegate 
{
	public static function output_delegate_list_header ()
	{
		$show_other_constituencies_control = self::generate_show_other_constituencies_control();
		\general_helpers::make_region_county_list_filter($show_other_constituencies_control);
	}

	public static function output_delegate_list($delegates, $page, $delegate_count) 
	{
		\View\controls::output_paging_row($page, $delegate_count);
		self::output_delegate_grid($delegates);
		\View\controls::output_paging_row($page, $delegate_count);
	}
	
	private static function output_delegate_grid($delegates) 
	{
		$columns = array("Rubrik", "Beskrivning", "Delegander");
		$rows = array_map(function($delegate) {
			return array(_link($delegate['title'], 'vote', 'view_delegate', 'id=' . $delegate['id'])
				, _limit_with_ellipsis(\Logic\text::make_plaintext_from_wiki_text($delegate['description']), 30)
				, $delegate['delegand_count']);
		}, $delegates);
		\View\controls::output_grid_view($columns, $rows);
	}

	// makes the top links for choosing page and sorting alternatives for a list_of_links
	private static function generate_show_other_constituencies_control (){
		$show_all = isset($_GET['show_all']) ? $_GET['show_all'] : 0;
		$html = '<input type="checkbox" name="show_all"' .
			($show_all ? ' checked' : '') 
			. ' id="show_all" onchange="this.form.submit()"><label for "show_all">' 
			. "Visa delegater från alla valkretsar" . '</label>';
		return _span($html, "list_sort_alternative");
	}
}
?>