<?php 
	__h1(_t("Member search", array('class' => 'noun')));
	if(isset($_GET['page'])) $page = $_GET['page']; else $page = 1;
	$search_query = \Logic\util::update_search_query("member");	
	$result = db_user::search_users($search_query, $page);
	if(empty($result))
		__t("The search gave no hits");
	else {
		echo '<div class="list_of_links">';
		foreach($result as $row){
			__link($row['full_name'], 'member', 'view', 'id=' . $row['id']);
			__br();			
		}
		echo '</div>';
	}
?>

