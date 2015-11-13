<ul>
	<li>
		<h2><?php __("Workgroups"); ?></h2>
		<ul>
			<li><?php \View\general::output_internal_link("See workgroups", "workgroup", "listall"); ?></li>
			<li><?php \View\general::output_internal_link("See proposed workgroups", "workgroup", "listproposed"); ?></li>
			<li><?php \View\general::output_internal_link("Create new workgroup", "workgroup", "create"); ?></li>
		</ul>
	</li>
	<li>
		<h2><?php __("Search workgroup"); ?></h2>
		<form method="post" class="sidebar_search_form" action="index.php?type=workgroup&action=search">
			<input tabindex="101" type="text" value="" name="workgroup_search_input" class="sidebar_search_input">
			<input tabindex="102" type="submit" class="sidebar_search_submit" value="<?php __("Search"); ?>">
		</form>
	</li>
</ul>