<form method="post" action="" class="text-editor">
	<fieldset>
		<legend class="create_new_topic"><?php __("Create new workgroup"); ?></legend>
		<label for "title"><?php __("Name of workgroup"); ?></label>
		<input type="text" name="title" id="title">
		<br>
		<label for "description"><?php __("Description of the workgroup"); ?></label>
		<textarea name="description" id="description" cols="60" rows="10"></textarea>
		<br>
		<input type="submit" value="<?php __("Create"); ?>">
	</fieldset>
</form>
<?php
	_p(_t("Workgroups can be created by three members together. By filling the form above you create a proposal for a workgroup. When three members support this proposed workgroup it will be transformed to an active workgroup."));
?>
