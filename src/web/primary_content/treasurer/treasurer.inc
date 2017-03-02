<?php 
	__h1("Bokföring");
	$page = isset($_GET['page']) ? $_GET['page'] : 1;

	$account_entries = db_treasurer::get_all_account_entries($page);
	$account_entries_count = db_treasurer::get_all_account_entries_count();

	if(!empty($account_entries)){
		\View\controls::output_paging_row($page, $account_entries_count, null, LIST_ITEMS_PER_PAGE);
		echo "<table class=\"accounting-table\"><tr>";
		echo "<th>Datum</th>";
		$transaktionstyper = Array("medlemsavgift", "donation", "annan inkomst", "webbutgift", "finansutgift", "marknadsföringsutgift", "övriga utgifter");
		foreach ($transaktionstyper as $typ) {
			echo "<th>" . ucfirst($typ) . "</th>";
		}
		echo "</tr>";
		foreach ($account_entries as $account_entry) {
			echo "<tr>";
			echo "<td>" . date("d/m-Y", $account_entry['timestamp_accounting']) . "</td>";
			foreach ($transaktionstyper as $typ) {
				if($typ == $account_entry['type_of_transaction'])
					echo "<td>" . $account_entry['amount'] . "</td>";
				else
					echo "<td></td>";
			}
		}
		echo "</table>";

	}
