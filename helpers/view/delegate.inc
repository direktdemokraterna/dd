<?php
namespace View;

class delegate 
{
	public static function output_delegate_list_header ($page, $result_counter, $sort_alternatives = null)
	{
		$show_other_constituencies_control = self::generate_show_other_constituencies_control();
		\general_helpers::make_list_header_with_region_county_filter($page, $result_counter, $sort_alternatives, $show_other_constituencies_control);
	}

	public static function output_delegate_list_rows($delegates) 
	{
		echo '<table class="message"><tr><td>' . _t("Title") . '</td><td>' . _t("Description") . '</td><td>' . _t("Delegands") . '</td></tr>';
		$i = 0;
		foreach($delegates as $delegate) {
			echo '<tr class="' . ($i++ % 2 ? "even_row" : "odd_row") . '">';
			echo '<td>';
			_link($delegate['title'], 'vote', 'view_delegate', 'id=' . $delegate['id']);
			echo '</td><td>' . _limit_with_ellipsis($delegate['description'], 30);
			echo '</td><td>' . $delegate['delegand_count'] . '</td>';
			echo '</tr>';			
		}
		echo '</table>';
	}

	// makes the top links for choosing page and sorting alternatives for a list_of_links
	private static function generate_show_other_constituencies_control (){
		$show_outside = isset($_GET['show_outside']) ? $_GET['show_outside'] : 0;
		$html = '<input type="checkbox" name="show_outside"' .
			($show_outside ? ' checked' : '') 
			. ' id="show_outside" onchange="this.form.submit()"><label for "show_outside">' 
			. _t("Show delegates outside your constituencies") . '</label>';
		return _span("list_sort_alternative", $html);
	}
}
?>
