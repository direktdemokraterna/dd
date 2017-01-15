<?php 
	$post_info = db_forum::get_full_post_info($_GET['id'], $_SESSION['id']);
	__h1(_t("Report post"));
	\View\forum::output_post($post_info, false);
?>
<form method="post" action="" id="report_post_form" class="text-editor">
	<fieldset>
		<legend class="report_post"><?php __t("Motivate why this post should be reported"); ?></legend>
		<input type="hidden" name="post_id" value="<?php echo $_GET['id']; ?>">
		<textarea name="report_post_argument" id="report_post_argument" rows="32" cols="30"></textarea><br>
        <div class="align-center">
		<button type="submit" id="report_post_submit" value="<?php __t('Report'); ?>"><?php __t('Report'); ?></button>
        </div>
	</fieldset>
</form>
