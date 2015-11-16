<ul>
	<li>
		<?php 
			_h2("Workgroups");
			\View\general::output_link_list("workgroup", array(
			"listall" => ":See workgroups"
			,"listproposed" => ":See proposed workgroups"
			,"create" => ":Create new workgroup"
			));
		?>
	</li>
	<li>
		<?php 
			\View\general::output_search_box("workgroup", "workgroup", "search", 101);
		?>
	</li>
</ul>