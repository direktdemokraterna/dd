<ul>
	<li>
		<?php 
			_h2(_t("Workgroups"));
			\View\controls::output_link_list("workgroup", array(
			"listall" => _t("See workgroups")
			,"listproposed" => _t("See proposed workgroups")
			,"create" => _t("Create new workgroup")
			));
		?>
	</li>
	<li>
		<?php 
			\View\controls::output_search_box("workgroup", "workgroup", "search", 101);
		?>
	</li>
</ul>