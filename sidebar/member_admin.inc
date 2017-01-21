<ul>
	<li>
		<?php
			__h2("Alternativ");
			$links = array(
				"list" => "Visa alla medlemmar"
				,"create_new" => "Skapa ny medlem"
				);
			if (db_user::get_all_user_applications())
				$links['list_applications'] = "Behandla ansökningar";
			$links['create_workgroup'] = "Skapa arbetsgrupp";
			\View\controls::output_link_list("member_admin", $links);
		?>
	</li>
</ul>