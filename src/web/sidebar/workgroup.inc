<ul>
	<li>
		<?php 
			__h2("Arbetsgrupper");
			\View\controls::output_link_list("workgroup", array(
			"listall" => "Visa arbetsgrupper"
			,"listproposed" => "Visa föreslagna arbetsgrupper"
			,"create" => "Skapa arbetsgrupp"
			));
		?>
	</li>
	<li>
		<?php 
			\View\controls::output_search_box("arbetsgrupper", "workgroup", "search", 101);
		?>
	</li>
</ul>