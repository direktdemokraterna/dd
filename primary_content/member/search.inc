<?php 
	_h1(_t("Member search", array('class' => 'noun')));
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	$search_query = \Logic\util::update_search_query("member");	
	$result = db_user::search_users($search_query, $page);
	if(empty($result))
		__("The search gave no hits");
	else {
		echo '<div class="list_of_links">';
		foreach($result as $row){
			_link($row['full_name'], 'member', 'view', 'id=' . $row['id']);
			_br();			
		}
		echo '</div>';
	}
?>

