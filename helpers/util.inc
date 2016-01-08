<?php
	function define_if_undefined($constant_name, $constant_value)
	{
		if (!defined($constant_name)) define($constant_name, $constant_value);
	}
?>
