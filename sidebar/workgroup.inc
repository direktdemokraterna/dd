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
		<?php _h2(":Search workgroup"); ?>
		<form method="post" class="sidebar_search_form" action="index.php?type=workgroup&action=search">
			<input tabindex="101" type="text" value="" name="workgroup_search_input" class="sidebar_search_input">
			<input tabindex="102" type="submit" class="sidebar_search_submit" value="<?php __("Search"); ?>">
		</form>
	</li>
</ul>